#ifndef _CHANGE_ICON_PREFAB_H_
#define _CHANGE_ICON_PREFAB_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ChangeIconPrefab : public ui::Layout
{
public:
	ChangeIconPrefab();
	~ChangeIconPrefab();
	virtual bool init();
	CREATE_FUNC(ChangeIconPrefab);

	void closeMenuCallback(Ref* pRef);


	static Scene* createScene();
private:
	Size visibleSize;

	Sprite* m_pBackground;
	Label* m_pDesLabel;
	Label* m_pTitle;
	MenuItemImage* m_pCloseItem;
	Menu* m_pCloseMenu;
	Label* m_pCloseLabel;

	Sprite* m_pIcon1;
	Sprite* m_pIcon2;
	Sprite* m_pIcon3;
	Sprite* m_pIcon4;
	Sprite* m_pIcon5;
	Vector<Sprite*> m_pIconList;

	std::vector<int> m_list;

	Sprite* m_pLast;
};

#endif // _CHANGE_ICON_PREFAB_H_