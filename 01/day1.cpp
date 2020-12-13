#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> v;

void init() {
  std::string s;
  while(std::getline(std::cin, s)) {
    v.push_back(std::stoi(s));
  }
  std::sort(v.begin(), v.end());
}

std::optional<int> part_one(int sum, size_t left_id) {
  size_t i = left_id, j = v.size() - 1;
  while(i < j) {
    if(std::binary_search(v.begin() + i, v.end(), sum - v[i])) {
      return v[i] * (sum - v[i]);
    }
    i++;
  }

  return {};
}

int part_two(int sum) {
  size_t i = 0, j = v.size() - 1;
  while(i < j) {
    auto opt = part_one(sum - v[i], i + 1);
    if(opt.has_value()) {
      return v[i] * opt.value();
    }
    i++;
  }

  return -1;
}

int main() {
  init();
  std::cout << part_one(2020, 0).value() << "\n"
            << part_two(2020) << "\n";
  return 0;
}
