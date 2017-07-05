#ifndef _GAME_PAUSE_LAYER_H_
#define _GAME_PAUSE_LAYER_H_
#include "cocos2d.h"
USING_NS_CC;

class GamePauseLayer : public Layer
{
public:
	GamePauseLayer();
	~GamePauseLayer();

	virtual bool init();
	static Scene* createScene();

	void onEnter();
	void onExit();

	void resumeGame(Ref* ref);
	void goBackToMenu(Ref* ref);
	void bgmOnOff(Ref* ref);
	void effectOnOff(Ref* ref);

	CREATE_FUNC(GamePauseLayer)
private:

	Sprite* bg;
	Sprite* dialog;
	Label* pauseLabel;
	Sprite* pointer1;
	Sprite* pointer2;
	MenuItemImage* resume;
	MenuItemImage* mainMenu;
	Label* label1;
	Label* label2;

	MenuItemSprite* bgm_on;
	Sprite* bgmSprite;

	MenuItemSprite* effect_on;
	Sprite* effectSprite;
};

#endif // _GAME_PAUSE_LAYER_H_
