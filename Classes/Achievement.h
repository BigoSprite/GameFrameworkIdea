#ifndef _ACHIEVEMENT_H_
#define _ACHIEVEMENT_H_
#include "cocos2d.h"
USING_NS_CC;

class Achievement : public Layer
{
public:
	Achievement();
	~Achievement();
	virtual bool init();
	CREATE_FUNC(Achievement);

	static Scene* createScene();
	void goBackToMainmenu(cocos2d::Ref * r);

	virtual void onEnter();
	virtual void onExit();

private:
	Size visiableSize;
	Sprite* m_pBg;
	Sprite* m_pMenu;
	Sprite* m_pTrophy;
	Sprite* m_pInfo;
	Sprite* m_pItem;
	Vector<Sprite*> m_pIconBtnList;
	MenuItemImage* m_pBackBtn;
	Sprite* m_pTransparentBg;
	Sprite* m_pGirl;
	Label* m_pDescription;


	bool m_isLayerAdded;

	
};

#endif // _ACHIEVEMENT_H_
