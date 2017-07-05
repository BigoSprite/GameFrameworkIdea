#pragma once
#include "cocos2d.h"
#include "BaseController.h"
USING_NS_CC;

class GuideController : public BaseController
{
public:
	GuideController();
	~GuideController();

	virtual bool init();
	CREATE_FUNC(GuideController);

	static Scene* createScene();

	//NEXT���ܻص�����
	void nextIntro(cocos2d::Ref * r);
	//���º�����girl�ƶ�����
	void girlMove(std::string str, float girlPosY, cocos2d::Point destination);

	//���������ƶ�����
	void move(float dt);
	//��ʼ��Ϸ��ɾ��layer
	void deleteLayer();
private:

	float vy_girl; //����y���ٶ�
	float girlPosY;//���õ�yλ�ã���Ϊmove�������ܴ��ݽ�pos����
	Sprite * girl;
	//����ÿһ���ı���
	int progress;

	cocos2d::Label * function;//label˵������
	cocos2d::MenuItemSprite * next;//��һ�����
	cocos2d::Menu * menuNext;
};

