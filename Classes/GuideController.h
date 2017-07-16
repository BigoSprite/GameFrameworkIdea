#pragma once
#include "cocos2d.h"
#include "BaseController.h"
USING_NS_CC;

class GuideController : public BaseController
{
public:
	GuideController();
	~GuideController();

	virtual bool init();
	CREATE_FUNC(GuideController);

	static Scene* createScene();

	//NEXT介绍回调函数
	void nextIntro(cocos2d::Ref * r);

	void teemoMoving(std::string str, float girlPosY, cocos2d::Point destination);

	//萌妹上下移动函数
	void move(float dt);
	//开始游戏，删除layer
	void deleteLayer();
private:
	Size vs;
	float vy_girl; //萌妹y轴速度
	float girlPosY;//萌妹的y位置，因为move函数不能传递进pos参数
	Sprite * girl;
	//控制每一步的变量
	int progress;

	Label * m_pIntroDes;
	MenuItemSprite * next;
	Menu * menuNext;
};

