#ifndef _BOMB_ICON_VIEW_H_
#define _BOMB_ICON_VIEW_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class BombIconView : public ui::Layout
{
public:
	BombIconView();
	~BombIconView();
	virtual bool init();
	CREATE_FUNC(BombIconView);

	void closeMenuCallback(Ref * ref);

private:
	Size visibleSize;
	Sprite* m_pBackground;
	Label* m_pDescription;
	MenuItemImage* m_pCloseItem;
	Menu* m_pClostMenu;
	Label* m_pCloseLabel;
	Sprite* m_pTurrent;
	Sprite* m_pMissle;
};

#endif //_BOMB_ICON_VIEW_H_