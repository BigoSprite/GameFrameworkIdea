#ifndef _FAIL_LAYER_H_
#define _FAIL_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class FailLayer : public Layer
{
public:
	FailLayer();
	~FailLayer();
	virtual bool init();
	CREATE_FUNC(FailLayer);

	static Scene* createScene();

	void yesButton(Ref* r);
	void noButton(Ref* r);

private:
	Sprite* bg;
	Sprite* fail;
	Sprite* transBg;
	Label* title;
	MenuItemImage *left, *right;
	Label *leftLabel, *rightLabel;
};


#endif // _FAIL_LAYER_H_