#pragma once

#include "cocos2d.h"
USING_NS_CC;

class BaseController : public Layer
{
public:
	BaseController();
	~BaseController();

	virtual bool init();
	CREATE_FUNC(BaseController);

	virtual void onEnter();
	virtual void onExit();
};