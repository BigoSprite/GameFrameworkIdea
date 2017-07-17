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
	// ������Ϸ
	auto continueLastPlayListener = EventListenerCustom::create(
		CONTINUE_LAST_PLAY_MSG,
		CC_CALLBACK_1(ContinueLastGameController::__onContinueLastPlayMsgReceived, this));
	dispatcher->addEventListenerWithSceneGraphPriority(continueLastPlayListener, this);
	// ��ʼ����Ϸ
	auto startNewPlayListener = EventListenerCustom::create(
		START_NEW_PLAY_MSG,
		CC_CALLBACK_1(ContinueLastGameController::__onStartNewPlayMsgReceived, this));
	dispatcher->addEventListenerWithSceneGraphPriority(startNewPlayListener, this);



	// ���θó����µĴ����¼�
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

	//���õ�ǰ�ؿ�
	int tempLevel = UserDefault::getInstance()->getIntegerForKey("level_Global");
	getDataManager().setGameLevel(tempLevel);

	//���õ�ǰ����
	int tempScore = UserDefault::getInstance()->getIntegerForKey("levelInitScore");
	getDataManager().setCurrentScore(tempScore);

	//����Ŀ�����
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