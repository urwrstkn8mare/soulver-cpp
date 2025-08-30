#pragma once
#include <expected>
#include <filesystem>
#include <optional>
#include <string>

extern "C" {
void soulver_initialize(const char *resourcesPath);
char *soulver_evaluate(const char *expression);
void soulver_free_string(char *ptr);
bool soulver_is_initialized();
}

namespace SoulverCore {

struct CalculationResultData {
  std::string value;
  std::string type;
};
struct CalculationError {
  std::string error;
};

using CalculationResult =
    std::expected<CalculationResultData, CalculationError>;

class Calculator {
public:
  CalculationResult calculate(const std::string &expression);
  void print(const std::string &expression);

  Calculator();

private:
  bool initialize();
  std::optional<std::filesystem::path> locateResourceDir();
  bool initialized = false;
};

}; // namespace SoulverCore
