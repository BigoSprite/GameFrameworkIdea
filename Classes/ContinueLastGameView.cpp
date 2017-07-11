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

	// ������Layout��ê�������½�
	this->setContentSize(Size(500, 800));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto size = this->getContentSize();

	m_pBackground = Sprite::create("mainback.png");
	m_pBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(m_pBackground);


	//ѡ������
	//��xml�������ģ��ǵ�xml�ļ�Ҫ����resource�ļ����������
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	const char *str_des = ((String*)dic->objectForKey("isContinue1"))->_string.c_str();
	m_pDescreption1 = Label::createWithTTF(str_des, "fonts/b.ttf", 23);
	m_pDescreption1->setPosition(size.width / 2, size.height / 2 + 210);
	addChild(m_pDescreption1, 6);

	const char *str_des2 = ((String*)dic->objectForKey("isContinue2"))->_string.c_str();
	m_pDescreption2 = Label::createWithTTF(str_des2, "fonts/b.ttf", 23);
	m_pDescreption2->setPosition(size.width / 2 + 180, size.height / 2 + 210);
	addChild(m_pDescreption2, 6);




	//2��menu��
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


	//�Ǻͷ��label
	const char *str_yes = ((String*)dic->objectForKey("yes"))->_string.c_str();
	m_pYesLabel = Label::createWithTTF(str_yes, "fonts/b.ttf", 25);
	m_pYesLabel->setPosition(size.width / 2 - 15, size.height / 2 + 150);
	addChild(m_pYesLabel, 7);

	const char *str_no = ((String*)dic->objectForKey("no"))->_string.c_str();
	m_pNoLabel = Label::createWithTTF(str_no, "fonts/b.ttf", 25);
	m_pNoLabel->setPosition(size.width / 2 + 130, size.height / 2 + 150);
	addChild(m_pNoLabel, 7);




	//�ؿ���
	char c[10];
	int tempLevel = UserDefault::getInstance()->getIntegerForKey("level_Global");
	sprintf(c, "%d", tempLevel);
	std::string str = c;
	m_pLevelNum = Label::createWithTTF(str, "fonts/b.ttf", 25);
	m_pLevelNum->setColor(Color3B(242, 221, 28));
	m_pLevelNum->setPosition(size.width / 2 + 110, size.height / 2 + 210);
	addChild(m_pLevelNum, 7);



	/*����Ϊ�˷�ֹ�ڸò����ܹ�������ò�����ľ��飬����Ҫ
	������û������Ϊtrue������ontouchbegin������Ҫ��true*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {

		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

// ������Ϸ
void ContinueLastGameView::gameStart(Ref * r)
{
	log("ContinueLastGameView::gameStart");

	// ������Ϣ
	std::string MSG = CONTINUE_LAST_PLAY_MSG;
	EventCustom customEvent(MSG);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}

//���¿�ʼ��Ϸ
void ContinueLastGameView::gameStartNew(Ref * r)
{
	log("ContinueLastGameView::gameStartNew");

	// ������Ϣ
	std::string MSG = START_NEW_PLAY_MSG;
	EventCustom customEvent(MSG);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}