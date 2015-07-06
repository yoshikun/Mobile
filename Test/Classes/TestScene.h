#ifndef __TEST__SCENE__H__
#define __TEST__SCENE__H__

#include "CCPlatformMacros.h"
#include "2d/CCScene.h"
#include "base/CCRef.h"
#include "BaseTest.h"
#include "2d/CCMenu.h"

USING_NS_CC;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual bool init();

	CREATE_FUNC(TestScene);
protected:
	
private:
	Menu* _menu;
	BaseTest* _currentTest;
	const int V_PADDING;
	std::map<std::string, std::function<BaseTest*()>> _menuFunctionMap;

	void MenuItemCallBack(Ref* sender);
	
};

#endif
