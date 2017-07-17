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

	//道具函数： 改变种类
	void changeIconType(Ref * r);
	//道具函数： 爆炸icon
	void bombIconType(Ref * r);

	//回到主菜单
	void returnToMenu(cocos2d::Ref* r);
	//重新开始
	void restartGame(cocos2d::Ref* r);
	//去下一关函数
	void goToNextLevel(Ref * r);


	//生产所有点阵
	void generatePoint();
	//添加装备(10*10)
	void addEquipment();

	std::vector<int> icon;


	//检测游戏是否结束：即没有2个相连的装备
	bool isGameOver();


	//开始计时函数
	void startTimer();

	//结束计时
	void endTimer();

	//计时方法
	virtual void update(float dt);


	//得到相应的装备
	Sprite* getEquipWithCoordinate(Sprite * e[][10], int row, int column);

	//找出相邻的装备的函数
	void findAdjacentEquip(int b[][10], int posX, int posY, int cur, bool single);

	//确定是否单独一个装备
	bool isSingleIcon(int b[][10], int row, int column, int cur);

	//装备消去特效
	void equipmentEffect(int boardValue, Point pos);
	void equipmentEffectWithNoGravity(int boardValue, Point pos);

	//下移函数
	void moveDown(int b[][10]);

	//向左移动的函数
	void moveLeft(int b[][10]);


	//替换icon时的动画函数
	void changeIconFlyAnimation(int temp, Point target);

	//飞弹击碎icon的函数，0.2秒击碎一个,type表示是row还是column消除
	void hitIconByMissile(int column, int row, int type);
	//飞弹击碎icon得到的分数,一个icon只加5分，这样就保证不会频繁使用飞弹
	void scoreGetFromMissile(int posX, int posY);

	void gameStep(float dt);




private:

	//胜利特效
	void __winEffect(Point pos);
	//游戏结束时摧毁剩下的方块
	void __destoryRemaining();

private:
	Size visibleSize;
	Vec2 origin;


	bool firstHit;
	bool isGameOverHit;

	//剩余奖励数组
	std::vector<int> leftBonus;

	//剩余奖励数组
	std::vector<int> bonus_vec;

	int board[10][10];//模拟摆放装备的数组


	//2个激光炮塔
	Sprite * tower1;
	Sprite * tower2;
	//2个飞弹
	Sprite * missile1;
	Sprite * missile2;

	bool isGameReady;
	bool isTargetReached;

	/// 道具不足时的提示框
	ItemNotEnoughPrefab* m_pItemNotEnoughSprite;

	//2个功能性道具
	MenuItemImage * changeIcon;
	MenuItemImage * bombIcon;
	//2个道具的数量以及label
	Label * changeIconLabel;
	Label * bombIconLabel;



	WelcomeDialogPrefab* m_pWelcomeDialogPrefab;

	BottomTexturePrefab* m_pBottomTexturePrefab;




	//每一关当前目标分数
	int target_score;
	int curLevel;
	Label * targetScore_label;
	Label * level_label;
	Label * levelNum_label;

	//计时器
	bool timerRunning;
	float startTime;//游戏开始的时间
	bool gameIsOver;//标志游戏结束的变量



    Label * label_score;//显示分数的控件
	int currentScore; // 游戏当前分数


	//数据统计
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

	//数据统计的label们
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


	PointArray *pointArray;//声明存放各个装备坐标的数组
						   
    //记录5个icon分别消去的个数的map
	std::map<int, int> icon_map;

	// 下一关
	Sprite* leftBonusBox;
	MenuItemImage* nextLevel;


	Vector<Sprite*> equip;//存放所有装备的数组
	Sprite* equipment[10][10];//存放装备的数组


	
	int count;//消除计数器：至少2个才能消除
	int totalScore;//一次消除的总分数
	Label * lb;
	Vector<Label*> vec_label;
	bool isDouble;
	int tempScore;


	Sprite * clear;
	Sprite * clear2;
	Sprite * gameEnd;
};


#endif // _GAME_H_
