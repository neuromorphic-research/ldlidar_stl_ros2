#pragma once

#include <cmath>

// Bounds use sensor-native degrees, before LaserScan index reversal.
inline bool validSelfMask(double low, double high, double distance) {
  return std::isfinite(low) && std::isfinite(high) && std::isfinite(distance) &&
         low >= 0.0 && low <= high && high <= 360.0 && distance >= 0.0;
}

inline bool validRangeBand(double low, double high) {
  return std::isfinite(low) && std::isfinite(high) && low >= 0.0 && high > low;
}

inline bool validSectors(double first, double second, double half_width) {
  return validSelfMask(first, first, half_width) &&
         validSelfMask(second, second, half_width) && half_width <= 180.0;
}

inline bool inRangeBand(double range, double low, double high) {
  return std::isfinite(range) && range >= low && range <= high;
}

inline bool maskedReturn(double angle, double range, bool legacy_sectors,
                         double self_low, double self_high, double self_distance,
                         double first = 90.0, double second = 270.0,
                         double half_width = 45.0) {
  if (legacy_sectors) {
    const double da = std::fabs(std::fmod(angle - first + 540.0, 360.0) - 180.0);
    const double db = std::fabs(std::fmod(angle - second + 540.0, 360.0) - 180.0);
    if (da > half_width && db > half_width) return true;
  }
  return self_distance > 0.0 && angle >= self_low && angle <= self_high &&
         std::isfinite(range) && range < self_distance;
}
