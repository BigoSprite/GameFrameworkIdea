#include "GameSelectionController.h"
#include "WelcomeSceneController.h"
#include "HelloWorldScene.h"
#include "GuideController.h"
#include "WorldMapScene.h"
#include "finalScene.h"
#include "FailLayer.h"
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
	m_pBackgroundSprite = Sprite::create("city2.png");
	m_pBackgroundSprite->setPosition(vs.width / 2, vs.height / 2);
	addChild(m_pBackgroundSprite);

	// 菜单1
	MenuItemImage* menu1 = MenuItemImage::create("menu.png", "menu.png",
		CC_CALLBACK_1(GameSelectionController::gameStart1, this));
	menu1->setScaleX(1.0);
	menu1->setScaleY(0.8);
	auto menu = Menu::create(menu1, NULL);
	menu->setPosition(vs.width / 2, vs.height - 500);
	addChild(menu, 2);
	// 菜单1标题
	const char *str_1 = ((String*)dic->objectForKey("global"))->_string.c_str();
	menuTitle1 = Label::createWithTTF(str_1, "fonts/b.ttf", 32);
	menuTitle1->setPosition(vs.width / 2, vs.height - 500);
	addChild(menuTitle1, 3);

	// 菜单2
	MenuItemImage* menu2 = MenuItemImage::create("menu.png", "menu.png",
		CC_CALLBACK_1(GameSelectionController::gameStart2, this));
	menu2->setScaleX(1.0);
	menu2->setScaleY(0.8);
	auto menu3 = Menu::create(menu2, NULL);
	menu3->setPosition(vs.width / 2, vs.height - 620);
	addChild(menu3, 2);
	// 菜单2标题
	const char *str_2 = ((String*)dic->objectForKey("iq"))->_string.c_str();
	menuTitle2 = Label::createWithTTF(str_2, "fonts/b.ttf", 32);
	menuTitle2->setPosition(vs.width / 2, vs.height - 620);
	addChild(menuTitle2, 3);

	////////女孩
	girl = Sprite::create("girl1.png");
	girl->setScale(0.25);
	girl->setPosition(vs.width / 2 - 300, vs.height / 2 + 20);
	girl->setAnchorPoint(Point(0, 0));
	addChild(girl, 4);


	/////半透明文字背景
	auto transBg = Sprite::create("transparent.png");
	transBg->setPosition(vs.width / 2, vs.height / 2 + 180);
	transBg->setScaleX(1.5);
	transBg->setScaleY(0.001);
	addChild(transBg, 3);


	// 女孩及动画
	const char *str_des = ((String*)dic->objectForKey("des"))->_string.c_str();
	auto des = Label::createWithTTF(str_des, "fonts/b.ttf", 20);
	des->setAnchorPoint(Point(0, 0));
	des->setPosition(vs.width / 2 - 80, vs.height / 2 + 85);
	des->setDimensions(320, 150);
	addChild(des, 4);
	des->setOpacity(0);
	ActionInterval * delaytime_des = CCDelayTime::create(2.0);
	auto fi_des = FadeIn::create(0.5);
	auto seq_des = Sequence::create(delaytime_des, fi_des, NULL);
	des->runAction(seq_des);


	// 指针1及其动画
	auto pointer1 = Sprite::create("pointer.png");
	pointer1->setPosition(vs.width / 2 - 75, vs.height / 2 + 170);
	pointer1->setRotation(-90);
	addChild(pointer1, 4);
	pointer1->setOpacity(0);
	ActionInterval * delaytime_p1 = CCDelayTime::create(2.5);
	auto fi_p1 = FadeIn::create(0.5);
	auto seq_p1 = Sequence::create(delaytime_p1, fi_p1, NULL);
	pointer1->runAction(seq_p1);
	// 指针1右边的文字
	const char *str_l1 = ((String*)dic->objectForKey("label1"))->_string.c_str();
	auto label1 = Label::createWithTTF(str_l1, "fonts/b.ttf", 17);
	label1->setColor(Color3B(242, 221, 28));
	label1->setPosition(vs.width / 2 + 80, vs.height / 2 + 170);
	addChild(label1, 4);
	label1->setOpacity(0);
	ActionInterval * delaytime_l1 = CCDelayTime::create(2.5);
	auto fi_l1 = FadeIn::create(0.5);
	auto seq_l1 = Sequence::create(delaytime_l1, fi_l1, NULL);
	label1->runAction(seq_l1);


	// 指针2及其动画
	auto pointer2 = Sprite::create("pointer.png");
	pointer2->setPosition(vs.width / 2 - 75, vs.height / 2 + 140);
	pointer2->setRotation(-90);
	//pointer1->setVisible(false);
	addChild(pointer2, 4);
	pointer2->setOpacity(0);
	ActionInterval * delaytime_p2 = CCDelayTime::create(3);
	auto fi_p2 = FadeIn::create(0.5);
	auto seq_p2 = Sequence::create(delaytime_p2, fi_p2, NULL);
	pointer2->runAction(seq_p2);
	// 指针2右边的文字
	const char *str_l2 = ((String*)dic->objectForKey("label2"))->_string.c_str();
	auto label2 = Label::createWithTTF(str_l2, "fonts/b.ttf", 17);
	label2->setColor(Color3B(242, 221, 28));
	label2->setPosition(vs.width / 2 + 80, vs.height / 2 + 140);
	addChild(label2, 4);
	label2->setOpacity(0);
	ActionInterval * delaytime_l2 = CCDelayTime::create(3);
	auto fi_l2 = FadeIn::create(0.5);
	auto seq_l2 = Sequence::create(delaytime_l2, fi_l2, NULL);
	label2->runAction(seq_l2);

	// 透明背景动画
	ActionInterval * delaytime_bg = CCDelayTime::create(1.5);
	auto st_bg = ScaleTo::create(0.5, 1.5, 0.8);  //这里的x y比例不是原来图片的大小了，是setscale之后的大小了
	auto sq_bg = Sequence::create(delaytime_bg, st_bg, NULL);
	transBg->runAction(sq_bg);



	//后退到主菜单
	auto back = MenuItemImage::create("back.png", "back.png",
		CC_CALLBACK_1(GameSelectionController::mainMenu, this));
	back->setScale(0.5);
	back->setRotation(180);
	auto menuBack = Menu::create(back, NULL);
	menuBack->setPosition(50, vs.height - 50);
	addChild(menuBack, 2);



	this->schedule(SEL_SCHEDULE(&GameSelectionController::move), 0.02f);

	return true;
}


void GameSelectionController::gameStart1(cocos2d::Ref * r)
{
	log("game start 1");

	// 让原来的文字不可见todo

	Size vs = Director::getInstance()->getVisibleSize();
	particleEffect(Point(vs.width / 2, vs.height - 500));
	
	//添加选择层,这里读取数据，如果level不是0，则添加选择层，否则直接开始游戏
	int globalLevelNum = UserDefault::getInstance()->getIntegerForKey("level_Global");

	if (globalLevelNum != 0)//弹出是否继续游戏的提示框
	{
		auto icl = ContinueLastGameController::create();
		icl->setPosition(0, 0);
		addChild(icl, 6);
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

//萌妹移动函数
void GameSelectionController::move(float dt)
{
	Size vs = Director::getInstance()->getVisibleSize();
	//萌妹沿着y轴上下移动
	float nextGirlY = girl->getPositionY() - vy_girl1;
	girl->setPositionY(nextGirlY);
	if (nextGirlY <= vs.height / 2 + 30)
	{
		vy_girl1 = -vy_girl1;
	}
	if (nextGirlY >= vs.height / 2 + 10)
	{
		vy_girl1 = -vy_girl1;
	}
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