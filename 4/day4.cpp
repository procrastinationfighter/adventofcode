#include <iostream>
#include <vector>
#include <regex>

std::vector<std::string> passports;

void init_passports() {
  std::string line;
  std::string curr_passport;

  while(std::getline(std::cin, line)) {
    if(line.empty()) {
      passports.push_back(curr_passport);
      curr_passport = " ";
    }
    else {
      curr_passport += line + " ";
    }
  }
  passports.push_back(curr_passport);
}

int part_one() {
  std::regex regex[7] = {
      std::regex(R"(byr:)"),
      std::regex(R"(iyr:)"),
      std::regex(R"(eyr:)"),
      std::regex(R"(hgt:)"),
      std::regex(R"(hcl:)"),
      std::regex(R"(ecl:)"),
      std::regex(R"(pid:)")
  };
  int count = 0;
  for(const auto &passport : passports) {
    bool ok = true;
    for(int i = 0; i < 7 && ok; i++) {
      if(!std::regex_search(passport, regex[i])) {
        ok = false;
      }
    }
    if(ok) {
      count++;
    }
  }
  return count;
}

bool is_byr_valid(const std::string &passport) {
  static const std::regex r(R"( byr:(\d{4}) )");
  static std::smatch match;
  if(std::regex_search(passport, match, r)) {
    int y = std::stoi(match[1]);
    return y >= 1920 && y <= 2002;
  }

  return false;
}

bool is_iyr_valid(const std::string &passport) {
  static const std::regex r(R"( iyr:(\d{4}) )");
  static std::smatch match;
  if(std::regex_search(passport, match, r)) {
    int y = std::stoi(match[1]);
    return y >= 2010 && y <= 2020;
  }

  return false;
}

bool is_eyr_valid(const std::string &passport) {
  static const std::regex r(R"( eyr:(\d{4}) )");
  static std::smatch match;
  if(std::regex_search(passport, match, r)) {
    int y = std::stoi(match[1]);
    return y >= 2020 && y <= 2030;
  }

  return false;
}

bool is_hgt_valid(const std::string &passport) {
  static const std::regex r(R"( hgt:(\d{2,3})(cm|in) )");
  static std::smatch match;
  if(std::regex_search(passport, match, r)) {
    int y = std::stoi(match[1]);
    if(match[2] == "cm") {
      return y >= 150 && y <= 193;
    }
    else if(match[2] == "in"){
      return y >= 59 && y <= 76;
    }
  }

  return false;
}

bool is_hcl_valid(const std::string &passport) {
  static const std::regex r(R"( hcl:#[0-9a-f]{6} )");
  static std::smatch match;
  return std::regex_search(passport, match, r);
}

bool is_ecl_valid(const std::string &passport) {
  static const std::regex r(R"(ecl:(amb|blu|brn|gry|grn|hzl|oth) )");
  static std::smatch match;
  return std::regex_search(passport, match, r);
}

bool is_pid_valid(const std::string &passport) {
  static const std::regex r(R"( pid:\d{9} )");
  static std::smatch match;
  return std::regex_search(passport, match, r);
}


bool all_valid(const std::string &passport) {
  return is_byr_valid(passport)
      && is_iyr_valid(passport)
      && is_eyr_valid(passport)
      && is_hgt_valid(passport)
      && is_hcl_valid(passport)
      && is_ecl_valid(passport)
      && is_pid_valid(passport);
}

int part_two() {
  int count = 0;
  for(const auto &passport: passports) {
    if(all_valid(passport)) {
      count++;
    }
  }
  return count;
}

int main() {
  init_passports();
  std::cout << part_one() << " " << part_two() << std::endl;
  return 0;
}