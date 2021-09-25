import functools
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


TURN_LEFT = 0
TURN_RIGHT = 1

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3
DIRECTIONS_COUNT = 4

BLACK = 0
WHITE = 1


class Robot:
    direction: int
    machine: OpcodeMachine
    x: int
    y: int
    white_fields: set[tuple[int, int]]

    def __init__(self, code: list[int]) -> None:
        self.direction = UP
        self.machine = OpcodeMachine(code)
        self.x = 0
        self.y = 0
        self.white_fields = set()

    def turn(self, turn_direction: int) -> None:
        if turn_direction == TURN_LEFT:
            self.direction = (self.direction - 1) % DIRECTIONS_COUNT
        else:
            self.direction = (self.direction + 1) % DIRECTIONS_COUNT

    def move(self) -> None:
        if self.direction == UP:
            self.y += 1
        elif self.direction == DOWN:
            self.y -= 1
        elif self.direction == LEFT:
            self.x -= 1
        else:
            self.x += 1

    def get_field_color(self) -> int:
        if (self.x, self.y) in self.white_fields:
            return WHITE
        else:
            return BLACK

    def change_color(self, new_color: int, old_color: int) -> None:
        if new_color == WHITE:
            if old_color != WHITE:
                self.white_fields.add((self.x, self.y))
        else:
            if old_color == WHITE:
                self.white_fields.remove((self.x, self.y))

    def work(self) -> set[tuple[int, int]]:
        colored: set[tuple[int, int]] = set()
        q = queue.Queue()

        while not self.machine.has_finished:
            old_color = self.get_field_color()
            q.put(old_color)
            new_color = self.machine.run_machine(q)

            if new_color is not None:
                self.change_color(new_color, old_color)
                turn_dir = self.machine.run_machine(q)
                colored.add((self.x, self.y))

                if turn_dir is None:
                    print("Did not get turn direction!")
                else:
                    self.turn(turn_dir)
                    self.move()

        return colored


def print_whites(fields: list[tuple[int, int]]) -> None:
    next_blank: tuple[int, int] = (0, 0)
    writing: str = ''

    for field in fields:
        if next_blank[1] != field[1]:
            writing += '\n'
            next_blank = (0, field[1])

        writing += '   ' * (field[0] - next_blank[0])
        writing += '[W]'
        next_blank = (field[0] + 1, field[1])

    print(writing)


def part2() -> None:
    robot2 = Robot(input_code)
    # Change the starting color.
    robot2.change_color(WHITE, BLACK)
    robot2.work()

    def compare(first: tuple[int, int], second: tuple[int, int]) -> int:
        x1, y1 = first
        x2, y2 = second

        if y1 == y2:
            return x1 - x2
        else:
            return y2 - y1

    white_fields = list(robot2.white_fields)
    white_fields.sort(key=functools.cmp_to_key(compare))
    print_whites(white_fields)


robot1 = Robot(input_code)
# Change the starting color.
robot1.change_color(WHITE, BLACK)
print("Part 1:", len(robot1.work()))
print("Part 2:")
part2()
