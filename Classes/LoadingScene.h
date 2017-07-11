#ifndef _LOAGING_SCENE_H_
#define _LOAGING_SCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Layer
{
public:
	LoadingScene();
	~LoadingScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);

private:
	Sprite* m_pBackground;
	Sprite* m_pGirl1;
	Sprite* m_pGirl2;
	Label* m_pLogo;

	void __initLogo();
	void __loadAudioResources();
	void __loadPlistResources();
};




#endif // _LOAGING_SCENE_H_
