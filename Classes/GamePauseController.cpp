#include "GamePauseController.h"

GamePauseController::GamePauseController()
{
}

GamePauseController::~GamePauseController()
{
}

Scene* GamePauseController::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePauseController::create();
	scene->addChild(layer);
	return scene;
}

bool GamePauseController::init()
{
	if (!BaseController::init())
		return false;

	Size size = Director::getInstance()->getVisibleSize();
	//��xml�������ģ��ǵ�xml�ļ�Ҫ����resource�ļ����������
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	bg = Sprite::create("mainback.png");
	bg->setPosition(size.width / 2, size.height / 2);
	addChild(bg, 10);

	dialog = Sprite::create("gameEnd.png");
	dialog->setPosition(size.width / 2, size.height / 2);
	dialog->setScale(0.85);
	addChild(dialog, 11);

	//һЩlabel
	const char *str_pause = ((String*)dic->objectForKey("gamePause"))->_string.c_str();
	pauseLabel = Label::createWithTTF(str_pause, "fonts/b.ttf", 40);
	pauseLabel->setPosition(size.width / 2, size.height - 280);
	addChild(pauseLabel, 12);

	pointer1 = Sprite::create("pointer.png");
	pointer1->setPosition(size.width / 2 - 100, size.height - 280);
	pointer1->setScale(1.5);
	pointer1->setRotation(90);
	addChild(pointer1, 12);

	pointer2 = Sprite::create("pointer.png");
	pointer2->setPosition(size.width / 2 + 100, size.height - 280);
	pointer2->setScale(1.5);
	pointer2->setRotation(-90);
	addChild(pointer2, 12);

	//������Ϸ�˵�
	resume = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(GamePauseController::resumeGame, this));
	resume->setScale(0.7);
	auto resumeMenu = Menu::create(resume, NULL);
	resumeMenu->setPosition(size.width / 2, size.height - 450);
	addChild(resumeMenu, 12);

	const char *str_resume = ((String*)dic->objectForKey("continue"))->_string.c_str();
	label1 = Label::createWithTTF(str_resume, "fonts/b.ttf", 30);
	label1->setPosition(size.width / 2 - 5, size.height - 450);
	addChild(label1, 13);

	//�������˵�
	mainMenu = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(GamePauseController::goBackToMenu, this));
	mainMenu->setScale(0.7);
	auto mainMenuMenu = Menu::create(mainMenu, NULL);
	mainMenuMenu->setPosition(size.width / 2, size.height - 525);
	addChild(mainMenuMenu, 12);

	const char *str_menu = ((String*)dic->objectForKey("saveExit"))->_string.c_str();
	label2 = Label::createWithTTF(str_menu, "fonts/b.ttf", 22);
	label2->setPosition(size.width / 2 - 5, size.height - 525);
	addChild(label2, 13);

	//�������ִ�
	bgmSprite = Sprite::create("bgm_on.png");
	bgmSprite->setScale(1.3);
	bgm_on = MenuItemSprite::create(bgmSprite, bgmSprite, 
		CC_CALLBACK_1(GamePauseController::bgmOnOff, this));
	auto menuBGMON = Menu::create(bgm_on, NULL);
	menuBGMON->setPosition(size.width / 2 - 80, size.height / 2 + 40);
	addChild(menuBGMON, 13);

	/*if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		bgmSprite->setTexture("bgm_off.png");
	}*/

	//��Ϸ��Ч��
	effectSprite = Sprite::create("sound_on.png");
	effectSprite->setScale(1.3);
	effect_on = MenuItemSprite::create(effectSprite, effectSprite, 
		CC_CALLBACK_1(GamePauseController::effectOnOff, this));
	auto menuEFFECTON = Menu::create(effect_on, NULL);
	menuEFFECTON->setPosition(size.width / 2 + 30, size.height / 2 + 40);
	addChild(menuEFFECTON, 13);

	/*if (getDataManager().getEffect() == false)
	{
		effectSprite->setTexture("sound_off.png");
	}*/


	auto listener = EventListenerTouchOneByOne::create();
	/*����Ϊ�˷�ֹ�ڸò����ܹ�������ò�����ľ��飬����Ҫ
	������û������Ϊtrue������ontouchbegin������Ҫ��true*/

	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *t, Event *e) {

		log("layer outouch");
		return true;

	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void GamePauseController::onEnter()
{
	BaseController::onEnter();
	this->setSwallowsTouches(true);
}

void GamePauseController::onExit()
{
	BaseController::onExit();
}

void GamePauseController::resumeGame(Ref* ref)
{
	//SimpleAudioEngine::getInstance()->playEffect("menu.OGG");
	//ȥ���ò�,���൱�ڻָ���Ϸ��
	this->removeFromParentAndCleanup(true);
}

void GamePauseController::goBackToMenu(Ref* ref)
{}

void GamePauseController::bgmOnOff(Ref* ref)
{}

void GamePauseController::effectOnOff(Ref* ref)
{}

