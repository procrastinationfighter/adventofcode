import queue
from itertools import permutations
from typing import Optional

with open("input") as f:
    input_code = [int(x) for x in f.read().rstrip('\n').split(',')]

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


# Copied from day 5 solution and transformed into a class
class OpcodeMachine:
    code: list[int]
    i: int
    has_finished: bool

    def __init__(self, code: list[int]) -> None:
        self.code = code.copy()
        self.i = 0
        self.has_finished = False

    def has_finished(self) -> bool:
        return self.has_finished

    def run_machine(self, input_q: queue) -> Optional[int]:
        while self.code[self.i] != HALT:
            i = self.i
            opcode = self.code[i] % 100
            first_mode = (self.code[i] // 100) % 10
            second_mode = (self.code[i] // 1000) % 10

            # Will throw an error if something goes wrong
            first_arg, second_arg, third_arg = -1, -1, -1

            instr_count = INSTRUCTIONS_COUNT[opcode]

            if opcode == ADD or opcode == MULTIPLY or opcode == LESS_THAN or opcode == EQUALS:
                first_arg = self.code[self.code[i + 1]] if first_mode == 0 else self.code[i + 1]
                second_arg = self.code[self.code[i + 2]] if second_mode == 0 else self.code[i + 2]
                third_arg = self.code[i + 3]
            elif opcode == JUMP_IF_TRUE or opcode == JUMP_IF_FALSE:
                first_arg = self.code[self.code[i + 1]] if first_mode == 0 else self.code[i + 1]
                second_arg = self.code[self.code[i + 2]] if second_mode == 0 else self.code[i + 2]
            elif opcode == INPUT:
                first_arg = self.code[i + 1]
            elif opcode == OUTPUT:
                first_arg = self.code[self.code[i + 1]] if first_mode == 0 else self.code[i + 1]

            if opcode == ADD:
                self.code[third_arg] = first_arg + second_arg
            elif opcode == MULTIPLY:
                self.code[third_arg] = first_arg * second_arg
            elif opcode == INPUT:
                # Halt if input is empty
                if input_q.empty():
                    return None
                else:
                    self.code[first_arg] = input_q.get()
            elif opcode == OUTPUT:
                self.i += instr_count
                return first_arg
            elif opcode == JUMP_IF_TRUE:
                if first_arg != 0:
                    self.i = second_arg
                    continue
            elif opcode == JUMP_IF_FALSE:
                if first_arg == 0:
                    self.i = second_arg
                    continue
            elif opcode == LESS_THAN:
                self.code[third_arg] = int(first_arg < second_arg)
            elif opcode == EQUALS:
                self.code[third_arg] = int(first_arg == second_arg)
            else:
                print("Unexpected opcode", opcode)

            self.i += instr_count

        # If code is halt, return none.
        self.has_finished = True
        return None


def calculate_signal_part_one(setting: tuple[int, int, int, int, int]) -> int:
    input_signal = 0

    for phase in setting:
        input_data = queue.Queue()
        input_data.put(phase)
        input_data.put(input_signal)

        input_signal = OpcodeMachine(input_code).run_machine(input_data)

    return input_signal


def part1() -> int:
    perms = list(permutations(range(0, 5)))
    max_signal = -1
    win = (-1, -1, -1, -1, -1)

    for setting in perms:
        signal = calculate_signal_part_one(setting)
        if signal > max_signal:
            win = setting
            max_signal = signal

    print(win)
    return max_signal


def calculate_signal_part_two(setting: tuple[int, int, int, int, int]) -> int:
    last_signal, last_e_signal = 0, -1
    machines = [OpcodeMachine(input_code) for _ in range(len(setting))]
    is_first_loop = True

    while not machines[len(setting) - 1].has_finished:
        for i in range(len(setting)):
            input_values = queue.Queue()
            if is_first_loop:
                input_values.put(setting[i])
            if last_signal is not None:
                input_values.put(last_signal)

            last_signal = machines[i].run_machine(input_values)

        if last_signal is not None:
            last_e_signal = last_signal
        is_first_loop = False

    return last_e_signal


def part2() -> int:
    perms = list(permutations(range(5, 10)))
    max_signal = -1
    win = (-1, -1, -1, -1, -1)

    for setting in perms:
        signal = calculate_signal_part_two(setting)
        if signal > max_signal:
            win = setting
            max_signal = signal

    print(win)
    return max_signal


print(part1())
print(part2())
