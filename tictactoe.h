#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>

enum class SymbolType {None, X = 1, O = 2};

struct Point
{
    int x;
    int y;
};

class Game
{
    private:
        Board m_board;
        SymbolType m_player;

        int m_move_count;

    private:
        bool makeMove();
        Point inputMove();

    public:
        Game();
        ~Game() = default;

        void startGame();
};

class Board
{
    private:
        std::vector<std::vector<SymbolType>> m_matrix;

    public:
        Board();
        ~Board() = default;

        void setSymbol(Point coord, SymbolType sym);
        SymbolType getSymbol(Point coord) const;
        
        bool checkWin(Point coord, SymbolType sym) const;

        void printBoard();
};

#endif