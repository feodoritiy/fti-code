import asyncio

async def main():
   task_t1 = asyncio.create_task(ticker1()) 
   task_t2 = asyncio.create_task(ticker2())
   
   await task_t1
   await task_t2


async def ticker1():
   for i in range(10):
      await asyncio.sleep(1)
      print(f'1: {i}s')

async def ticker2():
   for i in range(5):
      await asyncio.sleep(2)
      print(f'                  2: {i}s')

   
asyncio.run(main())