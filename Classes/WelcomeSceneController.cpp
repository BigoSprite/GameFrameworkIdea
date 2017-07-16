#include "WelcomeSceneController.h"
#include "HelloWorldScene.h"
#include "GameSelectionController.h"

#include "AchievementController.h"
#include "WorldMapScene.h"

WelcomeSceneController::WelcomeSceneController():vy(5),vx(2)
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
	auto st = ScaleBy::create(1.0f, 1.1f);
	auto sq = Sequence::create(st, st->reverse(), NULL);
	auto rp = RepeatForever::create(sq);
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
	m_pTitle2 = Label::createWithTTF("BIGOSPRITE IDEA", "fonts/Arial.ttf", 18);
	m_pTitle2->setPosition(visibleSize.width / 2 , visibleSize.height / 2 + 120);
	m_pTitle2->setColor(Color3B(200, 170, 110));
	this->addChild(m_pTitle2, 0);

	// Button
	// 菜单1——游戏开始
	auto enterGame_normal = Sprite::create("enterGame_1.png");
	auto enterGame_selected = Sprite::create("enterGame_2.png");
	auto item = MenuItemSprite::create(enterGame_normal, enterGame_selected,
		CC_CALLBACK_1(WelcomeSceneController::_gameStartCallback, this));
	auto enterGameMenu = Menu::create(item, NULL);
	enterGameMenu->setPosition(visibleSize.width / 2, visibleSize.height - 420);
	this->addChild(enterGameMenu, 0);

	// 菜单2——查看成就
	auto seeAchievement_normal = Sprite::create("achievement_1.png");
	auto seeAchievement_selected = Sprite::create("achievement_2.png");
	auto item1 = MenuItemSprite::create(seeAchievement_normal, seeAchievement_selected,
		CC_CALLBACK_1(WelcomeSceneController::_gameOptionCallback, this));
	auto seeAchievementMenu = Menu::create(item1, NULL);
	seeAchievementMenu->setPosition(visibleSize.width / 2, visibleSize.height - 520);
	this->addChild(seeAchievementMenu, 0);

	// 菜单3——查看地图
	auto seeMap_normal = Sprite::create("worldmap_menu_1.png");
	auto seeMap_selected = Sprite::create("worldmap_menu_2.png");
	auto item2 = MenuItemSprite::create(seeMap_normal, seeMap_selected,
		CC_CALLBACK_1(WelcomeSceneController::_gameEndCallback, this));
	auto seeAcMapMenu = Menu::create(item2, NULL);
	seeAcMapMenu->setPosition(visibleSize.width / 2, visibleSize.height - 620);
	this->addChild(seeAcMapMenu, 0);

	return true;
}

// 转到游戏选择场景
void WelcomeSceneController::_gameStartCallback(cocos2d::Ref *pSender)
{
	log("game start...");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_particleEffect(Point(visibleSize.width / 2, visibleSize.height - 420));
	Director::getInstance()->replaceScene(
		TransitionFade::create(2, GameSelectionController::createScene()));
}

// 转到世界地图场景
void WelcomeSceneController::_gameEndCallback(cocos2d::Ref *pSender)
{
	log("game end...");

	Director::getInstance()->replaceScene(
		TransitionFade::create(0.5f, WorldMapScene::createScene()));
}

// 转到Achievement场景
void WelcomeSceneController::_gameOptionCallback(cocos2d::Ref *pSender)
{
	log("game option...");

	Director::getInstance()->replaceScene(
		TransitionFade::create(0.5f, AchievementController::createScene()));
}


void WelcomeSceneController::_particleEffect(Point point)
{
	auto effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("menu.png"));
	effect->setTotalParticles(10);


	//让其为图片本身的颜色
	effect->setStartColor(Color4F(255, 255, 255, 255));
	effect->setEndColor(Color4F(255, 255, 255, 0));

	effect->setStartSize(50.0f);

	effect->setLife(2.6f);
	effect->setSpeed(200);
	effect->setSpeedVar(10);
	effect->setPosition(point);

	this->addChild(effect, 5);
}