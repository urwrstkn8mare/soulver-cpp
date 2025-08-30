# soulver-cpp (WIP)

Simple C++ bindings for the [SoulverCore](https://github.com/soulverteam/SoulverCore) Swift library.

```cpp
#include <iostream>
#include <print>
#include <soulver-cpp/core.hpp>

int main() {
  SoulverCore::Calculator calc;
  auto res = calc.calculate("time in ny in 2 hrs in utc");

  if (!res) {
    std::println(std::cerr, "Error: {}", res.error().error);
    return 1;
  }

  auto data = res.value();

  std::println("{} ({})", data.value, data.type);
}

```

# Build

The `SoulverCore` library is closed-source and distributed as a shared library.

This repository contains a copy of this library, originally distributed by the [Flare](https://github.com/ByteAtATime/flare) project.

We build the `SoulverWrapper` Swift library which exposes C bindings we can call from C++ code.

## Prerequisites

- A working swift toolchain for Swift >= 6.1.0 (required at compile time and runtime).
- [nlohmann/json](https://github.com/nlohmann/json) library.

## Build

```
make
```

# Installation

```
sudo make install
```

If all of the above went well, you should be able to build the example repl:

```
make repl
```

# Acknowledgments

Thanks to the [Flare](https://github.com/ByteAtATime/flare) project for the `SoulverWrapper` and the Raycast currency provider: they made making these bindings way easier.
