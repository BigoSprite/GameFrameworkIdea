#include "BottomTexturePrefab.h"

BottomTexturePrefab::BottomTexturePrefab()
{
}

BottomTexturePrefab::~BottomTexturePrefab()
{
}


bool BottomTexturePrefab::init()
{
	if (!Sprite::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();

	///bg
	m_pBg = Sprite::create("dialog.png");
	m_pBg->setPosition(visibleSize.width / 2, - m_pBg->getContentSize().height/2 - 22 );
	m_pBg->setScaleY(1.25f);
	this->addChild(m_pBg, -1);

	auto action_bg = Sequence::create(
		DelayTime::create(2.7f), 
		EaseOut::create(MoveTo::create(1, Vec2(visibleSize.width / 2, m_pBg->getContentSize().height / 2 + 22)), 7.0f),
		nullptr);
	m_pBg->runAction(action_bg);

	///icon
	m_pIcon = Sprite::create("level1_1.png");
	m_pIcon->setPosition(visibleSize.width / 2 - 160, 80);
	m_pIcon->setScale(0.5);
	m_pIcon->setVisible(false);
	this->addChild(m_pIcon, 0);
	///icon name
	m_pIconName = Label::createWithTTF("", "fonts/b.ttf", 20);
	m_pIconName->setPosition(visibleSize.width / 2 - 160, 40);
	m_pIconName->setVisible(false);
	this->addChild(m_pIconName, 0);

	///description
	m_pDescription = Label::createWithTTF("", "fonts/b.ttf", 20);
	m_pDescription->setPosition(visibleSize.width / 2 - 90, 40);
	m_pDescription->setAnchorPoint(Point(0, 0));
	m_pDescription->setDimensions(300, 60);
	this->addChild(m_pDescription, 0);

	return true;
}

void BottomTexturePrefab::updateShow(const std::string& enIconName, const int& curBordVal)
{
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	///更新图标及其名字
	std::string icon_name = "level1_" + std::to_string(curBordVal) + ".png";

	m_pIcon->setTexture(icon_name);
	m_pIcon->setVisible(true);

	//log("%s", enIconName);
	auto iconname = ((String*)dic->objectForKey(enIconName))->_string.c_str();
	m_pIconName->setString(iconname);
	m_pIconName->setVisible(true);


	///更新描述
	int randNumber = rand() % 4 + 1;
	std::string key_name = enIconName + "_" + std::to_string(randNumber);
	const char *icon_description = ((String*)dic->objectForKey(key_name))->_string.c_str();
	m_pDescription->setString(icon_description);
}
