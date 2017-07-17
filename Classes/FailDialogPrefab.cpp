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
	m_pDialogBg = Sprite::create("fail_logo.png");
	m_pDialogBg->setScale(0.70f);
	m_pDialogBg->setPosition(Vec2(size.width / 2, size.height / 2 + 100));
	this->addChild(m_pDialogBg);


	auto restartGame_normal = Sprite::create("reChanBtn_red_1.png");
	auto restartGame_selected = Sprite::create("reChanBtn_red_2.png");
	auto restartMenuItem = MenuItemSprite::create(
		restartGame_normal,
		restartGame_selected,
		CC_CALLBACK_1(FailDialogPrefab::__restartGameCallback, this));
	restartMenuItem->setScale(0.75f);

	auto back2WelcomeScene_normal = Sprite::create("q_Btn_1.png");
	auto back2WelcomeScene_selected = Sprite::create("q_Btn_2.png");
	auto back2WelcomeSceneMenuItem = MenuItemSprite::create(
		back2WelcomeScene_normal,
		back2WelcomeScene_selected,
		CC_CALLBACK_1(FailDialogPrefab::__quitGameCallback, this));
	back2WelcomeSceneMenuItem->setScale(0.75f);

	
	m_pMenu = Menu::create(restartMenuItem, back2WelcomeSceneMenuItem, nullptr);
	m_pMenu->setPosition(Vec2(m_pDialogBg->getPosition().x, 
		m_pDialogBg->getPosition().y - m_pDialogBg->getContentSize().height/2 + 55));
	m_pMenu->alignItemsVerticallyWithPadding(20);
	this->addChild(m_pMenu, 1);



}

void FailDialogPrefab::__restartGameCallback(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.75f, 
		Game::createScene()));
}

void FailDialogPrefab::__quitGameCallback(Ref* r)
{
	Director::getInstance()->end();
}