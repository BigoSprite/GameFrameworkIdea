#ifndef _FIAL_DIALOG_PREFAB_H_
#define _FIAL_DIALOG_PREFAB_H_

#include "cocos2d.h"
USING_NS_CC;

class FailDialogPrefab : public Layer
{
public:
	FailDialogPrefab();
	~FailDialogPrefab();
	virtual bool init();
	CREATE_FUNC(FailDialogPrefab);
	static Scene* createScene();


private:
	Sprite* m_pBg;
	Sprite* m_pDialogBg;
	Menu* m_pMenu;


	void __restartGameCallback(Ref* r);
	void __quitGameCallback(Ref* r);
};

#endif // !_FIAL_DIALOG_PREFAB_H_
