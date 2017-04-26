namespace game_framework {
    class Dice
    {
    public:
        Dice();
        void Initialize();				// �]�w���l����l��
        void LoadBitmap();				// ���J�ϧ�
        void OnShow();					// �N���l�ϧζK��e��
        void OnShow(double size);
        void OnMove();
        void SetXY(int nx, int ny);		// �]�w���l���W���y��
        void OnLButtonDown();
        void RandomValue();
        int GetValue();
        bool GetState();
        int GetPlayerRun();
        void SetPlayerRun(int set);
		void SetValue(int value);
    protected:
        
        CMovingBitmap dicebmp[6];
        int x, y, value, state, count, stops;					// ���l���W���y��
        int playerRun;
        //state 0 stop
        //state 1 run
        bool isStartRoll;			// �O�_���}�l��
    };
}
