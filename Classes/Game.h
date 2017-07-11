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
	static Scene* createScene();
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


	//�������е���
	void generatePoint();
	//���װ��(10*10)
	void addEquipment();

	std::vector<int> icon;

private:
	Size visibleSize;
	Vec2 origin;

	//2����������
	Sprite * tower1;
	Sprite * tower2;

	bool isGameReady;
	bool isTargetReached;



	//2�������Ե���
	MenuItemImage * changeIcon;
	MenuItemImage * bombIcon;
	//2�����ߵ������Լ�label
	Label * changeIconLabel;
	Label * bombIconLabel;

	
	Sprite * girl;//ÿһ�ؿ�ʼǰ���ܵ�Ů��
	Sprite * transBg;
	Label * welcome;//��ӭ����
	Label * spots;//�ص�

	//ready go Ʈ��label
	Label * readyLabel;
	Label * goLabel;


	//ÿһ�ص�ǰĿ�����
	int target_score;
	int curLevel;
	Label * targetScore_label;
	Label * level_label;
	Label * levelNum_label;


	bool timerRunning;
	bool gameIsOver;


	Label * knowledge_label;
	Label * name_label;
	Sprite * small_pic;


	MenuItemImage * btm;//�������˵�
	MenuItemImage * res;//���¿�ʼ

    Label * label_score;//��ʾ�����Ŀؼ�
	int currentScore; // ��Ϸ��ǰ����


	//����ͳ��
	int statistic_LeftIcon;
	int statistic_LeftBonus;
	int statistic_SingleMost;
	int statistic_MostIcon;
	int four_kill;
	int five_kill;
	int six_kill;
	int seven_kill;
	int legendary_kill;
	double statistic_Time;


	PointArray *pointArray;//������Ÿ���װ�����������
						   
    //��¼5��icon�ֱ���ȥ�ĸ�����map
	std::map<int, int> icon_map;
};


#endif // _GAME_H_
