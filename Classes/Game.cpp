#include "Game.h"
#include "DataManager.h"
#include "GuideController.h"
#include "ChangeIconPrefab.h"
#include "BombIconPrefab.h"
#include "GamePauseController.h"
#include "WelcomeSceneController.h"
#include "FinalSceneController.h"
#include "FailDialogPrefab.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


Game::Game()
{
}

Game::~Game()
{
}

Scene* Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!BaseController::init())
		return false;

	//这里更新每一次玩到的关卡数 
	int tempLevel = getDataManager().getGameLevel();
	UserDefault::getInstance()->setIntegerForKey("level_Global", tempLevel);

	//将每一关初始化分数存进文件，下次进游戏要用
	int tempCurrent = getDataManager().getInitCurrentScore();
	UserDefault::getInstance()->setIntegerForKey("levelInitScore", tempCurrent);

	//更新目标分数
	int tempTargetScore = getDataManager().getLevelTargetScore();
	UserDefault::getInstance()->setIntegerForKey("level_Global_targetScore", tempTargetScore);

	UserDefault::getInstance()->flush();

	firstHit = true;//第一次点击，播放firstblood音效
	isGameOverHit = false;

	//剩余奖励数组,5个以下才奖励
	leftBonus.push_back(1000);
	leftBonus.push_back(500);
	leftBonus.push_back(250);
	leftBonus.push_back(125);
	leftBonus.push_back(100);


	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	// 窗口大小
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


	/// 道具不足提示框
	m_pItemNotEnoughSprite = ItemNotEnoughPrefab::create();
	m_pItemNotEnoughSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	m_pItemNotEnoughSprite->setVisible(false);
	this->addChild(m_pItemNotEnoughSprite, 10);

	tower1 = nullptr;
	tower2 = nullptr;

	isGameReady = false;
	isTargetReached = false;
	curLevel = getDataManager().getGameLevel();




	////-------------------------------------------2个功能性道具
	//// 道具1的icon
	//changeIcon = MenuItemImage::create("changeIcon.png", "changeIcon.png", 
	//	CC_CALLBACK_1(Game::changeIconType, this));
	//changeIcon->setScale(0.5);
	//auto changeIconMenu = Menu::create(changeIcon, nullptr);
	//changeIconMenu->setPosition(visibleSize.width / 2 + 100, visibleSize.height - 75);
	//addChild(changeIconMenu, 3);
	//changeIcon->setOpacity(0);// 默认不显示
	//ActionInterval * delay_ci = DelayTime::create(4.6);   //每个sprite出现间隔0.4秒
	//auto fi_ci = FadeIn::create(0.5);
	//auto seq_ci = Sequence::create(delay_ci, fi_ci, nullptr);
	//changeIcon->runAction(seq_ci);
	////道具1的数量label
	//char cChangeIconNum[10];
	//sprintf(cChangeIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("ChangeNum"));
	//std::string strChangeIconNum = cChangeIconNum;
	//changeIconLabel = Label::createWithTTF(cChangeIconNum, "fonts/pirulenrg.ttf", 18);
	//changeIconLabel->setPosition(visibleSize.width / 2 + 125, visibleSize.height - 92);
	//addChild(changeIconLabel, 3);
	//changeIconLabel->setOpacity(0);
	//ActionInterval * delay_cil = DelayTime::create(4.6);   //每个sprite出现间隔0.4秒
	//auto fi_cil = FadeIn::create(0.5);
	//auto seq_cil = Sequence::create(delay_cil, fi_cil, nullptr);
	//changeIconLabel->runAction(seq_cil);
	////道具2的icon
	//bombIcon = MenuItemImage::create("bomb.png", "bomb.png", 
	//	CC_CALLBACK_1(Game::bombIconType, this));
	//bombIcon->setScale(0.5);
	//auto bombIconMenu = Menu::create(bombIcon, nullptr);
	//bombIconMenu->setPosition(visibleSize.width / 2 + 160, visibleSize.height - 75);
	//addChild(bombIconMenu, 3);
	//bombIcon->setOpacity(0);
	//ActionInterval * delay_bi = DelayTime::create(5);   //每个sprite出现间隔0.4秒
	//auto fi_bi = FadeIn::create(0.5);
	//auto seq_bi = Sequence::create(delay_bi, fi_bi, nullptr);
	//bombIcon->runAction(seq_bi);
	////道具2的数量label
	//char cBombIconNum[10];
	//sprintf(cBombIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("BombNum"));
	//std::string strBombIconNum = cBombIconNum;
	//bombIconLabel = Label::createWithTTF(cBombIconNum, "fonts/pirulenrg.ttf", 18);
	//bombIconLabel->setPosition(visibleSize.width / 2 + 185, visibleSize.height - 92);
	//addChild(bombIconLabel, 3);
	//bombIconLabel->setOpacity(0);
	//ActionInterval * delay_bil = DelayTime::create(5);   //每个sprite出现间隔0.4秒
	//auto fi_bil = FadeIn::create(0.5);
	//auto seq_bil = Sequence::create(delay_bil, fi_bil, nullptr);
	//bombIconLabel->runAction(seq_bil);
	////让道具数字变红
	//if (UserDefault::getInstance()->getIntegerForKey("BombNum") == 0)
	//{
	//	bombIconLabel->setColor(Color3B(208, 52, 13));
	//}
	//if (UserDefault::getInstance()->getIntegerForKey("ChangeNum") == 0)
	//{
	//	changeIconLabel->setColor(Color3B(208, 52, 13));
	//}
	////-------------------------------------------END 2个功能性道具


	/// 准备对话框
	m_pWelcomeDialogPrefab = WelcomeDialogPrefab::createWithLevel(curLevel);
	this->addChild(m_pWelcomeDialogPrefab, 10);
	isGameReady = m_pWelcomeDialogPrefab->getIsGameCanStart();


	//------------------------------------添加怎么玩的层,只有第一关才有
	if (getDataManager().getGameLevel() == 1)
	{
		ActionInterval * delaytime_htp = CCDelayTime::create(7.5);
		auto addHowToPlay = CallFunc::create([=]() {
			auto htp = GuideController::create();
			htp->setPosition(0, 0);
			this->addChild(htp, 20);
		});
		auto seq_htp = Sequence::create(delaytime_htp, addHowToPlay, nullptr);
		this->runAction(seq_htp);
	}
	//------------------------------------END 添加怎么玩的层,只有第一关才有


	//-------------------------------------每一关卡的目标和等级
	//更新每一关的目标分数
	target_score = getDataManager().getLevelTargetScore();
	targetScore_label = Label::createWithTTF(std::to_string(target_score), "fonts/watch.ttf", 25);
	targetScore_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	targetScore_label->setPosition(visibleSize.width / 2, 765);
	targetScore_label->setOpacity(0);
	auto seq_ts = Sequence::create(DelayTime::create(4.2f), FadeIn::create(0.5f), nullptr);
	targetScore_label->runAction(seq_ts);
	this->addChild(targetScore_label, 5);

	// 等级数目label-number
	levelNum_label = Label::createWithTTF(std::to_string(curLevel), "fonts/ethnocentricrg.ttf", 30);
	levelNum_label->setPosition(visibleSize.width / 2 - 120, visibleSize.height - 150);
	addChild(levelNum_label, 2);
	levelNum_label->setOpacity(0);
	auto seq_lnl = Sequence::create(DelayTime::create(5.6), FadeIn::create(0.5), nullptr);
	levelNum_label->runAction(seq_lnl);
	//-------------------------------------END 每一关卡的目标和等级


	/// 背景图片
	std::string bgName = "level_bg_" + std::to_string(curLevel) + ".png";
	auto background = Sprite::create(bgName);
	background->setAnchorPoint(Vec2(0, 0));
	this->addChild(background, -1);



	timerRunning = false;
	gameIsOver = false;


	/// 游戏底部对话框
	m_pBottomTexturePrefab = BottomTexturePrefab::create();
	this->addChild(m_pBottomTexturePrefab, 2);


	//-------------------------------------------------背景图片,上面的

	auto top_bar_bg = Sprite::create("top_bar_bg.png");
	top_bar_bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	top_bar_bg->setPosition(visibleSize.width / 2, visibleSize.height + 200);
	this->addChild(top_bar_bg, 3);
	auto action_top_bar_bg = Sequence::create(
		DelayTime::create(2.7f),
		EaseOut::create(MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height)), 7.0),
		nullptr);
	top_bar_bg->runAction(action_top_bar_bg);


	// 暂停和返回主菜单
	// 暂停
	auto pauseMenu_normal = Sprite::create("pauseBtn_1.png");
	auto pauseMenu_Selected = Sprite::create("pauseBtn_2.png");
	auto pauseItem = MenuItemSprite::create(pauseMenu_normal, pauseMenu_Selected, 
		CC_CALLBACK_1(Game::returnToMenu, this));
	pauseItem->setScale(0.3f);
	auto pauseMenu = Menu::create(pauseItem, nullptr);
	pauseMenu->setPosition(62, visibleSize.height - 25);
	this->addChild(pauseMenu, 3);

	pauseMenu->setOpacity(0);
	pauseMenu->runAction(Sequence::create(DelayTime::create(3.0f), FadeIn::create(0.5f), nullptr));
	
	// 返回主菜单
	auto back2MainMenu_normal = Sprite::create("mainMenu_1.png");
	auto back2MainMenu_Selected = Sprite::create("mainMenu_2.png");
	auto backItem = MenuItemSprite::create(back2MainMenu_normal, back2MainMenu_Selected,
		CC_CALLBACK_1(Game::restartGame, this));
	backItem->setScale(0.3f);
	auto backMenu = Menu::create(backItem, nullptr);
	backMenu->setPosition(128, visibleSize.height - 25);
	this->addChild(backMenu, 3);

	backMenu->setOpacity(0);
	backMenu->runAction(Sequence::create(DelayTime::create(3.4f), FadeIn::create(0.5f), nullptr));

	/*btm = MenuItemImage::create("backToMenu.png", "backToMenu.png", 
		CC_CALLBACK_1(Game::returnToMenu, this));
	btm->setAnchorPoint(Point(0, 0));
	btm->setScale(0.45);
	auto btm_menu = Menu::create(btm, nullptr);
	btm_menu->setPosition(visibleSize.width / 2 - 220, visibleSize.height - 60);
	btm_menu->setOpacity(0);
	auto action_1 = Sequence::create(DelayTime::create(3.0f), FadeIn::create(0.5f), nullptr);
	btm_menu->runAction(action_1);
	this->addChild(btm_menu, 3);*/
	////重新开始按钮
	//auto res = MenuItemImage::create("restart.png", "restart.png", 
	//	CC_CALLBACK_1(Game::restartGame, this));
	//res->setAnchorPoint(Point(0, 0));
	//res->setScale(0.45);
	//auto res_menu = Menu::create(res, nullptr);
	//res_menu->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 60);
	//res_menu->setOpacity(0);
	//auto action_2 = Sequence::create(DelayTime::create(3.4f), FadeIn::create(0.5f), nullptr);
	//res_menu->runAction(action_2);
	//this->addChild(res_menu, 3);



	// 道具1的icon
	changeIcon = MenuItemImage::create("changeIcon.png", "changeIcon.png",
		CC_CALLBACK_1(Game::changeIconType, this));
	changeIcon->setScale(0.5);
	auto changeIconMenu = Menu::create(changeIcon, nullptr);
	changeIconMenu->setPosition(visibleSize.width / 2 + 130, visibleSize.height - 45);
	this->addChild(changeIconMenu, 3);
	changeIcon->setOpacity(0);
	auto action_3 = Sequence::create(DelayTime::create(3.8f), FadeIn::create(0.5f), nullptr);
	changeIcon->runAction(action_3);
	//道具1的数量label
	char cChangeIconNum[10];
	sprintf(cChangeIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("ChangeNum"));
	std::string strChangeIconNum = cChangeIconNum;
	changeIconLabel = Label::createWithTTF(cChangeIconNum, "fonts/pirulenrg.ttf", 18);
	changeIconLabel->setPosition(visibleSize.width / 2 + 152, visibleSize.height - 57);
	this->addChild(changeIconLabel, 3);
	changeIconLabel->setOpacity(0);
	auto action_4 = Sequence::create(DelayTime::create(3.8f), FadeIn::create(0.5f), nullptr);
	changeIconLabel->runAction(action_4);
	//道具2的icon
	bombIcon = MenuItemImage::create("bomb.png", "bomb.png",
		CC_CALLBACK_1(Game::bombIconType, this));
	bombIcon->setScale(0.5);
	auto bombIconMenu = Menu::create(bombIcon, nullptr);
	bombIconMenu->setPosition(visibleSize.width / 2 + 185, visibleSize.height - 45);
	addChild(bombIconMenu, 3);
	bombIcon->setOpacity(0);
	auto action_5 = Sequence::create(DelayTime::create(4.2f), FadeIn::create(0.5f), nullptr);
	bombIcon->runAction(action_5);
	//道具2的数量label
	char cBombIconNum[10];
	sprintf(cBombIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("BombNum"));
	std::string strBombIconNum = cBombIconNum;
	bombIconLabel = Label::createWithTTF(cBombIconNum, "fonts/pirulenrg.ttf", 18);
	bombIconLabel->setPosition(visibleSize.width / 2 + 205, visibleSize.height - 57);
	addChild(bombIconLabel, 3);
	bombIconLabel->setOpacity(0);
	auto action_6 = Sequence::create(DelayTime::create(4.2f), FadeIn::create(0.5f), nullptr);
	bombIconLabel->runAction(action_6);

	//让道具数字变红
	if (UserDefault::getInstance()->getIntegerForKey("BombNum") == 0)
	{
		bombIconLabel->setColor(Color3B(208, 52, 13));
	}
	if (UserDefault::getInstance()->getIntegerForKey("ChangeNum") == 0)
	{
		changeIconLabel->setColor(Color3B(208, 52, 13));
	}
	//-------------------------------------------END 2个功能性道具


	//-------------------------------------------------END 背景图片,3个最上面的



	//-------------------------当前分数的初始化及显示
	//初始化分数
	int tmpCurScore = getDataManager().getCurrentScore();
	getDataManager().setInitCurrentScore(tmpCurScore);

	//当前分数的显示
    currentScore = getDataManager().getCurrentScore();
	label_score = Label::createWithTTF(std::to_string(currentScore), "fonts/HANGTHEDJ.ttf", 30);
	label_score->setPosition(visibleSize.width / 2, visibleSize.height - 150);
	this->addChild(label_score, 3);
	auto st = ScaleBy::create(1.0f, 1.1f);
	auto action_label_score = RepeatForever::create(Sequence::create(st, st->reverse(), nullptr));
	label_score->runAction(action_label_score);
	label_score->setOpacity(0);
	auto action_label_score_2 = Sequence::create(DelayTime::create(6.0f), FadeIn::create(0.5), nullptr);
	label_score->runAction(action_label_score_2);
	//-------------------------END 当前分数的初始化及显示



	//---------------------------------------数据统计对话框
	// 背景
	gameEnd = Sprite::create("level_data_bg.png");
	gameEnd->setPosition(visibleSize.width / 2, visibleSize.height/2);
	this->addChild(gameEnd, 5);
	gameEnd->setVisible(false);


	//初始化数据统计
	statistic_LeftIcon = 0;
	statistic_LeftBonus = 0;
	statistic_SingleMost = 0;
	statistic_MostIcon = 0;
	statistic_Time = 0;

	four_kill = 0;
	five_kill = 0;
	six_kill = 0;
	seven_kill = 0;
	legendary_kill = 0;

	//////////////////////////////////////////数据统计
	//剩余图标
	const char *str_2 = ((String*)dic->objectForKey("lefticon"))->_string.c_str();
	title1 = Label::createWithTTF(str_2, "fonts/b.ttf", 15);
	title1->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 330);
	title1->setVisible(false);
	addChild(title1, 6);

	leftIcon_label = Label::createWithTTF(std::to_string(statistic_LeftIcon), "fonts/watch.ttf", 16);
	leftIcon_label->setPosition(visibleSize.width / 2 - 50, visibleSize.height - 330);
	leftIcon_label->setVisible(false);
	addChild(leftIcon_label, 6);

	//剩余奖励
	const char *str_3 = ((String*)dic->objectForKey("leftbonus"))->_string.c_str();
	title2 = Label::createWithTTF(str_3, "fonts/b.ttf", 15);
	title2->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 361);
	title2->setVisible(false);
	this->addChild(title2, 6);
	//label-number
	leftBonus_label = Label::createWithTTF(std::to_string(statistic_LeftBonus), "fonts/watch.ttf", 16);
	leftBonus_label->setPosition(visibleSize.width / 2 - 50, visibleSize.height - 361);
	leftBonus_label->setVisible(false);
	addChild(leftBonus_label, 6);

	//单个最多
	const char *str_4 = ((String*)dic->objectForKey("singlerecord"))->_string.c_str();
	title3 = Label::createWithTTF(str_4, "fonts/b.ttf", 15);
	title3->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 392);
	title3->setVisible(false);
	addChild(title3, 6);
	// label-number
	singleMost_label = Label::createWithTTF(std::to_string(statistic_SingleMost) , "fonts/watch.ttf", 16);
	singleMost_label->setPosition(visibleSize.width / 2 - 50, visibleSize.height - 392);
	singleMost_label->setVisible(false);
	addChild(singleMost_label, 6);

	//消去最多
	const char *str_5 = ((String*)dic->objectForKey("mosterase"))->_string.c_str();
	title4 = Label::createWithTTF(str_5, "fonts/b.ttf", 15);
	title4->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 420);
	title4->setVisible(false);
	addChild(title4, 6);

	mostIcon_label = Label::createWithTTF(std::to_string(statistic_MostIcon), "fonts/watch.ttf", 16);
	mostIcon_label->setPosition(visibleSize.width / 2 - 50, visibleSize.height - 420);
	mostIcon_label->setVisible(false);
	addChild(mostIcon_label, 6);

	//时间
	const char *str_6 = ((String*)dic->objectForKey("time"))->_string.c_str();
	title5 = Label::createWithTTF(str_6, "fonts/b.ttf", 15);
	title5->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 446);
	title5->setVisible(false);
	addChild(title5, 6);

	timer_label = Label::createWithTTF(std::to_string(statistic_Time), "fonts/watch.ttf", 16);
	timer_label->setPosition(visibleSize.width / 2 - 50, visibleSize.height - 446);
	timer_label->setVisible(false);
	addChild(timer_label, 6);


	//4杀
	const char *str_7 = ((String*)dic->objectForKey("fourkill"))->_string.c_str();
	title6 = Label::createWithTTF(str_7, "fonts/b.ttf", 15);
	title6->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 330);
	title6->setVisible(false);
	addChild(title6, 6);

	fourKill_label = Label::createWithTTF(std::to_string(four_kill), "fonts/watch.ttf", 15);
	fourKill_label->setPosition(visibleSize.width / 2 + 140, visibleSize.height - 330);
	fourKill_label->setVisible(false);
	addChild(fourKill_label, 6);

	//5杀
	const char *str_8 = ((String*)dic->objectForKey("fivekill"))->_string.c_str();
	title7 = Label::createWithTTF(str_8, "fonts/b.ttf", 15);
	title7->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 361);
	title7->setVisible(false);
	addChild(title7, 6);

	fiveKill_label = Label::createWithTTF(std::to_string(five_kill), "fonts/watch.ttf", 16);
	fiveKill_label->setPosition(visibleSize.width / 2 + 140, visibleSize.height - 361);
	fiveKill_label->setVisible(false);
	addChild(fiveKill_label, 6);

	//6杀
	const char *str_9 = ((String*)dic->objectForKey("sixkill"))->_string.c_str();
	title8 = Label::createWithTTF(str_9, "fonts/b.ttf", 15);
	title8->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 392);
	title8->setVisible(false);
	addChild(title8, 6);

	sixKill_label = Label::createWithTTF(std::to_string(six_kill), "fonts/watch.ttf", 16);
	sixKill_label->setPosition(visibleSize.width / 2 + 140, visibleSize.height - 392);
	sixKill_label->setVisible(false);
	addChild(sixKill_label, 6);

	//7杀
	const char *str_10 = ((String*)dic->objectForKey("sevenkill"))->_string.c_str();
	title9 = Label::createWithTTF(str_10, "fonts/b.ttf", 15);
	title9->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 420);
	title9->setVisible(false);
	addChild(title9, 6);

	sevenKill_label = Label::createWithTTF(std::to_string(seven_kill), "fonts/watch.ttf", 16);
	sevenKill_label->setPosition(visibleSize.width / 2 + 140, visibleSize.height - 420);
	sevenKill_label->setVisible(false);
	addChild(sevenKill_label, 6);

	//超神
	const char *str_11 = ((String*)dic->objectForKey("legendary"))->_string.c_str();
	title10 = Label::createWithTTF(str_11, "fonts/b.ttf", 15);
	title10->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 446);
	title10->setVisible(false);
	addChild(title10, 6);

	legendaryKill_label = Label::createWithTTF(std::to_string(legendary_kill), "fonts/watch.ttf", 16);
	legendaryKill_label->setPosition(visibleSize.width / 2 + 140, visibleSize.height - 446);
	legendaryKill_label->setVisible(false);
	addChild(legendaryKill_label, 6);

	//////////////// 下一关 menuitem
	auto nextLevel_normal = Sprite::create("nextLevelBtn_1.png");
	auto nextLevel_selected= Sprite::create("nextLevelBtn_2.png");
	auto nextLevel_item = MenuItemSprite::create(nextLevel_normal, nextLevel_selected,
		CC_CALLBACK_1(Game::goToNextLevel, this));
	menuNextLevel = Menu::create(nextLevel_item, nullptr);
	menuNextLevel->setPosition(visibleSize.width / 2, gameEnd->getPosition().y - gameEnd->getContentSize().height/2 + 30);
	menuNextLevel->setVisible(false);
	this->addChild(menuNextLevel, 6);




	// 初始化数组
	pointArray = new PointArray();
	pointArray->initWithCapacity(100);
	//生产所有点阵
	generatePoint();

	//添加装备
	addEquipment();

	//初始化记录5个icon的数组
	icon_map.insert(std::make_pair(icon[0], 0));
	icon_map.insert(std::make_pair(icon[1], 0));
	icon_map.insert(std::make_pair(icon[2], 0));
	icon_map.insert(std::make_pair(icon[3], 0));
	icon_map.insert(std::make_pair(icon[4], 0));


	/// 触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* pTouch, Event* pEvent) {
		std::string icon_EnName[20] = { "nvjing","ez","yasuo","chuanzhang",
			"debang","jiansheng","ruiwen","goutou","kapai","guafu","eyv",
			"yaoji","aolafu","longgui","niutou","nvqiang","manwang","qinnv","shen","vn" };
		srand(time(nullptr));
		
		auto touchPosition = pTouch->getLocation();

		if (touchPosition.x >= 25 && touchPosition.y <= 475
			&& touchPosition.y >= 145 && touchPosition.y <= 590
			&& isGameReady == true) {
			log("onTouchBegan: touch vialid...");

			int row = (int)(590 - touchPosition.y) / 45;
			int column = (int)(touchPosition.x - 25) / 45;
			

			/////////////// #1
			if (getDataManager().getIsChangeLayerAdded() == false
				&& getDataManager().getIsBombLayerAdded() == false) {
				log("x: %f y: %f\n", touchPosition.x, touchPosition.y);
				log("矩阵坐标: x: %d y: %d", (int)(540 - touchPosition.y) / 45, (int)(touchPosition.x - 25) / 45);


				if (!timerRunning)
				{
					if (!isGameOver())
					{
						this->startTimer();//开始计时
					}
				}
				
				//------------------------main logic---------------------------
				//计算与之相邻的相同装备数量
				int currentBoardValue = board[row][column];
				//0表示是空白的，只有不为0时，才能继续计算,游戏未结束才能点击
				if (currentBoardValue != 0 && !gameIsOver) {
					count = 0;//count为2时才能消除
					totalScore = 0;

					Sprite* tempEquip = getEquipWithCoordinate(equipment, row, column); //保存一个副本
					Point tempPoint = tempEquip->getPosition();
				
				
					///更新底部介绍等
					auto keyStr = icon_EnName[currentBoardValue - 1];
					m_pBottomTexturePrefab->updateShow(keyStr, currentBoardValue);


					/////////////////////////////是否单独一个,这个函数用来避免点击单独的一个icon也会产生label的问题
					bool is = isSingleIcon(board, row, column, currentBoardValue);
					//找周围相同的,这里面就开始消除了
					findAdjacentEquip(board, row, column, currentBoardValue, is);


					/////////////////////////////更新至多单次消去的个数,写入文件
					int tempSingleBest = UserDefault::getInstance()->getIntegerForKey("singleBest");
					if (count > tempSingleBest)
					{
						UserDefault::getInstance()->setIntegerForKey("singleBest", count);
						UserDefault::getInstance()->flush();
					}


					////////////////////////////4~8杀计数
					if (count >= 2)
					{
						switch (count)
						{
						case 2:
							if (getDataManager().getIsEnableEffect() == true)
								SimpleAudioEngine::getInstance()->playEffect("explosion1.OGG");
							break;
						case 3:
							if (getDataManager().getIsEnableEffect() == true)
								SimpleAudioEngine::getInstance()->playEffect("explosion2.OGG");
							break;
						case 4:
						{
							if (!firstHit) {
								if (getDataManager().getIsEnableEffect() == true) {
									SimpleAudioEngine::getInstance()->playEffect("4kill.OGG");
									SimpleAudioEngine::getInstance()->playEffect("explosion3.OGG");
								}
							}
							four_kill++;
							break;
						}
						case 5:
						{
							five_kill++;
							auto praise = Sprite::create("praise0.png");
							praise->setPosition(tempPoint - Point(0, 70));
							praise->setScale(0.001);
							addChild(praise, 20);
							auto st = ScaleTo::create(0.5, 1.5);
							auto mt = MoveTo::create(1.5, Vec2(tempPoint + Point(0, 70)));
							auto st2 = ScaleTo::create(0.5, 0.001);
							auto deleteP = CallFunc::create([=]() {
								praise->removeFromParent();
							});
							auto seq = Sequence::create(st, mt, st2, deleteP, NULL);
							praise->runAction(seq);
							if (!firstHit)
							{
								if (getDataManager().getIsEnableEffect() == true)
								{
									SimpleAudioEngine::getInstance()->playEffect("5kill.OGG");
									SimpleAudioEngine::getInstance()->playEffect("explosion4.OGG");
									SimpleAudioEngine::getInstance()->playEffect("praise3.OGG");
								}
							}
							break;
						}
						case 6:
						{
							auto praise = Sprite::create("praise1.png");
							praise->setPosition(tempPoint - Point(0, 70));
							praise->setScale(0.001);
							addChild(praise, 20);
							auto st = ScaleTo::create(0.5, 1.5);
							auto mt = MoveTo::create(1.5, Vec2(tempPoint + Point(0, 70)));
							auto st2 = ScaleTo::create(0.5, 0.001);
							auto deleteP = CallFunc::create([=]() {
								praise->removeFromParent();
							});
							auto seq = Sequence::create(st, mt, st2, deleteP, NULL);
							praise->runAction(seq);
							six_kill++;
							if (!firstHit)
							{
								if (getDataManager().getIsEnableEffect() == true)
								{
									SimpleAudioEngine::getInstance()->playEffect("6kill.OGG");
									SimpleAudioEngine::getInstance()->playEffect("praise3.OGG");
									SimpleAudioEngine::getInstance()->playEffect("explosion4.OGG");
								}
							}
							break;
						}
						case 7:
						{
							auto praise = Sprite::create("praise2.png");
							praise->setPosition(tempPoint - Point(0, 70));
							praise->setScale(0.001);
							addChild(praise, 20);
							auto st = ScaleTo::create(0.5, 1.2);
							auto mt = MoveTo::create(1.5, Vec2(tempPoint + Point(0, 70)));
							auto st2 = ScaleTo::create(0.5, 0.001);
							auto deleteP = CallFunc::create([=]() {
								praise->removeFromParent();
							});
							auto seq = Sequence::create(st, mt, st2, deleteP, NULL);
							praise->runAction(seq);
							seven_kill++;
							if (!firstHit)
							{
								if (getDataManager().getIsEnableEffect() == true)
								{
									SimpleAudioEngine::getInstance()->playEffect("7kill.OGG");
									SimpleAudioEngine::getInstance()->playEffect("praise3.OGG");
									SimpleAudioEngine::getInstance()->playEffect("explosion4.OGG");
								}
							}
							break;
						}
						default: //超神
						{
							//超神数加一
							int tempLegend = UserDefault::getInstance()->getIntegerForKey("legendaryNum");
							UserDefault::getInstance()->setIntegerForKey("legendaryNum", tempLegend + 1);
							UserDefault::getInstance()->flush();

							auto praise = Sprite::create("praise3.png");
							praise->setPosition(tempPoint - Point(0, 70));
							praise->setScale(0.001);
							addChild(praise, 20);
							auto st = ScaleTo::create(0.5, 1.0);
							auto mt = MoveTo::create(1.5, Vec2(tempPoint + Point(0, 70)));
							auto st2 = ScaleTo::create(0.5, 0.001);
							auto deleteP = CallFunc::create([=]() {
								praise->removeFromParent();
							});
							auto seq = Sequence::create(st, mt, st2, deleteP, NULL);
							praise->runAction(seq);
							legendary_kill++;
							if (!firstHit)
							{
								if (getDataManager().getIsEnableEffect() == true)
								{
									SimpleAudioEngine::getInstance()->playEffect("8kill.OGG");
									SimpleAudioEngine::getInstance()->playEffect("praise3.OGG");
									SimpleAudioEngine::getInstance()->playEffect("explosion4.OGG");
								}
							}
					    }
					   }
					}

					////////////////////////////播放第一次击杀音效
					if (firstHit && count != 1)
					{
						firstHit = false;
						if (getDataManager().getIsEnableEffect() == true)
						{
							SimpleAudioEngine::getInstance()->playEffect("firstBlood.OGG");
							SimpleAudioEngine::getInstance()->playEffect("explosion4.OGG");
						}
					}

					//更新单个消除的最高值
					if (count >= statistic_SingleMost)
					{
						statistic_SingleMost = count;
					}
					//记录5种icon的消去个数
					if (count > 1)
					{
						std::map<int, int> ::iterator map_it;
						map_it = icon_map.find(currentBoardValue);
						(*map_it).second += count;

					}

					if (count == 1)//只有一个
					{
						//加上该装备,不能复制指针
						char c[10];
						sprintf(c, "%d", currentBoardValue);
						std::string str = c;
						Sprite* sTemp = Sprite::create("level1_" + str + ".png");
						sTemp->setScale(0.36);
						sTemp->setAnchorPoint(Point(0, 0));
						equip.pushBack(sTemp);

						sTemp->setPosition(tempPoint);
						addChild(sTemp, 2);
						equipment[row][column] = sTemp;
						//装备数组里得加上
						board[row][column] = currentBoardValue;
					}

					//////////////////左移 和下移函数
					moveDown(board);
					moveLeft(board);


					//////////////////每次点击生成   并显示  的点击总分
					if (count > 1)
					{
						//log("total score: %d", totalScore);
						char sl[20];
						sprintf(sl, "%d", totalScore);
						Label* totalScoreLabel;//上面的label
						totalScoreLabel = Label::createWithTTF(sl, "fonts/thg.ttf", 50);
						totalScoreLabel->setColor(Color3B(242, 221, 28));
						if (tempPoint.x < 100)
						{
							totalScoreLabel->setPosition(tempPoint + Point(60, 0));
						}
						else
						{
							totalScoreLabel->setPosition(tempPoint - Point(60, 0));
						}

						addChild(totalScoreLabel, 4);

						Point tp = totalScoreLabel->getPosition();

						auto mt = MoveTo::create(1.0f, tp + Point(0, 80));

						auto fo = FadeOut::create(0.4);

						//问题：为啥不能把spawn用在sequence中
						//auto st = ScaleTo::create(0.4, 0.01);
						//auto sp = Spawn::create(fo, st);


						auto actionDelete = CallFunc::create([=]() {

							totalScoreLabel->removeFromParent();
						});
						auto sq = Sequence::create(mt, fo, actionDelete, NULL);
						totalScoreLabel->runAction(sq);
					}
					//////////////////END 每次点击生成   并显示  的点击总分

				}
		
			}

			/////////////// #2
			else if (getDataManager().getIsChangeLayerAdded() == true) {
				//如果点击的icon与选取要变的不一样才能修改,-1是表示已经选取了5个要改变的icon之一
				if (getDataManager().getSelectedIconValue() != -1)
				{
					if (UserDefault::getInstance()->getIntegerForKey("ChangeNum") == 0)
					{
						//、、、、、、、、、 显示道具不足
						auto  action = Sequence::create(
							CallFunc::create([=]() {
							m_pItemNotEnoughSprite->setVisible(true);
						}),
							FadeOut::create(1.0f),
							nullptr);
						m_pItemNotEnoughSprite->runAction(action);
					}


					//如果2者不一样才能修改
					int temp = getDataManager().getSelectedIconValue();
					//此道具数量大于0且要修改的是不同的icon
					if (temp != board[row][column] && UserDefault::getInstance()->getIntegerForKey("ChangeNum") > 0 && board[row][column] != 0)
					{
						Sprite* tempEquipIcon = getEquipWithCoordinate(equipment, row, column);
						Point targetPos = tempEquipIcon->getPosition();
						/////////////////////////////////////替换道具及其动画的方法
						changeIconFlyAnimation(temp, targetPos);

						ActionInterval * delay_fly = DelayTime::create(1.0);
						auto change = CallFunc::create([=]() {

							equipmentEffectWithNoGravity(board[row][column], targetPos);
							board[row][column] = temp;
							char cIcon[10];
							sprintf(cIcon, "%d", temp);
							std::string strIcon = cIcon;
							tempEquipIcon->setTexture("level1_" + strIcon + ".png");
							if (getDataManager().getIsEnableEffect() == true)
							{
								SimpleAudioEngine::getInstance()->playEffect("change.OGG");
							}

						});
						auto sq = Sequence::create(delay_fly, change, NULL);
						this->runAction(sq);


						//数量减少1
						int tempNum = UserDefault::getInstance()->getIntegerForKey("ChangeNum");
						changeIconLabel->setString(StringUtils::format("%d", tempNum - 1));

						//写入文件
						UserDefault::getInstance()->setIntegerForKey("ChangeNum", tempNum - 1);
						UserDefault::getInstance()->flush();

						if (tempNum == 1)
						{
							changeIconLabel->setColor(Color3B(208, 52, 13));//数字变红色
						}

					}
					//一次点击的话只能修改一次，防止无限修改
					getDataManager().setSelectedIconValue(-1);
				}
			}

			/////////////// #3
			else if (getDataManager().getIsBombLayerAdded() == true) {
				int i, j;
				if (UserDefault::getInstance()->getIntegerForKey("BombNum") <= 0)
				{
					//、、、、、、、、、 显示道具不足
					auto  action = Sequence::create(
						CallFunc::create([=]() {
						m_pItemNotEnoughSprite->setVisible(true);
					}),
						FadeOut::create(1.0f),
						nullptr);
					m_pItemNotEnoughSprite->runAction(action);
				}

				if (missile1 == nullptr && missile2 == nullptr && UserDefault::getInstance()->getIntegerForKey("BombNum")>0)  //只有在2个导弹都飞出屏幕后才能继续使用bomb
				{

					//创建光圈，然后变小圈住目标icon	
					if (board[row][column] != 0)
					{

						auto lock = Sprite::create("lock.png");
						lock->setScale(1.3);

						Sprite* tempEquipIcon = getEquipWithCoordinate(equipment, row, column);
						Point targetPos = tempEquipIcon->getPosition();
						lock->setPosition(targetPos + Point(20, 20));
						addChild(lock, 20);
						auto rt = RotateBy::create(1, 90);
						auto rp = RepeatForever::create(rt);
						auto st = ScaleTo::create(1.0, 0.3);
						lock->runAction(st);
						lock->runAction(rp);

						//消除光圈
						//找到lock位置行列值较小的一个，计算时间
						float tempTime;
						if (10 - column > row + 1)
						{
							tempTime = (row + 1)*0.12;
						}
						else
						{
							tempTime = (10 - column)*0.12;
						}

						ActionInterval * delay_lock = DelayTime::create(tempTime + 2.4);
						auto deleteLock = CallFunc::create([=]() {

							lock->removeFromParent();

						});

						auto sq_lock = Sequence::create(delay_lock, deleteLock, NULL);
						lock->runAction(sq_lock);
					}

					missile1 = Sprite::create("missile.png");
					missile1->setScale(0.8);
					missile1->setPosition(45 + column * 45, 550);

					//tower1 是x轴上的tower				
					if (tower1 == nullptr)
					{
						log("tower1 null");
						tower1 = Sprite::create("tower.png");
						tower1->setScale(0.4);
						tower1->setOpacity(0);
						tower1->setPosition(45 + column * 45, 600);
						addChild(tower1, 10);
						auto fi_t1 = FadeIn::create(0.5);
						tower1->runAction(fi_t1);

						addChild(missile1, 10);
						ActionInterval *delay_m1 = DelayTime::create(1.7);
						auto mt_m1 = MoveTo::create(2.0, Vec2(45 + column * 45, -100));

						auto deleteM1 = CallFunc::create([=]() {

							moveDown(board);
							moveLeft(board);
							missile1->removeFromParentAndCleanup(true);
							missile1 = nullptr;

						});
						auto sq_m1 = Sequence::create(delay_m1, mt_m1, deleteM1, NULL);
						missile1->runAction(sq_m1);

						//消除icon的处理部分
						ActionInterval *delay_icon = DelayTime::create(1.7);
						auto hit = CallFunc::create([=]() {

							hitIconByMissile(column, row, 1); //type == 1  表示是按列消除，从上到下 ，0表示按行消除，从右到左

						});
						auto sq_deleteIcon = Sequence::create(delay_icon, hit, NULL);
						this->runAction(sq_deleteIcon);

					}
					else  //towerr存在的话就移动tower
					{
						auto mt_t1 = MoveTo::create(0.5, Vec2(45 + column * 45, 600));
						tower1->runAction(mt_t1);
						ActionInterval *delay_missile1 = DelayTime::create(1.5);
						auto addMissile1 = CallFunc::create([=]() {

							addChild(missile1, 10);

						});
						auto sq_missile1 = Sequence::create(delay_missile1, addMissile1, NULL);
						this->runAction(sq_missile1);
						ActionInterval *delay_m1 = DelayTime::create(0.7);
						auto mt_m1 = MoveTo::create(2.0, Vec2(45 + column * 45, -100));
						auto deleteM1 = CallFunc::create([=]() {

							moveDown(board);
							moveLeft(board);
							missile1->removeFromParentAndCleanup(true);
							missile1 = nullptr;

						});
						auto sq_m1 = Sequence::create(delay_m1, mt_m1, deleteM1, NULL);
						missile1->runAction(sq_m1);

						//消除icon的处理部分
						ActionInterval *delay_icon = DelayTime::create(2.2);
						auto hit = CallFunc::create([=]() {

							hitIconByMissile(column, row, 1); //type == 1  表示是按列消除，从上到下 ，0表示按行消除，从右到左

						});
						auto sq_deleteIcon = Sequence::create(delay_icon, hit, NULL);
						this->runAction(sq_deleteIcon);

					}
					/////////////////////第二个导弹
					missile2 = Sprite::create("missile.png");
					missile2->setRotation(90);
					missile2->setScale(0.8);
					missile2->setPosition(430, 570 - row * 45);

					if (tower2 == nullptr)
					{
						//tower2 是y轴上的tower
						tower2 = Sprite::create("tower.png");
						tower2->setRotation(90);
						tower2->setScale(0.4);
						tower2->setOpacity(0);
						tower2->setPosition(480, 570 - row * 45);
						addChild(tower2, 10);
						auto fi_t2 = FadeIn::create(0.5);
						tower2->runAction(fi_t2);

						addChild(missile2, 10);
						auto mt_m2 = MoveTo::create(2.0, Vec2(-100, 570 - row * 45));

						ActionInterval *delay_m2 = DelayTime::create(1.7);
						auto deleteM2 = CallFunc::create([=]() {

							moveDown(board);
							moveLeft(board);
							missile2->removeFromParentAndCleanup(true);
							missile2 = nullptr;

						});
						auto sq_m2 = Sequence::create(delay_m2, mt_m2, deleteM2, NULL);
						missile2->runAction(sq_m2);

						//消除icon的处理部分
						ActionInterval *delay_icon = DelayTime::create(1.7);
						auto hit = CallFunc::create([=]() {

							hitIconByMissile(column, row, 0); //type == 1  表示是按列消除，从上到下 ，0表示按行消除，从右到左

						});
						auto sq_deleteIcon = Sequence::create(delay_icon, hit, NULL);
						this->runAction(sq_deleteIcon);

					}
					else
					{
						auto mt_t2 = MoveTo::create(0.5, Vec2(480, 570 - row * 45));
						tower2->runAction(mt_t2);
						ActionInterval *delay_missile2 = DelayTime::create(1.5);
						auto addMissile2 = CallFunc::create([=]() {

							addChild(missile2, 10);

						});
						auto sq_missile2 = Sequence::create(delay_missile2, addMissile2, NULL);
						this->runAction(sq_missile2);

						ActionInterval *delay_m2 = DelayTime::create(0.7);
						auto deleteM2 = CallFunc::create([=]() {

							moveDown(board);
							moveLeft(board);
							missile2->removeFromParentAndCleanup(true);
							missile2 = nullptr;

						});
						auto mt_m2 = MoveTo::create(2.0, Vec2(-100, 570 - row * 45));
						auto sq_m2 = Sequence::create(delay_m2, mt_m2, deleteM2, NULL);
						missile2->runAction(sq_m2);


						//消除icon的处理部分
						ActionInterval *delay_icon = DelayTime::create(2.2);
						auto hit = CallFunc::create([=]() {

							hitIconByMissile(column, row, 0); //type == 1  表示是按列消除，从上到下 ，0表示按行消除，从右到左

						});
						auto sq_deleteIcon = Sequence::create(delay_icon, hit, NULL);
						this->runAction(sq_deleteIcon);

					}
					//数量减少1
					int tempNum = UserDefault::getInstance()->getIntegerForKey("BombNum");
					bombIconLabel->setString(StringUtils::format("%d", tempNum - 1));

					//写入文件
					UserDefault::getInstance()->setIntegerForKey("BombNum", tempNum - 1);
					UserDefault::getInstance()->flush();

					if (tempNum == 1)
					{
						bombIconLabel->setColor(Color3B(208, 52, 13));//数字变红色
					}
				}//end if nullptr	
			}

		}

		return true;
	};
	listener->onTouchEnded = [=](Touch* pTouch, Event* pEvent) {
		log("onTouchEnded touch vialid...");
	};
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);




	// 定时检测游戏逻辑
	this->schedule(SEL_SCHEDULE(&Game::gameStep), 0.02f);

	return true;
}




//道具函数： 改变种类
void Game::changeIconType(Ref * r)
{
	if (getDataManager().getIsEnableEffect() == true 
		&& UserDefault::getInstance()->getIntegerForKey("ChangeNum") > 0)
	{
		SimpleAudioEngine::getInstance()->playEffect("button.OGG");
	}
	if (UserDefault::getInstance()->getIntegerForKey("ChangeNum") <= 0)
	{
		// 显示道具不足
		auto  action = Sequence::create(
				CallFunc::create([=]() {
					m_pItemNotEnoughSprite->setVisible(true);
				}),
				FadeOut::create(1.0f), 
				nullptr);
		m_pItemNotEnoughSprite->runAction(action);


		SimpleAudioEngine::getInstance()->playEffect("buyFail.OGG");
	}
	else
	{
		if (getDataManager().getIsChangeLayerAdded() == false 
			&& getDataManager().getIsBombLayerAdded() == false) //如果已经添加了layer就不能再添加了
		{
			auto changeIconView = ChangeIconPrefab::create();
			changeIconView->setPosition(Vec2(0, 0));
			this->addChild(changeIconView, 20);
			getDataManager().setIsChangeLayerAdded(true);
		}
	}
}

//道具函数： 爆炸icon
void Game::bombIconType(Ref * r)
{
	if (getDataManager().getIsEnableEffect() == true 
		&& UserDefault::getInstance()->getIntegerForKey("BombNum") > 0)
	{
		SimpleAudioEngine::getInstance()->playEffect("button.OGG");
	}
	if (UserDefault::getInstance()->getIntegerForKey("BombNum") <= 0)
	{
		// 显示道具不足
		auto  action = Sequence::create(
			CallFunc::create([=]() {
			m_pItemNotEnoughSprite->setVisible(true);
		}),
			FadeOut::create(1.0f),
			nullptr);
		m_pItemNotEnoughSprite->runAction(action);

		SimpleAudioEngine::getInstance()->playEffect("buyFail.OGG");
	}
	else
	{
		if (getDataManager().getIsChangeLayerAdded() == false 
			&& getDataManager().getIsBombLayerAdded() == false) 
		{
			tower1 = nullptr;
			tower2 = nullptr;
			missile1 = nullptr;
			missile2 = nullptr;

			auto bil = BombIconPrefab::create();
			bil->setPosition(Vec2(0, 0));
			this->addChild(bil, 20);

			getDataManager().setIsBombLayerAdded(true);

		}
	}

}

void Game::returnToMenu(cocos2d::Ref* r)
{
	if (getDataManager().getIsChangeLayerAdded() == false
		&& getDataManager().getIsBombLayerAdded() == false) 
	{
		//在这里得更新当前分数,方便暂停层使用
		getDataManager().setCurrentScore(currentScore);

		auto gamePauseLayer = GamePauseController::create();
		gamePauseLayer->setPosition(0, 0);
		this->addChild(gamePauseLayer, 9);
	}
}

// 重新开始
void Game::restartGame(cocos2d::Ref* r)
{
	if (getDataManager().getIsChangeLayerAdded() == false 
		&& getDataManager().getIsBombLayerAdded() == false) 
	{
		Director::getInstance()->replaceScene(
			TransitionCrossFade::create(1.0f, WelcomeSceneController::createScene()));
	}
}

// 进入下一关
void Game::goToNextLevel(Ref * r)
{
	int tempIncrement = getDataManager().getScoreIncrement();
	getDataManager().setScoreIncrement(tempIncrement + 100);
	getDataManager().setCurrentScore(currentScore);

	//更新下一关目标分数
	getDataManager().setLevelTargetScore(target_score + tempIncrement);
	getDataManager().setGameLevel(curLevel + 1);
	//更新道具个数
	/*int tempChange = getDataManager().getChangeIconNum();
	getDataManager().setChangeIconNum(tempChange + 1);
	int tempBomb = getDataManager().getBombIconNum();
	getDataManager().setBombIconNum(tempBomb + 1);*/

	if (curLevel + 1 <= 20)
	{
		Director::getInstance()->replaceScene(
			TransitionFade::create(1, Game::createScene()));
	}
	else
	{
		Director::getInstance()->replaceScene(
			TransitionFade::create(1, FinalSceneController::createScene()));
	}
}

//生产所有点阵
void Game::generatePoint()
{
	int i, j;
	srand(time(NULL));
	//20个图标中随机选取5个	

	PointArray *p = new PointArray();
	p->initWithCapacity(20);
	for (i = 1; i <= 20; i++)
	{
		p->addControlPoint(Point(i, 0));
	}


	// 在这里初始化getDataManager中的vector
	getDataManager().clearIconVec();
	for (i = 1; i <= 5; i++)
	{
		int randNum = rand() % p->count();
		int temp = (p->getControlPointAtIndex(randNum)).x;
		icon.push_back(temp);
		getDataManager().setIconVec(temp);
		p->removeControlPointAtIndex(randNum);
	}


	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
		{
			int min = 0, max = 5;
			int range = max - min;
			int number = rand() % range + 1;
			board[i][j] = icon[number - 1];
			//board[i][j] = icon[0];

		}

}

//添加装备(10*10)
void Game::addEquipment()
{
	int row, column;
	for (row = 0; row < 10; row++)
	{

		for (column = 0; column < 10; column++)
		{
			int temp = board[row][column];
			if (temp != 0)
			{
				char num[10] = "";
				sprintf(num, "%d", temp);
				std::string n = num;
				std::string name = "level1_" + n + ".png";
				Sprite * s = Sprite::create(name);
				s->setAnchorPoint(Point(0, 0));
				s->setScale(0.001);
				s->setPosition(Point(25 + column * 45, 550 - row * 45));
				addChild(s, 2);
				//动画效果
				auto st = ScaleTo::create(0.8, 0.36);
				ActionInterval * delay = DelayTime::create(4);
				auto sq = Sequence::create(delay, st, NULL);
				s->runAction(sq);

				equip.pushBack(s);
				equipment[row][column] = s;//将装备放入对应的数组中
			}
		}
	}
}


//检测游戏是否结束：即没有2个相连的装备
bool Game::isGameOver()
{
	int i, j, count = 0;
	bool isGameOver = true;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (board[i][j] != 0)
			{
				if (board[i - 1][j] == board[i][j] || board[i + 1][j] == board[i][j] || board[i][j - 1] == board[i][j] || board[i][j + 1] == board[i][j])
				{

					isGameOver = false;
				}
			}
		}
	}

	return isGameOver;
}


void Game::startTimer()
{
	if (!timerRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timerRunning = true;
	}
}

//结束计时
void Game::endTimer()
{
	if (timerRunning)
	{
		unscheduleUpdate();
		timerRunning = false;
	}
}

//计时方法
void Game::update(float dt)
{
	statistic_Time = clock() - startTime;
	//timerLabel->setString(StringUtils::format("%0.1f", ((double)statistic_Time) / 1000));   //真机上再除以1000才行 
}

Sprite* Game::getEquipWithCoordinate(Sprite * e[][10], int row, int column)
{
	if (e[row][column] != nullptr)
	{
		return e[row][column];
	}
	else
		return nullptr;
}

//找出相邻的装备的函数
void Game::findAdjacentEquip(int b[][10], int posX, int posY, int cur, bool single)
{
	if (b[posX][posY] != cur || posX<0 || posX>9 || posY<0 || posY>9)
	{

		return;
	}

	//删除操作
	Sprite* sTemp = getEquipWithCoordinate(equipment, posX, posY);

	//(单个方块没有)粒子特效：装备向四周四散开来	
	if (count >= 1)
	{
		Point pos = sTemp->getPosition();
		equipmentEffect(b[posX][posY], pos);

	}


	b[posX][posY] = 0;
	count++;
	//游戏得分
	if (!single)
	{
		tempScore = count * 10 - 5;
		totalScore += tempScore;

		//创建label飞过来
		char s[20];
		sprintf(s, "%d", tempScore);
		lb = Label::createWithTTF(s, "fonts/ethnocentricrg.ttf", 30);
		lb->setPosition(sTemp->getPosition());
		//利用tag作为lb的分数，当然getDescription函数没搞懂
		lb->setTag(tempScore);

		//计算到达时间，根据距离来算
		float distance = sqrt((sTemp->getPositionX() - label_score->getPositionX())*(sTemp->getPositionX() - label_score->getPositionX()) + (sTemp->getPositionY() - label_score->getPositionY())*(sTemp->getPositionY() - label_score->getPositionY()));
		float time = distance / 400;
		auto mt = MoveTo::create(time, label_score->getPosition());
		addChild(lb, 4);
		vec_label.pushBack(lb);
		//延时
		float dt = count*0.05;
		ActionInterval * delaytime = CCDelayTime::create(dt);
		EaseOut * lb_easeIn = EaseOut::create(mt, 2.0);
		Sequence *sq = Sequence::create(delaytime, lb_easeIn, NULL);
		lb->runAction(sq);
	}



	if (sTemp != nullptr)
	{

		sTemp->removeFromParent();
		equipment[posX][posY] = nullptr;
		equip.eraseObject(sTemp);

	}


	//递归
	findAdjacentEquip(b, posX - 1, posY, cur, single);
	findAdjacentEquip(b, posX + 1, posY, cur, single);
	findAdjacentEquip(b, posX, posY - 1, cur, single);
	findAdjacentEquip(b, posX, posY + 1, cur, single);
}

//确定是否单独一个装备
bool Game::isSingleIcon(int b[][10], int row, int column, int cur)
{
	bool isSingle = true;
	if (b[row - 1][column] == cur || b[row + 1][column] == cur || b[row][column - 1] == cur || b[row][column + 1] == cur)
	{
		isSingle = false;
	}
	return isSingle;
}

void Game::equipmentEffect(int boardValue, Point pos)
{
	char c[10];
	sprintf(c, "%d", boardValue);
	std::string str = c;
	//log("board value: %d", boardValue);

	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("level1_" + str + ".png"));
	effect->setTotalParticles(10);

	//让其为图片本身的颜色
	effect->setStartColor(Color4F(255, 255, 255, 255));
	effect->setEndColor(Color4F(255, 255, 255, 0));

	effect->setStartSize(25.0f);
	effect->setGravity(Point(0, -300));
	effect->setLife(0.1f);
	effect->setSpeed(200);
	effect->setSpeedVar(10);
	effect->setPosition(pos);
	this->addChild(effect, 4);
}

void Game::equipmentEffectWithNoGravity(int boardValue, Point pos)
{
	char c[10];
	sprintf(c, "%d", boardValue);
	std::string str = c;
	//log("board value: %d", boardValue);

	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("level1_" + str + ".png"));
	effect->setTotalParticles(10);

	//让其为图片本身的颜色
	effect->setStartColor(Color4F(255, 255, 255, 255));
	effect->setEndColor(Color4F(255, 255, 255, 0));

	effect->setStartSize(25.0f);

	effect->setLife(0.1f);
	effect->setSpeed(200);
	effect->setSpeedVar(10);
	effect->setPosition(pos);
	this->addChild(effect, 4);

}

//下移函数
void Game::moveDown(int b[][10])
{
	//必须从下往上遍历才行

	int bound, i, j, k;
	//依次遍历每一列
	for (j = 0; j <= 9; j++)
	{

		for (i = 9; i >= 0; i--)
		{
			bound = -1;//点击第一行时，bound为-1
					   //找到分界点
			if (b[i][j] == 0 && b[i - 1][j] != 0)
			{
				bound = i - 1;
				if (bound != -1)//必须，否则就不会落下
				{
					int spaceNum = 0;
					k = bound + 1;
					while (b[k][j] == 0)
					{
						spaceNum++;
						k++;
						if (k > 9)
							break;
					}
					//cout << "空格数为" << spaceNum << endl;
					//log("space :%d", spaceNum);

					//下移操作					
					b[bound + spaceNum][j] = b[bound][j];//这一句必须放在if外面,找了好久bug

					Sprite *s = getEquipWithCoordinate(equipment, bound, j);
					Point temp = s->getPosition();
					float duration = (45 * spaceNum) / 200.0;
					//log("duration: %f", duration);
					auto mt = MoveTo::create(duration, temp - Point(0, 45 * spaceNum));
					s->runAction(mt);
					//更新equipment数组
					equipment[bound + spaceNum][j] = s;
					b[bound][j] = 0;//万万不能少
				}//end if

			}

		}
		//log("bound: %d", bound);
		//计算出空格数

	}//end j

}

//向左移动的函数
void Game::moveLeft(int b[][10])
{
	//log("after moveleft:");
	//printBoard(board);

	//改正后的方法，从左到右一次检测每一列
	int lowerBound, i, j, spaceNum, tempLowerBound;
	for (i = 0; i <= 8; i++)
	{
		lowerBound = -1;
		if (b[9][i] == 0 && b[9][i + 1] != 0)
		{
			lowerBound = i + 1;//找到最下面一行从右至左的bound
			tempLowerBound = lowerBound;//下面要用lowerBound，所以预先保存

		}
		//如果lowerBound存在的话才能进一步判断
		if (lowerBound >= 0)
		{
			//log("lower_bound: %d", lowerBound);
			spaceNum = 0;
			while (b[9][lowerBound - 1] == 0)
			{
				spaceNum++;
				lowerBound--;
				if (lowerBound < 1)
					break;
			}
			//log("spaceNum: %d", spaceNum);
			//左移：从上到下一次遍历每一行
			for (int row = 0; row <= 9; row++)
			{
				for (int column = tempLowerBound; column <= 9; column++)
				{
					b[row][column - spaceNum] = b[row][column];
					//log("c-s: %d", column - spaceNum);
					if (b[row][column] != 0)
					{
						Sprite *s = getEquipWithCoordinate(equipment, row, column);
						Point temp = s->getPosition();
						float duration = (45 * spaceNum) / 200.0;
						//log("duration: %f", duration);
						auto mt = MoveTo::create(duration, temp - Point(45 * spaceNum, 0));
						s->runAction(mt);
						//更新equipment数组
						equipment[row][column - spaceNum] = s;
					}
				}
				//数组还原0
				for (int k = 9; k >= 9 - spaceNum + 1; k--)
				{
					b[row][k] = 0;
				}


			}


		}
	}
}

//替换icon时的动画函数
void Game::changeIconFlyAnimation(int temp, Point target)
{
	//动画效果，一个icon飞过去替代原来的ICON
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point flyPos;
	char cFly[10];
	sprintf(cFly, "%d", temp);
	std::string strFly = cFly;
	Sprite * fly = Sprite::create("level1_" + strFly + ".png");
	fly->setAnchorPoint(Point(0, 0));
	std::vector<int> temp_vec = getDataManager().getIconVec();

	if (temp == temp_vec[0])
	{
		flyPos = Point(90, visibleSize.height - 110);
	}
	else if (temp == temp_vec[1])
	{
		flyPos = Point(90 + 80, visibleSize.height - 110);
	}
	else if (temp == temp_vec[2])
	{
		flyPos = Point(90 + 160, visibleSize.height - 110);
	}
	else if (temp == temp_vec[3])
	{
		flyPos = Point(90 + 240, visibleSize.height - 110);
	}
	else if (temp == temp_vec[4])
	{
		flyPos = Point(90 + 320, visibleSize.height - 110);
	}

	fly->setPosition(flyPos);
	fly->setScale(0.36);
	addChild(fly, 15);

	auto mt = MoveTo::create(1, target);
	auto deleteFly = CallFunc::create([=]() {

		fly->removeFromParent();

	});
	auto sq = Sequence::create(mt, deleteFly, NULL);
	fly->runAction(sq);

}


//飞弹击碎icon得到的分数,一个icon只加5分，这样就保证不会频繁使用飞弹
void Game::scoreGetFromMissile(int posX, int posY)
{
	int tempScore = 5;
	Sprite* sTemp = getEquipWithCoordinate(equipment, posX, posY);
	//创建label飞过来
	char s[20];
	sprintf(s, "%d", tempScore);
	lb = Label::createWithTTF(s, "fonts/ethnocentricrg.ttf", 30);
	lb->setPosition(sTemp->getPosition());
	//利用tag作为lb的分数，当然getDescription函数没搞懂
	lb->setTag(tempScore);

	//计算到达时间，根据距离来算
	float distance = sqrt((sTemp->getPositionX() - label_score->getPositionX())*(sTemp->getPositionX() - label_score->getPositionX()) + (sTemp->getPositionY() - label_score->getPositionY())*(sTemp->getPositionY() - label_score->getPositionY()));
	float time = distance / 400;
	auto mt = MoveTo::create(time, label_score->getPosition());
	addChild(lb, 4);
	vec_label.pushBack(lb);

	lb->runAction(mt);
}

//飞弹击碎icon的函数，0.2秒击碎一个,type表示是row还是column消除
void Game::hitIconByMissile(int column, int row, int type)
{
	int i;

	if (type == 1)
	{
		for (i = 0; i < 10; i++)
		{
			ActionInterval * delay = DelayTime::create(0.12*i);
			if (board[i][column] != 0)
			{
				Sprite * temp = getEquipWithCoordinate(equipment, i, column);
				Point tempPoint = temp->getPosition();

				auto deleteSelf = CallFunc::create([=]() {

					scoreGetFromMissile(i, column);
					equipmentEffect(board[i][column], tempPoint);
					temp->removeFromParent();
					board[i][column] = 0;
					if (getDataManager().getIsEnableEffect() == true)
					{
						SimpleAudioEngine::getInstance()->playEffect("bomb.OGG");
					}
				});
				auto sq = Sequence::create(delay, deleteSelf, NULL);
				temp->runAction(sq);
			}

		}
	}
	else //type ==0 按行消除
	{
		for (i = 9; i >= 0; i--)
		{
			ActionInterval * delay = DelayTime::create(0.12*(9 - i));
			if (board[row][i] != 0)
			{
				Sprite * temp = getEquipWithCoordinate(equipment, row, i);
				Point tempPoint = temp->getPosition();
				auto deleteSelf = CallFunc::create([=]() {

					scoreGetFromMissile(row, i);
					equipmentEffect(board[row][i], tempPoint);
					temp->removeFromParent();
					board[row][i] = 0;
					if (getDataManager().getIsEnableEffect() == true)
					{
						SimpleAudioEngine::getInstance()->playEffect("bomb.OGG");
					}
				});
				auto sq = Sequence::create(delay, deleteSelf, NULL);
				temp->runAction(sq);
			}


		}
	}
}

//胜利特效
void Game::__winEffect(Point pos)
{
	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("smallstar.png"));
	effect->setTotalParticles(30);

	//让其为图片本身的颜色
	effect->setStartColor(Color4F(255, 255, 255, 255));
	effect->setEndColor(Color4F(255, 255, 255, 0));

	effect->setStartSize(50.0f);
	effect->setGravity(Point(0, -300));
	effect->setLife(1.5f);
	effect->setSpeed(200);
	effect->setSpeedVar(10);
	effect->setPosition(pos);
	this->addChild(effect, 5);
}

//游戏结束时摧毁剩下的方块
void Game::__destoryRemaining()
{
	int row, column;
	//先遍历每一列，从左下角开始
	for (column = 0; column < 10; column++)
	{

		for (row = 9; row >= 0; row--)
		{
			float delay = column*0.4;
			ActionInterval * delaytime = CCDelayTime::create(delay);//延时动作,目的是为了让爆炸动画执行完毕
			if (board[row][column] != 0)
			{

				Sprite* tempEquip = getEquipWithCoordinate(equipment, row, column); //保存一个副本
				auto action = CallFunc::create([=]() {

					Point tempPoint = tempEquip->getPosition();
					equipmentEffect(board[row][column], tempPoint);
					tempEquip->removeFromParent();
					//不能忘了让数组归0
					board[row][column] = 0;
				});
				auto sq = Sequence::create(delaytime, action, NULL);
				tempEquip->runAction(sq);

			}
		}
	}
}


void Game::gameStep(float dt)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//检查飞行的分数是否飞到位，如果到位了就去除之
	if (vec_label.size() != 0)
	{
		int i;
		for (i = 0; i < vec_label.size(); i++)
		{
			Label* temp = vec_label.at(i);
			if (temp->getPosition() == label_score->getPosition())
			{

				int tempScore = temp->getTag();
				currentScore += tempScore;
				label_score->setString(StringUtils::format("%d", currentScore));
				vec_label.eraseObject(temp);
				temp->removeFromParent();


			}
		}
	}

	///////////////////////检测是否到达目标分数
	if (currentScore >= getDataManager().getLevelTargetScore() && isTargetReached == false)
	{
		//这是为了让所有的分数都飘到位了，防止成功又失败的情况出现，也有问题，点快了的话size一直不为0 ，则gameover要判断为失败
		if (vec_label.size() == 0)
		{
			if (getDataManager().getIsEnableEffect() == true)
			{
				SimpleAudioEngine::getInstance()->playEffect("game_level_win.OGG");
			}
			Size vs = Director::getInstance()->getVisibleSize();

			clear = Sprite::create("teemo.png");
			clear->setPosition(vs.width / 2 + 130, vs.height / 2);
			clear->setScale(1.3);
			addChild(clear, 4);

			auto fi_clear = FadeIn::create(0.5);
			auto st_clear = ScaleTo::create(0.5, 0.7);
			auto sp_clear = Spawn::create(fi_clear, st_clear, NULL);

			auto mt_clear = MoveTo::create(0.5, Point(vs.width / 2 + 180, vs.height - 170));
			auto st_clear2 = ScaleTo::create(0.5, 0.2);
			auto sp_clear2 = Spawn::create(mt_clear, st_clear2, NULL);

			ActionInterval * delay_clear = DelayTime::create(0.5);

			auto sq_clear = Sequence::create(sp_clear, delay_clear, sp_clear2, NULL);

			clear->runAction(sq_clear);

			//目标分数数字变颜色
			targetScore_label->setColor(Color3B(0, 255, 0));

			//达到目标分数
			isTargetReached = true;

			/////////显示胜利特效
			__winEffect(Point(vs.width / 2, vs.height - 200));
		}

	}

	//消去2个导弹
	if (getDataManager().getIsBombLayerAdded() == false)
	{
		if (tower1 != nullptr)
		{
			tower1->removeFromParent();
			tower1 = nullptr;

		}
		if (tower2 != nullptr)
		{
			tower2->removeFromParent();
			tower2 = nullptr;
		}
	}

	////////////////////检测是否游戏结束
	if (isGameOver() && isGameOverHit == false && getDataManager().getIsChangeLayerAdded() == false 
		&& getDataManager().getIsBombLayerAdded() == false)
	{
		//计算剩余icon数量
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (board[i][j] != 0)
				{
					statistic_LeftIcon++;
				}
			}
		}
		//判断剩余奖励
		if (statistic_LeftIcon < 5)
		{
			statistic_LeftBonus = leftBonus[statistic_LeftIcon];
			leftBonusBox->setTag(statistic_LeftBonus);
			auto fi = FadeIn::create(0.5);
			auto mt = MoveTo::create(1.5, Vec2(visibleSize.width / 2 - 15, visibleSize.height - 150));
			auto deleteLbb = CallFunc::create([=]() {

				currentScore += leftBonusBox->getTag();
				leftBonusBox->removeFromParent();
				label_score->setString(StringUtils::format("%d", currentScore));

			});
			auto seq = Sequence::create(fi, mt, deleteLbb, NULL);
			leftBonusBox->runAction(seq);
		}
		else
		{
			statistic_LeftBonus = 0;
		}

		///////////////判断是否达成目标

		ActionInterval * delayJudge = DelayTime::create(3.0);
		auto judge = CallFunc::create([=]() {

			if (isTargetReached) //如果目标达成
			{
				gameIsOver = true;
				//停止计时
				endTimer();

				//计算剩余icon数量
				statistic_LeftIcon = 0;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (board[i][j] != 0)
						{
							statistic_LeftIcon++;
						}
					}
				}

				//clear label飞到中间来放大缩小
				auto mt_clear = MoveTo::create(0.5, Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 150));
				auto st_clear = ScaleTo::create(0.5, 0.5);
				auto sp_clear = Spawn::create(mt_clear, st_clear, NULL);

				clear2 = Sprite::create("teemo.png");
				clear2->setPosition(visibleSize.width / 2 + 220, visibleSize.height - 140);
				clear2->setScale(0.2);
				addChild(clear2, 5);
				clear2->runAction(sp_clear);

				gameEnd->setVisible(true);
				//延时1秒执行摧毁动画
				ActionInterval * delaytime = CCDelayTime::create(2.0);
				//ActionInterval * delaytime2 = CCDelayTime::create(6.0);
				auto action = CallFunc::create([=]() {

					__destoryRemaining();
					//更新当前分数存进data manager

					getDataManager().setCurrentScore(currentScore);
					log("current score save: %d", currentScore);
				});
				/*auto action2 = CallFunc::create([=](){

				Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));

				});*/

				auto sq = Sequence::create(delaytime, action, NULL);
				this->runAction(sq);

				//播放音效
				SimpleAudioEngine::getInstance()->playEffect("win.OGG");

				////////////////////////////////显示数据统计
				gameEnd->setVisible(true);
				menuNextLevel->setVisible(true);
				//剩余图标
				title1->setVisible(true);
				leftIcon_label->setString(StringUtils::format("%d", statistic_LeftIcon));
				leftIcon_label->setVisible(true);


				leftBonus_label->setVisible(true);
				leftBonus_label->setString(StringUtils::format("%d", statistic_LeftBonus));
				title2->setVisible(true);

				//单个最多
				title3->setVisible(true);
				singleMost_label->setString(StringUtils::format("%d", statistic_SingleMost));
				singleMost_label->setVisible(true);

				//消去最多的icon	
				std::map<int, int> ::iterator map_it1;
				for (map_it1 = icon_map.begin(); map_it1 != icon_map.end(); map_it1++)
				{
					if (statistic_MostIcon < (*map_it1).second)
					{
						statistic_MostIcon = (*map_it1).second;
					}
				}

				title4->setVisible(true);
				mostIcon_label->setString(StringUtils::format("%d", statistic_MostIcon));
				mostIcon_label->setVisible(true);

				//时间
				title5->setVisible(true);
				timer_label->setVisible(true);
				timer_label->setString(StringUtils::format("%0.1f", statistic_Time / 1000000)); //真机得除1000000

				title6->setVisible(true);
				fourKill_label->setVisible(true);
				fourKill_label->setString(StringUtils::format("%d", four_kill));

				//5杀
				title7->setVisible(true);
				fiveKill_label->setVisible(true);
				fiveKill_label->setString(StringUtils::format("%d", five_kill));

				//6杀
				title8->setVisible(true);
				sixKill_label->setVisible(true);
				sixKill_label->setString(StringUtils::format("%d", six_kill));

				//7杀
				title9->setVisible(true);
				sevenKill_label->setVisible(true);
				sevenKill_label->setString(StringUtils::format("%d", seven_kill));

				//超神
				title10->setVisible(true);
				legendaryKill_label->setVisible(true);
				legendaryKill_label->setString(StringUtils::format("%d", legendary_kill));


			}
			else//添加失败层
			{
				auto failDialog = FailDialogPrefab::create();
				failDialog->setScale(0.00001f);
				this->addChild(failDialog, 10);
				failDialog->runAction(Sequence::create(DelayTime::create(0.5f), EaseOut::create(ScaleTo::create(0.5f, 1.0f), 0.75f), nullptr));

				//播放音效
				SimpleAudioEngine::getInstance()->playEffect("lose.OGG");
				//更新当前分数
				getDataManager().setCurrentScore(currentScore);
			}

		});//end call func

		auto seq = Sequence::create(delayJudge, judge, NULL);
		if (isGameOverHit == false)
		{
			this->runAction(seq);
			isGameOverHit = true;
		}

	}
}