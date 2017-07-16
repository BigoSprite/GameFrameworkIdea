#include "WelcomeSceneController.h"
#include "GameSelectionController.h"

WelcomeSceneController::WelcomeSceneController()
{}

WelcomeSceneController::~WelcomeSceneController()
{}

Scene* WelcomeSceneController::createScene()
{
	auto scene = Scene::create();
	auto welcomeLayer = WelcomeSceneController::create();
	scene->addChild(welcomeLayer);
	return scene;
}

//判断是否存在存档数据
void WelcomeSceneController::__initSaveFileInfo()
{
	if (!UserDefault::getInstance()->getBoolForKey("exist")) {
		UserDefault::getInstance()->setBoolForKey("exist", true);

		//初始化环球旅行的关卡数0 和 初始化最高分0 和 目标分数
		UserDefault::getInstance()->setIntegerForKey("level_Global", 0);
		UserDefault::getInstance()->setIntegerForKey("level_Global_highestScore", 0);
		UserDefault::getInstance()->setIntegerForKey("level_Global_targetScore", 1000);
		UserDefault::getInstance()->setIntegerForKey("level_Global_currentScore", 0);
		//初始化历史最高分
		UserDefault::getInstance()->setIntegerForKey("historyBestScore", 0);
		//初始化单次消去记录
		UserDefault::getInstance()->setIntegerForKey("singleBest", 0);
		//初始化超神次数
		UserDefault::getInstance()->setIntegerForKey("legendaryNum", 0);
		//初始化道具个数
		UserDefault::getInstance()->setIntegerForKey("BombNum", 10);
		UserDefault::getInstance()->setIntegerForKey("ChangeNum", 10);
		//初始化init分数
		UserDefault::getInstance()->setIntegerForKey("levelInitScore", 0);

		//写入
		UserDefault::getInstance()->flush();
	}
}

bool WelcomeSceneController::init()
{
	if (!BaseController::init())
		return false;

	__initSaveFileInfo();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 背景
	m_pBackgroundSprite = Sprite::create("welcome_bg.png");
	m_pBackgroundSprite->setAnchorPoint(Point(0, 0));
	m_pBackgroundSprite->setPosition(0, 0);
	addChild(m_pBackgroundSprite, -1);

	// logo
	auto logo = Sprite::create("logo.png");
	logo->setPosition(visibleSize.width/2, visibleSize.height / 2 + 280);
	this->addChild(logo, 0);
	auto action = ScaleBy::create(1.0f, 1.1f);
	auto rp = RepeatForever::create(
		Sequence::create(action, action->reverse(), nullptr));
	logo->runAction(rp);

	//6个图标
	float y = visibleSize.height / 2 + 190;
	auto icon1 = Sprite::create("yasuo.png");
	icon1->setPosition(101, y);
	icon1->setScale(0.45f);
	this->addChild(icon1, 0);

	auto icon2 = Sprite::create("ruiwen.png");
	icon2->setScale(0.5f);
	icon2->setPosition(icon1->getPosition().x + 60, y);
	this->addChild(icon2, 0);

	auto icon3 = Sprite::create("nvjing.png");
	icon3->setPosition(icon2->getPosition().x + 60, y);
	icon3->setScale(0.45f);
	this->addChild(icon3, 0);


	auto icon4 = Sprite::create("ez.png");
	icon4->setPosition(icon3->getPosition().x + 60, y);
	this->addChild(icon4, 0);
	icon4->setScale(0.45f);

	auto icon5 = Sprite::create("goutou.png");
	icon5->setPosition(icon4->getPosition().x + 60, y);
	icon5->setScale(0.45f);
	this->addChild(icon5, 0);
	

	auto icon6 = Sprite::create("eyv.png");
	icon6->setPosition(icon5->getPosition().x + 60, y);
	icon6->setScale(0.45f);
	this->addChild(icon6, 0);
	

	// BigoSprite Idea
	m_pTitle = Label::createWithTTF("BIGOSPRITE IDEA", "fonts/Arial.ttf", 18);
	m_pTitle->setPosition(visibleSize.width / 2 , visibleSize.height / 2 + 120);
	m_pTitle->setColor(Color3B(200, 170, 110));
	this->addChild(m_pTitle, 0);

	// Button
	// 菜单1——游戏开始
	auto enterGame_normal = Sprite::create("enterGame_1.png");
	auto enterGame_selected = Sprite::create("enterGame_2.png");
	auto item = MenuItemSprite::create(enterGame_normal, enterGame_selected,
		CC_CALLBACK_1(WelcomeSceneController::_gameStartCallback, this));
	auto enterGameMenu = Menu::create(item, NULL);
	enterGameMenu->setPosition(visibleSize.width / 2, visibleSize.height - 420);
	this->addChild(enterGameMenu, 0);

	// 菜单2——商店
	auto seeAchievement_normal = Sprite::create("shopBtn_1.png");
	auto seeAchievement_selected = Sprite::create("shopBtn_2.png");
	auto item1 = MenuItemSprite::create(seeAchievement_normal, seeAchievement_selected,
		CC_CALLBACK_1(WelcomeSceneController::_enterShopCallback, this));
	auto seeAchievementMenu = Menu::create(item1, NULL);
	seeAchievementMenu->setPosition(visibleSize.width / 2, visibleSize.height - 520);
	this->addChild(seeAchievementMenu, 0);

	// 菜单3——退出
	auto seeMap_normal = Sprite::create("quitBtn_1.png");
	auto seeMap_selected = Sprite::create("quitBtn_2.png");
	auto item2 = MenuItemSprite::create(seeMap_normal, seeMap_selected,
		CC_CALLBACK_1(WelcomeSceneController::_quitGameCallback, this));
	auto seeAcMapMenu = Menu::create(item2, NULL);
	seeAcMapMenu->setPosition(visibleSize.width / 2, visibleSize.height - 620);
	this->addChild(seeAcMapMenu, 0);

	return true;
}


void WelcomeSceneController::_gameStartCallback(cocos2d::Ref *pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Director::getInstance()->replaceScene(
		TransitionFade::create(2, GameSelectionController::createScene()));
}


void WelcomeSceneController::_enterShopCallback(Ref *pRef)
{
}


void WelcomeSceneController::_quitGameCallback(Ref *pRef)
{
	Director::getInstance()->end();
}
