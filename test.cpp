#include "board.h"
#include <iostream>

int main(int argc, const char **argv) {
  Piece w_king(Color::White, Type::King);
  w_king.isValidPiece();

  Piece invalid_piece(Color::Unknown, Type::Unknown);
  invalid_piece.isValidPiece();

  Piece pieces[]{w_king, invalid_piece};
  for (auto &e : pieces) {
    if (e.isValidPiece())
      std::cout << "piece is: " << e << std::endl;
  }

  Board b;
  std::cout << "board is: " << b << std::endl;

  return 0;
}
