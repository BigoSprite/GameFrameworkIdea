#include "WelcomeSceneController.h"
#include "HelloWorldScene.h"
#include "GameSelectionController.h"

#include "AchievementController.h"

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

bool WelcomeSceneController::init()
{
	if (!BaseController::init())
		return false;



	Size visibleSize = Director::getInstance()->getVisibleSize();



	// test
	auto lay = AchievementController::create();
	addChild(lay, 5);




	
	// 背景
	m_pBackgroundSprite1 = Sprite::create("welcome_bg1.png");
	m_pBackgroundSprite1->setAnchorPoint(Point(0, 0));
	m_pBackgroundSprite1->setPosition(0, 0);
	addChild(m_pBackgroundSprite1, 1);

	m_pBackgroundSprite2 = Sprite::create("welcome_bg1.png");
	m_pBackgroundSprite2->setAnchorPoint(Point(0, 0));
	m_pBackgroundSprite2->setPosition(0, 
		m_pBackgroundSprite1->getPositionY() + m_pBackgroundSprite1->getContentSize().height - 2);
	addChild(m_pBackgroundSprite2, 1);

	// 菜单1——游戏开始
	MenuItemImage* menu1 = MenuItemImage::create(
		"menu.png", 
		"menu.png",
		CC_CALLBACK_1(WelcomeSceneController::_gameStartCallback, this));
	menu1->setScaleX(1.0f);
	menu1->setScaleY(0.8f);
	auto menu = Menu::create(menu1, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height - 420);
	this->addChild(menu, 2);
	// 菜单2——游戏选项
	MenuItemImage* menu2 = MenuItemImage::create(
		"menu.png", 
		"menu.png", 
		CC_CALLBACK_1(WelcomeSceneController::_gameOptionCallback, this));
	menu2->setScaleX(1.0);
	menu2->setScaleY(0.8);
	auto menu5 = Menu::create(menu2, NULL);
	menu5->setPosition(visibleSize.width / 2, visibleSize.height - 520);
	addChild(menu5, 2);
	// 菜单3——游戏结束
	MenuItemImage* menu3 = MenuItemImage::create(
		"menu.png", 
		"menu.png", 
		CC_CALLBACK_1(WelcomeSceneController::_gameEndCallback, this));
	menu3->setScaleX(1.0);
	menu3->setScaleY(0.8);
	// 菜单
	auto menuEnd = Menu::create(menu3, NULL);
	menuEnd->setPosition(visibleSize.width / 2, visibleSize.height - 620);
	this->addChild(menuEnd, 2);

	//用xml保存中文，记得xml文件要存在resource文件夹里面才行
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	// 菜单字体
	const char *str_start = ((String*)dic->objectForKey("new"))->_string.c_str();
	m_pMenuTitle1 = Label::createWithTTF(str_start, "fonts/b.ttf", 50);
	m_pMenuTitle1->setColor(Color3B::WHITE);
	m_pMenuTitle1->setScale(0.60);
	m_pMenuTitle1->setAnchorPoint(Point(0, 0));//防止数字抖动
	m_pMenuTitle1->setPosition(visibleSize.width / 2 - 65, visibleSize.height - 438);
	addChild(m_pMenuTitle1, 3);

	const char *str_op = ((String*)dic->objectForKey("option"))->_string.c_str();
	m_pMenuTitle2 = Label::createWithTTF(str_op, "fonts/b.ttf", 50);
	m_pMenuTitle2->setColor(Color3B::WHITE);
	m_pMenuTitle2->setScale(0.60);
	m_pMenuTitle2->setAnchorPoint(Point(0, 0));//防止数字抖动
	m_pMenuTitle2->setPosition(visibleSize.width / 2 - 65, visibleSize.height - 538);
	addChild(m_pMenuTitle2, 3);

	const char *str_quit = ((String*)dic->objectForKey("quit"))->_string.c_str();
	m_pMenuTitle3 = Label::createWithTTF(str_quit, "fonts/b.ttf", 50);
	m_pMenuTitle3->setColor(Color3B::WHITE);
	m_pMenuTitle3->setScale(0.60);
	m_pMenuTitle3->setAnchorPoint(Point(0, 0));//防止数字抖动
	m_pMenuTitle3->setPosition(visibleSize.width / 2 - 65, visibleSize.height - 638);
	addChild(m_pMenuTitle3, 3);

	

	// 云彩
	m_pCloudSprite = Sprite::create("cloud.png");
	m_pCloudSprite->setAnchorPoint(Point(0, 0));
	m_pCloudSprite->setPosition(0, -80);
	this->addChild(m_pCloudSprite, 2);

	////22娘
	//gt = GirlTwo::create();
	//gt->setPosition(visibleSize.width / 2 - 150, visibleSize.height / 2 + 240);
	//gt->setScale(1.6);
	//gt->setScaleY(1.8);
	//addChild(gt, 2);


	//标题
	const char *str_title1 = ((String*)dic->objectForKey("welcomeTitle1"))->_string.c_str();
	m_pTitle1 = Label::createWithTTF(str_title1, "fonts/hbb.ttf", 130);
	m_pTitle1->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 + 320);
	m_pTitle1->setColor(Color3B(255, 255, 255));
	addChild(m_pTitle1, 2);
	//标题动画
	auto st = ScaleBy::create(1.0, 1.1);
	auto sq = Sequence::create(st, st->reverse(), NULL);
	auto rp = RepeatForever::create(sq);
	m_pTitle1->runAction(rp);
	// 标题2
	const char *str_title2 = ((String*)dic->objectForKey("welcomeTitle2"))->_string.c_str();
	m_pTitle2 = Label::createWithTTF(str_title2, "fonts/hbb.ttf", 55);
	m_pTitle2->setAnchorPoint(Point(0, 0));
	m_pTitle2->setPosition(visibleSize.width / 2 - 20, visibleSize.height / 2 + 100);
	m_pTitle2->setColor(Color3B(255, 255, 255));
	addChild(m_pTitle2, 2);
	auto lb1 = Sprite::create("leftBracket.png");
	lb1->setScale(0.06);
	lb1->setPosition(visibleSize.width / 2 + 20, visibleSize.height / 2 + 170);
	addChild(lb1, 2);
	auto lb2 = Sprite::create("rightBracket.png");
	lb2->setScale(0.06);
	lb2->setPosition(visibleSize.width / 2 + 160, visibleSize.height / 2 + 170);
	addChild(lb2, 2);
	auto lb3 = Sprite::create("leftBracket.png");
	lb3->setScale(0.06);
	lb3->setPosition(visibleSize.width / 2 + 20, visibleSize.height / 2 + 100);
	lb3->setFlippedY(true);
	addChild(lb3, 2);
	auto lb4 = Sprite::create("rightBracket.png");
	lb4->setScale(0.06);
	lb4->setPosition(visibleSize.width / 2 + 160, visibleSize.height / 2 + 100);
	lb4->setFlippedY(true);
	addChild(lb4, 2);


	//6个图标
	auto icon1 = Sprite::create("level1_3.png");
	icon1->setPosition(visibleSize.width / 2 - 20, visibleSize.height / 2 + 205);
	addChild(icon1, 2);
	icon1->setScale(0.26);
	auto icon2 = Sprite::create("level1_7.png");
	icon2->setPosition(visibleSize.width / 2 + 25, visibleSize.height / 2 + 205);
	addChild(icon2, 2);
	icon2->setScale(0.26);
	auto icon3 = Sprite::create("level1_1.png");
	icon3->setPosition(visibleSize.width / 2 + 70, visibleSize.height / 2 + 205);
	addChild(icon3, 2);
	icon3->setScale(0.26);
	auto icon4 = Sprite::create("level1_6.png");
	icon4->setPosition(visibleSize.width / 2 + 115, visibleSize.height / 2 + 205);
	addChild(icon4, 2);
	icon4->setScale(0.26);
	auto icon5 = Sprite::create("level1_5.png");
	icon5->setPosition(visibleSize.width / 2 + 160, visibleSize.height / 2 + 205);
	addChild(icon5, 2);
	icon5->setScale(0.26);
	auto icon6 = Sprite::create("level1_4.png");
	icon6->setPosition(visibleSize.width / 2 + 205, visibleSize.height / 2 + 205);
	addChild(icon6, 2);
	icon6->setScale(0.26);

	//移动背景
	this->schedule(SEL_SCHEDULE(&WelcomeSceneController::_move), 0.02f);

	return true;
}

void WelcomeSceneController::_gameStartCallback(cocos2d::Ref *pSender)
{
	log("game start...");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_particleEffect(Point(visibleSize.width / 2, visibleSize.height - 420));
	Director::getInstance()->replaceScene(
		TransitionFade::create(2, GameSelectionController::createScene()));
}

void WelcomeSceneController::_gameEndCallback(cocos2d::Ref *pSender)
{
	log("game end...");
}

void WelcomeSceneController::_gameOptionCallback(cocos2d::Ref *pSender)
{
	log("game option...");
}

void WelcomeSceneController::_move(float dt)
{
	Size visible = Director::getInstance()->getVisibleSize();

	float nextPos1 = m_pBackgroundSprite1->getPositionY() - vy;
	float nextPos2 = m_pBackgroundSprite2->getPositionY() - vy;
	m_pBackgroundSprite1->setPositionY(nextPos1);
	m_pBackgroundSprite2->setPositionY(nextPos2);

	if (nextPos1 < -m_pBackgroundSprite1->getContentSize().height)
	{
		nextPos1 = m_pBackgroundSprite2->getPositionY() + m_pBackgroundSprite2->getContentSize().height - 1;
		m_pBackgroundSprite1->setPositionY(nextPos1);
	}
	else if (nextPos2 < -m_pBackgroundSprite2->getContentSize().height)
	{
		nextPos2 = m_pBackgroundSprite1->getPositionY() + m_pBackgroundSprite1->getContentSize().height - 1;
		m_pBackgroundSprite1->setPositionY(nextPos2);
	}


	// 云移动, 横向移动
	float nextCloudX = m_pCloudSprite->getPositionX() - 2;
	m_pCloudSprite->setPositionX(nextCloudX);
	if (nextCloudX < -(m_pCloudSprite->getContentSize().width - visible.width))
	{
		vx = -vx;
		//log("%f", nextCloudX);
	}
	else if (nextCloudX > 0)
	{
		vx = -vx;
		//log("111");
	}
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