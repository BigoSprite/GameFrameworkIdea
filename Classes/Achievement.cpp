#include "Achievement.h"

Achievement::Achievement()
{
}

Achievement::~Achievement()
{
}

Scene* Achievement::createScene()
{
	auto scene = Scene::create();
	auto layer = Achievement::create();
	scene->addChild(layer);
	return scene;
}


bool Achievement::init()
{
	if (!Layer::init())
		return false;

	m_isLayerAdded = false;
	//��xml�������ģ��ǵ�xml�ļ�Ҫ����resource�ļ����������
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	visiableSize = Director::getInstance()->getVisibleSize();

	// ����
	m_pBg = Sprite::create("city2.png");
	m_pBg->setPosition(visiableSize.width / 2, visiableSize.height / 2);
	this->addChild(m_pBg, 1);
	// �˵�
	m_pMenu = Sprite::create("menuAchieve.png");
	m_pMenu->setPosition(visiableSize.width / 2 + 30, visiableSize.height / 2);
	m_pMenu->setScale(0.7);
	this->addChild(m_pMenu, 2);
	//����
	m_pTrophy = Sprite::create("trophy.png");
	m_pTrophy->setTag(1);
	m_pTrophy->setScale(1.5);
	m_pTrophy->setPosition(240, 512);
	this->addChild(m_pTrophy, 4);
	//��Ϣinfo
	m_pInfo = Sprite::create("info.png");
	m_pInfo->setTag(2);
	m_pInfo->setScale(1.5);
	m_pInfo->setPosition(305, 400);
	this->addChild(m_pInfo, 4);
	//����item
	m_pItem = Sprite::create("present.png");
	m_pItem->setTag(3);
	m_pItem->setScale(1.5);
	m_pItem->setPosition(242, 295);
	this->addChild(m_pItem, 4);

	m_pIconBtnList = { m_pTrophy, m_pInfo, m_pItem };

	//�������˵���ť
	m_pBackBtn = MenuItemImage::create("backAchieve.png", "backAchieve.png", 
		CC_CALLBACK_1(Achievement::goBackToMainmenu, this));
	m_pBackBtn->setScale(1.3);
	auto backMenu = Menu::create(m_pBackBtn, NULL);
	backMenu->setPosition(visiableSize.width / 2 - 70, visiableSize.height / 2 - 2);
	this->addChild(backMenu, 2);


	//���ܸ�scene�Ķ���
	//��͸����ɫ����
	m_pTransparentBg = Sprite::create("transparent.png");
	m_pTransparentBg->setPosition(visiableSize.width / 2, visiableSize.height - 110);
	m_pTransparentBg->setScaleX(1.5);
	m_pTransparentBg->setScaleY(0.001);
	this->addChild(m_pTransparentBg, 7);
	//����
	ActionInterval * delaytime_bg = CCDelayTime::create(1.5);
	auto st_bg = ScaleTo::create(0.5, 1.5, 0.8);  //�����x y��������ԭ��ͼƬ�Ĵ�С�ˣ���setscale֮��Ĵ�С��
	auto st_bg2 = ScaleTo::create(0.5, 1.5, 0.001);  //�����x y��������ԭ��ͼƬ�Ĵ�С�ˣ���setscale֮��Ĵ�С��
	ActionInterval * delay_bg = DelayTime::create(2.2);
	auto deleteBg = CallFunc::create([=]() {
		m_pTransparentBg->removeFromParent();
	});
	auto sq_bg = Sequence::create(delaytime_bg, st_bg, delay_bg, st_bg2, deleteBg, NULL);
	m_pTransparentBg->runAction(sq_bg);


	//Ů��������ܳ���
	m_pGirl = Sprite::create("girl1.png");
	m_pGirl->setScale(0.2);
	m_pGirl->setPosition(-100, visiableSize.height - 110);
	addChild(m_pGirl, 15);
	ActionInterval * delaytime_girl = CCDelayTime::create(2.0);
	auto mt_girl = MoveTo::create(0.5, Vec2(50, visiableSize.height - 110));
	auto mt_girl2 = MoveTo::create(0.5, Vec2(-100, visiableSize.height - 110));
	ActionInterval * delay_girl = DelayTime::create(1.5);
	auto sq_girl = Sequence::create(delaytime_girl, mt_girl, delay_girl, mt_girl2, NULL);
	m_pGirl->runAction(sq_girl);

	// ���ܵ�����
	//!!!��ʵ���ﲻ�ظ�������Ŀ�����ö�����ֻ��Ҫ�Ѹ�����Ŀ��Ϊ
	// ͸�������ĺ��ӣ���͸������������������
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

	
	return true;
}

void Achievement::goBackToMainmenu(cocos2d::Ref * r)
{

}


void Achievement::onEnter()
{
	Layer::onEnter();

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

				return true;
			}

			return false;
		};
		listener->onTouchEnded = [&](Touch* pTouch, Event* pEvent) {
			log("onTouchEnded called...");
		};
		listener->setSwallowTouches(true);
		dispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
	}

}

void Achievement::onExit()
{

	Layer::onExit();
}