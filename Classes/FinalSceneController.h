#ifndef _FINAL_SCENE_CONTROLLER_H_
#define _FINAL_SCENE_CONTROLLER_H_

#include "cocos2d.h"
#include "BaseController.h"
#include "FinalSceneView.h"

USING_NS_CC;

class FinalSceneController : public BaseController
{
public:
	FinalSceneController();
	~FinalSceneController();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(FinalSceneController);

private:
	FinalSceneView* m_pView;

	void __onBack2WelcomeSceneMsgReceived(EventCustom* pEvent);
};

#endif // !_FINAL_SCENE_CONTROLLER_H_
