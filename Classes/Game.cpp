#include "Game.h"
#include "GirlTwo.h"
#include "DataManager.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init()
{
	if (!BaseController::init())
		return false;

	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	
	auto bg_ = Sprite::create("city8.png");
	bg_->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(bg_, -1);


	// 22娘
	auto tg = GirlTwo::create();
	tg->setPosition(390, 650);
	tg->setScale(0.8);
	this->addChild(tg, 20);

	// 22娘左边的对话框
	auto lqy_dialog = Sprite::create("gameEnd.png");
	lqy_dialog->setScale(0.3);
	lqy_dialog->setPosition(tg->getPosition() - Point(130, 0));
	lqy_dialog->setVisible(false);
	this->addChild(lqy_dialog, 21);

	//处理22娘说的话
	//const char *str_girl = ((String*)dic->objectForKey(""))->_string.c_str();
	auto girlTalk = Label::createWithTTF("22娘说的话", "fonts/b.ttf", 18);
	girlTalk->setDimensions(130, 300);
	girlTalk->setPosition(tg->getPosition() - Point(125, 100));
	girlTalk->setVisible(false);
	addChild(girlTalk, 22);




	//--------道具不足的提示图片,开始不显示
	auto notEnough = Sprite::create("warning.png");
	notEnough->setScale(0.8);
	notEnough->setVisible(false);
	notEnough->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(notEnough, 10);
	// yellow icon
	auto yellow = Sprite::create("yellowWarning.png");
	yellow->setVisible(false);
	yellow->setScale(0.6);
	yellow->setPosition(visibleSize.width / 2 - 75, visibleSize.height / 2 + 40);
	addChild(yellow, 11);
	// yellow icon 右边的描述
	const char *str_notDes = ((String*)dic->objectForKey("notenough"))->_string.c_str();
	auto notEnoughDes = Label::createWithTTF(str_notDes, "fonts/b.ttf", 35);
	notEnoughDes->setPosition(visibleSize.width / 2 + 32, visibleSize.height / 2 + 40);
	notEnoughDes->setVisible(false);
	addChild(notEnoughDes, 11);


	// button
	auto notEnoughMII = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(Game::warningCallback, this));
	notEnoughMII->setScale(0.4);
	auto notEnoughMenu = Menu::create(notEnoughMII, NULL);
	notEnoughMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	notEnoughMenu->setVisible(false);
	addChild(notEnoughMenu, 12);
	// ok label
	const char *str_ok = ((String*)dic->objectForKey("ok"))->_string.c_str();
	auto ok = Label::createWithTTF(str_ok, "fonts/b.ttf", 20);
	ok->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
	ok->setVisible(false);
	addChild(ok, 13);





	//2个功能性道具
	auto changeIcon = MenuItemImage::create("changeIcon.png", "changeIcon.png", 
		CC_CALLBACK_1(Game::changeIconType, this));
	changeIcon->setScale(0.5);
	auto changeIconMenu = Menu::create(changeIcon, NULL);
	changeIconMenu->setPosition(visibleSize.width / 2 + 100, visibleSize.height - 75);
	addChild(changeIconMenu, 3);
	changeIcon->setOpacity(0);
	ActionInterval * delay_ci = DelayTime::create(4.6);   //每个sprite出现间隔0.4秒
	auto fi_ci = FadeIn::create(0.5);
	auto seq_ci = Sequence::create(delay_ci, fi_ci, NULL);
	changeIcon->runAction(seq_ci);
	//道具1的数量label
	char cChangeIconNum[10];
	sprintf(cChangeIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("ChangeNum"));
	std::string strChangeIconNum = cChangeIconNum;
	auto changeIconLabel = Label::createWithTTF(cChangeIconNum, "fonts/pirulenrg.ttf", 18);
	changeIconLabel->setPosition(visibleSize.width / 2 + 125, visibleSize.height - 92);
	addChild(changeIconLabel, 3);
	changeIconLabel->setOpacity(0);
	ActionInterval * delay_cil = DelayTime::create(4.6);   //每个sprite出现间隔0.4秒
	auto fi_cil = FadeIn::create(0.5);
	auto seq_cil = Sequence::create(delay_cil, fi_cil, NULL);
	changeIconLabel->runAction(seq_cil);

	//道具2
	auto bombIcon = MenuItemImage::create("bomb.png", "bomb.png", 
		CC_CALLBACK_1(Game::bombIconType, this));
	bombIcon->setScale(0.5);
	auto bombIconMenu = Menu::create(bombIcon, NULL);
	bombIconMenu->setPosition(visibleSize.width / 2 + 160, visibleSize.height - 75);
	addChild(bombIconMenu, 3);
	bombIcon->setOpacity(0);
	ActionInterval * delay_bi = DelayTime::create(5);   //每个sprite出现间隔0.4秒
	auto fi_bi = FadeIn::create(0.5);
	auto seq_bi = Sequence::create(delay_bi, fi_bi, NULL);
	bombIcon->runAction(seq_bi);
	//道具2的数量label
	char cBombIconNum[10];
	sprintf(cBombIconNum, "%d", UserDefault::getInstance()->getIntegerForKey("BombNum"));
	std::string strBombIconNum = cBombIconNum;
	auto bombIconLabel = Label::createWithTTF(cBombIconNum, "fonts/pirulenrg.ttf", 18);
	bombIconLabel->setPosition(visibleSize.width / 2 + 185, visibleSize.height - 92);
	addChild(bombIconLabel, 3);
	bombIconLabel->setOpacity(0);
	ActionInterval * delay_bil = DelayTime::create(5);   //每个sprite出现间隔0.4秒
	auto fi_bil = FadeIn::create(0.5);
	auto seq_bil = Sequence::create(delay_bil, fi_bil, NULL);
	bombIconLabel->runAction(seq_bil);

	//让道具数字变红
	if (UserDefault::getInstance()->getIntegerForKey("BombNum") == 0)
	{
		bombIconLabel->setColor(Color3B(208, 52, 13));
	}
	if (UserDefault::getInstance()->getIntegerForKey("ChangeNum") == 0)
	{
		changeIconLabel->setColor(Color3B(208, 52, 13));
	}






	//半透明黑色背景
	auto transBg = Sprite::create("transparent.png");
	transBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	transBg->setScaleX(1.5);
	transBg->setScaleY(0.001);
	addChild(transBg, 7);
	ActionInterval * delaytime_bg = CCDelayTime::create(1.5);
	auto st_bg = ScaleTo::create(0.5, 1.5, 0.8);  //这里的x y比例不是原来图片的大小了，是setscale之后的大小了
	auto sq_bg = Sequence::create(delaytime_bg, st_bg, NULL);
	transBg->runAction(sq_bg);
	//女孩飞入介绍城市
	auto girl = Sprite::create("girl1.png");
	girl->setScale(0.2);
	girl->setPosition(-100, visibleSize.height / 2);
	addChild(girl, 15);
	ActionInterval * delaytime_girl = CCDelayTime::create(2.0);
	auto mt_girl = MoveTo::create(0.5, Vec2(50, visibleSize.height / 2));
	auto sq_girl = Sequence::create(delaytime_girl, mt_girl, NULL);
	girl->runAction(sq_girl);
	//2条label相反方向飞入
	const char *str_welcome = ((String*)dic->objectForKey("welcome"))->_string.c_str();
	auto welcome = Label::createWithTTF(str_welcome, "fonts/b.ttf", 40);
	welcome->setRotationSkewX(15);//这个函数是倾斜字体用的
	welcome->setPosition(-100, visibleSize.width / 2 + 180);
	addChild(welcome, 8);
	ActionInterval * delaytime_welcome = CCDelayTime::create(2.0);
	auto mt_welcome = MoveTo::create(0.6, Vec2(200, visibleSize.width / 2 + 180));
	auto deleteWelcome = CallFunc::create([=]() {
		welcome->removeAllChildrenWithCleanup(true);
	});
	ActionInterval * delaytime_welcome2 = CCDelayTime::create(2.0);
	auto sq_welcome = Sequence::create(delaytime_welcome, mt_welcome, delaytime_welcome2, deleteWelcome, NULL);
	welcome->runAction(sq_welcome);


	bool isGameReady = false;
	auto curLevel = getDataManager().getGameLevel();


	//城市string，保存各个城市的名字
	std::string cityName[20] = { "beijing","tokyo","singnapore","hawaii","canada","newyork","sanfan","rio","london","germany","swiss","dutch","greece","moscow","paris","rome","africa","dubai","maldive","sydeny" };
	//介绍地名的label
	const char *str_city = ((String*)dic->objectForKey(cityName[curLevel - 1]))->_string.c_str();
	auto spots = Label::createWithTTF(str_city, "fonts/b.ttf", 30);
	spots->setColor(Color3B(242, 221, 28));
	spots->setRotationSkewX(15);
	spots->setPosition(650, visibleSize.width / 2 + 125);
	addChild(spots, 8);
	ActionInterval * delaytime_spots = CCDelayTime::create(2.0);
	auto mt_spots = MoveTo::create(0.6, Vec2(300, visibleSize.width / 2 + 125));
	auto deleteSpots = CallFunc::create([=]() {

		spots->removeAllChildrenWithCleanup(true);
	});
	ActionInterval * delaytime_spots2 = CCDelayTime::create(2.0);
	auto sq_spots = Sequence::create(delaytime_spots, mt_spots, delaytime_spots2, deleteSpots, NULL);
	spots->runAction(sq_spots);


	//ready go 动画
	auto readyLabel = Label::createWithTTF("READY", "fonts/HANGTHEDJ.ttf", 100);
	readyLabel->setPosition(visibleSize.width + 200, visibleSize.height / 2);
	addChild(readyLabel, 8);
	ActionInterval * delaytime_ready = CCDelayTime::create(4.7);
	auto mt_ready = MoveTo::create(0.3, Point(300, visibleSize.height / 2));
	auto mt_ready_1 = MoveTo::create(1.0, Point(200, visibleSize.height / 2));
	auto mt_ready_2 = MoveTo::create(0.3, Point(-200, visibleSize.height / 2));
	auto musicReady = CallFunc::create([=]() {
		//SimpleAudioEngine::getInstance()->playEffect("ready.OGG");
	});
	auto sq_ready = Sequence::create(delaytime_ready, musicReady, mt_ready, mt_ready_1, mt_ready_2, NULL);
	readyLabel->runAction(sq_ready);



	auto goLabel = Label::createWithTTF("GO", "fonts/HANGTHEDJ.ttf", 100);
	goLabel->setScale(2.5);
	goLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	goLabel->setOpacity(0);
	addChild(goLabel, 7);
	auto fi_go = FadeIn::create(0.5);
	auto st_go = ScaleTo::create(0.5, 1);
	auto sp_go = Spawn::create(fi_go, st_go, NULL);
	ActionInterval * delaytime_go = CCDelayTime::create(6.3);
	auto deleteBg = CallFunc::create([=]() {

		transBg->removeFromParentAndCleanup(true);
		goLabel->removeFromParentAndCleanup(true);
		girl->removeFromParentAndCleanup(true);
		//isGameReady = true;
	});
	ActionInterval * delaytime_wait = CCDelayTime::create(0.4);
	auto sq_go = Sequence::create(delaytime_go, sp_go, delaytime_wait, deleteBg, NULL);
	goLabel->runAction(sq_go);



	////添加怎么玩的层,只有第一关才有
	//if (getDataManager().getGameLevel() == 1)
	//{
	//	ActionInterval * delaytime_htp = CCDelayTime::create(7.5);
	//	auto addHowToPlay = CallFunc::create([=]() {
	//		HowToPlayLayer * htp = HowToPlayLayer::create();
	//		htp->setPosition(0, 0);
	//		addChild(htp, 20);
	//	});
	//	auto seq_htp = Sequence::create(delaytime_htp, addHowToPlay, NULL);
	//	this->runAction(seq_htp);
	//}



	//目标：字体
	const char *str_action = ((String*)dic->objectForKey("target_score"))->_string.c_str();
	auto label2 = Label::createWithTTF(str_action, "fonts/b.ttf", 18);
	label2->setPosition(visibleSize.width / 2 - 40, 750);
	label2->setOpacity(0);
	ActionInterval * delay_la = DelayTime::create(3.8);   //每个sprite出现间隔0.4秒
	auto fi_la = FadeIn::create(0.5);
	auto seq_la = Sequence::create(delay_la, fi_la, NULL);
	label2->runAction(seq_la);
	addChild(label2, 3);
	//目标：分数
	auto target_score = getDataManager().getLevelTargetScore();
	char target_temp[20];
	sprintf(target_temp, "%d", target_score);
	std::string target_str = target_temp;
	auto targetScore_label = Label::createWithTTF(target_str, "fonts/watch.ttf", 25);
	targetScore_label->setPosition(visibleSize.width / 2 + 10, 750);
	targetScore_label->setOpacity(0);
	ActionInterval * delay_ts = DelayTime::create(4.2);   //每个sprite出现间隔0.4秒
	auto fi_ts = FadeIn::create(0.5);
	auto seq_ts = Sequence::create(delay_ts, fi_ts, NULL);
	targetScore_label->runAction(seq_ts);
	addChild(targetScore_label, 5);

	// 等级LV：
	auto level_label = Label::createWithTTF("Lv:", "fonts/ethnocentricrg.ttf", 30);
	level_label->setPosition(visibleSize.width / 2 - 180, visibleSize.height - 160);
	addChild(level_label, 2);
	level_label->setOpacity(0);
	ActionInterval * delay_ll = DelayTime::create(5.4);   //每个sprite出现间隔0.4秒
	auto fi_ll = FadeIn::create(0.5);
	auto seq_ll = Sequence::create(delay_ll, fi_ll, NULL);
	level_label->runAction(seq_ll);
	// 等级数目
	log("cur level: %d", curLevel);
	char target_level[20];
	sprintf(target_level, "%d", curLevel);
	std::string target_str1 = target_level;
	auto levelNum_label = Label::createWithTTF(target_str1, "fonts/ethnocentricrg.ttf", 40);
	levelNum_label->setPosition(visibleSize.width / 2 - 120, visibleSize.height - 157);
	addChild(levelNum_label, 2);
	levelNum_label->setOpacity(0);
	ActionInterval * delay_lnl = DelayTime::create(5.6);   //每个sprite出现间隔0.4秒
	auto fi_lnl = FadeIn::create(0.5);
	auto seq_lnl = Sequence::create(delay_lnl, fi_lnl, NULL);
	levelNum_label->runAction(seq_lnl);

	char c[10];
	sprintf(c, "%d", curLevel);
	std::string str = c;
	std::string city = "city" + str;
	Sprite * bg = Sprite::create(city + ".png");
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg, 1);




	bool timerRunning = false;
	bool gameIsOver = false;


	//游戏对话框图片:显示每个icon的知识----------背景--------------------
	Sprite * dialog = Sprite::create("dialog.png");
	dialog->setPosition(visibleSize.width / 2 + 10, -100);
	dialog->setScaleY(1.4);
	auto mt_dialog = MoveTo::create(1, Vec2(visibleSize.width / 2 + 10, 90));
	ActionInterval * delay_dialog = DelayTime::create(2.7);
	EaseOut * dialog_slow = EaseOut::create(mt_dialog, 7.0);
	//由快到慢的动作，第二个参数是变化率
	auto seq_dialog = Sequence::create(delay_dialog, dialog_slow, NULL);
	dialog->runAction(seq_dialog);
	addChild(dialog, 2);

	//知识label
	auto knowledge_label = Label::createWithTTF("", "fonts/b.ttf", 20);
	knowledge_label->setPosition(visibleSize.width / 2 - 85, 40);
	knowledge_label->setAnchorPoint(Point(0, 0));
	knowledge_label->setDimensions(300, 60);
	addChild(knowledge_label, 6);

	//level1_1.png
	auto small_pic = Sprite::create("level1_1.png");
	small_pic->setPosition(visibleSize.width / 2 - 160, 80);
	small_pic->setScale(0.5);
	//small_pic->setVisible(false);
	addChild(small_pic, 5);
	// label
	auto name_label = Label::createWithTTF("evernote", "fonts/b.ttf", 20);
	name_label->setPosition(visibleSize.width / 2 - 160, 40);
	//name_label->setVisible(false);
	addChild(name_label, 5);



	//背景图片,3个最上面的
	//-------------------------目标分数的背景
	Sprite * m1 = Sprite::create("menu.png");
	m1->setScaleX(0.8);
	m1->setScaleY(0.8);
	m1->setPosition(visibleSize.width / 2, visibleSize.height + 80);                                       //dellta Y = 130
	auto mt_m1 = MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height - 50));
	ActionInterval * delay_m1 = DelayTime::create(2.7);
	EaseOut * m1_slow = EaseOut::create(mt_m1, 7.0);
	//由快到慢的动作，第二个参数是变化率
	auto seq_m1 = Sequence::create(delay_m1, m1_slow, NULL);
	m1->runAction(seq_m1);
	addChild(m1, 2);
	//-------------------------的背景
	Sprite * m2 = Sprite::create("menu.png");
	m2->setScaleX(0.8);
	m2->setScaleY(0.8);
	m2->setPosition(visibleSize.width / 2 - 140, visibleSize.height + 55);
	auto mt_m2 = MoveTo::create(1, Vec2(visibleSize.width / 2 - 140, visibleSize.height - 75));
	ActionInterval * delay_m2 = DelayTime::create(2.7);
	EaseOut * m2_slow = EaseOut::create(mt_m2, 7.0);
	//由快到慢的动作，第二个参数是变化率
	auto seq_m2 = Sequence::create(delay_m2, m2_slow, NULL);
	m2->runAction(seq_m2);
	addChild(m2, 2);
	//-------------------------功能性icon的背景 
	Sprite * m3 = Sprite::create("menu.png");
	m3->setScaleX(0.8);
	m3->setScaleY(0.8);
	m3->setPosition(visibleSize.width / 2 + 140, visibleSize.height + 55);
	auto mt_m3 = MoveTo::create(1, Vec2(visibleSize.width / 2 + 140, visibleSize.height - 75));
	ActionInterval * delay_m3 = DelayTime::create(2.7);
	EaseOut * m3_slow = EaseOut::create(mt_m3, 7.0);
	//由快到慢的动作，第二个参数是变化率
	auto seq_m3 = Sequence::create(delay_m3, m3_slow, NULL);
	m3->runAction(seq_m3);
	addChild(m3, 2);



	//返回主菜单和重新开始按钮
	auto btm = MenuItemImage::create("backToMenu.png", "backToMenu.png", 
		CC_CALLBACK_1(Game::returnToMenu, this));
	btm->setAnchorPoint(Point(0, 0));
	btm->setScale(0.45);
	auto btm_menu = Menu::create(btm, NULL);
	btm_menu->setPosition(visibleSize.width / 2 - 200, visibleSize.height - 105);
	btm_menu->setOpacity(0);
	ActionInterval * delay_btm = DelayTime::create(3.0);
	auto fi_btm = FadeIn::create(0.5);
	auto seq_btm = Sequence::create(delay_btm, fi_btm, NULL);
	btm_menu->runAction(seq_btm);
	addChild(btm_menu, 3);
	//重新开始按钮
	auto res = MenuItemImage::create("restart.png", "restart.png", 
		CC_CALLBACK_1(Game::restartGame, this));
	res->setAnchorPoint(Point(0, 0));
	res->setScale(0.45);
	auto res_menu = Menu::create(res, NULL);
	res_menu->setPosition(visibleSize.width / 2 - 140, visibleSize.height - 100);
	res_menu->setOpacity(0);
	ActionInterval * delay_res = DelayTime::create(3.4);   //每个sprite出现间隔0.4秒
	auto fi_res = FadeIn::create(0.5);
	auto seq_res = Sequence::create(delay_res, fi_res, NULL);
	res_menu->runAction(seq_res);
	addChild(res_menu, 3);





	//初始化分数
	int tempICS = getDataManager().getCurrentScore();
	getDataManager().setInitCurrentScore(tempICS);


	//当前分数的显示
	auto currentScore = getDataManager().getCurrentScore();
	log("current score init: %d", currentScore);
	char s[20];
	sprintf(s, "%d", currentScore);
	auto label_score = Label::createWithTTF(s, "fonts/HANGTHEDJ.ttf", 50);
	label_score->setPosition(visibleSize.width / 2 - 15, visibleSize.height - 150);
	addChild(label_score, 3);
	auto st = ScaleBy::create(1.0, 1.1);
	auto sq = Sequence::create(st, st->reverse(), NULL);
	auto rp = RepeatForever::create(sq);
	label_score->runAction(rp);
	label_score->setOpacity(0);
	ActionInterval * delay_ls = DelayTime::create(6);   //每个sprite出现间隔0.4秒
	auto fi_ls = FadeIn::create(0.5);
	auto seq_ls = Sequence::create(delay_ls, fi_ls, NULL);
	label_score->runAction(seq_ls);


	//---------------------------------------游戏结束对话框
	auto gameEnd = Sprite::create("gameEnd.png");
	gameEnd->setPosition(visibleSize.width / 2, visibleSize.height - 450);
	gameEnd->setScale(0.85);
	addChild(gameEnd, 5);
	gameEnd->setVisible(false);






	//初始化数据统计
	auto statistic_LeftIcon = 0;
	auto statistic_LeftBonus = 0;
	auto statistic_SingleMost = 0;
	auto statistic_MostIcon = 0;
	auto statistic_Time = 0;

	auto four_kill = 0;
	auto five_kill = 0;
	auto six_kill = 0;
	auto seven_kill = 0;
	auto legendary_kill = 0;

	//////////////////////////////////////////数据统计
	// title
	const char *str_1 = ((String*)dic->objectForKey("statistic"))->_string.c_str();
	auto statisticTitle = Label::createWithTTF(str_1, "fonts/b.ttf", 30);
	statisticTitle->setPosition(visibleSize.width / 2, visibleSize.height - 320);
	statisticTitle->setVisible(false);
	addChild(statisticTitle, 6);
	//剩余图标
	auto pointer1 = Sprite::create("pointer.png");
	pointer1->setPosition(visibleSize.width / 2 - 190, visibleSize.height - 380);
	pointer1->setRotation(-90);
	pointer1->setVisible(false);
	addChild(pointer1, 6);
	// label
	const char *str_2 = ((String*)dic->objectForKey("lefticon"))->_string.c_str();
	auto title1 = Label::createWithTTF(str_2, "fonts/b.ttf", 20);
	title1->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 380);
	title1->setVisible(false);
	addChild(title1, 6);
	// label：number
	char sLabel1[20];
	sprintf(sLabel1, "%d", statistic_LeftIcon);
	auto leftIcon_label = Label::createWithTTF(sLabel1, "fonts/watch.ttf", 25);
	leftIcon_label->setPosition(visibleSize.width / 2 - 30, visibleSize.height - 380);
	leftIcon_label->setVisible(false);
	addChild(leftIcon_label, 6);
	//剩余奖励
	auto pointer2 = Sprite::create("pointer.png");
	pointer2->setPosition(visibleSize.width / 2 - 190, visibleSize.height - 420);
	pointer2->setRotation(-90);
	pointer2->setVisible(false);
	addChild(pointer2, 6);
	//label
	const char *str_3 = ((String*)dic->objectForKey("leftbonus"))->_string.c_str();
	auto title2 = Label::createWithTTF(str_3, "fonts/b.ttf", 20);
	title2->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 420);
	title2->setVisible(false);
	addChild(title2, 6);
	//label-number
	char sLabel2[20];
	sprintf(sLabel2, "%d", statistic_LeftBonus);
	auto leftBonus_label = Label::createWithTTF(sLabel2, "fonts/watch.ttf", 25);
	leftBonus_label->setPosition(visibleSize.width / 2 - 30, visibleSize.height - 420);
	leftBonus_label->setVisible(false);
	addChild(leftBonus_label, 6);
	//单个最多
	auto pointer3 = Sprite::create("pointer.png");
	pointer3->setPosition(visibleSize.width / 2 - 190, visibleSize.height - 460);
	pointer3->setRotation(-90);
	pointer3->setVisible(false);
	addChild(pointer3, 6);
	// label
	const char *str_4 = ((String*)dic->objectForKey("singlerecord"))->_string.c_str();
	auto title3 = Label::createWithTTF(str_4, "fonts/b.ttf", 20);
	title3->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 460);
	title3->setVisible(false);
	addChild(title3, 6);
	// label-number
	char sLabel4[20];
	sprintf(sLabel4, "%d", statistic_SingleMost);
	auto singleMost_label = Label::createWithTTF(sLabel4, "fonts/watch.ttf", 25);
	singleMost_label->setPosition(visibleSize.width / 2 - 30, visibleSize.height - 460);
	singleMost_label->setVisible(false);
	addChild(singleMost_label, 6);
	//消去最多
	auto pointer4 = Sprite::create("pointer.png");
	pointer4->setPosition(visibleSize.width / 2 - 190, visibleSize.height - 500);
	pointer4->setRotation(-90);
	pointer4->setVisible(false);
	addChild(pointer4, 6);
	// label
	const char *str_5 = ((String*)dic->objectForKey("mosterase"))->_string.c_str();
	auto title4 = Label::createWithTTF(str_5, "fonts/b.ttf", 20);
	title4->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 500);
	title4->setVisible(false);
	addChild(title4, 6);
	// label-number
	char sLabel5[20];
	sprintf(sLabel5, "%d", statistic_MostIcon);
	auto mostIcon_label = Label::createWithTTF(sLabel5, "fonts/watch.ttf", 25);
	mostIcon_label->setPosition(visibleSize.width / 2 - 30, visibleSize.height - 500);
	mostIcon_label->setVisible(false);
	addChild(mostIcon_label, 6);

	//时间
	auto pointer5 = Sprite::create("pointer.png");
	pointer5->setPosition(visibleSize.width / 2 - 190, visibleSize.height - 540);
	pointer5->setRotation(-90);
	pointer5->setVisible(false);
	addChild(pointer5, 6);
	// label
	const char *str_6 = ((String*)dic->objectForKey("time"))->_string.c_str();
	auto title5 = Label::createWithTTF(str_6, "fonts/b.ttf", 20);
	title5->setPosition(visibleSize.width / 2 - 130, visibleSize.height - 540);
	title5->setVisible(false);
	addChild(title5, 6);
	//// label-number
	//char sLabel6[20];
	//sprintf(sLabel6, "%f", statistic_Time);
	//auto timer_label = Label::createWithTTF(sLabel6, "fonts/watch.ttf", 25);
	//timer_label->setPosition(visibleSize.width / 2 - 30, visibleSize.height - 540);
	////timer_label->setVisible(false);
	//addChild(timer_label, 6);
	//////////////////////////////////////////END 数据统计




	//////////////////////////////////显示4~8杀的label
	//4杀
	auto pointer6 = Sprite::create("pointer.png");
	pointer6->setPosition(visibleSize.width / 2 + 30, visibleSize.height - 380);
	pointer6->setRotation(-90);
	pointer6->setVisible(false);
	addChild(pointer6, 6);
	// label
	const char *str_7 = ((String*)dic->objectForKey("fourkill"))->_string.c_str();
	auto title6 = Label::createWithTTF(str_7, "fonts/b.ttf", 20);
	title6->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 380);
	title6->setVisible(false);
	addChild(title6, 6);
	//label-number
	char sLabel7[20];
	sprintf(sLabel7, "%d", four_kill);
	auto fourKill_label = Label::createWithTTF(sLabel7, "fonts/watch.ttf", 25);
	fourKill_label->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 380);
	fourKill_label->setVisible(false);
	addChild(fourKill_label, 6);
	//5杀
	auto pointer7 = Sprite::create("pointer.png");
	pointer7->setPosition(visibleSize.width / 2 + 30, visibleSize.height - 420);
	pointer7->setRotation(-90);
	pointer7->setVisible(false);
	addChild(pointer7, 6);
	//label
	const char *str_8 = ((String*)dic->objectForKey("fivekill"))->_string.c_str();
	auto title7 = Label::createWithTTF(str_8, "fonts/b.ttf", 20);
	title7->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 420);
	title7->setVisible(false);
	addChild(title7, 6);
	//label-number
	char sLabel8[20];
	sprintf(sLabel8, "%d", five_kill);
	auto fiveKill_label = Label::createWithTTF(sLabel8, "fonts/watch.ttf", 25);
	fiveKill_label->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 420);
	fiveKill_label->setVisible(false);
	addChild(fiveKill_label, 6);
	//6杀
	auto pointer8 = Sprite::create("pointer.png");
	pointer8->setPosition(visibleSize.width / 2 + 30, visibleSize.height - 460);
	pointer8->setRotation(-90);
	pointer8->setVisible(false);
	addChild(pointer8, 6);

	const char *str_9 = ((String*)dic->objectForKey("sixkill"))->_string.c_str();
	auto title8 = Label::createWithTTF(str_9, "fonts/b.ttf", 20);
	title8->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 460);
	title8->setVisible(false);
	addChild(title8, 6);

	char sLabel9[20];
	sprintf(sLabel9, "%d", six_kill);
	auto sixKill_label = Label::createWithTTF(sLabel8, "fonts/watch.ttf", 25);
	sixKill_label->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 460);
	sixKill_label->setVisible(false);
	addChild(sixKill_label, 6);

	//7杀
	auto pointer9 = Sprite::create("pointer.png");
	pointer9->setPosition(visibleSize.width / 2 + 30, visibleSize.height - 500);
	pointer9->setRotation(-90);
	pointer9->setVisible(false);
	addChild(pointer9, 6);

	const char *str_10 = ((String*)dic->objectForKey("sevenkill"))->_string.c_str();
	auto title9 = Label::createWithTTF(str_10, "fonts/b.ttf", 20);
	title9->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 500);
	title9->setVisible(false);
	addChild(title9, 6);

	char sLabel10[20];
	sprintf(sLabel10, "%d", seven_kill);
	auto sevenKill_label = Label::createWithTTF(sLabel10, "fonts/watch.ttf", 25);
	sevenKill_label->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 500);
	sevenKill_label->setVisible(false);
	addChild(sevenKill_label, 6);

	//超神
	auto pointer10 = Sprite::create("pointer.png");
	pointer10->setPosition(visibleSize.width / 2 + 30, visibleSize.height - 540);
	pointer10->setRotation(-90);
	pointer10->setVisible(false);
	addChild(pointer10, 6);

	const char *str_11 = ((String*)dic->objectForKey("legendary"))->_string.c_str();
	auto title10 = Label::createWithTTF(str_11, "fonts/b.ttf", 20);
	title10->setPosition(visibleSize.width / 2 + 70, visibleSize.height - 540);
	title10->setVisible(false);
	addChild(title10, 6);

	char sLabel11[20];
	sprintf(sLabel11, "%d", legendary_kill);
	auto legendaryKill_label = Label::createWithTTF(sLabel11, "fonts/watch.ttf", 25);
	legendaryKill_label->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 540);
	legendaryKill_label->setVisible(false);
	addChild(legendaryKill_label, 6);
	//////////////////////////////////END 显示4~8杀的label




	/////////////////////////剩余奖励icon
	auto leftBonusBox = Sprite::create("leftBonus.png");                                    //大小写问题，vs忽略大小写，adnroid不忽略，卧槽
	leftBonusBox->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	leftBonusBox->setScale(1);
	//leftBonusBox->setOpacity(0);
	addChild(leftBonusBox, 6);

	// 下一关 menuitem
	auto nextLevel = MenuItemImage::create("menu.png", "menu.png", 
		CC_CALLBACK_1(Game::goToNextLevel, this));
	nextLevel->setScale(0.5);
	auto menuNextLevel = Menu::create(nextLevel, NULL);
	menuNextLevel->setPosition(visibleSize.width / 2, visibleSize.height - 600);
	//menuNextLevel->setVisible(false);
	addChild(menuNextLevel, 6);
	// menuitem-label
	const char *str_nextLevel = ((String*)dic->objectForKey("nextLevel"))->_string.c_str();
	auto nextLevelLabel = Label::createWithTTF(str_nextLevel, "fonts/b.ttf", 20);
	nextLevelLabel->setPosition(visibleSize.width / 2 - 5, visibleSize.height - 600);
	addChild(nextLevelLabel, 7);
	//nextLevelLabel->setVisible(false);
	


	// TODO...






	return true;
}


//warning回调函数
void Game::warningCallback(cocos2d::Ref *r)
{}


//道具函数： 改变种类
void Game::changeIconType(Ref * r)
{}

//道具函数： 爆炸icon
void Game::bombIconType(Ref * r)
{}

void Game::returnToMenu(cocos2d::Ref* r)
{}

//重新开始
void Game::restartGame(cocos2d::Ref* r)
{}

void Game::goToNextLevel(Ref * r)
{}