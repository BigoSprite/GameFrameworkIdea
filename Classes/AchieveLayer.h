#ifndef _ACHIEVE_LAYER_H_
#define _ACHIEVE_LAYER_H_
#include "cocos2d.h"
USING_NS_CC;

class AchieveLayer : public Layer
{
public:
	AchieveLayer();
	~AchieveLayer();

	virtual bool init();
	CREATE_FUNC(AchieveLayer);

	//static Scene* createScene();

private:
	Sprite* dialog;
	Sprite* pointerLeft;
	Sprite* pointerRight;
	Label* record;
	Sprite* ok;
	Label* okLabel;
	Sprite* icon1;
	Label* historyBestScoreLabel;
	Label* historyBestScoreLabelNum;

	Sprite* icon2;
	Label* singleBest;
	Label* singleBestNum;

	// 游戏消息的label
	Sprite* pointerLeft1;
	Sprite* pointerRight1;
	Label* info1;
	Sprite* icon3;
	Label* infoLabel1;
	Sprite* icon4;
	Label* infoLabel2;
	Sprite * icon5;
	Label* infoLabel3;
	Sprite* icon6;
	Label* infoLabel4;

	//道具兑换信息
	cocos2d::Sprite * pointerLeft2;
	cocos2d::Sprite * pointerRight2;
	cocos2d::Label  * info2;
	cocos2d::Label  * des2;
	cocos2d::Sprite * legendaryDialog;
	cocos2d::Label  * legendaryLabelDes;
	cocos2d::Label  * legendaryLabelNum;
	cocos2d::Sprite * itemChange;
	cocos2d::Sprite * itemBomb;
	cocos2d::Label  * changeNum;
	cocos2d::Label  * bombNum;
	//换取道具时的对话框
	cocos2d::Sprite * buyDialog;
	cocos2d::Label  * isBuy;
	cocos2d::Sprite * buyYes;
	cocos2d::Sprite * buyNo;
	//cocos2d::Sprite * warning;

	int changeOrBomb;
	//防止重复点击换取道具的变量
	bool isClickedChange;
	bool isClickedBomb;

};

#endif // _ACHIEVE_LAYER_H_
