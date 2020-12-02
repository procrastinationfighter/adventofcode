#include <iostream>
#include <regex>

int part_one() {
  std::regex r(R"((\d+)-(\d+) (\w): (\w+))");
  std::smatch res;
  std::string line;
  int line_count = 0;
  int left, right;
  char ch;
  while(std::getline(std::cin, line)) {
    std::regex_search(line, res, r);
    left = std::stoi(res[1].str());
    right = std::stoi(res[2].str());
    ch = res[3].str()[0];
    std::string word = res[4].str();
    int curr_count = 0;
    for(auto curr : word) {
      if(ch == curr) {
        curr_count++;
      }
    }
    if(curr_count >= left && curr_count <= right) {
      line_count++;
    }
  }
  return line_count;
}

int part_two() {
  std::regex r(R"((\d+)-(\d+) (\w): (\w+))");
  std::smatch res;
  std::string line;
  int line_count = 0;
  int left, right;
  char ch;
  while(std::getline(std::cin, line)) {
    std::regex_search(line, res, r);

    left = std::stoi(res[1].str());
    right = std::stoi(res[2].str());
    ch = res[3].str()[0];
    std::string word = res[4].str();

    int curr_count = 0;
    if(word[left - 1] == ch) {
      curr_count++;
    }
    if(word[right - 1] == ch) {
      curr_count++;
    }

    if(curr_count == 1) {
      line_count++;
    }
  }
  return line_count;
}

int main() {
  std::cout << part_two() << "\n";
  return 0;
}



