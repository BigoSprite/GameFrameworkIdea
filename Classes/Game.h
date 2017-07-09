#ifndef _GAME_H_
#define _GAME_H_

#include "cocos2d.h"
#include "BaseController.h"

USING_NS_CC;
 
class Game : public BaseController
{
public:
	Game();
	~Game();
	virtual bool init();
	CREATE_FUNC(Game);


	//warning回调函数
	void warningCallback(cocos2d::Ref *r);

	//道具函数： 改变种类
	void changeIconType(Ref * r);
	//道具函数： 爆炸icon
	void bombIconType(Ref * r);

	//回到主菜单
	void returnToMenu(cocos2d::Ref* r);
	//重新开始
	void restartGame(cocos2d::Ref* r);
	//去下一关函数
	void goToNextLevel(Ref * r);

private:
	Size visibleSize;
	Vec2 origin;
};


#endif // _GAME_H_
