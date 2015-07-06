#ifndef __LUA__BRIDGE__TEST__H__
#define __LUA__BRIDGE__TEST__H__

#include "lua.h"
#include "BaseTest.h"
#include "LuaBridge/RefCountedPtr.h"
#include "base/CCScriptSupport.h"

using namespace luabridge;
USING_NS_CC;

class CCNode;

class LuaBridgeTest : public BaseTest
{
public:
	LuaBridgeTest();
	~LuaBridgeTest();

	virtual bool init();

	CREATE_FUNC(LuaBridgeTest);
	void initScript();
protected:

private:
	lua_State* _luaState;
};

#endif