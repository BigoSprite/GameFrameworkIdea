#include "ChangeIconView.h"

ChangeIconView::ChangeIconView()
{
}

ChangeIconView::~ChangeIconView()
{
}


bool ChangeIconView::init()
{
	if (!ui::Layout::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	visibleSize = Director::getInstance()->getVisibleSize();

	// 背景
	m_pBackground = Sprite::create("changeLayerBg.png");
	m_pBackground->setPosition(visibleSize.width / 2, visibleSize.height + 250);
	m_pBackground->runAction(MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height - 100)));
	this->addChild(m_pBackground);

	//说明用法的label
	const char *str_des = ((String*)dic->objectForKey("description"))->_string.c_str();
	m_pDesLabel = Label::createWithTTF(str_des, "fonts/b.ttf", 20);
	m_pDesLabel->setDimensions(380, 200);
	m_pDesLabel->setPosition(visibleSize.width / 2 + 10, visibleSize.height + 220);
	auto mt_des = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 10, visibleSize.height - 130));
	m_pDesLabel->runAction(mt_des);
	this->addChild(m_pDesLabel, 2);

	//关闭按钮
	m_pCloseItem = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(ChangeIconView::closeMenuCallback, this));
	m_pCloseItem->setScale(0.4);
	m_pCloseMenu = Menu::create(m_pCloseItem, NULL);
	m_pCloseMenu->setPosition(visibleSize.width / 2, visibleSize.height + 180);
	auto mt_close = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height - 170));
	this->addChild(m_pCloseMenu, 2);
	m_pCloseMenu->runAction(mt_close);

	//关闭按钮的文字
	const char *str_shut = ((String*)dic->objectForKey("shutdown"))->_string.c_str();
	m_pCloseLabel = Label::createWithTTF(str_shut, "fonts/b.ttf", 20);
	m_pCloseLabel->setPosition(visibleSize.width / 2 - 3, visibleSize.height + 180);
	auto mt_closeLabel = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height - 170));
	addChild(m_pCloseLabel, 3);
	m_pCloseLabel->runAction(mt_closeLabel);

	// TODO...

	return true;
}

void ChangeIconView::closeMenuCallback(Ref* pRef)
{

	auto mt_des = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 10, visibleSize.height + 220));
	m_pDesLabel->runAction(mt_des);

	auto mt_close = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 180));
	m_pCloseMenu->runAction(mt_close);

	auto mt_bg = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 250));
	m_pBackground->runAction(mt_bg);

	auto mt_cl = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 180));
	m_pCloseLabel->runAction(mt_cl);
}