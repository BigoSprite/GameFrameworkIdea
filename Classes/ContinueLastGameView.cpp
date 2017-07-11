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

	m_pBackground = Sprite::create("mainback.png");
	m_pBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(m_pBackground);


	//选择文字
	//用xml保存中文，记得xml文件要存在resource文件夹里面才行
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	const char *str_des = ((String*)dic->objectForKey("isContinue1"))->_string.c_str();
	m_pDescreption1 = Label::createWithTTF(str_des, "fonts/b.ttf", 23);
	m_pDescreption1->setPosition(size.width / 2, size.height / 2 + 210);
	addChild(m_pDescreption1, 6);

	const char *str_des2 = ((String*)dic->objectForKey("isContinue2"))->_string.c_str();
	m_pDescreption2 = Label::createWithTTF(str_des2, "fonts/b.ttf", 23);
	m_pDescreption2->setPosition(size.width / 2 + 180, size.height / 2 + 210);
	addChild(m_pDescreption2, 6);




	//2个menu框
	m_pLeftMenuItem = MenuItemImage::create("menu.png", "menu.png",
		CC_CALLBACK_1(ContinueLastGameView::gameStart, this));
	m_pLeftMenuItem->setScale(0.5);
	auto leftMenu = Menu::create(m_pLeftMenuItem, NULL);
	leftMenu->setPosition(size.width / 2 - 15, size.height / 2 + 150);
	addChild(leftMenu, 6);

	m_pRightMenuItem = MenuItemImage::create("menu.png", "menu.png",
		CC_CALLBACK_1(ContinueLastGameView::gameStartNew, this));
	m_pRightMenuItem->setScale(0.5);
	auto rightMenu = Menu::create(m_pRightMenuItem, NULL);
	rightMenu->setPosition(size.width / 2 + 130, size.height / 2 + 150);
	addChild(rightMenu, 6);


	//是和否的label
	const char *str_yes = ((String*)dic->objectForKey("yes"))->_string.c_str();
	m_pYesLabel = Label::createWithTTF(str_yes, "fonts/b.ttf", 25);
	m_pYesLabel->setPosition(size.width / 2 - 15, size.height / 2 + 150);
	addChild(m_pYesLabel, 7);

	const char *str_no = ((String*)dic->objectForKey("no"))->_string.c_str();
	m_pNoLabel = Label::createWithTTF(str_no, "fonts/b.ttf", 25);
	m_pNoLabel->setPosition(size.width / 2 + 130, size.height / 2 + 150);
	addChild(m_pNoLabel, 7);




	//关卡数
	char c[10];
	int tempLevel = UserDefault::getInstance()->getIntegerForKey("level_Global");
	sprintf(c, "%d", tempLevel);
	std::string str = c;
	m_pLevelNum = Label::createWithTTF(str, "fonts/b.ttf", 25);
	m_pLevelNum->setColor(Color3B(242, 221, 28));
	m_pLevelNum->setPosition(size.width / 2 + 110, size.height / 2 + 210);
	addChild(m_pLevelNum, 7);



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