#include "ItemNotEnoughPrefab.h"

ItemNotEnoughPrefab::ItemNotEnoughPrefab()
{
}

ItemNotEnoughPrefab::~ItemNotEnoughPrefab()
{
}

bool ItemNotEnoughPrefab::init()
{
	if (!Sprite::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	// 背景
	m_pBackground = Sprite::create("dialog_bg.png");
	m_pBackground->setScale(0.8f);
	m_pBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(m_pBackground, -1);
	// 背景的大小
	auto contentSize = m_pBackground->getContentSize();

	// 黄色icon
	m_pYellowIcon = Sprite::create("yellowWarning.png");
	m_pYellowIcon->setScale(0.6f);
	m_pYellowIcon->setColor(Color3B::ORANGE);
	m_pYellowIcon->setPosition(
		contentSize.width / 2 - m_pYellowIcon->getContentSize().width,
		contentSize.height - m_pYellowIcon->getContentSize().height * 0.8f);
	m_pBackground->addChild(m_pYellowIcon, 0);

	// 黄色icon右边的描述
	const char *str_notDes = ((String*)dic->objectForKey("notenough"))->_string.c_str();
	m_pNotEnoughDes = Label::createWithTTF(str_notDes, "fonts/b.ttf", 35);
	m_pNotEnoughDes->setColor(Color3B::ORANGE);
	m_pNotEnoughDes->setPosition(
		m_pYellowIcon->getPosition().x + m_pYellowIcon->getContentSize().width + 30,
		m_pYellowIcon->getPosition().y);
	m_pBackground->addChild(m_pNotEnoughDes, 0);

	//关闭按钮
	auto close_normal = Sprite::create("closeBtn_red_1.png");
	auto close_selected = Sprite::create("closeBtn_red_2.png");
	m_pCloseItem = MenuItemSprite::create(close_normal, close_selected,
		CC_CALLBACK_1(ItemNotEnoughPrefab::__onOkButtonClickedCallback, this));
	m_pMenu = Menu::create(m_pCloseItem, nullptr);
	m_pMenu->setScale(0.75f);
	m_pMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_pMenu->setPosition(
		contentSize.width / 2 - 60,
		-50);
	m_pBackground->addChild(m_pMenu, 0);

	//// 禁止触摸向下传递#1和#2
	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);// #1
	//listener->onTouchBegan = [=](Touch* pTouch, Event* pEvent) {
	//	return true;// #2
	//};
	//dispatcher->addEventListenerWithSceneGraphPriority(listener, m_pBackground);


	return true;
}

void ItemNotEnoughPrefab::__onOkButtonClickedCallback(Ref* pRef)
{
	this->setVisible(false);
}