#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <config.h>
#include <initializer_list>
#include <tuple>
#include <vector>

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

class Movement : public std::vector<Move> {
public:
  inline Movement() {}
  inline Movement(const std::initializer_list<Move> &moves) : vector(moves) {}
};

#endif // MOVEMENT_H
