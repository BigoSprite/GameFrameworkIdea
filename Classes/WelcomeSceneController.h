#pragma once
#include "BaseController.h"
#include "cocos2d.h"
USING_NS_CC;

class WelcomeSceneController : public BaseController
{
public:
	WelcomeSceneController();
	~WelcomeSceneController();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeSceneController);

private:
	// 初始化存档信息
	void __initSaveFileInfo();

private:
	Sprite* m_pBackgroundSprite;
	Label* m_pTitle;

	void _gameStartCallback(Ref *pRef);
	void _enterShopCallback(Ref *pRef);
	void _quitGameCallback(Ref *pRef);
};
