#include "AchieveLayer.h"

AchieveLayer::AchieveLayer()
{}

AchieveLayer::~AchieveLayer()
{}

//Scene* AchieveLayer::createScene()
//{
//	auto scene = Scene::create();
//	auto layer = AchieveLayer::create();
//	scene->addChild(layer);
//	return scene;
//}

bool AchieveLayer::init()
{
	if (!Layer::init())
		return false;

	//用xml保存中文，记得xml文件要存在resource文件夹里面才行
	Dictionary* dic = Dictionary::createWithContentsOfFile("chinese.xml");

	Size size = Director::getInstance()->getVisibleSize();

	// 对话框
	dialog = Sprite::create("gameEnd.png");
	dialog->setPosition(size.width / 2, -500);
	dialog->setScale(0.8);
	dialog->setScaleY(1.1);
	auto mt_dialog = MoveTo::create(2.0, Vec2(size.width / 2, size.height / 2));
	EaseOut * dialog_slow = EaseOut::create(mt_dialog, 7.0);
	dialog->runAction(dialog_slow);
	addChild(dialog, 2);

	///========================添加标题-个人记录
	const char *str = ((String*)dic->objectForKey("achieve2"))->_string.c_str();
	record = Label::createWithTTF(str, "fonts/b.ttf", 40);
	record->setPosition(size.width / 2, size.height / 2 + 150);
	record->setVisible(false);
    addChild(record, 2);
	// 左向按钮
	pointerLeft = Sprite::create("pointer.png");
	pointerLeft->setRotation(90);
	pointerLeft->setScale(1.5);
	pointerLeft->setPosition(size.width / 2 - 100, size.height / 2 + 150);
	pointerLeft->setVisible(false);
	addChild(pointerLeft, 3);
	// 右向按钮
	pointerRight = Sprite::create("pointer.png");
	pointerRight->setRotation(-90);
	pointerRight->setScale(1.5);
	pointerRight->setPosition(size.width / 2 + 100, size.height / 2 + 150);
	pointerRight->setVisible(false);
	addChild(pointerRight, 3);

	// ok
	ok = Sprite::create("menu.png");
	ok->setPosition(size.width / 2, size.height / 2 - 190);
	ok->setScale(0.5);
	ok->setVisible(false);
	addChild(ok, 3);
	//ok-button——label
	const char *str1 = ((String*)dic->objectForKey("achieve3"))->_string.c_str();
	okLabel = Label::createWithTTF(str1, "fonts/b.ttf", 20);
	okLabel->setPosition(size.width / 2, size.height / 2 - 190);
	addChild(okLabel, 4);
	okLabel->setVisible(false);

	//历史最高分icon
	icon1 = Sprite::create("achieveIcon.png");
	icon1->setPosition(size.width / 2 - 70, size.height / 2 + 70);
	icon1->setVisible(false);
	addChild(icon1, 5);
	//历史最高分label
	const char *str_bsl = ((String*)dic->objectForKey("achieve4"))->_string.c_str();
	historyBestScoreLabel = Label::createWithTTF(str_bsl, "fonts/b.ttf", 23);
	historyBestScoreLabel->setPosition(size.width / 2 + 10, size.height / 2 + 80);
	historyBestScoreLabel->setVisible(false);
	addChild(historyBestScoreLabel, 5);
	//历史最高分label_number
	char c1[10];
	int hbs = UserDefault::getInstance()->getIntegerForKey("historyBestScore");
	sprintf(c1, "%d", hbs);
	std::string str_hbln = c1;
	historyBestScoreLabelNum = Label::createWithTTF(str_hbln, "fonts/HANGTHEDJ.ttf", 40);
	historyBestScoreLabelNum->setPosition(size.width / 2, size.height / 2 + 20);
	historyBestScoreLabelNum->setVisible(false);
	addChild(historyBestScoreLabelNum, 5);

	//单次消去最多icon
	icon2 = Sprite::create("achieveIcon.png");
	icon2->setPosition(size.width / 2 - 70, size.height / 2 - 50);
	icon2->setVisible(false);
	addChild(icon2, 5);
	//单次消去最多label
	const char *str_sb = ((String*)dic->objectForKey("achieve5"))->_string.c_str();
	singleBest = Label::createWithTTF(str_sb, "fonts/b.ttf", 23);
	singleBest->setPosition(size.width / 2 + 20, size.height / 2 - 40);
	singleBest->setVisible(false);
	addChild(singleBest, 5);
	//单次消去最多label_number
	char c3[10];
	int sb = UserDefault::getInstance()->getIntegerForKey("singleBest");
	sprintf(c3, "%d", sb);
	std::string str_sb1 = c3;
	singleBestNum = Label::createWithTTF(str_sb1, "fonts/HANGTHEDJ.ttf", 40);
	singleBestNum->setPosition(size.width / 2, size.height / 2 - 100);
	singleBestNum->setVisible(false);
	addChild(singleBestNum, 5);




	/// ///////////////////////游戏信息的label
	//添加标题
	const char *str5 = ((String*)dic->objectForKey("achieve6"))->_string.c_str();
	info1 = Label::createWithTTF(str5, "fonts/b.ttf", 40);
	info1->setPosition(size.width / 2, size.height / 2 + 150);
	info1->setVisible(false);
	addChild(info1, 2);
	// 左箭头
	pointerLeft1 = Sprite::create("pointer.png");
	pointerLeft1->setRotation(90);
	pointerLeft1->setScale(1.5);
	pointerLeft1->setPosition(size.width / 2 - 100, size.height / 2 + 150);
	pointerLeft1->setVisible(false);
	addChild(pointerLeft1, 2);
	// 右箭头
	pointerRight1 = Sprite::create("pointer.png");
	pointerRight1->setRotation(-90);
	pointerRight1->setScale(1.5);
	pointerRight1->setPosition(size.width / 2 + 100, size.height / 2 + 150);
	pointerRight1->setVisible(false);
	addChild(pointerRight1, 2);

	// 开发周期 5 Weeks---label
	icon3 = Sprite::create("achieveIcon.png");
	icon3->setPosition(size.width / 2 - 150, size.height / 2 + 70);
	icon3->setVisible(false);
	addChild(icon3, 5);
	const char *str_10 = ((String*)dic->objectForKey("achieve7"))->_string.c_str();
	infoLabel1 = Label::createWithTTF(str_10, "fonts/b.ttf", 23);
	infoLabel1->setAnchorPoint(Point(0, 0));
	infoLabel1->setPosition(size.width / 2 - 120, size.height / 2 + 70);
	infoLabel1->setVisible(false);
	addChild(infoLabel1, 5);

	// 代码数目的icon和label
	icon4 = Sprite::create("achieveIcon.png");
	icon4->setPosition(size.width / 2 - 150, size.height / 2 + 10);
	icon4->setVisible(false);
	addChild(icon4, 5);
	const char *str_11 = ((String*)dic->objectForKey("achieve8"))->_string.c_str();
	infoLabel2 = Label::createWithTTF(str_11, "fonts/b.ttf", 23);
	infoLabel2->setAnchorPoint(Point(0, 0));
	infoLabel2->setPosition(size.width / 2 - 120, size.height / 2 + 10);
	infoLabel2->setVisible(false);
	addChild(infoLabel2, 5);

	// icon-label-买的素材
	icon5 = Sprite::create("achieveIcon.png");
	icon5->setPosition(size.width / 2 - 150, size.height / 2 - 50);
	icon5->setVisible(false);
	addChild(icon5, 5);
	const char *str_12 = ((String*)dic->objectForKey("achieve9"))->_string.c_str();
	infoLabel3 = Label::createWithTTF(str_12, "fonts/b.ttf", 23);
	infoLabel3->setAnchorPoint(Point(0, 0));
	infoLabel3->setPosition(size.width / 2 - 120, size.height / 2 - 50);
	infoLabel3->setVisible(false);
	addChild(infoLabel3, 5);

	// 游戏引擎介绍-icon和label
	icon6 = Sprite::create("achieveIcon.png");
	icon6->setPosition(size.width / 2 - 150, size.height / 2 - 110);
	icon6->setVisible(false);
	addChild(icon6, 5);
	const char *str_13 = ((String*)dic->objectForKey("achieve10"))->_string.c_str();
	infoLabel4 = Label::createWithTTF(str_13, "fonts/b.ttf", 23);
	infoLabel4->setAnchorPoint(Point(0, 0));
	infoLabel4->setPosition(size.width / 2 - 120, size.height / 2 - 110);
	infoLabel4->setVisible(false);
	addChild(infoLabel4, 5);




	/// ////////////////////////////////道具兑换信息
	//添加标题
	const char *str6 = ((String*)dic->objectForKey("achieve11"))->_string.c_str();
	info2 = Label::createWithTTF(str6, "fonts/b.ttf", 40);
	info2->setPosition(size.width / 2, size.height / 2 + 150);
	info2->setVisible(false);
	addChild(info2, 5);
	// 左箭头
	pointerLeft2 = Sprite::create("pointer.png");
	pointerLeft2->setRotation(90);
	pointerLeft2->setScale(1.5);
	pointerLeft2->setPosition(size.width / 2 - 100, size.height / 2 + 150);
	pointerLeft2->setVisible(false);
	addChild(pointerLeft2, 5);
	// 右箭头
	pointerRight2 = Sprite::create("pointer.png");
	pointerRight2->setRotation(-90);
	pointerRight2->setScale(1.5);
	pointerRight2->setPosition(size.width / 2 + 100, size.height / 2 + 150);
	pointerRight2->setVisible(false);
	addChild(pointerRight2, 5);

	//兑换具体描述
	const char *str7 = ((String*)dic->objectForKey("achieve12"))->_string.c_str();
	des2 = Label::createWithTTF(str7, "fonts/b.ttf", 23);
	des2->setPosition(size.width / 2, size.height / 2 + 50);
	des2->setDimensions(300, 70);
	des2->setVisible(false);
	addChild(des2, 5);


	// 对话框
	legendaryDialog = Sprite::create("menu.png");
	legendaryDialog->setPosition(size.width / 2, size.height - 80);
	legendaryDialog->setScaleY(0.9);
	legendaryDialog->setVisible(false);
	addChild(legendaryDialog, 2);
	// 对话框label
	const char *str8 = ((String*)dic->objectForKey("achieve13"))->_string.c_str();
	legendaryLabelDes = Label::createWithTTF(str8, "fonts/b.ttf", 23);
	legendaryLabelDes->setPosition(size.width / 2 - 27, size.height - 80);
	legendaryLabelDes->setVisible(false);
	addChild(legendaryLabelDes, 3);
	// 对话框label-number
	char legend[10];
	int tempLegend = UserDefault::getInstance()->getIntegerForKey("legendaryNum");
	sprintf(legend, "%d", tempLegend);
	std::string str_legend = legend;
	legendaryLabelNum = Label::createWithTTF(str_legend, "fonts/HANGTHEDJ.ttf", 26);
	legendaryLabelNum->setPosition(size.width / 2 + 40, size.height - 80);
	legendaryLabelNum->setVisible(false);
	addChild(legendaryLabelNum, 3);



	//item icon_number
	itemChange = Sprite::create("changeIcon.png");
	itemChange->setPosition(size.width / 2 - 100, size.height / 2 - 40);
	itemChange->setVisible(false);
	addChild(itemChange, 5);
	char cNum[10];
	sprintf(cNum, "%d", UserDefault::getInstance()->getIntegerForKey("ChangeNum"));
	std::string str_cNum = cNum;
	changeNum = Label::createWithTTF(str_cNum, "fonts/b.ttf", 40);
	changeNum->setPosition(size.width / 2 - 100, size.height / 2 - 120);
	changeNum->setVisible(false);
	addChild(changeNum, 5);

	// 炸弹icon和label_number
	itemBomb = Sprite::create("bomb.png");
	itemBomb->setPosition(size.width / 2 + 100, size.height / 2 - 40);
	itemBomb->setVisible(false);
	addChild(itemBomb, 5);
	char bNum[10];
	sprintf(bNum, "%d", UserDefault::getInstance()->getIntegerForKey("BombNum"));
	std::string str_bNum = bNum;
	bombNum = Label::createWithTTF(str_bNum, "fonts/b.ttf", 40);
	bombNum->setPosition(size.width / 2 + 100, size.height / 2 - 120);
	bombNum->setVisible(false);
	addChild(bombNum, 5);



	/// //////////////////////////////////////换取道具的对话框
	buyDialog = Sprite::create("changeLayerBg.png");
	buyDialog->setPosition(size.width / 2, -100);
	buyDialog->setScaleY(0.65);
	buyDialog->setScaleX(0.9);
	addChild(buyDialog, 5);

	const char *str9 = ((String*)dic->objectForKey("achieve14"))->_string.c_str();
	isBuy = Label::createWithTTF(str9, "fonts/b.ttf", 28);
	isBuy->setPosition(size.width / 2, -70);
	addChild(isBuy, 6);

	buyYes = Sprite::create("buyYes.png");
	buyYes->setScale(0.6);
	buyYes->setPosition(size.width / 2 - 80, -120);
	addChild(buyYes, 6);

	buyNo = Sprite::create("buyNo.png");
	buyNo->setScale(0.6);
	buyNo->setPosition(size.width / 2 + 70, -120);
	addChild(buyNo, 6);



	///logic///////////////////////////////////////////////////////////////////////////////////////////
	auto vis = CallFunc::create([=]() {
		record->setVisible(true);
		pointerLeft->setVisible(true);
		pointerRight->setVisible(true);
		okLabel->setVisible(true);
		ok->setVisible(true);
		icon1->setVisible(true);
		historyBestScoreLabel->setVisible(true);
		historyBestScoreLabelNum->setVisible(true);
		icon2->setVisible(true);
		singleBest->setVisible(true);
		singleBestNum->setVisible(true);
	});
	ActionInterval * delayVis = DelayTime::create(2.2);
	auto seqVis = Sequence::create(delayVis, vis, NULL);
	if (true/*getDataManager().getAdded() == 1*/)
	{
		this->runAction(seqVis);
	}


	auto vis2 = CallFunc::create([=]() {
		info1->setVisible(true);
		pointerLeft1->setVisible(true);
		pointerRight1->setVisible(true);
		okLabel->setVisible(true);
		ok->setVisible(true);
		icon3->setVisible(true);
		icon4->setVisible(true);
		icon5->setVisible(true);
		icon6->setVisible(true);
		infoLabel1->setVisible(true);
		infoLabel2->setVisible(true);
		infoLabel3->setVisible(true);
		infoLabel4->setVisible(true);
	});
	ActionInterval * delayVis2 = DelayTime::create(2.2);
	auto seqVis2 = Sequence::create(delayVis2, vis2, NULL);
	if (false/*getDataManager().getAdded() == 2*/)
	{
		this->runAction(seqVis2);
	}


	auto vis3 = CallFunc::create([=]() {
		info2->setVisible(true);
		pointerLeft2->setVisible(true);
		pointerRight2->setVisible(true);
		okLabel->setVisible(true);
		ok->setVisible(true);
		des2->setVisible(true);
		itemChange->setVisible(true);
		changeNum->setVisible(true);
		itemBomb->setVisible(true);
		bombNum->setVisible(true);

		legendaryDialog->setVisible(true);
		legendaryLabelDes->setVisible(true);
		legendaryLabelNum->setVisible(true);
	});
	ActionInterval * delayVis3 = DelayTime::create(2.2);
	auto seqVis3 = Sequence::create(delayVis3, vis3, NULL);

	if (false/*getDataManager().getAdded() == 3*/)
	{
		this->runAction(seqVis3);
	}

	// todo


	return true;
}