extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "LuaBridgeTest.h"
#include "LuaBridge.h"
#include "ui/UIWidget.h"
#include "2d/CCSprite.h"

LuaBridgeTest::LuaBridgeTest()
	: _luaState(luaL_newstate())
{
}

LuaBridgeTest::~LuaBridgeTest()
{

}

bool LuaBridgeTest::init()
{
	if (!BaseTest::init())
	{
		return false;
	}

	initScript();

	return true;
}

void LuaBridgeTest::initScript()
{
	luaL_openlibs(_luaState);

	//注册c++类给lua用
	getGlobalNamespace(_luaState)
		.beginNamespace("game")
		.beginClass<Sprite>("Sprite")
		//.addFunction("addChild", &Sprite::addChild)
		.endClass()
		;
}
