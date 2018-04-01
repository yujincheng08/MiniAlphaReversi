#ifndef CONFIG_H
#define CONFIG_H

#include <QVector>
#include <tuple>

namespace Config {
static unsigned constexpr SIZE = 8U;

enum Type : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e' };

static Type constexpr first = BLACK;

using InitPiece = std::tuple<size_t, size_t, Type>;

using Composition = QVector<QVector<Config::Type>>;

inline size_t xOf(InitPiece const &init) { return std::get<0>(init); }
inline size_t yOf(InitPiece const &init) { return std::get<1>(init); }
inline Type typeOf(InitPiece const &init) { return std::get<2>(init); }

inline Type operator~(Type const &type) {
  return type == BLACK ? WHITE : type != EMPTY ? BLACK : EMPTY;
}

inline bool operator!(Type const &type) { return type != EMPTY; }

static QVector<InitPiece> const initPieces = {
    {SIZE / 2U, SIZE / 2U, WHITE},
    {SIZE / 2U, SIZE / 2U - 1, BLACK},
    {SIZE / 2U - 1, SIZE / 2U, BLACK},
    {SIZE / 2U - 1, SIZE / 2U - 1, WHITE}};
} // namespace Config
#endif // CONFIG_H
