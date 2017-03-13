namespace game_framework {
    class Dice
    {
    public:
        Dice();
        void Initialize();				// �]�w���l����l��
        void LoadBitmap();				// ���J�ϧ�
        void OnRoll();					// �Y��l
        void OnShow();					// �N���l�ϧζK��e��
        void SetStartRoll(bool flag);	    // �]�w�O�_�}�l��
        void SetXY(int nx, int ny);		// �]�w���l���W���y��
    protected:
        CAnimation animation;		// ���l���ʵe
        int x, y;					// ���l���W���y��
        bool isStartRoll;			// �O�_���}�l��
    };
}
