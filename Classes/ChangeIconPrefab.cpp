#include "ChangeIconPrefab.h"
#include "DataManager.h"
#include "SimpleAudioEngine.h"

//#include "Game.h"

ChangeIconPrefab::ChangeIconPrefab()
{
}

ChangeIconPrefab::~ChangeIconPrefab()
{
}


bool ChangeIconPrefab::init()
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
		CC_CALLBACK_1(ChangeIconPrefab::closeMenuCallback, this));
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

	// 5个不同的icon///////////////////////////////
	//Game* game = new Game();//////////////////test
	//game->generatePoint();
	m_list = getDataManager().getIconVec();//////确保IconVec先被初始化

	char c1[10];
	sprintf(c1, "%d", m_list[0]);
	std::string str1 = c1;
	m_pIcon1 = Sprite::create("level1_" + str1 + ".png");
	m_pIcon1->setScale(0.36);
	m_pIcon1->setTag(m_list[0]);
	m_pIcon1->setPosition(90, visibleSize.height + 240);
	auto mt_1 = MoveTo::create(0.5, Vec2(90, visibleSize.height - 110));
	m_pIcon1->runAction(mt_1);
	this->addChild(m_pIcon1, 3);
	m_pIconList.pushBack(m_pIcon1);

	char c2[10];
	sprintf(c2, "%d", m_list[1]);
	std::string str2 = c2;
	m_pIcon2 = Sprite::create("level1_" + str2 + ".png");
	m_pIcon2->setScale(0.36);
	m_pIcon2->setTag(m_list[1]);
	m_pIcon2->setPosition(90 + 80, visibleSize.height + 240);
	auto mt_2 = MoveTo::create(0.5, Vec2(90 + 80, visibleSize.height - 110));
	m_pIcon2->runAction(mt_2);
	addChild(m_pIcon2, 3);
	m_pIconList.pushBack(m_pIcon2);

	char c3[10];
	sprintf(c3, "%d", m_list[2]);
	std::string str3 = c3;
	m_pIcon3 = Sprite::create("level1_" + str3 + ".png");
	m_pIcon3->setScale(0.36);
	m_pIcon3->setTag(m_list[2]);
	m_pIcon3->setPosition(90 + 160, visibleSize.height + 240);
	auto mt_3 = MoveTo::create(0.5, Vec2(90 + 160, visibleSize.height - 110));
	m_pIcon3->runAction(mt_3);
	addChild(m_pIcon3, 3);
	m_pIconList.pushBack(m_pIcon3);

	char c4[10];
	sprintf(c4, "%d", m_list[3]);
	std::string str4 = c4;
	m_pIcon4 = Sprite::create("level1_" + str4 + ".png");
	m_pIcon4->setScale(0.36);
	m_pIcon4->setTag(m_list[3]);
	m_pIcon4->setPosition(90 + 240, visibleSize.height + 240);
	auto mt_4 = MoveTo::create(0.5, Vec2(90 + 240, visibleSize.height - 110));
	m_pIcon4->runAction(mt_4);
	addChild(m_pIcon4, 3);
	m_pIconList.pushBack(m_pIcon4);

	char c5[10];
	sprintf(c5, "%d", m_list[4]);
	std::string str5 = c5;
	m_pIcon5 = Sprite::create("level1_" + str5 + ".png");
	m_pIcon5->setScale(0.36);
	m_pIcon5->setTag(m_list[4]);
	m_pIcon5->setPosition(90 + 320, visibleSize.height + 240);
	auto mt_5 = MoveTo::create(0.5, Vec2(90 + 320, visibleSize.height - 110));
	m_pIcon5->runAction(mt_5);
	addChild(m_pIcon5, 3);
	m_pIconList.pushBack(m_pIcon5);
	



	//////////////////////////////////触摸事件
	m_pLast = nullptr;
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch * t, Event * e) {

		if (m_pLast != nullptr)
		{
			m_pLast->stopAllActions();
			m_pLast->setScale(0.36);
		}
		for (int i = 0; i < m_pIconList.size(); i++)
		{
			if (m_pIconList.at(i)->getBoundingBox().containsPoint(t->getLocation()))
			{

				auto st = ScaleBy::create(0.5, 1.2);
				auto sq = Sequence::create(st, st->reverse(), NULL);
				auto rp = RepeatForever::create(sq);
				m_pIconList.at(i)->runAction(rp);
				m_pLast = m_pIconList.at(i);


				///////////////更新
				getDataManager().setSelectedIconValue(m_pIconList.at(i)->getTag()); //通过tag获取其board值
				break;
			}
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;

	return true;
}

void ChangeIconPrefab::closeMenuCallback(Ref* pRef)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.OGG");

	auto mt_des = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 10, visibleSize.height + 220));
	m_pDesLabel->runAction(mt_des);

	auto mt_close = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 180));
	m_pCloseMenu->runAction(mt_close);

	auto mt_bg = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 250));
	m_pBackground->runAction(mt_bg);

	auto mt_cl = MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height + 180));
	m_pCloseLabel->runAction(mt_cl);



	//5个icon的移除
	auto mt_1 = MoveTo::create(0.5, Vec2(90, visibleSize.height + 240));
	m_pIcon1->runAction(mt_1);
	auto mt_2 = MoveTo::create(0.5, Vec2(90 + 80, visibleSize.height + 240));
	m_pIcon2->runAction(mt_2);
	auto mt_3 = MoveTo::create(0.5, Vec2(90 + 160, visibleSize.height + 240));
	m_pIcon3->runAction(mt_3);
	auto mt_4 = MoveTo::create(0.5, Vec2(90 + 240, visibleSize.height + 240));
	m_pIcon4->runAction(mt_4);
	auto mt_5 = MoveTo::create(0.5, Vec2(90 + 320, visibleSize.height + 240));
	m_pIcon5->runAction(mt_5);

	auto deleteLayer = CallFunc::create([=]() {

		this->removeFromParentAndCleanup(true);
		getDataManager().setIsChangeLayerAdded(false);
		getDataManager().setSelectedIconValue(-1);
	});

	ActionInterval * delay = DelayTime::create(0.5);
	auto sq = Sequence::create(delay, deleteLayer, NULL);

	this->runAction(sq);
}

Scene* ChangeIconPrefab::createScene()
{
	auto scene = Scene::create();
	auto layer = ChangeIconPrefab::create();
	scene->addChild(layer);
	return scene;
}
