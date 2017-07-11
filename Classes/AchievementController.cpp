#include "AchievementController.h"
#include "Tags.h"
#include "Messages.h"
#include "WelcomeSceneController.h"

AchievementController::AchievementController()
{
}

AchievementController::~AchievementController()
{
}

Scene* AchievementController::createScene()
{
	auto scene = Scene::create();
	auto layer = AchievementController::create();
	scene->addChild(layer);
	return scene;
}

bool AchievementController::init()
{
	if (!BaseController::init())
		return false;

	Size visiableSize = Director::getInstance()->getVisibleSize();

	/// Add View
	m_pView = AchievementView::create();
	m_pView->setPosition(Vec2(visiableSize.width / 2, visiableSize.height / 2));
	this->addChild(m_pView, 1);

	/// Subscribe Message
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	// 成就按钮
	auto customTrophyListener = EventListenerCustom::create(
		ACHEVEMENTVIEW_TOUCH_MSG + std::to_string(AchievementViewTag::TROPHY_TAG),
		CC_CALLBACK_1(AchievementController::__onTrophyIconTouched, this));
	dispatcher->addEventListenerWithSceneGraphPriority(customTrophyListener, this);
	// 信息
	auto customInfoListener = EventListenerCustom::create(
		ACHEVEMENTVIEW_TOUCH_MSG + std::to_string(AchievementViewTag::INFO_TAG),
		CC_CALLBACK_1(AchievementController::__onInfoIconTouched, this));
	dispatcher->addEventListenerWithSceneGraphPriority(customInfoListener, this);
	// item
	auto customItemListener = EventListenerCustom::create(
		ACHEVEMENTVIEW_TOUCH_MSG + std::to_string(AchievementViewTag::ITEM_TAG),
		CC_CALLBACK_1(AchievementController::__onItemIconTouched, this));
	dispatcher->addEventListenerWithSceneGraphPriority(customItemListener, this);
	// 返回欢迎场景的信息
	auto customBack2WelcomeSceneListener = EventListenerCustom::create(
		BACK_TO_WELCOME_SCENE_MSG,
		CC_CALLBACK_1(AchievementController::__onBack2WelcomeSceneMsgReceived, this));
	dispatcher->addEventListenerWithSceneGraphPriority(customBack2WelcomeSceneListener, this);

	return true;
}


void AchievementController::__onTrophyIconTouched(EventCustom* pEvent)
{
	log("trophy touch msg received...");
}

void AchievementController::__onInfoIconTouched(EventCustom* pEvent)
{
	log("info touch msg received...");
}

void AchievementController::__onItemIconTouched(EventCustom* pEvent)
{
	log("item touch msg received...");
}

void AchievementController::__onBack2WelcomeSceneMsgReceived(EventCustom* pEvent)
{
	log("AchievementController::__onBack2WelcomeSceneMsgReceived");
	Director::getInstance()->replaceScene(
		TransitionFade::create(1.0, WelcomeSceneController::createScene()));
}