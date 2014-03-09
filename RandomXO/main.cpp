#include "header.h"

#include <iostream>

int main()
{
    Game g;
    int res = g.Init();
    if (res == 1) std::cout << "X wins\n";
    else
        if (res == 2) std::cout << "O wins\n";
        else std::cout << "Draw\n";
    return 0;
}
