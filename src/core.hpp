#pragma once
#include <expected>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <optional>
#include <print>
#include <string>

extern "C" {
bool soulver_initialize(const char *resourcesPath);
char *soulver_evaluate(const char *expression);
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
  void print(const std::string &expression) {
    auto res = calculate(expression);

    if (!res) {
      std::println(std::cerr, "Error: {}", res.error().error);
      return;
    }

    auto value = res.value();

    std::println(std::cout, "{} ({})", value.value, value.type);
  }

  CalculationResult calculate(const std::string &expression) {
    char *ptr = soulver_evaluate(expression.c_str());
    std::string s(ptr);

    free(ptr);

    nlohmann::json data = nlohmann::json::parse(s);
    CalculationResultData result;

    result.value = data["value"];
    result.type = data["type"];

    return result;
  }

  Calculator() {
    if (!soulver_is_initialized()) {
      initialize();
    }
  }

private:
  bool initialize() {
    auto resources = locateResourceDir();

    if (!resources)
      return false;

    soulver_initialize(resources->c_str());
    initialized = true;
    return true;
  }

  std::optional<std::filesystem::path> locateResourceDir() {
    const char *path = getenv("XDG_DATA_DIRS");

    if (!path)
      return std::nullopt;

    for (const auto &part :
         std::views::split(std::string_view(path), std::string_view(":"))) {
      std::filesystem::path path = std::string_view(part);
      std::filesystem::path resourceDir = path / "soulver-cpp" / "resources";

      if (std::filesystem::is_directory(resourceDir))
        return resourceDir;
    }

    return std::nullopt;
  }
  bool initialized = false;
};

}; // namespace SoulverCore
