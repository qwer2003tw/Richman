#pragma once
namespace game_framework {
   

    class Button
    {
    public:
        Button();
        Button(int sn);
        void LoadBitmap(char* fileName1, char* fileName2, COLORREF colorkey); // fileName1未滑過 fileName2滑過
        void OnShow();											
        void SetXY(int nx, int ny);								
        void SetEnable(bool e);
        void OnClick(CPoint point);
        void OnNoClick();
        void OnMove(CPoint point);
        bool GetSignal();
    protected:
        int n;
        int x, y;
        CMovingBitmap bmp[2];
        bool enable;
        int state;
        bool signal;                    // 點擊Signal
    private:
       
    };
}