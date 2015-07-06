#ifndef __EVENT__TEST__H__
#define __EVENT__TEST__H__

#include "BaseTest.h"
#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "base/CCRef.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;

class EventTest : public BaseTest
{
public:
	EventTest();
	~EventTest();

	virtual bool init();

	CREATE_FUNC(EventTest);
private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

class IPoker : public Widget
{
public:
	IPoker();
	~IPoker();

	virtual bool init();
	virtual void setTouched(bool value);
	virtual bool getTouched();

	CREATE_FUNC(IPoker);
protected:
	bool _touched;

private:
	
};

class Poker : public IPoker
{
public:
	Poker();
	~Poker();
	
	virtual bool init();
	virtual void onPressStateChangedToDisabled() override;

	void setTouched(bool value);

	CREATE_FUNC(Poker);
protected:
	
private:
	Sprite* _icon;	
};
#endif