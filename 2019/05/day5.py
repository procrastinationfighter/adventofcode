with open("input", "r") as f:
    code = [int(x) for x in f.readline().split(',')]
    input_numbers = [int(x) for x in f.read().split('\n')]
    input_counter = 0


ADD = 1
MULTIPLY = 2
INPUT = 3
OUTPUT = 4
JUMP_IF_TRUE = 5
JUMP_IF_FALSE = 6
LESS_THAN = 7
EQUALS = 8
HALT = 99

INSTRUCTIONS_COUNT = {
    ADD: 4,
    MULTIPLY: 4,
    INPUT: 2,
    OUTPUT: 2,
    JUMP_IF_TRUE: 3,
    JUMP_IF_FALSE: 3,
    LESS_THAN: 4,
    EQUALS: 4,
    HALT: 1
}


def get_next_input() -> int:
    global input_counter
    input_counter += 1
    return input_numbers[input_counter - 1]


def is_input_available() -> bool:
    return input_counter < len(input_numbers)


def run_machine():
    i = 0
    while code[i] != HALT:
        opcode = code[i] % 100
        first_mode = (code[i] // 100) % 10
        second_mode = (code[i] // 1000) % 10

        # Will throw an error if something goes wrong
        first_arg, second_arg, third_arg = -1, -1, -1

        instr_count = INSTRUCTIONS_COUNT[opcode]

        if opcode == ADD or opcode == MULTIPLY or opcode == LESS_THAN or opcode == EQUALS:
            first_arg = code[code[i + 1]] if first_mode == 0 else code[i + 1]
            second_arg = code[code[i + 2]] if second_mode == 0 else code[i + 2]
            third_arg = code[i + 3]
        elif opcode == JUMP_IF_TRUE or opcode == JUMP_IF_FALSE:
            first_arg = code[code[i + 1]] if first_mode == 0 else code[i + 1]
            second_arg = code[code[i + 2]] if second_mode == 0 else code[i + 2]
        elif opcode == INPUT:
            first_arg = code[i + 1]
        elif opcode == OUTPUT:
            first_arg = code[code[i + 1]] if first_mode == 0 else code[i + 1]

        if opcode == ADD:
            code[third_arg] = first_arg + second_arg
        elif opcode == MULTIPLY:
            code[third_arg] = first_arg * second_arg
        elif opcode == INPUT:
            code[first_arg] = get_next_input()
        elif opcode == OUTPUT:
            print(first_arg)
        elif opcode == JUMP_IF_TRUE:
            if first_arg != 0:
                i = second_arg
                continue
        elif opcode == JUMP_IF_FALSE:
            if first_arg == 0:
                i = second_arg
                continue
        elif opcode == LESS_THAN:
            code[third_arg] = int(first_arg < second_arg)
        elif opcode == EQUALS:
            code[third_arg] = int(first_arg == second_arg)
        else:
            print("Unexpected opcode", opcode)

        i += instr_count


run_machine()
