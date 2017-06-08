#pragma once
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
class SelectCharactor
{
public:
    SelectCharactor(int c0, int c1, int c2, int c3);
    SelectCharactor();
    ~SelectCharactor();

    static SelectCharactor* setInstance(int input[4]);
    static SelectCharactor* getInstance();
    static SelectCharactor* instance;
    int charactor[4];
};

