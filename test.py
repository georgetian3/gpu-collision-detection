import random

for i in range(100):
    print(f's {str(round(random.random(), 3)).ljust(5, "0")} {str(round(random.random(), 3)).ljust(5, "0")} {str(round(random.random(), 3)).ljust(5, "0")} 0.01')