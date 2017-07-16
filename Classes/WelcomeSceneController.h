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
	// ��ʼ���浵��Ϣ
	void __initSaveFileInfo();

private:
	float vy;  //y�������ƶ��ٶ�
	float vx;  //x�������ƶ��ٶ�

	Sprite* m_pBackgroundSprite;
	//Sprite* m_pBackgroundSprite2;
	//Sprite* m_pCloudSprite;

	Label* m_pMenuTitle1;
	Label* m_pMenuTitle2;
	Label* m_pMenuTitle3;
	Label* m_pTitle1;
	Label* m_pTitle2;
	Label* m_pTitle3;

	void _gameStartCallback(cocos2d::Ref *pSender);
	void _gameEndCallback(cocos2d::Ref *pSender);
	void _gameOptionCallback(cocos2d::Ref *pSender);


	void _particleEffect(Point point);
};
