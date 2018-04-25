#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <initializer_list>
#include <tuple>
#include <vector>
#include "config.h"

namespace Config {
enum Type : char;
}

class Move : public std::tuple<size_t, size_t, Config::Type> {
 public:
  inline Move(size_t const &x, size_t const &y, Config::Type const &t)
      : tuple({x, y, t}) {}
  inline decltype(auto) x() const { return std::get<0>(*this); }
  inline decltype(auto) y() const { return std::get<1>(*this); }
  inline decltype(auto) type() const { return std::get<2>(*this); }
};

#endif  // MOVEMENT_H
