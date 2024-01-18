import random

collidables = []

n = 2 ** 4

print(n)

shapes = ['c', 's']

def rand_dec(low = 0, high = 1) -> str:
    return str(round(random.uniform(low, high), 3)).ljust(5, '0')

for i in range(n):
    mass = str(int(random.random() * 100)).rjust(3)
    cor = rand_dec()
    shape = random.sample(shapes, 1)[0]

    position = f'{rand_dec()} {rand_dec()} {rand_dec()}'
    velocity = f'{rand_dec()} {rand_dec()} {rand_dec()}'

    collidable = f'{shape} {position} {velocity} {mass} {cor}'

    l = rand_dec(0.01, 0.05)
    w = rand_dec(0.01, 0.05)
    h = rand_dec(0.01, 0.05)

    if shape == 'c':
        collidable += f' {l}'
    else:
        collidable += f' {l} {w} {h}'

    collidables.append(collidable)


with open('resources/collidables.txt', 'w') as f:
    f.write('\n'.join(collidables))