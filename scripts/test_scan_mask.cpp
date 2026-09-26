// Run: c++ -std=c++14 -Iinclude scripts/test_scan_mask.cpp -o /tmp/test_scan_mask && /tmp/test_scan_mask
#include "scan_mask.hpp"
#include <cassert>
#include <limits>

int main() {
  for (int a = 0; a <= 360; ++a) {
    const bool legacy = !((a >= 45 && a <= 135) || (a >= 225 && a <= 315));
    assert(maskedReturn(a, 0.4, true, 0, 0, 0) == legacy);
    assert(!maskedReturn(a, 0.4, false, 240, 260, 0.38));
    assert(maskedReturn(a, 0.35, false, 240, 260, 0.38) == (a >= 240 && a <= 260));
  }
  assert(!maskedReturn(250, 0.38, false, 240, 260, 0.38));
  assert(!maskedReturn(250, 0.35, false, 240, 260, 0));
  assert(validSelfMask(240, 260, 0.38));
  assert(!validSelfMask(260, 240, 0.38));
  assert(!validSelfMask(-1, 260, 0.38));
  assert(!validSelfMask(240, 361, 0.38));
  assert(!validSelfMask(240, 260, -0.38));
  assert(!validSelfMask(240, 260, std::numeric_limits<double>::infinity()));
}
