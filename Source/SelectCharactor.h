#pragma once
class SelectCharactor
{
public:
    int charactor[4];

    static SelectCharactor* setInstance(int input[4]);
    static SelectCharactor* getInstance();

    static SelectCharactor* instance;


private:
    SelectCharactor(int c0, int c1, int c2, int c3);
    SelectCharactor();
    ~SelectCharactor();
};

