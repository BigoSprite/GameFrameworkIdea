#ifndef _ITEM_NOT_ENOUGH_H_
#define _ITEM_NOT_ENOUGH_H_

#include "cocos2d.h"
USING_NS_CC;

class ItemNotEnoughPrefab : public Sprite
{
public:
	ItemNotEnoughPrefab();
	~ItemNotEnoughPrefab();
	virtual bool init();
	CREATE_FUNC(ItemNotEnoughPrefab);

private:
	Sprite* m_pBackground;
	Sprite* m_pYellowIcon;
	Label* m_pNotEnoughDes;
	Menu* m_pMenu;
	Label* m_pButtonLabel;

	void __onOkButtonClickedCallback(Ref* pRef);

};

#endif // _ITEM_NOT_ENOUGH_H_