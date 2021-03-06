#ifndef _CONTINUE_LAST_GAME_VIEW_H_
#define _CONTINUE_LAST_GAME_VIEW_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class ContinueLastGameView : public ui::Layout
{
public:
	ContinueLastGameView();
	~ContinueLastGameView();
	virtual bool init();
	CREATE_FUNC(ContinueLastGameView);

	//游戏开始
	void gameStart(Ref * r);
	//重新开始游戏
	void gameStartNew(Ref * r);

private:
	Sprite* m_pBackground;
	Sprite* m_pTipBg;
	Label* m_pDescreption1;
	Label* m_pDescreption2;
	MenuItemSprite* m_pLeftMenuItem;
	MenuItemSprite* m_pRightMenuItem;
	Label* m_pLevelNum;
};

#endif // _CONTINUE_LAST_GAME_VIEW_H_
