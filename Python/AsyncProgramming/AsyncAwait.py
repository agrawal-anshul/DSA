import asyncio, time, random

# 1. coroutines: async def + await
async def do_work(name, delay):
   await asyncio.sleep(delay)        # non-blocking sleep (simulates I/O)
   return f"{name} done after {delay}s"

async def main1():
   t0 = time.perf_counter()
   # run sequentially (await one by one)
   a = await do_work("A", 1)
   b = await do_work("B", 1)
   print(a, b, f"(took {time.perf_counter()-t0:.2f}s)", sep="\n")

# 2. concurrency: asyncio.gather
async def main2():
   t0 = time.perf_counter()
   a, b = await asyncio.gather(
      do_work("A", 1),
      do_work("B", 1),
   )
   print(a, b, f"(took {time.perf_counter()-t0:.2f}s)", sep = "\n")

# 3. fire-and-forget-ish: create_task
async def tick():
   for i in range(3):
      print("tick", i)
      await asyncio.sleep(0.5)

async def main3():
   task = asyncio.create_task(tick())     # scheduled but not awaited yet
   await asyncio.sleep(0.8)
   print("doing something else…")
   await task                              # now ensure it finished

# 4.timeouts & cancellation 
async def sometimes_slow():
   await asyncio.sleep(random.uniform(0.1, 2.0))
   return "ok"

async def main4():
   try:
      res = await asyncio.wait_for(sometimes_slow(), timeout=0.5)
      print(res)
   except asyncio.TimeoutError:
      print("timed out!")

# Cancelling a task:
async def main5():
   t = asyncio.create_task(asyncio.sleep(10))
   await asyncio.sleep(0.2)
   t.cancel()
   try:
      await t
   except asyncio.CancelledError:
      print("cancelled")

# 5. limit concurrency: Semaphore (rate-limit / batching)

sem = asyncio.Semaphore(5)   # at most 5 concurrent jobs
async def job(i):
    async with sem:
        await asyncio.sleep(random.uniform(0.2, 1.0)) # random.uniform(a, b) from Python's random module returns a random floating-point number N such that a<= N<=b.
        return i

async def main6():
   
   results = await asyncio.gather(*(job(i) for i in range(20))) 
   print(results)



if __name__ == "__main__":
   asyncio.run(main1())
   # asyncio.run(main2())
   # asyncio.run(main3())
   # asyncio.run(main4())
   # asyncio.run(main5())
   # asyncio.run(main6())
