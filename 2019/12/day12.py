import copy
import re
from math import lcm


def get_velocity_change(x: int, other_x: int) -> int:
    if x > other_x:
        return - 1
    elif x < other_x:
        return 1
    else:
        return 0


class Moon:
    position: tuple[int, int, int]
    velocity: tuple[int, int, int]

    def __init__(self, x: int, y: int, z: int) -> None:
        self.position = (x, y, z)
        self.velocity = (0, 0, 0)

    def apply_gravity(self, other: "Moon"):
        my_x, my_y, my_z = self.position
        other_x, other_y, other_z = other.position
        vx, vy, vz = self.velocity

        vx += get_velocity_change(my_x, other_x)
        vy += get_velocity_change(my_y, other_y)
        vz += get_velocity_change(my_z, other_z)

        self.velocity = (vx, vy, vz)

    def move(self) -> None:
        x, y, z = self.position
        dx, dy, dz = self.velocity
        self.position = (x + dx, y + dy, z + dz)

    def get_kinetic_energy(self):
        x, y, z = self.velocity
        return abs(x) + abs(y) + abs(z)

    def get_potential_energy(self):
        x, y, z = self.position
        return abs(x) + abs(y) + abs(z)

    def get_total_energy(self) -> int:
        return self.get_kinetic_energy() * self.get_potential_energy()


POSITION_REGEX = r"<x=(-?\d+), y=(-?\d+), z=(-?\d+)>"

with open("input", "r") as f:
    moons_list: list[Moon] = []
    for line in f.readlines():
        if not len(line) == 0:
            positions = re.match(POSITION_REGEX, line).groups()
            nx, ny, nz = int(positions[0]), int(positions[1]), int(positions[2])
            moons_list.append(Moon(nx, ny, nz))


def part1() -> int:
    steps = 1000
    moons = copy.deepcopy(moons_list)

    for _ in range(steps):
        for moon in moons:
            for other_moon in moons:
                moon.apply_gravity(other_moon)

        for moon in moons:
            moon.move()

    return sum([moon.get_total_energy() for moon in moons])


def get_repeat_steps(cords: list[tuple[int, int]]) -> int:
    count = 0
    first_state = tuple(cords)

    while True:
        new_cords: list[tuple[int, int]] = []
        for cord in cords:
            new_cords.append((cord[0], cord[1] + sum(get_velocity_change(cord[0], other) for (other, _) in cords)))

        cords = [(pos + vel, vel) for (pos, vel) in new_cords]
        count += 1
        if tuple(cords) == first_state:
            return count


def part2() -> int:
    # It assumes that the first step will be the one to repeat.
    # It's a heuristic, but works for this problem.
    x_cords = [(moon.position[0], 0) for moon in moons_list]
    y_cords = [(moon.position[1], 0) for moon in moons_list]
    z_cords = [(moon.position[2], 0) for moon in moons_list]

    return lcm(get_repeat_steps(x_cords), lcm(get_repeat_steps(y_cords), get_repeat_steps(z_cords)))


print("Part 1", part1())
print("Part 2", part2())
