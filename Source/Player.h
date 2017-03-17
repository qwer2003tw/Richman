#pragma once
namespace game_framework {
    class Player {
    public:
        Player();
        void LoadBitmap();										// ���J�ϧ�
        void OnMove(int x, int y);								// ����
        void OnShow();											// �N�ϧζK��e�� 
    protected:
        CMovingBitmap bmp;			// �y����
        int x, y;					// ��ߪ��y��
        int dx, dy;					// �a�Ϫ��y��
        int index;					// �y���u���סv�A0-17���0-360��
    private:
        void SetXY();               // �]�w�H�����ߪ��y��
    };
}
