#ifndef _FINAL_SCENE_VIEW_H_
#define _FINAL_SCENE_VIEW_H_

#include "cocos2d.h"
USING_NS_CC;

class FinalSceneView : public Sprite
{
public:
	FinalSceneView();
	~FinalSceneView();
	virtual bool init();
	CREATE_FUNC(FinalSceneView);

	virtual void onEnter();
	virtual void onExit();

private:
	Sprite * m_pBg;
	Sprite * m_pDialog;
	Sprite * m_pOk;
	Label  * m_pOkLabel;
	Sprite * m_pClear;
	Sprite * m_pTitle;
	Sprite * m_pGirl1;
	Sprite * m_pGirl2;
	Label  * m_pWeb;
	Label  * m_pWeb2;

};

#endif //_FINAL_SCENE_VIEW_H_