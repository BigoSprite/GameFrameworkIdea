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

	void nextIntro(cocos2d::Ref * r);

	void teemoMoving(std::string str, float girlPosY, cocos2d::Point destination);

	void move(float dt);

	void deleteLayer();
private:
	Size vs;
	float vy_teemo; 
	float teemoPosY;
	Sprite * m_pTeemo;
	//控制每一步的变量
	int progress;

	Label * m_pIntroDes;
	MenuItemSprite * next;
	Menu * menuNext;
};

