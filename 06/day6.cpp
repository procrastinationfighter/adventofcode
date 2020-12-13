#include <iostream>
#include <vector>
#include <set>

std::vector<std::string> group_answers;

// Copied from day 4.
void init_answers() {
  std::string line;
  std::string curr_group;

  while(std::getline(std::cin, line)) {
    if(line.empty()) {
      group_answers.push_back(curr_group);
      curr_group = "";
    }
    else {
      curr_group += line + ' ';
    }
  }
  group_answers.push_back(curr_group);
}

int part_one() {
  std::set<char> curr_answers;
  int sum = 0;

  for(const auto &group: group_answers) {
    for(char ch: group) {
      if(ch != ' ') {
        curr_answers.insert(ch);
      }
    }
    sum += curr_answers.size();
    curr_answers.clear();
  }

  return sum;
}

int char_occurences[26];

void reset_buckets() {
  for(int &char_occurence : char_occurences) {
    char_occurence = 0;
  }
}

int part_two() {
  std::set<char> curr_answers;
  int sum = 0;

  for(const auto &group: group_answers) {
    reset_buckets();
    int members_count = 0;
    for(char ch: group) {
      if(ch == ' ') {
        for(char answered: curr_answers) {
          char_occurences[answered - 'a']++;
        }

        curr_answers.clear();
        members_count++;
      }
      else {
        curr_answers.insert(ch);
      }
    }

    for(int char_occurence : char_occurences) {
      if(char_occurence == members_count) {
        sum++;
      }
    }
    curr_answers.clear();
  }

  return sum;
}

int main() {
  init_answers();
  std::cout << part_one() << " " << part_two() << "\n";
  return 0;
}