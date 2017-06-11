#include "stdafx.h"
#include "SelectCharactor.h"

void SelectCharactor::setData(int input[4])
{
    charactor[0] = input[0];
    charactor[1] = input[1];
    charactor[2] = input[2];
    charactor[3] = input[3];
}

int * SelectCharactor::getCharactor()
{
    return charactor;
}

SelectCharactor * SelectCharactor::getInstance()
{
    static SelectCharactor instance;
    return &instance;
}

SelectCharactor::SelectCharactor()
{
    for (int i = 0; i < 4; i++) charactor[i] = 0;
}

