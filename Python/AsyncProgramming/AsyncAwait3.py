import asyncio
import time

# --------- Config you can tweak ----------
MAX_CONCURRENCY = 3          # at most 3 tasks run at once
REQUEST_TIMEOUT = 1.0         # per-attempt timeout (seconds)
MAX_RETRIES = 2               # total attempts = 1 + MAX_RETRIES

# We'll simulate "HTTP calls" with these delays (seconds).
# Some are > REQUEST_TIMEOUT, so they will time out and trigger retries.
SIMULATED_DELAYS = [0.2, 0.8, 1.5, 0.4, 0.6, 2.0, 0.3, 1.2]
# ----------------------------------------


async def fake_http_call(item_id: int, delay: float) -> str:
    """
    Simulates an I/O call (e.g., HTTP). Replace with a real client.get(...)
    if you like. Here we just sleep for 'delay' seconds and return text.
    """
    await asyncio.sleep(delay)  # non-blocking wait
    return f"item {item_id}: OK in {delay:.2f}s"


async def fetch_with_retry(item_id: int, delay: float, sem: asyncio.Semaphore) -> dict:
    """
    One "unit of work":
      - Enforced by a semaphore (bounded concurrency)
      - Each attempt has a timeout
      - Retries on timeout (up to MAX_RETRIES)
      - Returns a structured result dict
    """
    attempt = 0
    while True:
        attempt += 1
        async with sem:  # <= this enforces MAX_CONCURRENCY
            try:
                # The actual I/O, but wrapped with a per-attempt timeout:
                result = await asyncio.wait_for(
                    fake_http_call(item_id, delay),
                    timeout=REQUEST_TIMEOUT
                )
                return {"id": item_id, "status": "success", "attempt": attempt, "detail": result}

            except asyncio.TimeoutError:
                if attempt <= MAX_RETRIES:
                    # Backoff a bit (non-blocking) before retrying
                    await asyncio.sleep(0.05 * attempt)
                else:
                    return {
                        "id": item_id,
                        "status": "timeout",
                        "attempt": attempt,
                        "detail": f"timed out after {attempt} attempt(s)"
                    }


async def heartbeat():
    """
    A tiny background task to show that the loop is alive while work runs.
    """
    i = 0
    try:
        while True:
            await asyncio.sleep(0.3)
            print(f"[heartbeat] tick {i}")
            i += 1
    except asyncio.CancelledError:
        # graceful shutdown
        print("[heartbeat] stopping…")
        raise


async def main():
    t0 = time.perf_counter()
    sem = asyncio.Semaphore(MAX_CONCURRENCY)

    # Start background heartbeat "fire-and-forget" (but we'll await it later to clean up)
    hb_task = asyncio.create_task(heartbeat())

    # Schedule all fetches concurrently (bounded by the semaphore inside)
    tasks = [
        asyncio.create_task(fetch_with_retry(i, d, sem))
        for i, d in enumerate(SIMULATED_DELAYS, start=1)
    ]

    # Gather results; return_exceptions=False so real exceptions propagate
    results = await asyncio.gather(*tasks)

    # Stop heartbeat cleanly
    hb_task.cancel()
    try:
        await hb_task
    except asyncio.CancelledError:
        pass

    dt = time.perf_counter() - t0

    # ---------- Pretty print a small report ----------
    ok = sum(1 for r in results if r["status"] == "success")
    ko = len(results) - ok

    print("\n=== RESULTS ===")
    for r in results:
        print(f"- #{r['id']:02d}: {r['status']:7} (attempt {r['attempt']}), {r['detail']}")

    print(f"\nTotal: {len(results)} | Success: {ok} | Timeouts: {ko}")
    print(f"Elapsed: {dt:.2f}s with max concurrency = {MAX_CONCURRENCY}")
    # ------------------------------------------------


if __name__ == "__main__":
    asyncio.run(main())