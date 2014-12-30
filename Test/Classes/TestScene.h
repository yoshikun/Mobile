#ifndef __TEST__SCENE__H__
#define __TEST__SCENE__H__

#include "CCPlatformMacros.h"
#include "2d/CCScene.h"
#include "base/CCRef.h"
#include "Test.h"
#include "2d/CCMenu.h"

USING_NS_CC;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual bool init();

protected:
	
private:
	Menu* _menu;
	Test* _currentTest;
	const int V_PADDING;
	std::map<std::string, std::function<Test*()>> _menuFunctionMap;

	void MenuItemCallBack(Ref* sender);
	
};

#endif
