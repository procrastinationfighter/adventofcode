#include <iostream>
#include <vector>

std::vector<int> numbers;

void init() {
  int x;
  while(std::cin >> x) {
    numbers.push_back(x);
  }
}

bool check(int i) {
  for(int j = i - 25; j < i; j++) {
    int diff = numbers[i] - numbers[j];
    for(int k = j + 1; k < i; k++) {
      if(numbers[k] == diff) {
        return true;
      }
    }
  }

  return false;
}

std::pair<int, int> part_one() {
  for(int i = 25; i < numbers.size(); i++) {
    if(!check(i)) {
      return {numbers[i], i};
    }
  }

  return {-42, -15};
}

std::pair<int, int> find_min_max_in_contiguous_set(int left_lim, int right_lim, int value) {
  int sum = numbers[left_lim];

  int left = left_lim, right = left_lim;
  while (right < right_lim) {
    if (sum > value) {
      sum -= numbers[left];
      left++;
      if (left > right) {
        right++;
        sum += numbers[right];
      }
    } else if (sum < value) {
      right++;
      sum += numbers[right];

    } else if(left != right && sum == value) {
      // We look for max and min
      int min = INT32_MAX;
      int max = INT32_MIN;

      for (int j = left; j <= right; j++) {
        int x = numbers[j];
        min = std::min(min, x);
        max = std::max(max, x);
      }
      return {min, max};
    }
  }

  return {1, -1};
}

int part_two(int index) {

  auto x = find_min_max_in_contiguous_set(0, index, numbers[index]);
  if (x.first <= x.second) {
    return x.first + x.second;
  }
  //If not found, look farther
  if(index + 1 < numbers.size()) {
    x = find_min_max_in_contiguous_set(index + 1, numbers.size(), numbers[index]);
    if (x.first <= x.second) {
      return x.first + x.second;
    }
  }

  return -42;
}

int main() {
  init();
  auto x = part_one();
  std::cout << x.first << " " << part_two(x.second) << "\n";
  return 0;
};