#ifndef _BOTTOM_TEXTURE_PREFAB_H_
#define _BOTTOM_TEXTURE_PREFAB_H_

#include "cocos2d.h"
USING_NS_CC;

class BottomTexturePrefab : public Sprite
{
public:
	BottomTexturePrefab();
	~BottomTexturePrefab();
	virtual bool init();
	CREATE_FUNC(BottomTexturePrefab);

	void updateShow(const std::string& enIconName, const int& curBordVal);

private:
	Size visibleSize;
	Sprite* m_pBg;
	Sprite* m_pIcon;
	Label* m_pIconName;
	Label* m_pDescription;

};

#endif // !_BOTTOM_TEXTURE_PREFAB_H_
