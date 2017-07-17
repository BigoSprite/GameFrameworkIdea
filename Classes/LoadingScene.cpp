#include "LoadingScene.h"
#include "WelcomeSceneController.h"
#include "SimpleAudioEngine.h"


#include "FailDialogPrefab.h"

using namespace CocosDenshion;

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;

	__initLogo();

	__loadAudioResources();

	__loadPlistResources();

	// 0.5s之后进入欢迎界面场景
	auto seq = Sequence::create(
		DelayTime::create(1.5f), 
		CallFunc::create([=]() {
		Director::getInstance()->replaceScene(
			TransitionFade::create(1.0f, WelcomeSceneController::createScene()));
	    }), 
		nullptr
	);
	this->runAction(seq);

	return true;
}

void LoadingScene::__initLogo()
{
	Size size = Director::getInstance()->getVisibleSize();

	m_pBackground = Sprite::create("loading_bg.png");
	m_pBackground->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(m_pBackground, -1);

	m_pLogo = Label::createWithTTF("BigoSprite Idea", "fonts/ethnocentricrg.ttf", 25);
	m_pLogo->setPosition(size.width / 2, size.height / 2);
	m_pLogo->setColor(Color3B::WHITE);
	m_pLogo->setOpacity(0);
	this->addChild(m_pLogo, 0);

	auto fi = FadeIn::create(1.5f);
	m_pLogo->runAction(fi);
}


void LoadingScene::__loadAudioResources()
{
	//预加载音乐和bgm
	//添加音乐 预加载
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mswlm.OGG");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("air.OGG");

	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("mswlm.OGG", true);
	}
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.6f);

	//添加音效预加载
	SimpleAudioEngine::getInstance()->preloadEffect("firstBlood.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("4kill.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("5kill.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("6kill.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("7kill.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("8kill.OGG");

	SimpleAudioEngine::getInstance()->preloadEffect("explosion1.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("explosion2.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("explosion3.OGG");

	SimpleAudioEngine::getInstance()->preloadEffect("praise3.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("win.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("lose.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("change.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("bomb.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("button.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("menu.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("game_level_win.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("achieve.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("buySuccess.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("buyFail.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("ready.OGG");

	//罗秋雨 语音
	SimpleAudioEngine::getInstance()->preloadEffect("lqy_drag.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("4.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("5.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("6.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("7.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("8.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("9.wav");


	SimpleAudioEngine::getInstance()->setEffectsVolume(0.7);

}

void LoadingScene::__loadPlistResources()
{}