#pragma once

// piece color: white and black
#include <cctype>
#include <iostream>
#include <map>
#include <string>

enum class Color { White, Black, Unknown };
static std::map<Color, std::string> ViewColor{{Color::White, "Wihte"},
                                              {Color::Black, "Black"},
                                              {Color::Unknown, "Unknown"}};

enum class Type { King, Pawn, Queen, Knight, Rook, Bishop, Unknown };
static std::map<Type, std::string> ViewType{
    {Type::King, "King"},      {Type::Pawn, "Pawn"}, {Type::Queen, "Queen"},
    {Type::Knight, "Knight"},  {Type::Rook, "Rook"}, {Type::Bishop, "Bishop"},
    {Type::Unknown, "Unknown"}};

static std::map<const char, Type> Symbol2Type{
    {'K', Type::King}, {'P', Type::Pawn},   {'N', Type::Knight},
    {'R', Type::Rook}, {'B', Type::Bishop}, {'Q', Type::Queen}};

using coord = unsigned int;

static auto isUpper = [](char c) { return c >= 'A' && c <= 'Z'; };
static auto isNum = [](char c) { return c >= '0' && c <= '9'; };
static auto isLower = [](char c) { return c >= 'a' && c <= 'z'; };
static auto isPieceSymbol = [](char c) { return isLower(c) || isUpper(c); };

class Piece {
public:
  Piece();
  Piece(Color c, Type t);
  Piece(const char symbol);
  Piece(Piece &&) = default;
  Piece(const Piece &) = default;
  Piece &operator=(Piece &&) = default;
  Piece &operator=(const Piece &) = default;
  ~Piece();

  bool isValidPiece() {
    return color != Color::Unknown && type != Type::Unknown;
  }

  //   virtual bool moveTo(coord m) = 0;

  friend std::ostream &operator<<(std::ostream &in, const Piece &piece) {
    return in << ViewColor[piece.color] << " " << ViewType[piece.type];
  }

  std::ostream &viewInBoard(std::ostream &in, coord loc = 0) const {

    char symbol = ViewType[type][0];
    if (type == Type::Knight)
      symbol = 'n';
    // std::cout << " symbol is " << symbol << std::endl;
    switch (color) {
    case Color::White:
      return in << static_cast<char>(std::toupper(symbol));
    case Color::Black:
      return in << static_cast<char>(std::tolower(symbol));
    case Color::Unknown:
      return in << " ";
    default:
      return in << " ";
    };
  }

private:
  Color color = Color::Unknown;
  Type type = Type::Unknown;
};

Piece::Piece() {}
Piece::Piece(Color c, Type t) : color(c), type(t) {}
Piece::Piece(const char symbol) {
  Color c;
  if (isUpper(symbol)) {
    c = Color::White;
  } else if (isLower(symbol)) {
    c = Color::Black;
  } else {
    c = Color::Unknown;
  }
  color = c;

  char upper_symbol = std::toupper(symbol);
  type = Symbol2Type[std::toupper(symbol)];
}

Piece::~Piece() {}