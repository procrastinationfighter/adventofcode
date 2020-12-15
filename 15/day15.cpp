#include <iostream>
#include <vector>
#include <map>

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

long long count(long long round) {
    std::map<long long, long long> numbers;

    long long last = input[0];

    for(long long i = 1; i < input.size(); i++) {

        numbers[last] = i; // We use i because we're counting from 0, but turns are counted from 1.
        last = input[i];
    }

    for(long long i = input.size(); i < round; i++) {
        if(numbers.find(last) == numbers.end()) {
            numbers[last] = i;
            last = 0;
        }
        else {
            long long curr = i - numbers[last];
            numbers[last] = i;
            last = curr;
        }
    }

    return last;
}

long long part_one() {
    return count(2020);
}

long long part_two() {
    return count(30000000);
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}