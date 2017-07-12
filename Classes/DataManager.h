#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DataManager
{
public:
	DataManager();
	~DataManager();

	CC_SYNTHESIZE(int, currentScore, CurrentScore);
	CC_SYNTHESIZE(int, levelTargetScore, LevelTargetScore);
	CC_SYNTHESIZE(int, gameLevel, GameLevel);
	CC_SYNTHESIZE(int, scoreIncrement, ScoreIncrement);
	CC_SYNTHESIZE(bool, isChangeLayerAdded, IsChangeLayerAdded);
	CC_SYNTHESIZE(bool, isBombLayerAdded, IsBombLayerAdded);
	CC_SYNTHESIZE(int, selectedIconValue, SelectedIconValue);
	CC_SYNTHESIZE(int, changeIconNum, ChangeIconNum);
	CC_SYNTHESIZE(int, bombIconNum, BombIconNum);
	CC_SYNTHESIZE(bool, isEnableEffect, IsEnableEffect);
	CC_SYNTHESIZE(int, achievedLayer, AchievedLayer);
	CC_SYNTHESIZE(int, initCurrentScore, InitCurrentScore);

	//cocos2d::Sprite* getCityAccoringToLevel(int level);


	std::vector<int> getIconVec();
	void setIconVec(int value);
	void clearIconVec();

private:
	std::vector<int> iconVec;

};

DataManager& getDataManager();
