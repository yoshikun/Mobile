#include "EventTest.h"
#include "base/ccMacros.h"

EventTest::EventTest()
{

}

EventTest::~EventTest()
{

}

bool EventTest::init()
{
	BaseTest::init();
	
	int len = 5;
	for (int i = 0; i < len; i++)
	{
		auto poker = Poker::create();
		poker->setName(std::to_string(i));
		poker->setPosition(Vec2(200 + i * 30, 200));
		poker->setSwallowTouches(false);
		this->addChild(poker);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(EventTest::onTouchBegan, this);
	//listener->onTouchEnded = CC_CALLBACK_2(EventTest::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(EventTest::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void EventTest::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 pos = touch->getLocation();
	
	int len = this->getChildrenCount();
	for (int i = 0; i < len; i++)
	{
		auto poker = dynamic_cast<IPoker*>(this->getChildren().at(i));
		if (poker)
		{
			Rect rect = poker->getBoundingBox();
			if (rect.containsPoint(pos))
			{
				if (!poker->getTouched())
				{
					poker->setTouched(true);
				}
			}
		}
	}
}

bool EventTest::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

IPoker::IPoker()
	: _touched(false)
{

}

IPoker::~IPoker()
{

}

void IPoker::setTouched(bool value)
{
	_touched = value;
}

bool IPoker::getTouched()
{
	return _touched;
}

bool IPoker::init()
{
	Widget::init();

	return true;
}

Poker::Poker()
{

}

Poker::~Poker()
{

}

bool Poker::init()
{
	IPoker::init();

	_icon = Sprite::create("2071.png");
	_icon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(_icon);

	this->setContentSize(_icon->getContentSize());

	this->setBright(false);

	return true;
}

void Poker::setTouched(bool value)
{
	IPoker::setTouched(value);

	if (value)
	{
		_icon->stopAllActions();

		auto action = MoveTo::create(5, Vec2(0, 50));
		_icon->runAction(action);
	}
	else
	{
		_icon->setPosition(Vec2::ZERO);
	}
}

void Poker::onPressStateChangedToDisabled()
{
	auto program = GLProgram::createWithFilenames("shaders/sprite.vs", "shaders/sprite_gray.fs");
	GLProgramCache::getInstance()->addGLProgram(program, "sprite_gray");
	_icon->setGLProgram(program);
}
