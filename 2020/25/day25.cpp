#include <iostream>

long door_key = 14082811, card_key = 5249543;

long long part_one() {
    int res = 1;
    int door_loop = 0;
    while (res != door_key) {
        door_loop++;
        res *= 7;
        res %= 20201227;
    }

    res = 1;
    int card_loop = 0;
    while (res != card_key) {
        card_loop++;
        res *= 7;
        res %= 20201227;
    }

    long long card_res = 1;
    for (int i = 0; i < card_loop; i++) {
        card_res *= door_key;
        card_res %= 20201227;
    }
    return card_res;
}

int main() {
    std::cout << part_one() << "\n";
    return 0;
}