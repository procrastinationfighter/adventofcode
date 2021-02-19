#include <iostream>
#include <vector>
#include <unordered_map>

const long INPUT = 389547612;

using List = struct node {
  int val;
  node *next;
};


size_t play_round_part_one(std::vector<int> &cups, unsigned pos, unsigned max_val) {
    int curr_val = cups[pos];
    unsigned size = cups.size();
    unsigned curr = cups[pos] - 1;
    int first = cups[(pos + 1) % size],
        second = cups[(pos + 2) % size],
        third = cups[(pos + 3) % size];

    for(int i = 0; i < 3; i++) {
        unsigned curr_er_pos = ((pos + 1) % cups.size());
        if(curr_er_pos < pos) {
            pos--;
        }
        cups.erase(cups.begin() + curr_er_pos);
    }

    int id = -1;
    while (id < 0) {
        if(curr == 0) {
            curr = max_val;
        }

        for(int i = 0; i < cups.size(); i++) {
            if (cups[i] == curr) {
                id = i;
            }
        }
        curr--;
    }

    cups.insert(cups.begin() + ((id + 1) % size), first);
    cups.insert(cups.begin() + ((id + 2) % size), second);
    cups.insert(cups.begin() + ((id + 3) % size), third);

    for(int i = 0; i < cups.size(); i++) {
        if(cups[i] == curr_val) {
            return i;
        }
    }

    return -20;
}

long part_one() {
    std::vector<int> cups;
    int curr = INPUT;
    while (curr != 0) {
        cups.insert(cups.begin(), curr % 10);
        curr /= 10;
    }

    size_t last = -1;
    for (unsigned i = 0; i < 100; i++) {
        last = play_round_part_one(cups, (last + 1) % cups.size(), 9);
    }

    // I don't have enough patience right now to make it correctly
    long result = 0;

    for(int a : cups) {
        result += a;
        result *= 10;
    }
    return result / 10;
}

// Part two requires doing things more carefully
std::unordered_map<int, node*> map;
const int numbers = 1e6;
const int repeat = 1e7;

List *init_list() {
    int c = static_cast<int>(10e6), x = INPUT % static_cast<int>(10e7);
    List *first = new List, *curr;

    first->val = static_cast<int>(INPUT / 10e7);
    first->next = nullptr;
    curr = first;
    map[curr->val] = curr;

    while(c != 0) {
        curr->next = new List;
        curr = curr->next;
        curr->val = static_cast<int>(x / c);
        curr->next = nullptr;
        x %= c;
        c /= 10;
        map[curr->val] = curr;
    }

    for (int i = 10; i <= numbers; i++) {
        curr->next = new List;
        curr = curr->next;
        curr->val = i;
        curr->next = nullptr;
        map[curr->val] = curr;
    }

    curr->next = first;
    return first;
}

bool is_number_in_list(int num, List* list) {
    while (list != nullptr) {
        if(list->val == num) {
            return true;
        }
        list = list->next;
    }

    return false;
}

int decrease_in_cycle(int num) {
    if (num - 1 == 0) {
        return numbers;
    }
    else {
        return num - 1;
    }
}

void play_round_part_two(List *curr) {
    List *three_nodes = curr->next;
    curr->next = curr->next->next->next->next;
    three_nodes->next->next->next = nullptr;

    int target = decrease_in_cycle(curr->val);
    while (is_number_in_list(target, three_nodes)) {
        target = decrease_in_cycle(target);
    }

    List *target_node = map[target];
    three_nodes->next->next->next = target_node->next;
    target_node->next = three_nodes;
}

long long part_two() {
    List *curr = init_list();

    for (int i = 0; i < repeat; i++) {
        play_round_part_two(curr);
        curr = curr->next;
    }

    long long result = static_cast<long long>(map[1]->next->val) * static_cast<long long>(map[1]->next->next->val);

    for(auto nd : map) {
        delete nd.second;
    }

    return result;
}

int main() {
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}