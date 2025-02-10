#!pip install python-kasa

from kasa import SmartPlug

import asyncio

async def power_off(plug):
    await plug.turn_off()

async def power_on(plug):
    await plug.turn_on()

async def power_cycle(plug):
    await power_off(plug)
    await asyncio.sleep(DELAY_BETWEEN_CYCLES)
    await power_on(plug)
    await asyncio.sleep(DELAY_BETWEEN_CYCLES)

async def main():
    plug = SmartPlug("192.168.1.100")  
    await plug.update()

    for i in range(1, POWER_CYCLES + 1):
        print(f"Performing power cycle {i} of {POWER_CYCLES}...")
        await power_cycle(plug)
        print(f"Power cycle {i} completed.")

    print("All power cycles completed.")

if __name__ == "__main__":
    asyncio.run(main())