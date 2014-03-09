#ifndef header_h
#define header_h

#include <iostream>

class Game;
class Player;

class Player
{
public:
    Player();
    Player(bool, char);
    void Go(char[3][3]);
    void Go(char[3][3], int, int);
    bool GetState();
    char GetSign();
    void SetState(bool);
    void SetSign(char);
    inline Player& operator=(Player&);
private:
    bool state;
    char sign;
};

inline Player& Player::operator=(Player& p)
{
    state = p.state;
    sign = p.sign;
    return *this;
}

class Game
{
public:
    Game();
    int Init();
    int GetResult();
    void PrintMap();
private:
    int result;
    bool current;
    char map[3][3];
    Player players[2];
};

#endif
