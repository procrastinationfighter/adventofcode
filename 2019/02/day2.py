f = open('input', 'r')

data = [int(x) for x in f.read().split(',')]

ADD_OPCODE = 1
MULTIPLY_OPCODE = 2
HALT_OPCODE = 99


def part1(noun, verb):
    code = data.copy()
    code[1] = noun
    code[2] = verb

    for i in range(len(code) // 4):
        first, second, result_index = code[code[4 * i + 1]], code[code[4 * i + 2]], code[4 * i + 3]
        if code[4 * i] == ADD_OPCODE:
            code[result_index] = first + second
        elif code[4 * i] == MULTIPLY_OPCODE:
            code[result_index] = first * second
        else:
            break

    return code[0]


def part2():
    for noun in range(100):
        for verb in range(100):
            if part1(noun, verb) == 19690720:
                return 100 * noun + verb


print(part1(12, 2))
print(part2())