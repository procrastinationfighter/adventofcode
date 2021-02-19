#include <iostream>
#include <vector>
#include <regex>
#include <set>
#include <cassert>

using range = std::pair<int, int>;

std::vector<std::pair<range, range>> ranges;
std::vector<std::vector<int>> tickets;
std::vector<int> my_ticket;

void init() {
    std::regex numbers(R"((\d+)-(\d+) or (\d+)-(\d+))");
    std::string curr;
    std::smatch match;

    // Properties
    while (std::getline(std::cin, curr) && !curr.empty()) {
        std::regex_search(curr, match, numbers);
        ranges.push_back({{std::stoi(match[1].str()), std::stoi(match[2].str())},
                          {std::stoi(match[3].str()), std::stoi(match[4].str())}});
    }

    // My ticket
    std::getline(std::cin, curr);
    int x;
    char ch;
    do {
        std::cin >> x;
        my_ticket.push_back(x);
        std::cin >> ch;
    } while(ch == ',');

    // Other tickets
    std::getline(std::cin, curr);

    while(std::cin >> x) {
        std::vector<int> new_vec;
        new_vec.push_back(x);
        while(std::cin >> ch && ch == ',') {
            std::cin >> x;
            new_vec.push_back(x);
        }
        std::cin.putback(ch);
        tickets.push_back(new_vec);
    }
}

bool is_in_ranges(std::pair<range, range> rng, int val) {
    return (val >= rng.first.first && val <= rng.first.second)
        || (val >= rng.second.first && val <= rng.second.second);
}

int part_one() {
    int sum = 0;
    for(const auto &ticket : tickets) {
        for(const auto val : ticket) {
            bool valid = false;
            for(const auto &rng : ranges) {
                if(is_in_ranges(rng, val)) {
                    valid = true;
                    break;
                }
            }
            if(!valid) {
                sum += val;
            }
        }
    }

    return sum;
}

auto pick_valid_tickets() {
    std::vector<std::vector<int>> valid_tickets;
    for(const auto &ticket : tickets) {
        bool ticket_valid = true;
        for(const auto val : ticket) {
            bool val_valid = false;
            for(const auto &rng : ranges) {
                if(is_in_ranges(rng, val)) {
                    val_valid = true;
                    break;
                }

            }
            if(!val_valid) {
                ticket_valid = false;
                break;
            }
        }
        if(ticket_valid) {
            valid_tickets.push_back(ticket);
        }
    }

    return valid_tickets;
}

std::vector<int> verify_candidates(std::vector<std::set<int>> &cands) {
    std::vector<int> result(my_ticket.size());

    while(true) {
        int to_delete = -1;
        for (int i = 0; i < cands.size(); i++) {
            if(cands[i].size() == 1) {
                to_delete = *cands[i].begin();
                result[i] = to_delete;
                break;
            }
        }

        for(auto &cand : cands) {
            cand.erase(to_delete);
        }

        if(to_delete == -1) {
            break;
        }
    }

    return result;
}

long long part_two() {
    auto valid_tickets = pick_valid_tickets();

    std::vector<std::set<int>> indices_candidates;
    for(const auto &rng : ranges) {
        std::set<int> cand;
        // We check for every position on a ticket
        for(int j = 0; j < my_ticket.size(); j++) {
            bool valid_pos = true;
            for(const auto &ticket : valid_tickets) {
                if(!is_in_ranges(rng, ticket[j])) {
                    valid_pos = false;
                    break;
                }
            }

            if(valid_pos) {
                cand.insert(j);
            }
        }

        indices_candidates.push_back(cand);
    }

    auto inds = verify_candidates(indices_candidates);

    // In my input only the first six properties start with "departure",
    // may be different for other inputs
    long long mult = 1;

    for(int i = 0; i < 6; i++) {
        mult *= my_ticket[inds[i]];
    }

    return mult;
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}