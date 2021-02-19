#include <iostream>
#include <map>
#include <vector>
#include <regex>

const int a_number = -21;
const int b_number = -37;

std::map<int, std::pair<std::vector<int>, std::vector<int>>> rules;
std::map<int, std::string> regexes;

std::vector<std::string> messages;

void read_numbers(const std::string &list, std::vector<int> &vec) {
    static std::regex regex(R"(\d+)");
    std::string c = list;
    std::smatch match;

    while (std::regex_search(c, match, regex)){
        vec.push_back(std::stoi(match[0].str()));
        c = match.suffix();
    }
}

void init() {
    std::string curr;
    std::smatch match;
    std::regex numb_regex(R"((\d+):((?: \d+)+) ?\|?((?: \d+)+)?)");
    std::regex letter_regex(R"((\d+): \"(a|b)\")");

    while(std::getline(std::cin, curr) && !curr.empty()) {
        std::vector<int> first, second;
        int rule_numb;
        if(std::regex_search(curr, match, numb_regex)) {
            read_numbers(match[2].str(), first);
            if(match.size() == 4) {
                read_numbers(match[3].str(), second);
            }
            rule_numb = std::stoi(match[1].str());
        }
        else if(std::regex_search(curr, match, letter_regex)) {
            if(match[2].str() == "a") {
                rule_numb = std::stoi(match[1].str());
                first.push_back(a_number);
                regexes[rule_numb] = "(a)";
            }
            else {
                rule_numb = std::stoi(match[1].str());
                first.push_back(b_number);
                regexes[rule_numb] = "(b)";
            }
        }

        rules[rule_numb] = {first, second};
    }

    while(std::getline(std::cin, curr)) {
        messages.push_back(curr);
    }
}

void generate_regex(int num);

void generate_regex_11() {
    std::string curr = "(";
    generate_regex(42);
    generate_regex(31);
    auto &reg_42 = regexes[42];
    auto &reg_31 = regexes[31];
    for(int i = 1; i <= 5; i++) {
        curr.append(reg_42 + "{" + std::to_string(i) + "}");
        curr.append(reg_31 + "{" + std::to_string(i) + "}");
        if(i < 5) {
            curr.push_back('|');
        }
    }
    curr.push_back(')');
    regexes[11] = curr;
}

// To get answer for part one, comment mentioned parts
void generate_regex(int num) {
    if (regexes[num].empty()) {
        // Comment the if out if you want answer for part one
        if(num == 11) {
            generate_regex_11();
        }
        else {
            std::string curr = "(";
            auto &y = rules[num];
            for (auto &x : y.first) {
                generate_regex(x);
                curr.append(regexes[x]);
            }
            if (!y.second.empty()) {
                curr.push_back('|');
                for (auto &x : y.second) {
                    generate_regex(x);
                    curr.append(regexes[x]);
                }
            }
            curr.push_back(')');

            // comment this if out for part one
            if (num == 8) {
                curr.push_back('+');
            }
            regexes[num] = curr;
        }
    }
}


long solution() {
    long sum = 0;
    generate_regex(0);
    std::regex rg(regexes[0]);
    for(const auto &line : messages) {
        if(std::regex_match(line, rg)) {
            sum++;
        }
    }

    return sum;
}


int main() {
    init();
    std::cout << solution() << "\n";
    return 0;
}