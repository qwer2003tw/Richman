namespace game_framework {
    class Number
    {
    public:
        Number();
        void Initialize();				// �]�w���l����l��
        void LoadBitmap();				// ���J�ϧ�
        void OnShow(int value);					// �N���l�ϧζK��e��
        void SetXY(int nx, int ny);		// �]�w���l���W���y��
    protected:
        CMovingBitmap digitbmp[10];
        int x, y;
    };
}

