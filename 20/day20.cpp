#include <iostream>
#include <utility>
#include <vector>
#include <regex>

const int TILE_SIZE = 9;

class Tile {
 private:
  std::vector<std::string> pattern;
  Tile *left, *up, *down, *right;
  const int id;

 public:
  Tile(std::vector<std::string> p, int id) : pattern(std::move(p)), id(id) {
      left = right = up = down = nullptr;
  }

  bool try_appending_tile(Tile *tile) {
      bool ok = false;

      if (left == nullptr) {
          ok = true;
          for (int i = 0; i < TILE_SIZE && ok; i++) {
              if (pattern[i][0] != tile->pattern[i][TILE_SIZE - 1]) {
                  ok = false;
              }
          }

          if (ok) {
              left = tile;
              tile->right = this;
          }
      }

      if (right == nullptr && !ok) {
          ok = true;
          for (int i = 0; i < TILE_SIZE && ok; i++) {
              if (pattern[i][TILE_SIZE - 1] != tile->pattern[i][0]) {
                  ok = false;
              }
          }

          if (ok) {
              right = tile;
              tile->left = this;
          }
      }

      if (up == nullptr && !ok) {
          ok = true;
          for (int i = 0; i < TILE_SIZE && ok; i++) {
              if (pattern[0][i] != tile->pattern[TILE_SIZE - 1][i]) {
                  ok = false;
              }
          }

          if (ok) {
              up = tile;
              tile->down = this;
          }
      }

      if (down == nullptr && !ok) {
          ok = true;
          for (int i = 0; i < TILE_SIZE && ok; i++) {
              if (pattern[TILE_SIZE - 1][i] != tile->pattern[0][i]) {
                  ok = false;
              }
          }

          if (ok) {
              down = tile;
              tile->up = this;
          }
      }

      return ok;
  }

  // Rotates by 90 degrees
  void rotate() {
      std::vector<std::string> temp(TILE_SIZE, std::string(TILE_SIZE, '*'));
      int N = temp.size();
      for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				temp[i][j] = pattern[N - j - 1][i];
		}
      pattern = temp;
  }

  [[nodiscard]] int get_id() const {
      return id;
  }

  [[nodiscard]] Tile* get_right() const {
      return right;
  }

  [[nodiscard]] Tile* get_down() const {
      return down;
  }

};

class Image {
 private:
  Tile *left_upper = nullptr;

 public:
  Image() = default;

  bool try_appending(Tile *tile) {
      //todo BFS/DFS
      return false;
  }

  long long get_corners_multiplication() {
      long long mult = left_upper->get_id();
      Tile *curr = left_upper;
      Tile *prev;
      while (curr != nullptr) {
          prev = curr;
          curr = prev->get_down();
      }

      mult *= prev->get_id();

      curr = prev;
      while (curr != nullptr) {
          prev = curr;
          curr = prev->get_right();
      }

      mult *= prev->get_id();

      curr = left_upper;
      prev = nullptr;
      while (curr != nullptr) {
          prev = curr;
          curr = prev->get_right();
      }

      mult *= prev->get_id();

      return mult;
  }

};

std::vector<Tile> input;

bool read_tile() {
    std::string curr;
    static std::regex tile_name(R"(Tile (\d+):)");
    std::getline(std::cin, curr);
    if(curr.empty()) {
        return false;
    }
    else {
        std::smatch match;
        std::regex_match(curr, match, tile_name);
        int number = std::stoi(match[1].str());
        std::vector<std::string> tile;
        while(std::getline(std::cin, curr) && !curr.empty()) {
            tile.push_back(curr);
        }
        input.emplace_back(tile, number);
        std::cout << number << "\n";
        for(auto &y : tile) {
            std::cout << y << "\n";
        }
        std::cout << "\n";
        return true;
    }
}

void init() {
    while (read_tile());
        // Empty.
}

int main() {
    init();
    return 0;
}