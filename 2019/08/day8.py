WIDTH = 25
HEIGHT = 6
LAYER_SIZE = WIDTH * HEIGHT

with open("input", "r") as f:
    line = f.readline().rstrip('\n')
    layers = [line[i:i + LAYER_SIZE] for i in range(0, len(line), LAYER_SIZE)]


def part1() -> int:
    min_zeroes = LAYER_SIZE + 1
    chosen = layers[0]

    for layer in layers:
        zeroes = layer.count('0')
        if zeroes < min_zeroes:
            min_zeroes = zeroes
            chosen = layer

    return chosen.count('1') * chosen.count('2')


BLACK = '0'
WHITE = '1'
TRANSPARENT = '2'


def part2() -> None:
    image = [TRANSPARENT for _ in range(LAYER_SIZE)]

    for layer in layers:
        for i in range(LAYER_SIZE):
            if image[i] == TRANSPARENT:
                image[i] = layer[i]

    for i in range(HEIGHT):
        for j in range(WIDTH):
            print(image[i * WIDTH + j].replace("0", " "), end='')
        print()


print(part1())
part2()
