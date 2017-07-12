#include "FinalSceneView.h"
#include "Messages.h"

FinalSceneView::FinalSceneView()
{
}

FinalSceneView::~FinalSceneView()
{
}

bool FinalSceneView::init()
{
	if (!Sprite::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	Size vs = Director::getInstance()->getVisibleSize();

	// 背景
	m_pBg = Sprite::create("bg.jpg");
	m_pBg->setPosition(vs.width / 2, vs.height / 2);
	this->addChild(m_pBg);

	// 对话框
	m_pDialog = Sprite::create("gameEnd.png");
	m_pDialog->setPosition(vs.width / 2, -500);
	m_pDialog->setScale(0.8f);
	m_pDialog->setScaleY(1.1f);
	auto mt_dialog = MoveTo::create(2.0, Vec2(vs.width / 2, vs.height / 2));
	EaseOut * dialog_slow = EaseOut::create(mt_dialog, 7.0);
	m_pDialog->runAction(dialog_slow);
	this->addChild(m_pDialog, 2);

	m_pOk = Sprite::create("menu.png");
	m_pOk->setPosition(vs.width / 2, vs.height / 2 - 190);
	m_pOk->setScale(0.5f);
	m_pOk->setVisible(false);
	this->addChild(m_pOk, 2);

	const char *str1 = ((String*)dic->objectForKey("mainMenu"))->_string.c_str();
	m_pOkLabel = Label::createWithTTF(str1, "fonts/b.ttf", 20);
	m_pOkLabel->setPosition(vs.width / 2, vs.height / 2 - 190);
	this->addChild(m_pOkLabel, 3);
	m_pOkLabel->setVisible(false);

	m_pClear = Sprite::create("clear.png");
	m_pClear->setPosition(vs.width / 2 + 100, vs.height - 130);
	m_pClear->setVisible(false);
	m_pClear->setScale(0.6f);
	this->addChild(m_pClear, 2);

	m_pTitle = Sprite::create("praise2.png");
	m_pTitle->setPosition(vs.width / 2, vs.height - 250);
	m_pTitle->setScale(1.2);
	m_pTitle->setVisible(false);
	this->addChild(m_pTitle, 3);

	m_pGirl1 = Sprite::create("22-h.png");
	m_pGirl1->setPosition(vs.width - 160, 60);
	m_pGirl1->setVisible(false);
	this->addChild(m_pGirl1, 3);

	m_pGirl2 = Sprite::create("33-h.png");
	m_pGirl2->setPosition(vs.width - 80, 60);
	m_pGirl2->setVisible(false);
	this->addChild(m_pGirl2, 3);

	const char *str_web = ((String*)dic->objectForKey("web"))->_string.c_str();
	m_pWeb = Label::createWithTTF(str_web, "fonts/b.ttf", 18);
	m_pWeb->setPosition(vs.width / 2, vs.height / 2);
	m_pWeb->setVisible(false);
	this->addChild(m_pWeb, 3);

	m_pWeb2 = Label::createWithTTF("https://github.com/BigoSprite/GameFrameworkIdea", "fonts/b.ttf", 12);
	m_pWeb2->setPosition(vs.width / 2, vs.height / 2 - 40);
	m_pWeb2->setVisible(false);
	this->addChild(m_pWeb2, 3);

	auto vis = CallFunc::create([=]() {

		m_pOkLabel->setVisible(true);
		m_pOk->setVisible(true);
		m_pClear->setVisible(true);
		m_pTitle->setVisible(true);
		m_pGirl1->setVisible(true);
		m_pGirl2->setVisible(true);
		m_pWeb->setVisible(true);
		m_pWeb2->setVisible(true);
	});
	ActionInterval * delayVis = DelayTime::create(2.2);
	auto seqVis = Sequence::create(delayVis, vis, NULL);
	this->runAction(seqVis);

	return true;
}

void FinalSceneView::onEnter()
{
	Sprite::onEnter();

	// 触摸逻辑并发布消息
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* pTouch, Event* pEvent) {

		auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
		auto localPostion = target->convertTouchToNodeSpace(pTouch);
		auto size = target->getContentSize();
		auto rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(localPostion)) {

			m_pOkLabel->setTextColor(Color4B::BLUE);
	
			return true;
		}

		return false;
	};
	listener->onTouchEnded = [=](Touch* pTouch, Event* pEvent) {

		auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
		m_pOkLabel->setTextColor(Color4B::WHITE);

		// 发布消息
		std::string MSG = BACK_TO_WELCOME_SCENE_MSG;
		EventCustom eventCustom(MSG);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventCustom);
	};
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, m_pOk);
}

void FinalSceneView::onExit()
{

	Sprite::onExit();
}
