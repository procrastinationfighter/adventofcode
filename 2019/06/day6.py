with open("input", "r") as f:
    orbits = dict()
    all_planets, not_dangling = set(), set()
    for line in f.readlines():
        pair = line.rstrip('\n').split(')')
        orbits[pair[1]] = pair[0]
        # Every planet orbits around something,
        # not every planet is orbited by something.
        all_planets.add(pair[1])


def part1() -> int:
    orbits_count = 0

    for planet in orbits.keys():
        value = planet

        while value != "COM":
            key, value = value, orbits[value]
            orbits_count += 1

    return orbits_count


def list_orbits(node: str) -> list[str]:
    value = node
    orbits_list = list()

    while value != "COM":
        key, value = value, orbits[value]
        orbits_list.append(value)

    return orbits_list


def calculate_ancestor_distances(first: list[str], second: list[str]) -> tuple[int, int]:
    # Returns distances from starting nodes to the first common node.
    for i in range(len(first)):
        try:
            return i, second.index(first[i])
        except ValueError:
            continue


def part2() -> int:
    # This would be awesomely solved using the LCA algorithm,
    # but this file is too narrow to contain it.
    you_orbits, san_orbits = list_orbits("YOU"), list_orbits("SAN")
    you_dist, san_dist = calculate_ancestor_distances(you_orbits, san_orbits)

    return you_dist + san_dist


print(part1())
print(part2())