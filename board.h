#pragma once

#include "piece.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#define BOARD_SIZE 8
#define FEN_SIZE (BOARD_SIZE) * (BOARD_SIZE)
using coord_xy = std::pair<coord, coord>;
using fen = const std::string;
fen INIT_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

class Board {
public:
  Board();
  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;
  ~Board();

  coord_xy coordToXY(coord m) {
    coord x = std::floor(m / board_size_);
    coord y = m - board_size_ * x;
    return {x, y};
  }

  void setPieceAt(const Piece &in_piece, coord m) {
    auto [x, y] = coordToXY(m);
    board_[x][y] = in_piece;
  }

  void setPieceWhenFenMeetSymbol(const char symbol, size_t &piece_loc) {
    // std::cout << "symbol is: " << symbol << std::endl;
    Piece p(symbol);
    setPieceAt(p, piece_loc++);
  }

  void setPieceWhenFenMeetNum(const char symbol, const fen &board_fen,
                              size_t &idx, size_t &piece_loc) {
    std::string char_num{symbol};
    char char_after_num = board_fen[idx + 1];

    if (isNum(char_after_num)) {
      char_num += char_after_num;
      idx++;
    }

    size_t skip_num = std::atoi(char_num.c_str());
    if (skip_num > BOARD_SIZE) {
      std::cout << "invalid fen..." << std::endl;
      return;
    }

    for (size_t _ = 0; _ < skip_num; _++) {
      setPieceWhenFenMeetSymbol(' ', piece_loc);
    }
  }

  void setFenToBoard(fen board_fen) {
    // std::cout << "fen is: " << board_fen << std::endl;
    size_t size = board_fen.length();
    size_t idx = 0;
    size_t piece_loc = 0;
    while (idx < size) {
      char c = board_fen[idx];
      if (isPieceSymbol(c)) {
        setPieceWhenFenMeetSymbol(c, piece_loc);
      } else if (c == '/') { // isFenSplitorForRow
        // std::cout << "idx is : " << idx << " when meet /" << std::endl;
      } else if (isNum(c)) {
        setPieceWhenFenMeetNum(c, board_fen, idx, piece_loc);
      }
      idx++;
    }
  }

  bool initBoard() {
    Piece w_king(Color::White, Type::King);
    setPieceAt(w_king, 0);
    setPieceAt(w_king, 2);
    setPieceAt(w_king, 4);
    setPieceAt(w_king, 8);
    setPieceAt(w_king, 54);
    setPieceAt(w_king, 60);
    return true;
  }

  bool initBoard(fen fen) {
    setFenToBoard(fen);
    return true;
  }

  bool resetBoard();
  bool movePieceTo(Piece p, coord move_target);

  friend std::ostream &operator<<(std::ostream &in, const Board &board) {
    in << "\n--------------\n";
    in << "   12345678 \n";
    coord row_idx = 1;

    for (const auto &row : board.board_) {
      in << " " << std::to_string(row_idx) << " ";
      for (const auto &piece : row) {
        piece.viewInBoard(in);
      }
      in << " " << std::to_string(row_idx) << " ";
      in << "\n";
      row_idx++;
    }

    in << "   12345678 \n";
    in << "--------------\n";
    return in;
  }

private:
  int board_size_ = BOARD_SIZE;
  std::vector<std::vector<Piece>> board_;
};

Board::Board() {
  board_.resize(board_size_);

  for (auto &e : board_)
    e.resize(board_size_);

  initBoard(INIT_FEN);
}

Board::~Board() {}