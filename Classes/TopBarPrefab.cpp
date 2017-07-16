#include "TopBarPrefab.h"
#include "DataManager.h"
#include "GamePauseController.h"
#include "WelcomeSceneController.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

TopBarPrefab::TopBarPrefab()
{
}

TopBarPrefab::~TopBarPrefab()
{
}

bool TopBarPrefab::init()
{
	if (!Sprite::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();

	///bg
	m_pTopBarBg = Sprite::create("top_bar_bg.png");
	m_pTopBarBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	m_pTopBarBg->setPosition(visibleSize.width / 2, visibleSize.height + 200);
	this->addChild(m_pTopBarBg, -1);
	auto action_top_bar_bg = Sequence::create(
		DelayTime::create(2.7f),
		EaseOut::create(MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height)), 7.0),
		nullptr);
	m_pTopBarBg->runAction(action_top_bar_bg);

	///pause
	auto pause_normal = Sprite::create("backToMenu.png");
	auto pause_selected = Sprite::create("backToMenu.png");
	m_pPause = MenuItemSprite::create(pause_normal, pause_selected,
		CC_CALLBACK_1(TopBarPrefab::__pauseCallback, this));
	m_pPause->setAnchorPoint(Vec2(0, 0));
	m_pPause->setScale(0.45);
	auto pause_menu = Menu::create(m_pPause, nullptr);
	pause_menu->setPosition(visibleSize.width / 2 - 220, visibleSize.height - 60);
	pause_menu->setOpacity(0);
	auto action_1 = Sequence::create(DelayTime::create(3.0f), FadeIn::create(0.5f), nullptr);
	pause_menu->runAction(action_1);
	this->addChild(pause_menu, 0);

	///back to welcome scene
	auto back_normal = Sprite::create("backToMenu.png");
	auto back_selected = Sprite::create("backToMenu.png");
	m_pBack2WelcomeScene = MenuItemSprite::create(back_normal, back_selected,
		CC_CALLBACK_1(TopBarPrefab::__back2WelcomeSceneCallback, this));
	m_pBack2WelcomeScene->setAnchorPoint(Point(0, 0));
	m_pBack2WelcomeScene->setScale(0.45);
	auto bcak_menu = Menu::create(m_pBack2WelcomeScene, nullptr);
	bcak_menu->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 60);
	bcak_menu->setOpacity(0);
	auto action_2 = Sequence::create(DelayTime::create(3.4f), FadeIn::create(0.5f), nullptr);
	bcak_menu->runAction(action_2);
	this->addChild(bcak_menu, 3);

	

	///skill_1
	auto change_normal = Sprite::create("changeIcon.png");
	auto change_selected = Sprite::create("changeIcon.png");
	m_pSkill_1 = MenuItemSprite::create(change_normal, change_selected,
		CC_CALLBACK_1(TopBarPrefab::__changeIconTypeCallback, this));
	m_pSkill_1->setScale(0.5);
	auto changeIconMenu = Menu::create(m_pSkill_1, nullptr);
	changeIconMenu->setPosition(visibleSize.width / 2 + 130, visibleSize.height - 45);
	this->addChild(changeIconMenu, 3);
	m_pSkill_1->setOpacity(0);
	auto action_3 = Sequence::create(DelayTime::create(3.8f), FadeIn::create(0.5f), nullptr);
	m_pSkill_1->runAction(action_3);
	
	char cChangeIconNum[10];
	sprintf(cChangeIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("ChangeNum"));
	std::string strChangeIconNum = cChangeIconNum;
	m_pSkill1Num = Label::createWithTTF(cChangeIconNum, "fonts/pirulenrg.ttf", 18);
	m_pSkill1Num->setPosition(visibleSize.width / 2 + 152, visibleSize.height - 57);
	this->addChild(m_pSkill1Num, 3);
	m_pSkill1Num->setOpacity(0);
	auto action_4 = Sequence::create(DelayTime::create(3.8f), FadeIn::create(0.5f), nullptr);
	m_pSkill1Num->runAction(action_4);


	///skill_2
	auto bomb_normal = Sprite::create("bomb.png");
	auto bomb_selected = Sprite::create("bomb.png");
	m_pSkill_2 = MenuItemSprite::create(bomb_normal, bomb_selected,
		CC_CALLBACK_1(TopBarPrefab::__bombIconTypeCallback, this));
	m_pSkill_2->setScale(0.5);
	auto bombIconMenu = Menu::create(m_pSkill_2, nullptr);
	bombIconMenu->setPosition(visibleSize.width / 2 + 185, visibleSize.height - 45);
	addChild(bombIconMenu, 3);
	m_pSkill_2->setOpacity(0);
	auto action_5 = Sequence::create(DelayTime::create(4.2f), FadeIn::create(0.5f), nullptr);
	m_pSkill_2->runAction(action_5);

	char cBombIconNum[10];
	sprintf(cBombIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("BombNum"));
	std::string strBombIconNum = cBombIconNum;
	m_pSkill2Num = Label::createWithTTF(cBombIconNum, "fonts/pirulenrg.ttf", 18);
	m_pSkill2Num->setPosition(visibleSize.width / 2 + 205, visibleSize.height - 57);
	this->addChild(m_pSkill2Num, 3);
	m_pSkill2Num->setOpacity(0);
	auto action_6 = Sequence::create(DelayTime::create(4.2f), FadeIn::create(0.5f), nullptr);
	m_pSkill2Num->runAction(action_6);

	// skill数量label变红
	if (UserDefault::getInstance()->getIntegerForKey("BombNum") == 0)
	{
		m_pSkill2Num->setColor(Color3B::RED);
	}
	if (UserDefault::getInstance()->getIntegerForKey("ChangeNum") == 0)
	{
		m_pSkill1Num->setColor(Color3B::RED);
	}



	/// 道具不足提示框
	m_pItemNotEnoughSprite = ItemNotEnoughPrefab::create();
	m_pItemNotEnoughSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_pItemNotEnoughSprite->setVisible(false);
	this->addChild(m_pItemNotEnoughSprite, 10);



	return true;
}


void TopBarPrefab::__pauseCallback(Ref* pRef)
{
	if (getDataManager().getIsChangeLayerAdded() == false
		&& getDataManager().getIsBombLayerAdded() == false) //如果已经添加了layer就不能再添加了
	{
		//在这里得更新当前分数,方便暂停层使用
		getDataManager().setCurrentScore(/*currentScore*/111);

		auto gamePauseLayer = GamePauseController::create();
		gamePauseLayer->setPosition(0, 0);
		this->addChild(gamePauseLayer, 9);
	}
}

void TopBarPrefab::__back2WelcomeSceneCallback(Ref* pRef)
{
	if (getDataManager().getIsChangeLayerAdded() == false
		&& getDataManager().getIsBombLayerAdded() == false) //如果已经添加了layer就不能再添加了
	{
		Director::getInstance()->replaceScene(
			TransitionCrossFade::create(1.0f, WelcomeSceneController::createScene()));
	}
}

void TopBarPrefab::__changeIconTypeCallback(Ref* pRef)
{
}

void TopBarPrefab::__bombIconTypeCallback(Ref* pRef)
{
}