#include "tictactoe.h"
#include <format>
#include <stdlib.h>

Game::Game() : m_board(), m_player(SymbolType::X), m_move_count(0) {}

void Game::startGame()
{
    while (true)
    {
        if (makeMove())
        {
            system("clear");
            m_board.printBoard();
            std::cout << std::format("Player {} wins:\n", static_cast<int>(m_player));
            break;
        }

        if (m_move_count == 9)
        {
            system("clear");
            m_board.printBoard();
            std::cout << std::format("It's draw:\n");
            break;
        }
    }
}

bool Game::makeMove()
{
    Point move = inputMove();

    m_board.setSymbol(move, m_player);
    ++m_move_count;

    if (m_board.checkWin(move, m_player))
    {
        return true;
    }

    if (m_player == SymbolType::X)
    {
        m_player = SymbolType::O;
    }

    else
    {
        m_player = SymbolType::X;
    }

    return false;
}

Point Game::inputMove()
{
    Point move;
    while (true)
    {
        system("clear");
        m_board.printBoard();
        std::string str;
        
        std::cout << std::format("Player {}, Enter the move: ", static_cast<int>(m_player));
        std::cin >> str;

        if (str.size() == 3 && '0' <= str[0] && str[0] <= '2' &&
            str[1] == ':' && '0' <= str[0] && str[2] <= '2')
        {
            move.x = str[0] - '0';
            move.y = str[2] - '0';
        }

        else
        {
            continue;
        }

        if (m_board.getSymbol(move) == SymbolType::None)
        {
            break;
        }
    }
    
    return move;
}

Board::Board() : m_matrix(3, std::vector<SymbolType>(3, SymbolType::None)) {}

void Board::setSymbol(Point coord, SymbolType sym)
{
    m_matrix[coord.x][coord.y] = sym;
}

SymbolType Board::getSymbol(Point coord) const
{
    return m_matrix[coord.x][coord.y];
}

bool Board::checkWin(Point coord, SymbolType sym) const
{
    Point dir[4][2] = {
        {{0, -1}, {0, 1}},
        {{-1, 1}, {1, -1}},
        {{-1, 0}, {1, 0}},
        {{-1, -1}, {1, 1}}
    };

    for (int i = 0; i < 4; ++i)
    {
        int sym_count_line = 1;
        for (int j = 0; j < 2; ++j)
        {
            int x = coord.x;
            int y = coord.y;
            while (0 <= x + dir[i][j].x && x + dir[i][j].x <= 2 &&
                   0 <= y + dir[i][j].y && y + dir[i][j].y <= 2 &&
                   m_matrix[x + dir[i][j].x][y + dir[i][j].y] == m_matrix[coord.x][coord.y])
            {
                x += dir[i][j].x;
                y += dir[i][j].y;
                ++sym_count_line;                
            }
        }

        if (sym_count_line == 3)
        {
            return true;
        }
    }

    return false;
}

void Board::printBoard() const
{
    for (int i = 0; i < m_matrix.size() * 4 + 1; ++i)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < m_matrix.size(); ++i)
    {
        for (int j = 0; j < m_matrix.size(); ++j)
        {
            switch (m_matrix[i][j])
            {
                case SymbolType::None:
                    std::cout << "|   "; 
                    break;

                case SymbolType::X:
                    std::cout << "| X "; 
                    break;

                case SymbolType::O:
                    std::cout << "| O "; 
                    break;
            }
        }

        std::cout << "|\n";

        for (int i = 0; i < m_matrix.size() * 4 + 1; ++i)
        {
            std::cout << "-";
        }
        std::cout << std::endl;
    }   
}