#include "AchievementView.h"
#include "Tags.h"
#include "Messages.h"

AchievementView::AchievementView()
{
}

AchievementView::~AchievementView()
{
}

bool AchievementView::init()// 类似于Unity中的start函数
{
	if (!ui::Layout::init())
		return false;

	visiableSize = Director::getInstance()->getVisibleSize();

	// 背景
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setBackGroundImage("city1.png");
	this->setContentSize(Size(500, 800));
	this->setLayoutType(ui::LayoutType::RELATIVE);

	// 初始化
	_initDes();
	_initMenu();

	return true;
}

void AchievementView::onEnter()
{
	ui::Layout::onEnter();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	for (auto& sprite : m_pIconBtnList) {
		listener->onTouchBegan = [=](Touch* pTouch, Event* pEvent) {

			auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
			auto localPoint = target->convertTouchToNodeSpace(pTouch);
			auto size = target->getContentSize();
			auto rect = Rect(0, 0, size.width, size.height);

			if (rect.containsPoint(localPoint)) {
				log("%d", target->getTag());

				target->setColor(Color3B::BLUE);

				return true;
			}

			return false;
		};
		listener->onTouchEnded = [&](Touch* pTouch, Event* pEvent) {
			log("onTouchEnded called...");
	
			auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
			target->setColor(Color3B::WHITE);

			// 发布消息
			std::string MSG = ACHEVEMENTVIEW_TOUCH_MSG + std::to_string(target->getTag());
			EventCustom eventCustom(MSG);
			eventCustom.setUserData((void*)target->getTag());
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventCustom);
		};
		listener->setSwallowTouches(true);
		dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
	}
}

void AchievementView::onExit()
{

	ui::Layout::onExit();
}


void AchievementView::_initDes()
{
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	// 介绍的背景
	m_pDesBg = Sprite::create("transparent.png");
	m_pDesBg->setPosition(visiableSize.width / 2, visiableSize.height - 110);
	this->addChild(m_pDesBg, 1);
	m_pDesBg->setScaleX(1.5);
	m_pDesBg->setScaleY(0.001);
	auto delaytime_bg = DelayTime::create(1.5);
	auto st_bg = ScaleTo::create(0.5, 1.5, 0.8);
	auto st_bg2 = ScaleTo::create(0.5, 1.5, 0.001);
	auto delay_bg = DelayTime::create(2.2);
	auto deleteBg = CallFunc::create([=]() {
		m_pDesBg->removeFromParent();
	});
	auto sq_bg = Sequence::create(delaytime_bg, st_bg, delay_bg, st_bg2, deleteBg, NULL);
	m_pDesBg->runAction(sq_bg);

	//女孩
	m_pGirl = Sprite::create("girl1.png");
	m_pGirl->setScale(0.2);
	m_pGirl->setPosition(-100, visiableSize.height - 110);
	this->addChild(m_pGirl, 2);
	ActionInterval * delaytime_girl = CCDelayTime::create(2.0);
	auto mt_girl = MoveTo::create(0.5, Vec2(50, visiableSize.height - 110));
	auto mt_girl2 = MoveTo::create(0.5, Vec2(-100, visiableSize.height - 110));
	ActionInterval * delay_girl = DelayTime::create(1.5);
	auto sq_girl = Sequence::create(delaytime_girl, mt_girl, delay_girl, mt_girl2, NULL);
	m_pGirl->runAction(sq_girl);

	// 介绍的文字
	const char *str = ((String*)dic->objectForKey("achieve1"))->_string.c_str();
	m_pDescription = Label::createWithTTF(str, "fonts/b.ttf", 23);
	m_pDescription->setPosition(visiableSize.width / 2 - 140, visiableSize.height - 100);
	m_pDescription->setAnchorPoint(Point(0, 0));
	m_pDescription->setOpacity(0);
	this->addChild(m_pDescription, 8);
	auto fi = FadeIn::create(0.5);
	ActionInterval * delay = DelayTime::create(2.1);
	ActionInterval * delay_des = DelayTime::create(1.2);
	auto deleteDes = CallFunc::create([=]() {
		m_pDescription->removeFromParent();
	});
	auto seq = Sequence::create(delay, fi, delay_des, deleteDes, NULL);
	m_pDescription->runAction(seq);
}

void AchievementView::_initMenu()
{
	// 菜单
	m_pMenuBackground = Sprite::create("menuAchieve.png");
	m_pMenuBackground->setPosition(visiableSize.width / 2 + 30, visiableSize.height / 2);
	m_pMenuBackground->setScale(0.7f);
	this->addChild(m_pMenuBackground, 1);
	//奖杯
	m_pTrophy = Sprite::create("trophy.png");
	m_pTrophy->setTag(AchievementViewTag::TROPHY_TAG);
	m_pTrophy->setScale(1.5f);
	m_pTrophy->setPosition(240, 512);
	this->addChild(m_pTrophy, 4);
	//信息info
	m_pInfo = Sprite::create("info.png");
	m_pInfo->setTag(AchievementViewTag::INFO_TAG);
	m_pInfo->setScale(1.5f);
	m_pInfo->setPosition(305, 400);
	this->addChild(m_pInfo, 4);
	//道具item
	m_pItem = Sprite::create("present.png");
	m_pItem->setTag(AchievementViewTag::ITEM_TAG);
	m_pItem->setScale(1.5f);
	m_pItem->setPosition(242, 295);
	this->addChild(m_pItem, 4);

	m_pIconBtnList = { m_pTrophy, m_pInfo, m_pItem };
	
	//返回主菜单按钮
	m_pBackBtn = MenuItemImage::create("backAchieve.png", "backAchieve.png",
		CC_CALLBACK_1(AchievementView::_goBackToMainmenu, this));
	m_pBackBtn->setScale(1.3f);
	auto backMenu = Menu::create(m_pBackBtn, NULL);
	backMenu->setPosition(visiableSize.width / 2 - 70, visiableSize.height / 2 - 2);
	this->addChild(backMenu, 2);
}

void AchievementView::_goBackToMainmenu(Ref * ref)
{
	log("go back to main scene...");
	// 发布消息
	std::string MSG = BACK_TO_WELCOME_SCENE_MSG;
	EventCustom eventCustom(MSG);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventCustom);
}