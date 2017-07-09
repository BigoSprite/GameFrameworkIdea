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


	//warning�ص�����
	void warningCallback(cocos2d::Ref *r);

	//���ߺ����� �ı�����
	void changeIconType(Ref * r);
	//���ߺ����� ��ըicon
	void bombIconType(Ref * r);

	//�ص����˵�
	void returnToMenu(cocos2d::Ref* r);
	//���¿�ʼ
	void restartGame(cocos2d::Ref* r);
	//ȥ��һ�غ���
	void goToNextLevel(Ref * r);

private:
	Size visibleSize;
	Vec2 origin;
};


#endif // _GAME_H_
