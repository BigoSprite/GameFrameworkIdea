#include "FailLayer.h"

FailLayer::FailLayer()
{}

FailLayer::~FailLayer()
{}

Scene* FailLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = FailLayer::create();
	scene->addChild(layer);
	return scene;
}


bool FailLayer::init()
{
	if (!Layer::init())
		return false;

	auto dic = Dictionary::createWithContentsOfFile("chinese.xml");

	auto size = Director::getInstance()->getVisibleSize();

	// ����
	bg = Sprite::create("mainback.png");
	bg->setPosition(size.width / 2, size.height / 2);
	addChild(bg, 10);
	// ʧ�ܵľ���
	fail = Sprite::create("fail.png");
	fail->setPosition(size.width / 2 + 100, size.height / 2 + 100);
	fail->setScale(0.5);
	addChild(fail, 10);
	//��͸����ɫ����
	transBg = Sprite::create("transparent.png");
	transBg->setPosition(size.width / 2, size.height / 2);
	transBg->setScaleX(1.5);
	transBg->setScaleY(0.001);
	addChild(transBg, 7);
	// ���¿�ʼlabel
	const char *str_restart = ((String*)dic->objectForKey("restartGame"))->_string.c_str();
	title = Label::createWithTTF(str_restart, "fonts/b.ttf", 32);
	title->setPosition(size.width / 2, size.height / 2 + 40);
	addChild(title, 12);


	//�� �� ��İ�ť
	left = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(FailLayer::yesButton, this));
	left->setScale(0.7);
	left->setScaleX(0.5);
	auto leftMenu = Menu::create(left, NULL);
	leftMenu->setPosition(size.width / 2 - 105, size.height / 2 - 20);
	addChild(leftMenu, 12);

	right = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(FailLayer::noButton, this));
	right->setScale(0.7);
	right->setScaleX(0.5);
	auto rightMenu = Menu::create(right, NULL);
	rightMenu->setPosition(size.width / 2 + 80, size.height / 2 - 20);
	addChild(rightMenu, 12);

	// �Ǻͷ��label
	//�� �� �������
	const char *str_yes = ((String*)dic->objectForKey("yes"))->_string.c_str();
	leftLabel = Label::createWithTTF(str_yes, "fonts/b.ttf", 25);
	leftLabel->setPosition(size.width / 2 - 105, size.height / 2 - 20);
	addChild(leftLabel, 13);

	const char *str_no = ((String*)dic->objectForKey("no"))->_string.c_str();
	rightLabel = Label::createWithTTF(str_no, "fonts/b.ttf", 25);
	rightLabel->setPosition(size.width / 2 + 80, size.height / 2 - 20);
	addChild(rightLabel, 13);



	// ���µ�Ӧ�������θó����µĴ����¼���������TODO������
	auto listener = EventListenerTouchOneByOne::create();
	/*����Ϊ�˷�ֹ�ڸò����ܹ�������ò�����ľ��飬����Ҫ
	������û������Ϊtrue������ontouchbegin������Ҫ��true*/

	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {

		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

// TODO...
void FailLayer::yesButton(Ref* r)
{}

// TODO...
void FailLayer::noButton(Ref* r)
{}