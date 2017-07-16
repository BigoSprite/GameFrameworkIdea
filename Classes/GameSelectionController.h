#pragma once

#include "cocos2d.h"
#include "BaseController.h"

USING_NS_CC;

class GameSelectionController : public BaseController
{
public:
	GameSelectionController();
	~GameSelectionController();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameSelectionController);


	void gameStart1(Ref * r);
	void gameStart2(Ref * r);

	//�ص����˵�
	void mainMenu(cocos2d::Ref * r);


	//��Ч����
	void particleEffect(Point pos);

private:
	Sprite* m_pBackgroundSprite;
	Label * menuTitle1;
	Label * menuTitle2;
	float vy_girl1; //����y���ٶ�



};
