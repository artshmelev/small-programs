#include "header.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Player::Player()
{
}

Player::Player(bool st, char ch)
{
    state = st;
    sign = ch;
}

bool Player::GetState()
{
    return state;
}

char Player::GetSign()
{
    return sign;
}

void Player::SetState(bool b)
{
    state = b;
}

void Player::SetSign(char c)
{
    sign = c;
}

void Player::Go(char map[3][3])
{
    srand(time(NULL));
    int x = rand() % 3,
        y = rand() % 3;
    while (map[y][x] != '.')
    {
        x = rand() % 3;
        y = rand() % 3;
    }
    map[y][x] = sign;
}

void Player::Go(char map[3][3], int x, int y)
{
    map[y-1][x-1] = sign;
}

Game::Game()
{
    result = 0;
    char ch;
    std::cout << "First or Second?(f/s): ";
    std::cin >> ch;
    players[0].SetState(0);
    players[1].SetState(1);
    if (ch == 'f')
    {
        current = 0;
        players[0].SetSign('X');
        players[1].SetSign('O');
    }
    else
    {
        current = 1;
        players[0].SetSign('O');
        players[1].SetSign('X');
    }
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++) map[i][j] = '.';
}

int Game::Init()
{
    PrintMap();
    while (!GetResult())
    {
        if (players[current].GetState() == 0)
        {
            int x, y;
            std::cout << "Enter your turn (x, y): ";
            std::cin >> x >> y;
            while (x < 1 || y < 1 || x > 3 || y > 3 ||
                   map[y-1][x-1] != '.')
            {
                std::cout << "INCORRECT TURN\n";
                std::cout << "Enter your turn (x, y): ";
                std::cin >> x >> y;
            }
            players[current].Go(map, x, y);
        }
        else
        {
            players[current].Go(map);
        }
        current ^= 1;
        PrintMap();
    }
    return GetResult();
}

void Game::PrintMap()
{
    system("clear");
    std::cout << " ";
    for (int i=0; i<3; i++) std::cout << i+1;
    std::cout << "\n";
    for (int i=0; i<3; i++)
    {
        std::cout << i+1;
        for (int j=0; j<3; j++) std::cout << map[i][j];
        std::cout << "\n";
    }
    std::cout << "\n";
}

int Game::GetResult()
{
    if (map[0][0] == map[0][1] && map[0][0] == map[0][2])
    {
        if (map[0][0] == 'X') return 1;
        else
            if (map[0][0] == 'O') return 2;
    }
    if (map[1][0] == map[1][1] && map[1][0] == map[1][2])
    {
        if (map[1][0] == 'X') return 1;
        else
            if (map[1][0] == 'O') return 2;
    }
    if (map[2][0] == map[2][1] && map[2][0] == map[2][2])
    {
        if (map[2][0] == 'X') return 1;
        else
            if (map[2][0] == 'O') return 2;
    }
    if (map[0][0] == map[1][0] && map[0][0] == map[2][0])
    {
        if (map[0][0] == 'X') return 1;
        else
            if (map[0][0] == 'O') return 2;
    }
    if (map[0][1] == map[1][1] && map[0][1] == map[2][1])
    {
        if (map[0][1] == 'X') return 1;
        else
            if (map[0][1] == 'O') return 2;
    }
    if (map[0][2] == map[1][2] && map[0][2] == map[2][2])
    {
        if (map[0][2] == 'X') return 1;
        else
            if (map[0][2] == 'O') return 2;
    }
    if (map[0][0] == map[1][1] && map[0][0] == map[2][2])
    {
        if (map[0][0] == 'X') return 1;
        else
            if (map[0][0] == 'O') return 2;
    }
    if (map[2][0] == map[1][1] && map[2][0] == map[0][2])
    {
        if (map[2][0] == 'X') return 1;
        else
            if (map[2][0] == 'O') return 2;
    }
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (map[i][j] == '.') return 0;
    return 3;
}
