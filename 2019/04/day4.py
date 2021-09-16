import math

with open("input", "r") as f:
    input_line = f.readline()

lower_bound = int(input_line[:6])
upper_bound = int(input_line[7:])
MAX_DIGITS = 6


def part1():
    count = 0

    for i in range(lower_bound, upper_bound + 1):
        is_ok = False

        left, right = i % 10, 0
        for j in range(1, MAX_DIGITS):
            right = left
            left = (i // 10**j) % 10

            if left == right:
                is_ok = True
            elif left > right:
                is_ok = False
                break

        if is_ok:
            count += 1

    return count


def part2():
    count = 0

    for i in range(lower_bound, upper_bound + 1):
        is_ok = False

        left, right = i % 10, 0
        curr_group = -1
        is_single_group = False
        for j in range(1, MAX_DIGITS):
            right = left
            left = (i // 10 ** j) % 10

            if left == right:
                if left == curr_group:
                    is_single_group = False
                else:
                    curr_group = left
                    is_single_group = True
            else:
                curr_group = -1

                if is_single_group:
                    is_ok = True
                    is_single_group = False

                if left > right:
                    is_ok = False
                    break

        if is_single_group:
            is_ok = True
            is_single_group = False

        if is_ok:
            count += 1

    return count


print(part1())
print(part2())
