import time
import random

def memory_test():
    memory_size = 1024 * 1024 * 1024  # 1 GB
    memory_block = bytearray(memory_size)

    end_time = time.time() + 24 * 60 * 60

    while time.time() < end_time:
        pattern = random.randint(0, 255)
        for i in range(memory_size):
            memory_block[i] = pattern

        for i in range(memory_size):
            if memory_block[i] != pattern:
                print(f"Memory error at address {i}: expected {pattern}, got {memory_block[i]}")
                return

        time.sleep(1)  

if __name__ == "__main__":
    memory_test()