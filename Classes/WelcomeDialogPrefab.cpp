#include "WelcomeDialogPrefab.h"
#include "Global.h"

std::string serverEnName[20] = { "bejwt","dmxy","wwxf","srm",
"nqcl","aony","nkss","bdec","pejwt","hsmg","pcjb",
"swzh","za","ayd","gtly","jsf","jhjp","sjzh","zzxy","cjzd" };

WelcomeDialogPrefab::WelcomeDialogPrefab(): m_isCompleted (false)
{
}

WelcomeDialogPrefab::~WelcomeDialogPrefab()
{
}

WelcomeDialogPrefab* WelcomeDialogPrefab::createWithLevel(const int& level)
{
	auto instance = new WelcomeDialogPrefab();

	if (instance && instance->initWithLevel(level)) {
		return instance;
	}
	else {
		delete instance;
		instance = nullptr;
		return nullptr;
	}
	
}

bool WelcomeDialogPrefab::initWithLevel(const int& level)
{
	if (!Sprite::init())
		return false;

	m_iCurrentLevel = level;// ����ؿ���

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");
	visibleSize = Director::getInstance()->getVisibleSize();
	
	/// ����
	m_pServerBg = Sprite::create("city_bg.png");
	m_pServerBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_pServerBg->setScaleX(1);
	m_pServerBg->setScaleY(0.001f);
	this->addChild(m_pServerBg, -1);
	// ��������
	auto action_cityBg = Sequence::create(
		DelayTime::create(1.5f), 
		ScaleTo::create(0.5f, 1, 1), nullptr);
	m_pServerBg->runAction(action_cityBg);

	// ������ͼ��
	std::string server_icon_name = "server_" + std::to_string(level) + ".png";
	m_pServerIcon = Sprite::create(server_icon_name);
	m_pServerIcon->setPosition(-100, visibleSize.height / 2);
	this->addChild(m_pServerIcon, 0);
	auto action_server = Sequence::create(
		DelayTime::create(2.0f), 
		MoveTo::create(0.5f, Vec2(visibleSize.width/2 - m_pServerIcon->getContentSize().width - 20, visibleSize.height / 2)), nullptr);
	m_pServerIcon->runAction(action_server);


	/// ��������
	const char *str_city = ((String*)dic->objectForKey(serverEnName[m_iCurrentLevel - 1]))->_string.c_str();
	m_pServerName = Label::createWithTTF(str_city, "fonts/b.ttf", 30);
	m_pServerName->setColor(Color3B::ORANGE);
	m_pServerName->setRotationSkewX(15);
	m_pServerName->setPosition(650, visibleSize.height / 2);
	this->addChild(m_pServerName, 0);
	// �������ֶ���
	auto action_cityName = Sequence::create(
		DelayTime::create(2.0f),
		MoveTo::create(0.6, Vec2(visibleSize.width / 2 + m_pServerName->getContentSize().width/2, visibleSize.height/2)),
		DelayTime::create(2.0),
		CallFunc::create([=]() {
		m_pServerName->removeAllChildrenWithCleanup(true);
	}), nullptr);
	m_pServerName->runAction(action_cityName);


	/// ׼��
	////!!!!��װAPI ���ܼ���ʱͻ��һ���ⲿ�ֹ��������ã�
	std::string readyString = ((String*)dic->objectForKey("ready"))->_string.c_str();
	m_pReadyLabel = Label::createWithTTF(readyString, "fonts/zzgfh.otf", 80);
	m_pReadyLabel->setPosition(visibleSize.width + 200, visibleSize.height / 2);
	this->addChild(m_pReadyLabel, 1);
	// ׼������
	auto musicReady = CallFunc::create([=]() {
		//SimpleAudioEngine::getInstance()->playEffect("ready.OGG");
	});
	auto action_ready = Sequence::create(
		DelayTime::create(4.5f), 
		musicReady, 
		MoveTo::create(0.3f, Vec2(300, visibleSize.height / 2)),
		MoveTo::create(1.0f, Point(200, visibleSize.height / 2)), 
		MoveTo::create(0.3f, Point(-200, visibleSize.height / 2)), nullptr);
	m_pReadyLabel->runAction(action_ready);

	/// ��ʼ
	std::string startString = ((String*)dic->objectForKey("start"))->_string.c_str();
	m_pStartLabel = Label::createWithTTF(startString, "fonts/zzgfh.otf", 60);
	m_pStartLabel->setScale(2.5f);
	m_pStartLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_pStartLabel->setOpacity(0);
	this->addChild(m_pStartLabel, 2);

	auto action_removeComponts = CallFunc::create([=]() {

		m_pServerBg->removeFromParentAndCleanup(true);
		m_pServerIcon->removeFromParentAndCleanup(true);
		m_pStartLabel->removeFromParentAndCleanup(true);
		m_pServerName->removeFromParentAndCleanup(true);
	});
	auto action_start = Sequence::create(
		DelayTime::create(6.3f), 
		Spawn::create(FadeIn::create(0.5f), ScaleTo::create(0.5f, 1), nullptr), 
		DelayTime::create(0.4f), 
		action_removeComponts, nullptr);
	m_pStartLabel->runAction(action_start);

	// ������������Ϸ���Կ�ʼ��
	m_isCompleted = true;

	return true;
}


bool WelcomeDialogPrefab::getIsGameCanStart()
{
	return m_isCompleted;
}