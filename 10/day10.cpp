#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> input;

void init() {
  int x;
  input.push_back(0);
  while(std::cin >> x) {
    input.push_back(x);
  }
  std::sort(input.begin(), input.end());
  input.push_back(input[input.size() - 1] + 3);
}

int part_one() {
  int one = 0;
  int three = 0;

  for(int i = 1; i < input.size(); i++) {
    int diff = input[i] - input[i - 1];
    if(diff == 1) {
      one++;
    }
    else if(diff == 3) {
      three++;
    }
  }

  return one * three;
}

std::int64_t part_two() {
  std::vector<std::int64_t> DP(input.size(), 1);

  // Normally we should not cast size_t to int,
  // but the input is not too big and we don't want the loop to be ugly
  for(int i = input.size() - 2; i >= 0; i--) {
    std::int64_t curr = 0;
    for(int j = 1; j <= 3 && i + j < input.size(); j++) {
      if(input[i + j] - 3 <= input[i]) {
        curr += DP[i + j];
      }
    }
    DP[i] = curr;
  }
  return DP[0];
}

int main() {
  init();
  std::cout << part_one() << " " << part_two() << "\n";
  return 0;
}