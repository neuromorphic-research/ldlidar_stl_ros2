#pragma once

#include <cmath>

// Bounds use sensor-native degrees, before LaserScan index reversal.
inline bool validSelfMask(double low, double high, double distance) {
  return std::isfinite(low) && std::isfinite(high) && std::isfinite(distance) &&
         low >= 0.0 && low <= high && high <= 360.0 && distance >= 0.0;
}

inline bool maskedReturn(double angle, double range, bool legacy_sectors,
                         double self_low, double self_high, double self_distance) {
  if (legacy_sectors) {
    const double da = std::fabs(std::fmod(angle - 90.0 + 540.0, 360.0) - 180.0);
    const double db = std::fabs(std::fmod(angle - 270.0 + 540.0, 360.0) - 180.0);
    if (da > 45.0 && db > 45.0) return true;
  }
  return self_distance > 0.0 && angle >= self_low && angle <= self_high &&
         std::isfinite(range) && range < self_distance;
}
