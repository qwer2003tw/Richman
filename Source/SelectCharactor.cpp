#include "stdafx.h"
#include "SelectCharactor.h"





SelectCharactor * SelectCharactor::setInstance(int input[4])
{
    instance = nullptr;
    instance = new SelectCharactor(input[0], input[1], input[2], input[3]);
    return instance;
}

SelectCharactor * SelectCharactor::getInstance()
{
    return instance;
}

SelectCharactor::SelectCharactor(int c0, int c1, int c2, int c3)
{
    charactor[0] = c0;
    charactor[1] = c1;
    charactor[2] = c2;
    charactor[3] = c3;
}

SelectCharactor::SelectCharactor()
{
    for (int i = 0; i < 4; i++) charactor[i] = 0;
}
