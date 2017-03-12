#pragma once
namespace game_framework {
   

    class Button
    {
    public:
        Button();
        Button(int sn);
        void LoadBitmap();										
        void OnShow();											
        void SetXY(int nx, int ny);								
        void SetEnable(bool e);
        void OnClick(CPoint point);
        void OnNoClick();
        void OnMove(CPoint point);
        void Setcga(CGameState* c);
    protected:
        int n;
        int x, y;
        CMovingBitmap bmp[2];
        bool enable;
        int state;
        //
        CGameState* cga;
    private:
       
    };
}