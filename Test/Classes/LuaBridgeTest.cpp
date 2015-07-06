#include "LuaBridgeTest.h"
#include "LuaBridge/detail/Namespace.h"

#include "LuaBridge/LuaBridge.h"
#include "lualib.h"
#include "lauxlib.h"

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

}

void LuaBridgeTest::initScript()
{
	luaL_openlibs(_luaState);
	//getGlobalNamespace(_luaState);
}
