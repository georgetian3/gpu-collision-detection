import random

collidables = []

n = 2 ** 12

print(n)

shapes = ['c', 's']

def rand_dec(low = 0, high = 1) -> str:
    return str(round(random.uniform(low, high), 3)).ljust(5, '0')

for i in range(n):
    mass = str(int(random.random() * 100)).rjust(3)
    cor = rand_dec(0.8, 1)
    shape = random.sample(shapes, 1)[0]

    position = f'{rand_dec(0.05, 0.95)} {rand_dec(0.05, 0.95)} {rand_dec(0.05, 0.95)}'
    velocity = f'{rand_dec(-1, 1)} {rand_dec(-1, 1)} {rand_dec(-1, 1)}'
    # velocity = f'0 0 0'

    collidable = f'{shape} {position} {velocity} {mass} {cor}'

    l = rand_dec(0.01, 0.01)
    w = rand_dec(0.001, 0.01)
    h = rand_dec(0.001, 0.01)

    if shape == 's':
        collidable += f' {l}'
    else:
        collidable += f' {l} {w} {h}'

    collidables.append(collidable)


with open('resources/collidables.txt', 'w') as f:
    f.write('\n'.join(collidables))