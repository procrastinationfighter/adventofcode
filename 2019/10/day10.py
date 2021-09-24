import functools
from math import gcd, atan, pi, copysign

import imath

with open("input", "r") as f:
    asteroids_map = [line.rstrip('\n') for line in f.readlines()]


def cut_vector(vec: tuple[int, int]) -> tuple[int, int, int]:
    divisor = gcd(abs(vec[0]), abs(vec[1]))
    return vec[0] // divisor, vec[1] // divisor, divisor


def calculate_seen(x: int, y: int) -> int:
    seen_vectors = set()
    for i in range(len(asteroids_map[0])):
        for j in range(len(asteroids_map)):
            if not (x == i and y == j) and asteroids_map[j][i] == '#':
                seen_vectors.add(cut_vector((i - x, j - y))[0:2])

    return len(seen_vectors)


def part1() -> tuple[int, tuple[int, int]]:
    max_seen = -1
    cords = (-1, -1)

    for x in range(len(asteroids_map[0])):
        for y in range(len(asteroids_map)):
            if asteroids_map[y][x] == '#':
                seen = calculate_seen(x, y)
                if seen > max_seen:
                    max_seen = seen
                    cords = (x, y)

    return max_seen, cords


def compare_vectors(vec1: tuple[int, int, int], vec2: tuple[int, int, int]) -> int:
    # This can probably be done more concisely, but I'm afraid of maths at this point
    x1, y1, div1 = vec1
    x2, y2, div2 = vec2

    def sign(x: int) -> float:
        return copysign(1, x)

    x1_sign, x2_sign = sign(x1), sign(x2)
    if x1_sign == x2_sign:
        if x1 == 0:
            return 1 if y1 < 0 else -1
        cross = x1 * y2 - x2 * y1
        return div1 - div2 if cross == 0 else cross
    else:
        if x1_sign > 0:
            return -1
        else:
            return 1


def part2(cords: tuple[int, int]) -> int:
    asteroids_list: list[tuple[int, int, int]] = []
    for x in range(len(asteroids_map[0])):
        for y in range(len(asteroids_map)):
            if not (x == cords[0] and y == cords[1]) and asteroids_map[y][x] == '#':
                asteroids_list.append((cut_vector((x - cords[0], cords[1] - y))))

    asteroids_list.sort(key=functools.cmp_to_key(compare_vectors))
    curr_turn, next_turn = [], asteroids_list
    i = 0
    prev = (0, 0)

    while i != 200 and len(next_turn) != 0:
        prev = (0, 0, 0)
        curr_turn = next_turn
        next_turn = []
        for asteroid_vec in curr_turn:
            if asteroid_vec[0] == prev[0] and asteroid_vec[1] == prev[1]:
                next_turn.append(asteroid_vec)
            else:
                prev = asteroid_vec
                i += 1
                if i == 200:
                    break

    final_x = prev[0] * prev[2] + cords[0]
    final_y = cords[1] - (prev[1] * prev[2])
    return 100 * final_x + final_y


asteroids_seen, station_cords = part1()
print("Part 1:", asteroids_seen, station_cords)
print("Part 2:", part2(station_cords))
