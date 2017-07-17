#include "GameSelectionController.h"
#include "WelcomeSceneController.h"
#include "HelloWorldScene.h"
#include "GuideController.h"
#include "ContinueLastGameController.h"
#include "Game.h"

GameSelectionController::GameSelectionController():vy_girl1(0.5f)
{}

GameSelectionController::~GameSelectionController()
{}

Scene* GameSelectionController::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSelectionController::create();
	scene->addChild(layer);
	return scene;
}

bool GameSelectionController::init()
{
	if (!BaseController::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	Size vs = Director::getInstance()->getVisibleSize();

	// 背景
	m_pBackgroundSprite = Sprite::create("gameSelection_bg.png");
	m_pBackgroundSprite->setPosition(vs.width / 2, vs.height / 2);
	this->addChild(m_pBackgroundSprite, -1);

	// 人机模式
	auto normal_1 = Sprite::create("computer_1.png");
	auto selected_1 = Sprite::create("computer_2.png");
	auto item_1 = MenuItemSprite::create(normal_1, selected_1,
		CC_CALLBACK_1(GameSelectionController::gameStart1, this));
	auto menu = Menu::create(item_1, nullptr);
	menu->setPosition(vs.width / 2, 200);
	this->addChild(menu, 0);
	// 匹配模式
	auto normal_2 = Sprite::create("p2p_1.png");
	auto selected_2 = Sprite::create("p2p_2.png");
	auto item_2 = MenuItemSprite::create(normal_2, selected_2,
		CC_CALLBACK_1(GameSelectionController::gameStart2, this));
	auto menu_2 = Menu::create(item_2, nullptr);
	menu_2->setPosition(vs.width / 2, 100);
	this->addChild(menu_2, 0);

	/////头像
	auto head_bg = Sprite::create("intro_bg.png");
	head_bg->setPosition(vs.width / 2, vs.height / 2 + 120);
	head_bg->setScale(0.0001f, 0.0001f);
	this->addChild(head_bg, 3);
	auto action = Sequence::create(
		DelayTime::create(1.5), 
		ScaleTo::create(1.0f, 0.9, 0.9), nullptr);
	head_bg->runAction(action);



	//后退到主菜单
	auto back = MenuItemImage::create("back.png", "back.png",
		CC_CALLBACK_1(GameSelectionController::mainMenu, this));
	back->setScale(0.5);
	back->setRotation(180);
	auto menuBack = Menu::create(back, NULL);
	menuBack->setPosition(50, vs.height - 50);
	addChild(menuBack, 2);

	return true;
}


void GameSelectionController::gameStart1(Ref * r)
{
	// 让原来的文字不可见todo

	Size vs = Director::getInstance()->getVisibleSize();
	particleEffect(Point(vs.width / 2, vs.height - 500));
	
	//添加选择层,这里读取数据，如果level不是0，则添加选择层，否则直接开始游戏
	int globalLevelNum = UserDefault::getInstance()->getIntegerForKey("level_Global");

	if (globalLevelNum != 0)//弹出是否继续游戏的提示框
	{
		auto icl = ContinueLastGameController::create();
		icl->setOpacity(0);
		icl->setPosition(0, 0);
		this->addChild(icl, 10);

		icl->runAction(FadeIn::create(1.5f));
	}
	else //否则直接开始游戏
	{
		Director::getInstance()->replaceScene(
			TransitionFade::create(2, Game::createScene()));
	}



}

void GameSelectionController::gameStart2(cocos2d::Ref * r)
{
	log("game start 2");
}


//回到主菜单
void GameSelectionController::mainMenu(cocos2d::Ref * r)
{
	Director::getInstance()->replaceScene(
		TransitionFade::create(1.0, WelcomeSceneController::createScene()));
}

void GameSelectionController::particleEffect(Point pos)
{

	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("menu.png"));
	effect->setTotalParticles(10);

	//让其为图片本身的颜色
	effect->setStartColor(Color4F(255, 255, 255, 255));
	effect->setEndColor(Color4F(255, 255, 255, 0));

	effect->setStartSize(50.0f);

	effect->setLife(2.6f);
	effect->setSpeed(200);
	effect->setSpeedVar(10);
	effect->setPosition(pos);
	this->addChild(effect);
}