#ifndef __ACTION__TEST__H__
#define __ACTION__TEST__H__

#include "BaseTest.h"
#include "cocos2d.h"

USING_NS_CC;

class ActionTest : public BaseTest
{
public:
	ActionTest();
	~ActionTest();
	
	virtual bool init();

	CREATE_FUNC(ActionTest);
protected:
	
private:
	void callBack2(CCNode* sender, void* data);
};

#endif