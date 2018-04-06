# endian_swapper
Simple one-header code for swapping endiannes

# Usage:

```
#include "endian_swapper.hpp"

std::uint8_t x0;
std::uint16_t x1;
std::uint32_t x2;
std::uint64_t x3;

x0 = EndianSwapper::swap(x0);
x1 = EndianSwapper::swap(x1);
x2 = EndianSwapper::swap(x2);
x3 = EndianSwapper::swap(x3);
```

# Kudos to:
https://github.com/voidah/archive
