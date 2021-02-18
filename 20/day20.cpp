#include <iostream>
#include <utility>
#include <vector>
#include <regex>
#include <cmath>
#include <unordered_set>
#include <cassert>

// Finished with the help of Errichto's Youtube video.
// I did not have enough patience and time to do it properly by myself.

const int TILE_SIZE = 10;

class Tile {
 private:
  std::vector<std::string> pattern;
  const int id;

 public:
  Tile(std::vector<std::string> &p, int id) : pattern(p), id(id) {}

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

  void flip() {
      for (auto &row : pattern) {
          for (int column = 0; column < pattern.size()/2; column++) {
              std::swap(row[column], row[pattern.size() - 1 - column]);
          }
      }
  }

  void print_tile() {
      for(auto &i : pattern) {
          std::cout << i << "\n";
      }
  }

  [[nodiscard]] int get_id() const {
      return id;
  }

  std::vector<std::string> &get_pattern() {
      return pattern;
  }

  bool matches_down(const Tile &tile) {
      for (int i = 0; i < TILE_SIZE; i++) {
          if (pattern[TILE_SIZE - 1][i] != tile.pattern[0][i]) {
              return false;
          }
      }

      return true;
  }

  bool matches_right(const Tile &tile) {
      for (int i = 0; i < TILE_SIZE; i++) {
          if (pattern[i][TILE_SIZE - 1] != tile.pattern[i][0]) {
              return false;
          }
      }

      return true;
  }
};


std::vector<Tile> tiles;
size_t grid[20][20];
unsigned grid_side;
std::unordered_set<int> visited_ids;

std::vector<std::string> sea;

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
        std::vector<std::string> pattern;
        while(std::getline(std::cin, curr) && !curr.empty()) {
            pattern.push_back(curr);
        }
        Tile tile(pattern, number);
        for (int i = 0; i < 4; i++) {
            tiles.push_back(tile);
            tiles.push_back(tile);
            tiles.back().flip();
            tile.rotate();
        }
        return true;
    }
}

void init() {
    while (read_tile());
        // Empty.
    grid_side = std::sqrt(tiles.size() / 8);
}

bool search(int row, int column) {
    if (row == grid_side) {
        std::cout << "Grid found!\n";
        return true;
    } else {
        for (size_t i = 0; i < tiles.size(); i++) {
            if (!visited_ids.count(tiles[i].get_id())) {
                bool up = true, left = true;
                if (row > 0) {
                    up = tiles[grid[row - 1][column]].matches_down(tiles[i]);
                }
                if (column > 0) {
                    left = tiles[grid[row][column - 1]].matches_right(tiles[i]);
                }

                if (up && left) {
                    grid[row][column] = i;
                    visited_ids.insert(tiles[i].get_id());
                    if (column == grid_side - 1) {
                        if (search(row + 1, 0)) {
                            return true;
                        }
                    } else {
                        if (search(row, column + 1)) {
                            return true;
                        }
                    }

                    visited_ids.erase(tiles[i].get_id());
                }
            }
        }

        return false;
    }
}

unsigned long long multiply_corners() {
    unsigned long long first = tiles[grid[0][0]].get_id(),
    second = tiles[grid[0][grid_side - 1]].get_id(),
    third = tiles[grid[grid_side - 1][0]].get_id(),
    fourth = tiles[grid[grid_side - 1][grid_side - 1]].get_id();

    unsigned long long result = first * second * third * fourth;

    return result;
}

unsigned long long part_one() {
    search(0, 0);
    return multiply_corners();
}

std::string monster[3] = {"                  # ",
                          "#    ##    ##    ###",
                          " #  #  #  #  #  #   "};

void create_sea() {
    for (int row = 0; row < grid_side; row++) {
        for (int i = 1; i < TILE_SIZE - 1; i++) {
            std::string curr;
            for (int column = 0; column < grid_side; column++) {
                auto &p = tiles[grid[row][column]].get_pattern();
                for (int j = 1; j < TILE_SIZE - 1; j++) {
                    curr.push_back(p[i][j]);
                }
            }
            sea.push_back(curr);
        }
    }
}

int calculate_roughness(std::vector<std::string> pattern) {

}

int part_two() {
    int max_rough = 0;
    create_sea();
    Tile sea_tile(sea, 2137);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            max_rough = std::max(max_rough, calculate_roughness(sea_tile.get_pattern()));
            sea_tile.rotate();
        }
        sea_tile.flip();
    }
    return 0;
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    create_sea();
    Tile s(sea, 2137);
    s.print_tile();
    return 0;
}