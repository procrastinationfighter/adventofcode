f = open('input', 'r')
data = [int(line.rstrip()) for line in f.readlines()]


def part1():
    mass_sum = 0
    for mass in data:
        mass_sum += (mass // 3) - 2

    return mass_sum


def part2():
    def fuel(mass):
        new_fuel = mass // 3 - 2
        if new_fuel > 0:
            return new_fuel + fuel(new_fuel)
        else:
            return 0

    mass_sum = 0
    for mass in data:
        mass_sum += fuel(mass)

    return mass_sum


print(part1())
print(part2())