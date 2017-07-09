#ifndef _ACHIEVEMENT_CONTROLLER_H_
#define _ACHIEVEMENT_CONTROLLER_H_

#include "cocos2d.h"
#include "BaseController.h"
#include "AchievementView.h"

USING_NS_CC;

class AchievementController : public BaseController
{
public:
	AchievementController();
	~AchievementController();
	virtual bool init();
	CREATE_FUNC(AchievementController);

private:
	AchievementView* m_pView;

	void __onTrophyIconTouched(EventCustom* pEvent);
	void __onInfoIconTouched(EventCustom* pEvent);
	void __onItemIconTouched(EventCustom* pEvent);
};

#endif // _ACHIEVEMENT_CONTROLLER_H_