#include <iostream>
#include <regex>
#include <set>

std::vector<std::string> input;

void init() {
  std::string curr;
  while(std::getline(std::cin, curr)) {
    input.push_back(curr);
  }
}

int part_one(const std::string &bag) {
  std::smatch match;
  std::deque<std::string> next;
  std::set<std::string> checked;

  next.push_back(bag);

  while(!next.empty()) {
    std::regex regex(R"((\w+ \w+) bags contain (\d+ \w+ \w+ bags?, )*\d+ )" + next.front());
    next.pop_front();
    for (const auto &line: input) {
      if (std::regex_search(line, match, regex)) {
        std::string curr = match[1].str();
        if (checked.find(curr) == checked.end()) {
          next.push_back(curr);
          checked.insert(curr);
        }
      }
    }
  }

  return checked.size();
}

int part_two(const std::string &bag) {
  std::regex outside(bag + R"( bags contain)");
  std::smatch match;
  static std::regex bag_info(R"((\d+) (\w+ \w+) bags?)");

  for(auto line: input) {
    if(std::regex_search(line,  outside)) {
      int sum = 0;
      while(std::regex_search(line, match, bag_info)) {
        sum += std::stoi(match[1].str()) * part_two(match[2].str());
        line = match.suffix().str();
      }
      return 1 + sum;
    }
  }

  return -20;
}

int main() {
  init();
  // We add -1 because we don't want to count the shiny gold bag.
  std::cout << part_two("shiny gold") - 1 << std::endl;
  return 0;
}