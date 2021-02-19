#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <cassert>
#include <algorithm>

// My input uses only one digit numbers, so I use this fact to simplify parsing.
std::vector<std::string> input;

void init() {
    std::string curr;

    while(std::getline(std::cin, curr)) {
        input.push_back(curr);
    }
}

long count_op(long left, long right, char sign) {
    if(sign == '*') {
        return left * right;
    }
    else {
        return left + right;
    }
}

long read_line(std::stringstream &stream) {
    char ch;
    std::stack<std::pair<long, char>> stack;
    long curr_val = 0;
    char curr_op = '+';
    while(stream >> ch) {
        if(isdigit(ch)) {
            curr_val = count_op(curr_val, ch - '0', curr_op);
        }
        else if(isspace(ch)) {
            continue;
        }
        else if(ch == '*' || ch == '+') {
            curr_op = ch;
        }
        else if(ch == '(') {
            stack.push({curr_val, curr_op});
            curr_val = 0;
            curr_op = '+';
        }
        else { // ch == ')'
            assert(!stack.empty());
            auto p = stack.top();
            stack.pop();
            curr_val = count_op(p.first, curr_val, p.second);
        }
    }

    return curr_val;
}

long part_one() {
    std::vector<long> results;

    for(const auto &line : input) {
        std::stringstream stream;
        stream << line;
        long curr_result = read_line(stream);

        results.push_back(curr_result);
    }

    long sum = 0;
    for(const auto x : results) {
        sum += x;
    }

    return sum;
}


std::string add_parenthesis(std::string line) {
    int i = 0;
    line.insert(0, "(");
    line.push_back(')');
    while(line[i] != '\0') {
        if(line[i] == '*') {
            line.insert(i, ")");
            line.insert(i + 2, "(");
            i = i + 3;
        }
        else if(line[i] == '(') {
            line.insert(i, "(");
            i = i + 2;
        }
        else if(line[i] == ')') {
            line.insert(i, ")");
            i = i + 2;
        }
        else {
            i++;
        }
    }
    return line;
}

long part_two() {
    std::vector<long> results;

    for(const auto &line : input) {
        std::string curr = add_parenthesis(line);
        std::stringstream stream;
        stream << curr;
        long curr_result = read_line(stream);

        results.push_back(curr_result);
    }

    long sum = 0;
    for(const auto x : results) {
        sum += x;
    }

    return sum;
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}