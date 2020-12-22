#include <iostream>
#include <vector>
#include <deque>
#include <set>

std::vector<int> one_deck, second_deck;

void init() {
    std::string curr;
    std::getline(std::cin, curr);
    std::getline(std::cin, curr);
    while(!curr.empty()) {
        one_deck.push_back(std::stoi(curr));
        std::getline(std::cin, curr);
    }

    std::getline(std::cin, curr);

    while(std::getline(std::cin, curr)) {
        second_deck.push_back(std::stoi(curr));
    }

}

long part_one() {
    std::deque<int> first, second;
    for(int x : one_deck) {
        first.push_back(x);
    }

    for(int x : second_deck) {
        second.push_back(x);
    }

    while (!first.empty() && !second.empty()) {
        int f = first.front(), s = second.front();
        first.pop_front();
        second.pop_front();

        if(f > s) {
            first.push_back(f);
            first.push_back(s);
        }
        else {
            second.push_back(s);
            second.push_back(f);
        }
    }

    std::deque<int> &winner = first.empty() ? second : first;

    long sum = 0;
    int i = 1;

    while (!winner.empty()) {
        sum += i * winner.back();
        winner.pop_back();
        i++;
    }

    return sum;
}

// NOT recommendable - a lot of redundant copying of large decks. But it works.
std::deque<int> clone_deck(std::deque<int> deck, int number_of_cards) {
    while(deck.size() > number_of_cards) {
        deck.pop_back();
    }

    return deck;
}

// True if player 1 won.
bool recursive_combat(std::deque<int> &first, std::deque<int> &second) {
    std::set<std::pair<std::deque<int>, std::deque<int>>> former_positions;

    while (!first.empty() && !second.empty()) {
        if (former_positions.find({first, second}) != former_positions.end()) {
            return true;
        } else {
            former_positions.insert({first, second});
            int f = first.front(), s = second.front();
            first.pop_front();
            second.pop_front();

            if (f <= first.size() && s <= second.size()) {
                auto first_copy = clone_deck(first, f);
                auto second_copy = clone_deck(second, s);

                if (recursive_combat(first_copy, second_copy)) {
                    first.push_back(f);
                    first.push_back(s);
                } else {
                    second.push_back(s);
                    second.push_back(f);
                }
            } else {
                if (f > s) {
                    first.push_back(f);
                    first.push_back(s);
                } else {
                    second.push_back(s);
                    second.push_back(f);
                }
            }
        }
    }

    return second.empty();
}

long part_two() {
    std::deque<int> first, second;
    for(int x : one_deck) {
        first.push_back(x);
    }

    for(int x : second_deck) {
        second.push_back(x);
    }

    std::deque<int> &winner = recursive_combat(first, second) ? first : second;

    long sum = 0;
    int i = 1;

    while (!winner.empty()) {
        sum += i * winner.back();
        winner.pop_back();
        i++;
    }

    return sum;
}


int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}