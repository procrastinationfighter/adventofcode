import queue
from typing import Optional

# Copied from day 9 solution,
# because renaming directories in order to make a module
# would make the repository look ugly.
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
ADJUST_BASE = 9
HALT = 99

POSITION_MODE = 0
IMMEDIATE_MODE = 1
RELATIVE_MODE = 2

INSTRUCTIONS_COUNT = {
    ADD: 4,
    MULTIPLY: 4,
    INPUT: 2,
    OUTPUT: 2,
    JUMP_IF_TRUE: 3,
    JUMP_IF_FALSE: 3,
    LESS_THAN: 4,
    EQUALS: 4,
    ADJUST_BASE: 2,
    HALT: 1
}


class OpcodeMachine:
    code: list[int]
    i: int
    has_finished: bool
    relative_base: int

    def __init__(self, code: list[int]) -> None:
        self.code = code.copy()
        self.i = 0
        self.has_finished = False
        self.relative_base = 0

    def has_finished(self) -> bool:
        return self.has_finished

    def try_to_resize_memory(self, index):
        if index >= len(self.code):
            self.code.extend([0] * (index - len(self.code) + 1))

    def parse_single_argument_in_value(self, index: int, mode: int) -> int:
        # Resize if needed
        self.try_to_resize_memory(index)

        if mode == POSITION_MODE:
            i = self.code[index]
            self.try_to_resize_memory(i)
            return self.code[i]
        elif mode == IMMEDIATE_MODE:
            return self.code[index]
        elif mode == RELATIVE_MODE:
            i = self.relative_base + self.code[index]
            self.try_to_resize_memory(i)
            return self.code[i]
        else:
            print("Wrong mode on index", index)
            return -1

    def parse_single_argument_out_index(self, index: int, mode: int):
        # Resize if needed
        self.try_to_resize_memory(index)

        if mode == POSITION_MODE:
            self.try_to_resize_memory(self.code[index])
            return self.code[index]
        elif mode == RELATIVE_MODE:
            i = self.relative_base + self.code[index]
            self.try_to_resize_memory(i)
            return i

    def parse_arguments(self) -> tuple[int, int, int]:
        i = self.i
        opcode = self.code[i] % 100
        first_mode = (self.code[i] // 100) % 10
        second_mode = (self.code[i] // 1000) % 10
        third_mode = (self.code[i] // 10000) % 10

        # Will throw an error if something goes wrong
        first_arg, second_arg, third_arg = -1, -1, -1

        if opcode == ADD or opcode == MULTIPLY or opcode == LESS_THAN or opcode == EQUALS:
            first_arg = self.parse_single_argument_in_value(i + 1, first_mode)
            second_arg = self.parse_single_argument_in_value(i + 2, second_mode)
            third_arg = self.parse_single_argument_out_index(i + 3, third_mode)
        elif opcode == JUMP_IF_TRUE or opcode == JUMP_IF_FALSE:
            first_arg = self.parse_single_argument_in_value(i + 1, first_mode)
            second_arg = self.parse_single_argument_in_value(i + 2, second_mode)
        elif opcode == INPUT:
            first_arg = self.parse_single_argument_out_index(i + 1, first_mode)
        elif opcode == OUTPUT or ADJUST_BASE:
            first_arg = self.parse_single_argument_in_value(i + 1, first_mode)

        return first_arg, second_arg, third_arg

    def run_machine(self, input_q: queue) -> Optional[int]:
        while self.code[self.i] != HALT:
            i = self.i
            opcode = self.code[i] % 100

            instr_count = INSTRUCTIONS_COUNT[opcode]
            first_arg, second_arg, third_arg = self.parse_arguments()

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
            elif opcode == ADJUST_BASE:
                self.relative_base += first_arg
            else:
                print("Unexpected opcode", opcode)

            self.i += instr_count

        # If code is halt, return none.
        self.has_finished = True
        return None


EMPTY = 0
WALL = 1
BLOCK = 2
HORIZONTAL_PADDLE = 3
BALL = 4


def part1() -> int:
    machine = OpcodeMachine(input_code)
    q = queue.Queue()
    tiles: dict[tuple[int, int], int] = dict()

    while not machine.has_finished:
        x = machine.run_machine(q)
        if x is None:
            break
        y = machine.run_machine(q)
        tile_id = machine.run_machine(q)
        tiles[(x, y)] = tile_id

    count = 0
    for tile_type in tiles.values():
        if tile_type == BLOCK:
            count += 1

    return count


def part2():
    input_code[0] = 2
    machine = OpcodeMachine(input_code)
    q = queue.Queue()
    tiles: list[list[int]] = [[0 for _ in range(20)] for _ in range(44)]
    output_count = 0

    while not machine.has_finished:
        x = machine.run_machine(q)
        if x is None:
            if machine.has_finished:
                break
            else:
                print(output_count)
                output_count = 0
                q.put(0)
                x = machine.run_machine(q)
        y = machine.run_machine(q)
        tile_id = machine.run_machine(q)
        tiles[x][y] = tile_id
        output_count += 1


print("Part 1", part1())

part2()