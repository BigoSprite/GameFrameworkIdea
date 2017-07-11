#ifndef _CONTINUE_LAST_GAME_CONTROLLER_H_
#define _CONTINUE_LAST_GAME_CONTROLLER_H_
#include "cocos2d.h"
#include "BaseController.h"
#include "ContinueLastGameView.h"
USING_NS_CC;

class ContinueLastGameController : public BaseController
{
public:
	ContinueLastGameController();
	~ContinueLastGameController();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ContinueLastGameController);

private:
	ContinueLastGameView* m_pView;

	void __onContinueLastPlayMsgReceived(EventCustom* pEvent);

	void __onStartNewPlayMsgReceived(EventCustom* pEvent);

};

#endif // _CONTINUE_LAST_GAME_CONTROLLER_H_