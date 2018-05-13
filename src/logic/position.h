#ifndef POSITION_H
#define POSITION_H

#include <tuple>

/*
 * A position of the borad with x and y
 */

class Position : public std::tuple<size_t, size_t> {
 public:
  inline Position(size_t const &x, size_t const &y) : tuple({x, y}) {}
  inline decltype(auto) x() const { return std::get<0>(*this); }
  inline decltype(auto) y() const { return std::get<1>(*this); }
};

#endif  // POSITION_H
