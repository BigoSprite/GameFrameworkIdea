#include "FailDialogPrefab.h"
#include "Game.h"
#include "WelcomeSceneController.h"

FailDialogPrefab::FailDialogPrefab()
{
}

FailDialogPrefab::~FailDialogPrefab()
{
}


Scene* FailDialogPrefab::createScene()
{
	auto scene = Scene::create();
	auto layer = FailDialogPrefab::create();
	scene->addChild(layer);
	return scene;
}


bool FailDialogPrefab::init()
{
	if (!Layer::init())
		return false;

	auto dic = Dictionary::createWithContentsOfFile("chinese.xml");

	auto size = Director::getInstance()->getVisibleSize();

	// bg
	m_pBg = Sprite::create("mainback.png");
	m_pBg->setPosition(size.width / 2, size.height / 2);
	this->addChild(m_pBg, -1);

	// dialog
	m_pDialogBg = Sprite::create("gamePause_bg.png");
	m_pDialogBg->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(m_pDialogBg);


	auto restartGame_normal = Sprite::create("yesBtn_1.png");
	auto restartGame_selected = Sprite::create("yesBtn_2.png");
	auto restartMenuItem = MenuItemSprite::create(
		restartGame_normal,
		restartGame_selected,
		CC_CALLBACK_1(FailDialogPrefab::__restartGameCallback, this));

	auto back2WelcomeScene_normal = Sprite::create("noBtn_1.png");
	auto back2WelcomeScene_selected = Sprite::create("noBtn_2.png");
	auto back2WelcomeSceneMenuItem = MenuItemSprite::create(
		back2WelcomeScene_normal,
		back2WelcomeScene_selected,
		CC_CALLBACK_1(FailDialogPrefab::__back2WelcomeSceneCallback, this));

	
	m_pMenu = Menu::create(restartMenuItem, back2WelcomeSceneMenuItem, nullptr);
	m_pMenu->setPosition(Vec2(m_pDialogBg->getPosition().x, 
		m_pDialogBg->getPosition().y - m_pDialogBg->getContentSize().height/2 + 35));
	m_pMenu->alignItemsHorizontallyWithPadding(10);
	this->addChild(m_pMenu, 1);



	// 屏蔽该场景下的触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void FailDialogPrefab::__restartGameCallback(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.75f, 
		Game::createScene()));
}

void FailDialogPrefab::__back2WelcomeSceneCallback(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.75f,
		WelcomeSceneController::createScene()));
}