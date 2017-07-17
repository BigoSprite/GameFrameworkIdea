#include "ContinueLastGameController.h"
#include "Messages.h"
#include "DataManager.h"
#include "Game.h"

ContinueLastGameController::ContinueLastGameController()
{
}

ContinueLastGameController::~ContinueLastGameController()
{
}

Scene* ContinueLastGameController::createScene()
{
	auto scene = Scene::create();
	auto layer = ContinueLastGameController::create();
	scene->addChild(layer);
	return scene;
}

bool ContinueLastGameController::init()
{
	if (!BaseController::init())
		return false;

	Size size = Director::getInstance()->getVisibleSize();

	/// Add View
	m_pView = ContinueLastGameView::create();
	m_pView->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(m_pView);

	/// Subscrib Message
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	// 继续游戏
	auto continueLastPlayListener = EventListenerCustom::create(
		CONTINUE_LAST_PLAY_MSG,
		CC_CALLBACK_1(ContinueLastGameController::__onContinueLastPlayMsgReceived, this));
	dispatcher->addEventListenerWithSceneGraphPriority(continueLastPlayListener, this);
	// 开始新游戏
	auto startNewPlayListener = EventListenerCustom::create(
		START_NEW_PLAY_MSG,
		CC_CALLBACK_1(ContinueLastGameController::__onStartNewPlayMsgReceived, this));
	dispatcher->addEventListenerWithSceneGraphPriority(startNewPlayListener, this);



	// 屏蔽该场景下的触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

	return true;
}

void ContinueLastGameController::__onContinueLastPlayMsgReceived(EventCustom* pEvent)
{
	log("ContinueLastGameController::__onContinueLastPlayMsgReceived");

	//设置当前关卡
	int tempLevel = UserDefault::getInstance()->getIntegerForKey("level_Global");
	getDataManager().setGameLevel(tempLevel);

	//设置当前分数
	int tempScore = UserDefault::getInstance()->getIntegerForKey("levelInitScore");
	getDataManager().setCurrentScore(tempScore);

	//设置目标分数
	int tempTargetScore = UserDefault::getInstance()->getIntegerForKey("level_Global_targetScore");
	getDataManager().setLevelTargetScore(tempTargetScore);


	Director::getInstance()->replaceScene(TransitionFade::create(2, Game::createScene()));
}

void ContinueLastGameController::__onStartNewPlayMsgReceived(EventCustom* pEvent)
{
	log("ContinueLastGameController::__onStartNewPlayMsgReceived");

	getDataManager().setGameLevel(1);

	getDataManager().setCurrentScore(0);

	getDataManager().setLevelTargetScore(1000);


	Director::getInstance()->replaceScene(TransitionFade::create(2, Game::createScene()));
}