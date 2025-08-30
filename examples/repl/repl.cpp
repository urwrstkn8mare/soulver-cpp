#include <iostream>
#include <ostream>
#include <print>
#include <soulver-cpp/core.hpp>
#include <string>

int main() {
  SoulverCore::Calculator calc;
  std::string line;

  std::cout << "[SoulverCore] $> ";

  while (std::getline(std::cin, line)) {
    auto res = calc.calculate(line);

    if (!res) {
      std::cerr << "error while calculating" << res.error().error << std::endl;
      continue;
    }

    auto data = res.value();

    std::println("{} ({})", data.value, data.type);
    std::cout << "[SoulverCore] $> ";
  }

  return 0;
}
