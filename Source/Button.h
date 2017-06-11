#pragma once
namespace game_framework {
   

    class Button
    {
    public:
        Button();
        Button(int sn);
        void LoadBitmap(char* fileName1, char* fileName2, COLORREF colorkey); // fileName1���ƹL fileName2�ƹL
        void OnShow();											
        void SetXY(int nx, int ny);								
        void SetEnable(bool e);
        void OnClick(CPoint point);
        void OnNoClick();
        void OnMove(CPoint point);
        int GetSignal();
        void SetSignal(int s);
    protected:
        int n;         //���s���Ϊ�
        int x, y;
        CMovingBitmap bmp[2];
        bool enable;
        int state;
        int signal;                    // �I��Signal
    };
}