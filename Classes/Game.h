#ifndef _GAME_H_
#define _GAME_H_

#include "cocos2d.h"
#include "BaseController.h"

USING_NS_CC;
 
class Game : public BaseController
{
public:
	Game();
	~Game();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Game);


	//warning回调函数
	void warningCallback(cocos2d::Ref *r);

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

private:
	Size visibleSize;
	Vec2 origin;

	//2个激光炮塔
	Sprite * tower1;
	Sprite * tower2;

	bool isGameReady;
	bool isTargetReached;



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
};


#endif // _GAME_H_
