#pragma once
namespace game_framework {
    class Player {
    public:
        Player();
        void LoadBitmap();							// ���J�ϧ�
        void OnMove();					            // ����
        void OnShow(int sx, int sy);				// �N�ϧζK��e�� 
        int GetMapX();                              // ���o�H���a�Ϯy�� X
        int GetMapY();                              // ���o�H���a�Ϯy�� Y
        void SetPositionNum(int amount);            // �]�w�Ӧ��֥[�I��
        void SetState(int ns);                      // �]�w���A
    protected:
        CMovingBitmap bmp;			                // �H���Ϥ�
        int dx, dy;					                // �H���a�Ϯy��
    private:
        int positionX[36], positionY[36];           // 
        int prePositionNum;                         // �e�@����m�I��
        int positionNum;                            // ��m�I��
        int state;                                  // 0�H�����ʪ��A 1�H�����ʪ��A
    };
}
