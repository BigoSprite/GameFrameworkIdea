#ifndef _CHANGEICONLAYER_H_
#define _CHANGEICONLAYER_H_
#include "cocos2d.h"
#include "HelloWorldScene.h"
class changeIconLayer :public cocos2d::Layer
{
public:
	changeIconLayer();
	~changeIconLayer();
	virtual bool init();
	CREATE_FUNC(changeIconLayer);
	static Scene* createScene();
	void closeMenuCallback(cocos2d::Ref * r);
	//std::vector<int> getIconVector();
private:
	cocos2d::Sprite * bg;
	cocos2d::Label * descriptionLabel;
	cocos2d::Label * titleLabel;
	cocos2d::MenuItemImage * close;
	cocos2d::Menu * closeMenu;
	cocos2d::Label * closeLabel;

	cocos2d::Sprite *icon1;
	cocos2d::Sprite *icon2;
	cocos2d::Sprite *icon3;
	cocos2d::Sprite *icon4;
	cocos2d::Sprite *icon5;

	std::vector<int> vec;
	cocos2d::Vector<cocos2d::Sprite*> iconVec;//���5��icon ��vector�����ڵ���������ĸ�icon�������
	cocos2d::Sprite * last;





};
#endif

