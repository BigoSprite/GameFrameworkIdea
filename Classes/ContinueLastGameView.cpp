#include "ContinueLastGameView.h"
#include "DataManager.h"
#include "Game.h"
#include "Messages.h"

ContinueLastGameView::ContinueLastGameView()
{
}

ContinueLastGameView::~ContinueLastGameView()
{
}

bool ContinueLastGameView::init()
{
	if (!ui::Layout::init())
		return false;

	// ！！！Layout的锚点在左下角
	this->setContentSize(Size(500, 800));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto size = this->getContentSize();

	// 黑色背景
	m_pBackground = Sprite::create("mainback.png");
	m_pBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(m_pBackground, -1);

	//////////////////////////// 提示框
	// 背景
	m_pTipBg = Sprite::create("tip_bg_1.png");
	m_pTipBg->setPosition(size.width/2, size.height/2 + 100);
	this->addChild(m_pTipBg, 0);
	auto tipBgSize = m_pTipBg->getContentSize();
	//// 是-btn
	auto normal_1 = Sprite::create("yesBtn_1.png");
	auto selected_1 = Sprite::create("yesBtn_2.png");
	m_pLeftMenuItem = MenuItemSprite::create(normal_1, selected_1,
		CC_CALLBACK_1(ContinueLastGameView::gameStart, this));
	auto menu = Menu::create(m_pLeftMenuItem, nullptr);
	menu->setPosition(tipBgSize.width / 2 - 36, normal_1->getContentSize().height / 2 + 7);
	m_pTipBg->addChild(menu, 0);
	//// 否-btn
	auto normal_2 = Sprite::create("noBtn_1.png");
	auto selected_2 = Sprite::create("noBtn_2.png");
	m_pRightMenuItem = MenuItemSprite::create(normal_2, selected_2,
		CC_CALLBACK_1(ContinueLastGameView::gameStartNew, this));
	auto menu_2 = Menu::create(m_pRightMenuItem, nullptr);
	menu_2->setPosition(tipBgSize.width / 2 + 36, normal_1->getContentSize().height / 2 + 7);
	m_pTipBg->addChild(menu_2, 0);
	//// 选择文字
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	// title
	const char *str_des2 = ((String*)dic->objectForKey("isContinue_title"))->_string.c_str();
	m_pDescreption2 = Label::createWithTTF(str_des2, "fonts/b.ttf", 22);
	m_pDescreption2->setPosition(tipBgSize.width / 2 + 10, tipBgSize.height / 2 + 40);
	m_pTipBg->addChild(m_pDescreption2, 0);
	// content
	const char *str_des = ((String*)dic->objectForKey("isContinue_content"))->_string.c_str();
	m_pDescreption1 = Label::createWithTTF(str_des, "fonts/b.ttf", 18);
	m_pDescreption1->setPosition(tipBgSize.width / 2, tipBgSize.height / 2 + 9);
	m_pTipBg->addChild(m_pDescreption1, 0);
	////关卡数
	char c[10];
	int tempLevel = UserDefault::getInstance()->getIntegerForKey("level_Global");
	sprintf(c, "%d", tempLevel);
	std::string str = c;
	m_pLevelNum = Label::createWithTTF(str, "fonts/b.ttf", 18);
	m_pLevelNum->setColor(Color3B(242, 221, 28));
	m_pLevelNum->setPosition(m_pDescreption1->getPosition().x + m_pDescreption1->getContentSize().width/2 + 6, m_pDescreption1->getPosition().y);
	m_pTipBg->addChild(m_pLevelNum, 0);



	/*这里为了防止在该层点击能够点击到该层下面的精灵，所以要
	设置吞没函数，为true，而且ontouchbegin函数返要是true*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {

		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

// 继续游戏
void ContinueLastGameView::gameStart(Ref * r)
{
	log("ContinueLastGameView::gameStart");

	// 发布消息
	std::string MSG = CONTINUE_LAST_PLAY_MSG;
	EventCustom customEvent(MSG);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}

//重新开始游戏
void ContinueLastGameView::gameStartNew(Ref * r)
{
	log("ContinueLastGameView::gameStartNew");

	// 发布消息
	std::string MSG = START_NEW_PLAY_MSG;
	EventCustom customEvent(MSG);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}