#ifndef _TOP_BAR_PREFAB_H_
#define _TOP_BAR_PREFAB_H_

#include "cocos2d.h"
#include "ItemNotEnoughPrefab.h"
USING_NS_CC;

class TopBarPrefab : public Sprite
{
public:
	TopBarPrefab();
	~TopBarPrefab();
	virtual bool init();
	CREATE_FUNC(TopBarPrefab);

private:
	Size visibleSize;

	Sprite* m_pTopBarBg;
	Label* m_pCurrentScore;
	MenuItemSprite* m_pPause;
	MenuItemSprite* m_pBack2WelcomeScene;
	MenuItemSprite* m_pSkill_1;
	Label* m_pSkill1Num;
	MenuItemSprite* m_pSkill_2;
	Label* m_pSkill2Num;

	/// 道具不足时的提示框
	ItemNotEnoughPrefab* m_pItemNotEnoughSprite;

private:
	void __pauseCallback(Ref* pRef);
	void __back2WelcomeSceneCallback(Ref* pRef);
	void __changeIconTypeCallback(Ref* pRef);
	void __bombIconTypeCallback(Ref* pRef);

};

#endif // !_TOP_BAR_PREFAB_H_
