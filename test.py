import random

collidables = []

for i in range(64):
    collidables.append(f's {str(round(random.random(), 3)).ljust(5, "0")} {str(round(random.random(), 3)).ljust(5, "0")} {str(round(random.random(), 3)).ljust(5, "0")} 0.01')

with open('resources/collidables.txt', 'w') as f:
    f.write('\n'.join(collidables))