#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> seats_plane_part_one;

void init() {
  int x;
  seats_plane_part_one.push_back(0);
  while(std::cin >> x) {
    seats_plane_part_one.push_back(x);
  }
  std::sort(seats_plane_part_one.begin(), seats_plane_part_one.end());
  seats_plane_part_one.push_back(seats_plane_part_one[seats_plane_part_one.size() - 1] + 3);
}

int part_one() {
  int one = 0;
  int three = 0;

  for(int i = 1; i < seats_plane_part_one.size(); i++) {
    int diff = seats_plane_part_one[i] - seats_plane_part_one[i - 1];
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
  std::vector<std::int64_t> DP(seats_plane_part_one.size(), 1);
  // Normally we should not cast size_t to int,
  // but the seats_plane_part_one is not too big and we don't want the loop to be ugly
  for(int i = seats_plane_part_one.size() - 2; i >= 0; i--) {
    std::int64_t curr = 0;
    for(int j = 1; j <= 3 && i + j < seats_plane_part_one.size(); j++) {
      if(seats_plane_part_one[i + j] - 3 <= seats_plane_part_one[i]) {
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