with open("input", "r") as file:
    first_path = file.readline().rstrip().split(",")
    second_path = file.readline().rstrip().split(",")


def calculate_cords_part_one(path):
    x, y = 0, 0
    cords = set()

    for command in path:
        steps = int(command[1:])
        for i in range(steps):
            if command[0] == 'U':
                y += 1
            elif command[0] == 'D':
                y -= 1
            elif command[0] == 'L':
                x -= 1
            else:
                x += 1
            cords.add((x, y))

    return cords


def part1():
    first_cords, second_cords = calculate_cords_part_one(first_path), calculate_cords_part_one(second_path)
    min_dist = -1

    for intersection in first_cords.intersection(second_cords):
        distance = abs(intersection[0]) + abs(intersection[1])
        if distance < min_dist or min_dist < 0:
            min_dist = distance

    return min_dist


def calculate_cords_part_two(path):
    x, y = 0, 0
    total_steps = 0
    cords = set()
    cords_steps = dict()

    for command in path:
        steps = int(command[1:])
        for i in range(steps):
            if command[0] == 'U':
                y += 1
            elif command[0] == 'D':
                y -= 1
            elif command[0] == 'L':
                x -= 1
            else:
                x += 1
            total_steps += 1
            cords.add((x, y))
            cords_steps[(x, y)] = total_steps

    return cords, cords_steps


def part2():
    first_cords, first_steps =  calculate_cords_part_two(first_path)
    second_cords, second_steps = calculate_cords_part_two(second_path)
    min_dist = -1

    for intersection in first_cords.intersection(second_cords):
        distance = first_steps[intersection] + second_steps[intersection]
        if distance < min_dist or min_dist < 0:
            min_dist = distance

    return min_dist


print(part1())
print(part2())
