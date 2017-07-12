#include "FinalSceneController.h"
#include "WelcomeSceneController.h"
#include "Messages.h"
FinalSceneController::FinalSceneController()
{
}

FinalSceneController::~FinalSceneController()
{
}

Scene* FinalSceneController::createScene()
{
	auto scene = Scene::create();
	auto layer = FinalSceneController::create();
	scene->addChild(layer);
	return scene;
}

bool FinalSceneController::init()
{
	if (!BaseController::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 添加视图
	m_pView = FinalSceneView::create();
	this->addChild(m_pView);

	// 订阅消息
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto customTrophyListener = EventListenerCustom::create(
		BACK_TO_WELCOME_SCENE_MSG,
		CC_CALLBACK_1(FinalSceneController::__onBack2WelcomeSceneMsgReceived, this));
	dispatcher->addEventListenerWithSceneGraphPriority(customTrophyListener, this);

	return true;
}

void FinalSceneController::__onBack2WelcomeSceneMsgReceived(EventCustom* pEvent)
{
	Director::getInstance()->replaceScene(
		TransitionFade::create(2.0f, WelcomeSceneController::createScene()));
}
