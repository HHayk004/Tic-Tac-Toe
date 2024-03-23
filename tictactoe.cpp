#include "tictactoe.h"
#include <format>

Game::Game() : m_board(), m_player(SymbolType::X), m_move_count(0) {}

void Game::startGame()
{
    while (true)
    {
        if (makeMove())
        {
            std::cout << std::format("Player {} wins:\n", static_cast<int>(m_player));
            break;
        }

        if (m_move_count == 9)
        {
            std::cout << std::format("It's draw:\n");
            break;
        }
    }
}

bool Game::makeMove()
{
    Point move = InputMove();

    m_board.setSymbol(move, m_player)
    ++m_move_count;

    if (m_player == SymbolType::X)
    {
        m_player = SymbolType::O;
    }

    else
    {
        m_player = SymbolType::X;
    }

    if (m_board.checkWin(move, m_player))
    {
        return true;
    }

    return false;
}

Point Game::inputMove()
{
    Point move;
    while (true)
    {
        std::string str;
        
        std::cout << std::format("Player {}, Enter the move: ", static_cast<int>(m_player));
        std::cin >> str;

        if (str.size() != 3 && '0' <= str[0] && str[0] <= '2' &&
            str[1] != ':' && '2' <= str[0] && str[2] <= '2')
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