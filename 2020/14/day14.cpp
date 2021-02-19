#include <iostream>
#include <vector>
#include <regex>
#include <cmath>

std::vector<std::string> input;

void init() {
    std::string curr;
    while(std::getline(std::cin, curr)) {
        input.push_back(curr);
    }
}

long send_number_through_mask(const std::string &mask, long number) {
    long result = 0, power = 1;
    for(int i = 35; i >= 0; i--) {
        switch (mask[i]) {
            case '0':
                break;
            case '1':
                result += power;
                break;
            default: /* case 'X' */
                if(number % 2 == 1) {
                    result += power;
                }
                break;
        }
        number /= 2;
        power *= 2;
    }

    return result;
}

long part_one() {
    std::regex mem_regex(R"(mem\[(\d+)\] = (\d+))");
    std::regex mask_regex(R"(mask = ([10X]+))");
    std::smatch match;

    std::map<long, long> values;

    std::string curr_mask;

    for(const auto &line : input) {
        if(std::regex_match(line, match, mem_regex)) {
            long address = std::stol(match[1].str());
            long value = std::stol(match[2].str());

            auto iter = values.find(address);
            long masked_value = send_number_through_mask(curr_mask, value);
            if(iter != values.end()) {
                values.erase(iter);
            }

            values.insert({address, masked_value});
        }
        else if(std::regex_match(line, match, mask_regex)) {
            curr_mask = match[1].str();
        }
        else {
            std::cout << "ERROR, WRONG INPUT" << std::endl;
        }
    }

    long sum = 0;

    for(const auto &pair : values) {
        sum += pair.second;
    }

    return sum;
}

void add_values(std::map<long, long> &values, std::vector<long> &addresses, long value_to_add) {
    for (long addr : addresses) {
        auto iter = values.find(addr);
        if (iter != values.end()) {
            values.erase(iter);
        }
        values.insert({addr, value_to_add});
    }
}

void fill_all_addresses(const std::string &mask, std::vector<long> &addresses,
                        long value, long left_index) {
    long power = std::pow(2, 35 - left_index);
    while(left_index < 36 && mask[left_index] != 'X') {
        if(mask[left_index] == '1') {
            value += power;
        }

        power /= 2;
        left_index++;
    }
    if(left_index >= 36) {
        addresses.push_back(value);
    }
    else {
        fill_all_addresses(mask, addresses, value, left_index + 1);
        fill_all_addresses(mask, addresses, value + power, left_index + 1);
    }
}

void get_addresses(const std::string &mask, std::vector<long> &addresses, long address) {
    std::string floating_address;
    for(int i = 35; i >= 0; i--) {
        switch (mask[i]) {
            case '0':
                if(address % 2 == 1) {
                    floating_address.push_back('1');
                }
                else {
                    floating_address.push_back('0');
                }
                break;
            case '1':
                floating_address.push_back('1');
                break;
            default:
                floating_address.push_back('X');
                break;
        }
        address /= 2;
    }
    fill_all_addresses(floating_address, addresses, 0, 0);
}

long part_two() {
    std::regex mem_regex(R"(mem\[(\d+)\] = (\d+))");
    std::regex mask_regex(R"(mask = ([10X]+))");
    std::smatch match;

    std::map<long, long> values;

    std::string curr_mask;

    for(const auto &line : input) {
        if(std::regex_match(line, match, mem_regex)) {
            long address = std::stol(match[1].str());
            long value = std::stol(match[2].str());

            std::vector<long> addresses;

            get_addresses(curr_mask, addresses, address);
            add_values(values, addresses, value);
        }
        else if(std::regex_match(line, match, mask_regex)) {
            curr_mask = match[1].str();
        }
        else {
            std::cout << "ERROR, WRONG INPUT" << std::endl;
        }
    }

    long sum = 0;

    for(const auto &pair : values) {
        sum += pair.second;
    }

    return sum;
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}