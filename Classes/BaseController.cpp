#include "BaseController.h"

BaseController::BaseController()
{}

BaseController::~BaseController()
{}

bool BaseController::init()
{
	bool ret = false;

	if (Layer::init())
		ret = true;

	return ret;
}