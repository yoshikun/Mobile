#include "ClippingNodeTest.h"
#include "2d/CCDrawNode.h"
#include "2d/CCClippingNode.h"
#include "base/CCDirector.h"
#include "2d/CCSprite.h"

ClippingNodeTest::~ClippingNodeTest()
{

}

ClippingNodeTest::ClippingNodeTest()
{

}

bool ClippingNodeTest::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto layer = Layer::create();
	this->addChild(layer);

	auto icon = Sprite::create("HelloWorld.png");

	auto shape = DrawNode::create();
	shape->drawDot(Vec2::ZERO, 50, Color4F(0, 1, 0, 1));

	//shape->clear();
	//int sum = 360;
	//int radius = 50;
	//const float coef = radius * (float)M_PI / sum;
	//CCPoint *vertices = new CCPoint[sum];
	////底部圆
	//for (unsigned int i = 0; i < sum; i++)
	//{
	//	float rads = i*coef;
	//	GLfloat j = radius * cosf(rads);
	//	GLfloat k = radius * sinf(rads);
	//	vertices[i].x = j;
	//	vertices[i].y = k;
	//}
	//shape->drawPolygon(vertices, sum, Color4F::BLACK, 1, Color4F::BLACK);
	//delete[] vertices;
	// 
	//			auto nodef = Node::create();//创建模版  
	//			Sprite* headMask = Sprite::createWithSpriteFrameName("headbg.png");
	//			nodef->addChild(headMask);

	ClippingNode* mask = ClippingNode::create(shape);
	mask->setAlphaThreshold(0.05f);
	//mask->setInverted(true);
	mask->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	mask->setPositionY(mask->getPositionY() + 8);
	mask->addChild(icon);

	layer->addChild(mask);
	return true;
}

