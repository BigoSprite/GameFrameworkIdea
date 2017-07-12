#include "DataManager.h"

DataManager::DataManager()
{
	this->gameLevel = 1;
	this->levelTargetScore = 1000;
	this->currentScore = 0;
	this->scoreIncrement = 1500;
	this->isChangeLayerAdded = false;
	this->isBombLayerAdded = false;
	this->selectedIconValue = -1;
	this->changeIconNum = 10;
	this->bombIconNum = 10;
	this->isEnableEffect = true;
	this->achievedLayer = 0;
}

DataManager::~DataManager()
{}

std::vector<int> DataManager::getIconVec()
{
	return this->iconVec;
}

void DataManager::setIconVec(int value)
{
	iconVec.push_back(value);
}

void DataManager::clearIconVec()
{
	iconVec.clear();
}

DataManager& getDataManager()
{
	static DataManager mgr;
	return mgr;
}