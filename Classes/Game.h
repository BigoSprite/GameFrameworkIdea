#ifndef _GAME_H_
#define _GAME_H_

#include "cocos2d.h"
#include "BaseController.h"

#include "ItemNotEnoughPrefab.h"
#include "WelcomeDialogPrefab.h"
#include "BottomTexturePrefab.h"

USING_NS_CC;
 
class Game : public BaseController
{
public:
	Game();
	~Game();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Game);

	//���ߺ����� �ı�����
	void changeIconType(Ref * r);
	//���ߺ����� ��ըicon
	void bombIconType(Ref * r);

	//�ص����˵�
	void returnToMenu(cocos2d::Ref* r);
	//���¿�ʼ
	void restartGame(cocos2d::Ref* r);
	//ȥ��һ�غ���
	void goToNextLevel(Ref * r);


	//�������е���
	void generatePoint();
	//���װ��(10*10)
	void addEquipment();

	std::vector<int> icon;


	//�����Ϸ�Ƿ��������û��2��������װ��
	bool isGameOver();


	//��ʼ��ʱ����
	void startTimer();

	//������ʱ
	void endTimer();

	//��ʱ����
	virtual void update(float dt);


	//�õ���Ӧ��װ��
	Sprite* getEquipWithCoordinate(Sprite * e[][10], int row, int column);

	//�ҳ����ڵ�װ���ĺ���
	void findAdjacentEquip(int b[][10], int posX, int posY, int cur, bool single);

	//ȷ���Ƿ񵥶�һ��װ��
	bool isSingleIcon(int b[][10], int row, int column, int cur);

	//װ����ȥ��Ч
	void equipmentEffect(int boardValue, Point pos);
	void equipmentEffectWithNoGravity(int boardValue, Point pos);

	//���ƺ���
	void moveDown(int b[][10]);

	//�����ƶ��ĺ���
	void moveLeft(int b[][10]);


	//�滻iconʱ�Ķ�������
	void changeIconFlyAnimation(int temp, Point target);

	//�ɵ�����icon�ĺ�����0.2�����һ��,type��ʾ��row����column����
	void hitIconByMissile(int column, int row, int type);
	//�ɵ�����icon�õ��ķ���,һ��iconֻ��5�֣������ͱ�֤����Ƶ��ʹ�÷ɵ�
	void scoreGetFromMissile(int posX, int posY);

	void gameStep(float dt);




private:

	//ʤ����Ч
	void __winEffect(Point pos);
	//��Ϸ����ʱ�ݻ�ʣ�µķ���
	void __destoryRemaining();

private:
	Size visibleSize;
	Vec2 origin;


	bool firstHit;
	bool isGameOverHit;

	//ʣ�ཱ������
	std::vector<int> leftBonus;

	//ʣ�ཱ������
	std::vector<int> bonus_vec;

	int board[10][10];//ģ��ڷ�װ��������


	//2����������
	Sprite * tower1;
	Sprite * tower2;
	//2���ɵ�
	Sprite * missile1;
	Sprite * missile2;

	bool isGameReady;
	bool isTargetReached;

	/// ���߲���ʱ����ʾ��
	ItemNotEnoughPrefab* m_pItemNotEnoughSprite;

	//2�������Ե���
	MenuItemImage * changeIcon;
	MenuItemImage * bombIcon;
	//2�����ߵ������Լ�label
	Label * changeIconLabel;
	Label * bombIconLabel;



	WelcomeDialogPrefab* m_pWelcomeDialogPrefab;

	BottomTexturePrefab* m_pBottomTexturePrefab;




	//ÿһ�ص�ǰĿ�����
	int target_score;
	int curLevel;
	Label * targetScore_label;
	Label * level_label;
	Label * levelNum_label;

	//��ʱ��
	bool timerRunning;
	float startTime;//��Ϸ��ʼ��ʱ��
	bool gameIsOver;//��־��Ϸ�����ı���



    Label * label_score;//��ʾ�����Ŀؼ�
	int currentScore; // ��Ϸ��ǰ����


	//����ͳ��
	int statistic_LeftIcon;
	int statistic_LeftBonus;
	int statistic_SingleMost;
	int statistic_MostIcon;
	int four_kill;
	int five_kill;
	int six_kill;
	int seven_kill;
	int legendary_kill;
	double statistic_Time;

	//����ͳ�Ƶ�label��
	Label * title1;
	Label * title2;
	Label * title3;
	Label * title4;
	Label * title5;
	Label * title6;
	Label * title7;
	Label * title8;
	Label * title9;
	Label * title10;

	Label* leftIcon_label;
	Label* leftBonus_label;
	Label* singleMost_label;
	Label* mostIcon_label;
	Label* timer_label;
    Label* fourKill_label;
	Label* fiveKill_label;
	Label* sixKill_label;
	Label* sevenKill_label;
	Label* legendaryKill_label;

	Menu* menuNextLevel;
	Label* nextLevelLabel;


	PointArray *pointArray;//������Ÿ���װ�����������
						   
    //��¼5��icon�ֱ���ȥ�ĸ�����map
	std::map<int, int> icon_map;

	// ��һ��
	Sprite* leftBonusBox;
	MenuItemImage* nextLevel;


	Vector<Sprite*> equip;//�������װ��������
	Sprite* equipment[10][10];//���װ��������


	
	int count;//����������������2����������
	int totalScore;//һ���������ܷ���
	Label * lb;
	Vector<Label*> vec_label;
	bool isDouble;
	int tempScore;


	Sprite * clear;
	Sprite * clear2;
	Sprite * gameEnd;
};


#endif // _GAME_H_
