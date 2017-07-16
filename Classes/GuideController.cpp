#include "GuideController.h"

GuideController::GuideController():vy_girl(0.5),progress(0)
{}

GuideController::~GuideController()
{}

bool GuideController::init()
{
	if (!BaseController::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	vs = Director::getInstance()->getVisibleSize();

	////////////背景
	auto bg = Sprite::create("mainback.png");
	bg->setPosition(vs.width / 2, vs.height / 2);
	this->addChild(bg, -1);

	////////////对话框
	auto dialog = Sprite::create("dialog_bg.png");
	dialog->setScale(0.00001f);
	dialog->setPosition(vs.width / 2, vs.height / 2);
	this->addChild(dialog, 0);


	//1 秋晓萌飞入动画：从左边外面进场
    girl = Sprite::create("teemo.png");
	girl->setScale(0.20);
	girl->setPosition(-100, vs.height / 2);
	this->addChild(girl, 1);
	// 动画
	auto mt_girl_1 = MoveTo::create(1, Vec2(100, vs.height / 2));
	EaseOut * eo_mt_girl_1 = EaseOut::create(mt_girl_1, 7.0);
	girl->runAction(eo_mt_girl_1);
	// 文字
	const char *str_1 = ((String*)dic->objectForKey("guide_intro_1"))->_string.c_str();
	m_pIntroDes = Label::createWithTTF(str_1, "fonts/b.ttf", 18);
	m_pIntroDes->setDimensions(190, 300);
	m_pIntroDes->setPosition(vs.width / 2 + 20, vs.height / 2 - 110);
	m_pIntroDes->setVisible(false);
	this->addChild(m_pIntroDes, 1);

	//下一项按钮
	auto nextItem_normal = Sprite::create("nextItemBtn_1.png");
	auto nextItem_selected = Sprite::create("nextItemBtn_2.png");
	next = MenuItemSprite::create(nextItem_normal, nextItem_selected,
		CC_CALLBACK_1(GuideController::nextIntro, this));

	menuNext = Menu::create(next, nullptr);
	menuNext->setScale(0.9f);
	menuNext->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menuNext->setPosition(vs.width / 2 - 25, vs.height / 2 - 90);
	menuNext->setVisible(false);
	this->addChild(menuNext, 1);



	//对话框动画
	auto dialog_st = ScaleTo::create(0.5f, 0.8f);
	ActionInterval * delay_dst = DelayTime::create(1.2);
	auto vis = CallFunc::create([=]() {

		menuNext->setVisible(true);
		m_pIntroDes->setVisible(true);
	});
	dialog->runAction(Sequence::create(delay_dst, dialog_st, vis, nullptr));




	auto listener = EventListenerTouchOneByOne::create();
	/*这里为了防止在该层点击能够点击到该层下面的精灵，所以要
	设置吞没函数，为true，而且ontouchbegin函数返要是true*/
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {
		//log("touched...");
		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//调用girl 移动函数
	girlPosY = vs.height / 2;
	this->schedule(SEL_SCHEDULE(&GuideController::move), 0.02f);


	return true;
}


Scene* GuideController::createScene()
{
	auto scene = Scene::create();
	auto layer = GuideController::create();
	scene->addChild(layer);
	return scene;
}

//NEXT介绍回调函数
void GuideController::nextIntro(Ref * r)
{
	progress++;

	switch (progress)
	{
	case 1:
		teemoMoving("guide_intro_2", 730, Point(50, 730));
		break;
	case 2:
		teemoMoving("guide_intro_3", 750, Point(250, 750));
		break;
	case 3:
		teemoMoving("guide_intro_4", 730, Point(350, 730));
		break;
	case 4:
		teemoMoving("guide_intro_5", 730, Point(400, 730));
		break;
	case 5:
		teemoMoving("guide_intro_6", 650, Point(45, 650));
		break;
	case 6:
		teemoMoving("guide_intro_7", 650, Point(250, 650));
		break;
	case 7:
		teemoMoving("guide_intro_8", 400, Point(100, 400));
		break;
	case 8:
		teemoMoving("guide_intro_9", 50, Point(450, 50));
		break;
	case 9:
		teemoMoving("guide_intro_10", 400, Point(245, 400));
		break;
	case 10:
		teemoMoving("guide_intro_11", 400, Point(100, 400));
		break;
	case 11:
		deleteLayer();
		break;
	}
}

//以下函数是girl移动函数
void GuideController::teemoMoving(std::string str, float girlPosY, cocos2d::Point destination)
{
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	const char *str_1 = ((String*)dic->objectForKey(str))->_string.c_str();
	m_pIntroDes->setString(StringUtils::format(str_1));

	this->girlPosY = girlPosY;
	vy_girl = 0.2;
	this->unschedule(SEL_SCHEDULE(&GuideController::move));
	ActionInterval * delay = DelayTime::create(0.55);
	auto schedule = CallFunc::create([=]() {

		this->schedule(SEL_SCHEDULE(&GuideController::move), 0.02f);
	});
	auto seq = Sequence::create(delay, schedule, NULL);
	this->runAction(seq);
	auto mt = MoveTo::create(0.5, destination);
	ScaleTo * st;
	if (progress == 7)
		st = ScaleTo::create(0.5, 0.2);
	else if (progress == 8)
		st = ScaleTo::create(0.5, 0.15);
	else if (progress == 9)
		st = ScaleTo::create(0.5, 0.2);
	else if (progress == 10)
		st = ScaleTo::create(0.5, 0.2);
	else
		st = ScaleTo::create(0.5, 0.1);

	auto sp = Spawn::create(mt, st, NULL);
	girl->runAction(sp);


	if (progress == 10)
	{
		menuNext->removeFromParent();

		auto close_normal = Sprite::create("closeBtn_1.png");
		auto close_selected = Sprite::create("closeBtn_2.png");
		next = MenuItemSprite::create(close_normal, close_selected,
			CC_CALLBACK_1(GuideController::nextIntro, this));
		auto closeMenu = Menu::create(next, NULL);
		closeMenu->setPosition(vs.width / 2, vs.height / 2 - 50);
		this->addChild(closeMenu, 1);

	}
}

void GuideController::deleteLayer()
{
	this->removeFromParent();
}

//萌妹上下移动函数
void GuideController::move(float dt)
{
	Size vs = Director::getInstance()->getVisibleSize();
	//萌妹沿着y轴上下移动
	int delta;
	if (progress == 0)
	{
		delta = 10;
	}
	else
	{
		delta = 4;

	}


	float nextGirlY = girl->getPositionY() - vy_girl;
	//log("nextGirlY: %f", nextGirlY);
	//log("girlPosY: %f", girlPosY);
	girl->setPositionY(nextGirlY);
	if (nextGirlY >= girlPosY + delta)
	{
		vy_girl = -vy_girl;
	}
	if (nextGirlY <= girlPosY - delta)
	{
		//log("vy_girl: %f",vy_girl);
		vy_girl = -vy_girl;
	}
}