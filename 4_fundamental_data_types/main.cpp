//
// Created by 9527 on 2/9/23.
//

#include <iostream>
#include <string>
#include <string_view>

int main() {
  std::cout << "Enter your full name: ";
  std::string name{};
  std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

  std::cout << "Enter your age: ";
  std::string age{};
  std::cin >> age;

  std::cout << "Your name is " << name << " and your age is " << age << '\n';

  using namespace std::literals; // easiest way to access the s and sv suffixes
  std::cout << "asdfb"s;

  return 0;
}