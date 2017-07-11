#ifndef _WORLDMAPSCENE_H_
#define _WORLDMAPSCENE_H_
#include "cocos2d.h"
#include "vector"
#include "GirlTwo.h"
using namespace std;
USING_NS_CC;
class WorldMapScene : public Layer
{
public:
	WorldMapScene();
	~WorldMapScene();
	virtual bool init();
	CREATE_FUNC(WorldMapScene);
	static Scene * createScene();

	void backToMenu(Ref * r);

	void traceMove();

	void previousLocation(Ref  * r);
	void nextLocation(Ref  * r);
private:
	Sprite * bg;
	Sprite * menuBg;
	MenuItemImage * back;
	MenuItemImage * restart;

	int curLevelNum;

	vector<Point> pos_vec; //�洢20�����еĵ���λ��

	GirlTwo * gt;

	Sprite * dialog;

	MenuItemImage * previous;
	MenuItemImage * next;

	int loc;
	vector<Sprite*> loc_vec;

	Label * locLabel;
};

#endif
