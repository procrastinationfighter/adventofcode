import re
from collections import namedtuple

Product = namedtuple("Product", ["name", "quantity"])

ELEMENT_REGEX = r"(\d+) ([A-Z]+)"
# REACTION_REGEX = ELEMENT_REGEX + r"(?:, " + ELEMENT_REGEX + r")*" + r" => " + ELEMENT_REGEX

with open("input", "r") as f:
    recipes: dict[str, list[Product]] = dict()
    quantities: dict[str, int] = dict()

    for line in f.readlines():
        elements = re.findall(ELEMENT_REGEX, line.rstrip('\n'))
        ingredients: list[Product] = list()
        product = elements.pop()

        for el in elements:
            if el[0] is not None:
                ingredients.append(Product(el[1], int(el[0])))

        recipes[product[1]] = ingredients
        quantities[product[1]] = int(product[0])


available: dict[str, int] = dict()


def use_resources(product: Product) -> int:
    amount = available.get(product.name)
    if amount is None:
        amount = 0

    to_create = product.quantity - amount
    spent_ore = 0
    produced = 0

    if to_create > 0:
        reaction_count = to_create // quantities[product.name]
        if to_create % quantities[product.name] > 0:
            reaction_count += 1
        produced = reaction_count * quantities[product.name]

        for ingredient in recipes[product.name]:
            if ingredient.name == "ORE":
                spent_ore += reaction_count * ingredient.quantity
            else:
                spent_ore += use_resources(Product(ingredient.name, reaction_count * ingredient.quantity))

    available[product.name] = amount + produced - product.quantity
    return spent_ore


def part1() -> int:
    return use_resources(Product("FUEL", 1))


def part2() -> int:
    i = 1
    limit = 1000000000000
    available.clear()
    one = part1()
    left = limit // one
    right = limit

    while left < right:
        mid = (left + right) // 2
        available.clear()
        ore = use_resources(Product("FUEL", mid))
        if ore >= limit:
            right = mid - 1
        else:
            left = mid + 1

    return left


print("Part 1", part1())
print("Part 2", part2())
