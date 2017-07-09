#include "BombIconView.h"

BombIconView::BombIconView()
{
}

BombIconView::~BombIconView()
{
}

bool BombIconView::init()
{
	if (!ui::Layout::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	visibleSize = Director::getInstance()->getVisibleSize();

	// 背景
	m_pBackground = Sprite::create("changeLayerBg.png");
	m_pBackground->setPosition(visibleSize.width / 2, visibleSize.height + 250);
	auto mt_bg = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height - 100));
	m_pBackground->runAction(mt_bg);
	this->addChild(m_pBackground);

	// 说明用法的label
	const char *str_des = ((String*)dic->objectForKey("descriptionBomb"))->_string.c_str();
	m_pDescription = Label::createWithTTF(str_des, "fonts/b.ttf", 20);
	m_pDescription->setDimensions(380, 200);
	m_pDescription->setPosition(visibleSize.width / 2 + 10, visibleSize.height + 220);
	auto mt_des = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 10, visibleSize.height - 130));
	m_pDescription->runAction(mt_des);
	this->addChild(m_pDescription, 2);


	//关闭按钮
	m_pCloseItem = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(BombIconView::closeMenuCallback, this));
	m_pCloseItem->setScale(0.4);
	m_pClostMenu = Menu::create(m_pCloseItem, NULL);
	m_pClostMenu->setPosition(visibleSize.width / 2, visibleSize.height + 180);
	auto mt_close = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height - 170));
	this->addChild(m_pClostMenu, 2);
	m_pClostMenu->runAction(mt_close);

	//关闭按钮的文字
	const char *str_shut = ((String*)dic->objectForKey("shutdown"))->_string.c_str();
	m_pCloseLabel = Label::createWithTTF(str_shut, "fonts/b.ttf", 20);
	m_pCloseLabel->setPosition(visibleSize.width / 2 - 3, visibleSize.height + 180);
	auto mt_closeLabel = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height - 170));
	this->addChild(m_pCloseLabel, 3);
	m_pCloseLabel->runAction(mt_closeLabel);


	//飞弹和炮塔
	m_pTurrent = Sprite::create("tower.png");
	m_pTurrent->setScale(0.4);
	m_pTurrent->setRotation(-90);
	m_pTurrent->setPosition(visibleSize.width / 2 - 60, visibleSize.height + 240);
	auto mt_turret = MoveTo::create(0.5, Vec2(visibleSize.width / 2 - 60, visibleSize.height - 110));
	m_pTurrent->runAction(mt_turret);
	this->addChild(m_pTurrent, 3);

	m_pMissle = Sprite::create("missile.png");
	m_pMissle->setScale(0.9);
	m_pMissle->setRotation(-90);
	m_pMissle->setPosition(visibleSize.width / 2 + 30, visibleSize.height + 240);
	auto mt_missile = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 30, visibleSize.height - 110));
	m_pMissle->runAction(mt_missile);
	this->addChild(m_pMissle, 3);


	return true;
}

void BombIconView::closeMenuCallback(Ref * ref)
{
	auto mt_des = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 10, visibleSize.height + 220));
	m_pDescription->runAction(mt_des);

	auto mt_close = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 180));
	m_pClostMenu->runAction(mt_close);

	auto mt_bg = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 250));
	m_pBackground->runAction(mt_bg);

	auto mt_cl = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 180));
	m_pCloseLabel->runAction(mt_cl);

	auto mt_turret = MoveTo::create(0.5, Vec2(visibleSize.width / 2 - 60, visibleSize.height + 240));
	m_pTurrent->runAction(mt_turret);

	auto mt_missile = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 30, visibleSize.height + 240));
	m_pMissle->runAction(mt_missile);


	auto deleteLayer = CallFunc::create([=]() {

		this->removeFromParentAndCleanup(true);
		//getDataManager().setBombLayerAdded(false);
	});

	ActionInterval * delay = DelayTime::create(0.5);
	auto sq = Sequence::create(delay, deleteLayer, NULL);

	this->runAction(sq);
}