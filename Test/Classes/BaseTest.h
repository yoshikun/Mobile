#ifndef __TEST__H__
#define __TEST__H__

#include "2d/CCLayer.h"

USING_NS_CC;

class BaseTest : public Layer
{
public:
	BaseTest();
	~BaseTest();

	virtual bool init();

	CREATE_FUNC(BaseTest);
};

#endif