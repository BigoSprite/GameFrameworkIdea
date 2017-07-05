#include "GirlTwo.h"
USING_NS_CC;

GirlTwo::GirlTwo()
{
}


GirlTwo::~GirlTwo()
{
}

bool GirlTwo::init()
{
	Sprite::init();

	//initWithSpriteFrameName("22-w1.png");

	initWithFile("22-w1.png");
	girlAction();

	return true;
}

void GirlTwo::girlAction()
{
	//�������2�Ŷ�������
	Vector<SpriteFrame*> actionList;

	SpriteFrame * frame_1 = SpriteFrame::create("22-w1.png", Rect(0, 0, 150, 150));
	SpriteFrame * frame_2 = SpriteFrame::create("22-w2.png", Rect(0, 0, 150, 150));
	SpriteFrame * frame_3 = SpriteFrame::create("22-w3.png", Rect(0, 0, 150, 150));
	SpriteFrame * frame_4 = SpriteFrame::create("22-w4.png", Rect(0, 0, 150, 150));


	actionList.pushBack(frame_1);
	actionList.pushBack(frame_2);
	actionList.pushBack(frame_3);
	actionList.pushBack(frame_4);

	Animation * mAnimation = Animation::createWithSpriteFrames(actionList, 0.3f);//����֡����
	Animate *mAnimate = Animate::create(mAnimation);//��������
	RepeatForever* loop = RepeatForever::create(mAnimate);

	runAction(loop);
}
