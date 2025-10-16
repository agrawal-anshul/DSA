# async_simple.py
import asyncio
import time

# --- tweak these to see behavior change ---
MAX_CONCURRENCY = 2      # at most 2 tasks run at once
REQUEST_TIMEOUT = 1.0    # each job must finish within 1.0s
DELAYS = [0.3, 0.8, 1.2, 0.4, 0.5, 2, 0.6]  # pretend "work" times (seconds)
# -----------------------------------------

async def fake_io(item_id: int, delay: float) -> str:
    """Simulate an I/O call by sleeping 'delay' seconds."""
    await asyncio.sleep(delay)           # non-blocking sleep
    return f"item {item_id} OK in {delay:.2f}s"

async def run_job(item_id: int, delay: float, sem: asyncio.Semaphore) -> str:
    """
    One job:
      - Limit concurrency with a semaphore
      - Apply a simple per-job timeout
    """
    async with sem:  # ensures at most MAX_CONCURRENCY jobs run at once
        try:
            # If fake_io takes longer than REQUEST_TIMEOUT, we time out
            result = await asyncio.wait_for(fake_io(item_id, delay), timeout=REQUEST_TIMEOUT)
            return f"[#{item_id}] success: {result}"
        except asyncio.TimeoutError:
            return f"[#{item_id}] timeout after {REQUEST_TIMEOUT:.2f}s (delay was {delay:.2f}s)"

async def main():
    t0 = time.perf_counter()
    sem = asyncio.Semaphore(MAX_CONCURRENCY)

    # Create all tasks together (they'll be throttled by the semaphore)
    tasks = [asyncio.create_task(run_job(i, d, sem)) for i, d in enumerate(DELAYS, start=1)]

    # Wait for all to finish
    results = await asyncio.gather(*tasks)

    # Pretty print
    print("\n--- RESULTS ---")
    for line in results:
        print(line)

    print(f"\nElapsed: {time.perf_counter() - t0:.2f}s "
          f"(max concurrency = {MAX_CONCURRENCY}, timeout = {REQUEST_TIMEOUT:.2f}s)")

if __name__ == "__main__":
    asyncio.run(main())
