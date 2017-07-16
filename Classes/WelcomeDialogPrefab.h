#ifndef _WELCOME_DIALOG_PREFAB_H_
#define _WELCOME_DIALOG_PREFAB_H_

#include "cocos2d.h"
USING_NS_CC;

class WelcomeDialogPrefab : public Sprite
{
public:
	WelcomeDialogPrefab();
	~WelcomeDialogPrefab();
	bool initWithLevel(const int& level);
	static WelcomeDialogPrefab* createWithLevel(const int& level);

	bool getIsGameCanStart();

private:
	Size visibleSize;

	// 当前关卡
	int m_iCurrentLevel;

	// 欢迎对话框加载完毕，完毕后游戏进入开始状态
	bool m_isCompleted;

	// 服务器背景
	Sprite* m_pServerBg;
	// 服务器的icon
	Sprite* m_pServerIcon;
	// 服务器名字 
	Label* m_pServerName;

	// 准备和开始
	Label* m_pReadyLabel;
	Label* m_pStartLabel;
};

#endif // !_WELCOME_DIALOG_PREFAB_H_
