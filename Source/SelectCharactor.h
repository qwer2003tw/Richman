#pragma once
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
class SelectCharactor
{
public:

    static SelectCharactor* getInstance();
    void setData(int input[4]);
    int* getCharactor();
protected:
    SelectCharactor();
    int charactor[4];
};

