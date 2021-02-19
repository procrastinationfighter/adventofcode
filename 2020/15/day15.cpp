#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

std::vector<int> input;

void init() {
    int x;
    char ch;
    std::cin >> x;
    input.push_back(x);
    while(std::cin >> ch) {
        std::cin >> x;
        input.push_back(x);
    }
}

unsigned count(unsigned round) {
    std::unordered_map<unsigned, unsigned> numbers;

    unsigned last = input[0];

    for(unsigned i = 1; i < input.size(); i++) {
        numbers[last] = i; // We use i because we're counting from 0, but turns are counted from 1.
        last = input[i];
    }

    for(unsigned i = input.size(); i < round; i++) {
        int nr_last = numbers[last];
        if(nr_last == 0) {
            numbers[last] = i;
            last = 0;
        }
        else {
            unsigned curr = i - nr_last;
            numbers[last] = i;
            last = curr;
        }
    }

    return last;
}

unsigned part_one() {
    return count(2020);
}

unsigned part_two() {
    return count(30000000);
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}