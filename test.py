import random

collidables = []

n = 2 ** 4

print(n)

for i in range(n):
    collidables.append(f'c {str(round(random.random(), 3)).ljust(5, "0")} {str(round(random.random(), 3)).ljust(5, "0")} {str(round(random.random(), 3)).ljust(5, "0")} 0.01 0.01 0.01')

with open('resources/collidables.txt', 'w') as f:
    f.write('\n'.join(collidables))