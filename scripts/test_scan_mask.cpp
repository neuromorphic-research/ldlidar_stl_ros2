// Run: c++ -std=c++14 -Iinclude scripts/test_scan_mask.cpp -o /tmp/test_scan_mask && /tmp/test_scan_mask
#include "scan_mask.hpp"
#include <cassert>
#include <limits>

int main() {
  assert(validRangeBand(0.32, 0.60));
  assert(!validRangeBand(0.6, 0.32));
  assert(!validRangeBand(0.32, 0.32));
  assert(!validRangeBand(-0.1, 1));
  assert(!validRangeBand(0, std::numeric_limits<double>::infinity()));
  assert(!validRangeBand(std::numeric_limits<double>::quiet_NaN(), 1));
  assert(inRangeBand(0.32, 0.32, 0.60));
  assert(inRangeBand(0.60, 0.32, 0.60));
  assert(!inRangeBand(0.61, 0.32, 0.60));
  assert(!inRangeBand(0.31, 0.32, 0.60));
  assert(!inRangeBand(std::numeric_limits<double>::quiet_NaN(), 0, 1));
  assert(validSectors(0, 180, 10));
  assert(!validSectors(361, 180, 10));
  assert(!validSectors(0, 180, 181));
  assert(!validSectors(0, 180, -1));
  assert(!maskedReturn(355, 0.4, true, 0, 0, 0, 0, 180, 10));
  assert(!maskedReturn(10, 0.4, true, 0, 0, 0, 0, 180, 10));
  assert(maskedReturn(11, 0.4, true, 0, 0, 0, 0, 180, 10));
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
