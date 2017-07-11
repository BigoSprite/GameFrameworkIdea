#pragma once

#include "cocos2d.h"
#include "BaseController.h"

USING_NS_CC;

class GameSelectionController : public BaseController
{
public:
	GameSelectionController();
	~GameSelectionController();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameSelectionController);


	void gameStart1(cocos2d::Ref * r);
	void gameStart2(cocos2d::Ref * r);

	//�ص����˵�
	void mainMenu(cocos2d::Ref * r);

	//�����ƶ�����
	void move(float dt);

	//��Ч����
	void particleEffect(Point pos);

private:
	Sprite* m_pBackgroundSprite;
	Label * menuTitle1;
	Label * menuTitle2;
	float vy_girl1; //����y���ٶ�
	Sprite* girl;



};
