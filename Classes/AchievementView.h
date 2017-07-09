#ifndef _ACHIEVEMENT_VIEW_H_
#define _ACHIEVEMENT_VIEW_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class AchievementView : public ui::Layout
{
public:
	AchievementView();
	~AchievementView();
	virtual bool init();
	CREATE_FUNC(AchievementView);

	virtual void onEnter();
	virtual void onExit();

private:
	Size visiableSize;

	Sprite* m_pDesBg;
	Sprite* m_pGirl;
	Label* m_pDescription;

	Sprite* m_pMenuBackground;
	Sprite* m_pTrophy;
	Sprite* m_pInfo;
	Sprite* m_pItem;
	Vector<Sprite*> m_pIconBtnList;

	MenuItemImage* m_pBackBtn;
private:
	void _initDes();
	void _initMenu();

	void _goBackToMainmenu(Ref * ref);
};

#endif // _ACHIEVEMENT_VIEW_H_
