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

	// ��ǰ�ؿ�
	int m_iCurrentLevel;

	// ��ӭ�Ի��������ϣ���Ϻ���Ϸ���뿪ʼ״̬
	bool m_isCompleted;

	// ����������
	Sprite* m_pServerBg;
	// ��������icon
	Sprite* m_pServerIcon;
	// ���������� 
	Label* m_pServerName;

	// ׼���Ϳ�ʼ
	Label* m_pReadyLabel;
	Label* m_pStartLabel;
};

#endif // !_WELCOME_DIALOG_PREFAB_H_
