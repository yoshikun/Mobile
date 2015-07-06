#include "TestScene.h"
<<<<<<< HEAD

TestScene::TestScene()
=======
#include "2d/CCMenuItem.h"
#include "2d/CCLabel.h"
#include "2d/CCMenu.h"
#include "base/CCDirector.h"
#include "ClippingNodeTest.h"
#include "CompressPngTest.h"
#include "base/CCEventListenerTouch.h"
#include "ActionTest.h"
#include "VisibleRect.h"
#include "EventTest.h"
#include "LuaBridgeTest.h"

TestScene::~TestScene()
>>>>>>> 70ab6f4eefabce28cebb6d176be76eaff1e352db
{

}

<<<<<<< HEAD
TestScene::~TestScene()
{

}

=======
TestScene::TestScene()
	: V_PADDING(40)
	, _currentTest(nullptr)
{
	//初始化菜单项
	_menuFunctionMap["PngCompressTest"] = []() {return CompressPngTest::create();};
	_menuFunctionMap["ClippinNodeTest"] = []() {return ClippingNodeTest::create();};
	_menuFunctionMap["ActionTest"] = []() {return ActionTest::create();};
	_menuFunctionMap["EventTest"] = []() {return EventTest::create();};
	_menuFunctionMap["LuaBridgeTest"] = []() {return LuaBridgeTest::create();};
}

bool TestScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto layer = Layer::create();
	this->addChild(layer);

	//创建菜单
	_menu = Menu::create();
	_menu->setPosition(VisibleRect::center());
	layer->addChild(_menu);

	auto nameIter = _menuFunctionMap.begin();
	for (nameIter; nameIter != _menuFunctionMap.end(); nameIter++)
	{
		std::string name = nameIter->first;	
		auto label = Label::create(name, "", 24);
		auto item = MenuItemLabel::create(label, CC_CALLBACK_1(TestScene::MenuItemCallBack, this));
		
		_menu->addChild(item);
	}
	//设置布局
	_menu->alignItemsVerticallyWithPadding(V_PADDING);

	//添加鼠标事件
	auto listener = this->getEventDispatcher();
	auto event = EventListenerTouchAllAtOnce::create();

	return true;
}

void TestScene::MenuItemCallBack(Ref* sender)
{
	//点击开始某一项测试
	auto item = static_cast<MenuItemLabel*>(sender);
	auto label = static_cast<Label*>(item->getLabel());

	//执行方法
	auto func = _menuFunctionMap[label->getString()];
	_currentTest = func();

	this->addChild(_currentTest);

	_menu->setVisible(false);
}
>>>>>>> 70ab6f4eefabce28cebb6d176be76eaff1e352db
