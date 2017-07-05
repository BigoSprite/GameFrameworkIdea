#pragma once

#include "cocos2d.h"
#include "BaseController.h"

USING_NS_CC;

class GameSelectionController : public BaseController
{
public:
	GameSelectionController();
	~GameSelectionController();
	CREATE_FUNC(GameSelectionController);

	virtual bool init();
	static cocos2d::Scene* createScene();


	void gameStart1(cocos2d::Ref * r);
	void gameStart2(cocos2d::Ref * r);

	//�ص����˵�
	void mainMenu(cocos2d::Ref * r);

	//�����ƶ�����
	void move(float dt);

private:
	Sprite* m_pBackgroundSprite;
	cocos2d::Label * menuTitle1;
	cocos2d::Label * menuTitle2;
	float vy_girl1; //����y���ٶ�
	Sprite* girl;



};
