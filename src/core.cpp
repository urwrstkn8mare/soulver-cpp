#include "core.hpp"
#include <cstdlib>
#include <expected>
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>
#include <ranges>

using namespace nlohmann;
using namespace SoulverCore;

namespace fs = std::filesystem;

Calculator::Calculator() {
  if (!soulver_is_initialized()) {
    initialize();
  }
}

bool Calculator::initialize() {
  auto resources = locateResourceDir();

  if (!resources)
    return false;

  soulver_initialize(resources->c_str());
  initialized = true;
  return true;
}

void Calculator::print(const std::string &expression) {
  auto res = calculate(expression);

  if (!res) {
    std::println(std::cerr, "Error: {}", res.error().error);
    return;
  }

  auto value = res.value();

  std::println(std::cout, "{} ({})", value.value, value.type);
}

CalculationResult Calculator::calculate(const std::string &expression) {
  char *ptr = soulver_evaluate(expression.c_str());
  std::string s(ptr);

  free(ptr);

  json data = json::parse(s);
  CalculationResultData result;

  result.value = data["value"];
  result.type = data["type"];

  return result;
}

std::optional<std::filesystem::path> Calculator::locateResourceDir() {
  const char *path = getenv("XDG_DATA_DIRS");

  if (!path)
    return std::nullopt;

  for (const auto &part :
       std::views::split(std::string_view(path), std::string_view(":"))) {
    fs::path path = std::string_view(part);
    fs::path resourceDir = path / "soulver-cpp" / "resources";

    if (fs::is_directory(resourceDir))
      return resourceDir;
  }

  return std::nullopt;
}
