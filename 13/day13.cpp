#include <iostream>
#include <vector>
#include <regex>

int arrival_time;
std::vector<std::pair<int, int>> buses;

void init() {
    std::cin >> arrival_time;

    char ch;
    int bus_order = 0;
    std::string curr;
    while(std::cin >> ch) {
        if(isdigit(ch)) {
            curr.push_back(ch);
        }
        else if(ch == ',') {
            if(!curr.empty()) {
                buses.emplace_back(std::stoi(curr), bus_order);
                curr = "";
            }
            bus_order++;
        }
    }

    buses.emplace_back(std::stoi(curr), bus_order);
}

int part_one() {
    int shortest_time = INT32_MAX;
    int best_id = -1;

    for(auto id : buses) {
        int how_long = id.first - (arrival_time % id.first);
        how_long = (how_long == id.first ? 0 : how_long);
        if(how_long < shortest_time) {
            shortest_time = how_long;
            best_id = id.first;
        }
    }

    return best_id * shortest_time;
}

// Inspired by wikipedia
long long find_mult(long long a, long long b) {
    long long old_r = a, r = b, old_s = 1, s = 0, old_t = 0, t = 1;

    while(r != 0) {
        long long q = old_r / r;
        long long temp_r = r, temp_s = s, temp_t = t;
        r = old_r - q * r;
        s = old_s - q * s;
        t = old_t - q * t;

        old_r = temp_r;
        old_s = temp_s;
        old_t = temp_t;
    }

    //std::cout << old_s << " " << old_t << " " << old_r <<  "\n";
    return old_t;
}

long long part_two() {
    long long mult = 1;
    for(auto x : buses) {
        mult *= x.first;
    }

    long long sum = 0;
    for(auto & bus : buses) {
        long long curr = mult / bus.first;
        sum += find_mult(bus.first, curr) * curr * (bus.second);
    }

    if(sum < 0) {
        sum = (sum * (-1) + mult) % mult;
    }
    return sum;
}


int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";

    return 0;
}