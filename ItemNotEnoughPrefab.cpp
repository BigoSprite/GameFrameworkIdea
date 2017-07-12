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

	// ����
	m_pBackground = Sprite::create("warning.png");
	m_pBackground->setScale(0.8f);
	this->addChild(m_pBackground, -1);
	// �����Ĵ�С
	auto contentSize = m_pBackground->getContentSize();

	// ��ɫicon
	m_pYellowIcon = Sprite::create("yellowWarning.png");
	m_pYellowIcon->setScale(0.6f);
	m_pYellowIcon->setPosition(
		contentSize.width / 2 - m_pYellowIcon->getContentSize().width,
		contentSize.height - m_pYellowIcon->getContentSize().height*1.2f);
	m_pBackground->addChild(m_pYellowIcon, 0);

	// ��ɫicon�ұߵ�����
	const char *str_notDes = ((String*)dic->objectForKey("notenough"))->_string.c_str();
	m_pNotEnoughDes = Label::createWithTTF(str_notDes, "fonts/b.ttf", 35);
	m_pNotEnoughDes->setPosition(
		m_pYellowIcon->getPosition().x + m_pYellowIcon->getContentSize().width + 30,
		m_pYellowIcon->getPosition().y);
	m_pBackground->addChild(m_pNotEnoughDes, 0);

	// ȷ����ť
	auto item = MenuItemImage::create("menu.png", "menu.png",
			CC_CALLBACK_1(ItemNotEnoughPrefab::__onOkButtonClickedCallback, this));
	item->setScale(0.6f);
	m_pMenu = Menu::create(item, nullptr);
	m_pMenu->setPosition(
		contentSize.width/2,
		contentSize.height/2 - 40);
	m_pBackground->addChild(m_pMenu, 0);


	// ok label
	const char *str_ok = ((String*)dic->objectForKey("ok"))->_string.c_str();
	m_pButtonLabel = Label::createWithTTF(str_ok, "fonts/b.ttf", 20);
	m_pButtonLabel->setPosition(m_pMenu->getPosition().x, m_pMenu->getPosition().y);
	m_pBackground->addChild(m_pButtonLabel, 1);

	return true;
}

void ItemNotEnoughPrefab::__onOkButtonClickedCallback(Ref* pRef)
{
	this->setVisible(false);
}