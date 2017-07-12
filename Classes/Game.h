#ifndef _GAME_H_
#define _GAME_H_

#include "cocos2d.h"
#include "BaseController.h"

#include "ItemNotEnoughPrefab.h"

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

	// 道具不足时的提示框
	ItemNotEnoughPrefab* m_pItemNotEnoughSprite;

	//2个功能性道具
	MenuItemImage * changeIcon;
	MenuItemImage * bombIcon;
	//2个道具的数量以及label
	Label * changeIconLabel;
	Label * bombIconLabel;

	
	Sprite * girl;//每一关开始前介绍的女孩
	Sprite * transBg;
	Label * welcome;//欢迎来到
	Label * spots;//地点

	//ready go 飘字label
	Label * readyLabel;
	Label * goLabel;


	//每一关当前目标分数
	int target_score;
	int curLevel;
	Label * targetScore_label;
	Label * level_label;
	Label * levelNum_label;


	bool timerRunning;
	bool gameIsOver;


	Label * knowledge_label;
	Label * name_label;
	Sprite * small_pic;


	MenuItemImage * btm;//返回主菜单
	MenuItemImage * res;//重新开始

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


	PointArray *pointArray;//声明存放各个装备坐标的数组
						   
    //记录5个icon分别消去的个数的map
	std::map<int, int> icon_map;

	// 下一关
	Sprite* leftBonusBox;
	MenuItemImage* nextLevel;


	Vector<Sprite*> equip;//存放所有装备的数组
	Sprite* equipment[10][10];//存放装备的数组

};


#endif // _GAME_H_
