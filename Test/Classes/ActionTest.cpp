#include "ActionTest.h"
#include "2d/CCSprite.h"
#include "VisibleRect.h"
#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "deprecated/CCDeprecated.h"

ActionTest::~ActionTest()
{

}

ActionTest::ActionTest()
{

}

bool ActionTest::init()
{
	if (!BaseTest::init())
	{
		return false;
	}

	auto sprite = Sprite::create("ActionTest.png");
	sprite->setPosition(VisibleRect::center());
	this->addChild(sprite);

	//一般来说by的相对动作都支持reverse

	//MoveTo 移动到某点
	//参数 时间,位置
	auto moveToAction = MoveTo::create(1, VisibleRect::bottom());
	//sprite->runAction(moveToAction);

	//CCMoveBy 移动相对位置
	//参数 时间,向量
	auto mvoeByAction = CCMoveBy::create(1, Vec2(0, 100));
	//sprite->runAction(mvoeByAction);

	//ScaleTo 缩放
	//参数 时间,缩放比例
	auto scaleToAction = ScaleTo::create(1, 2);
	//sprite->runAction(scaleToAction);

	//ScaleBy 缩放相对大小
	//参数 时间,缩放比例
	//sprite->setScale(0.5);
	//auto scaleByAction = ScaleBy::create(1, 2);
	//sprite->runAction(scaleByAction);

	//RotateTo 旋转
	//参数 时间,角度(-360到360)
	auto rotateToAction = RotateTo::create(1, -90);
	//sprite->runAction(rotateToAction);

	//CCSkewTo 倾斜
	//参数 时间,x轴角度,y轴角度
	auto skewToAction = CCSkewTo::create(5, 180, 180);
	//sprite->runAction(skewToAction);

	//CCJumpTo 跳跃
	//参数 时间,目标位置,跳跃高度,跳跃次数
	auto jumpToAction = CCJumpTo::create(5, VisibleRect::right(), 100, 5);
	//sprite->runAction(jumpToAction);

	//CCBezierTo 曲线运动
	//参数 时间,ccBezierConfig
	ccBezierConfig config;
	config.controlPoint_1 = Vec2(0, 0);
	config.controlPoint_2 = Vec2(200, 200);
	config.endPosition = Vec2(300, 0);

	auto bezierByAction = CCBezierBy::create(5, config);
	//sprite->runAction(bezierByAction);

	//CCFadeIn 渐变出现
	//参数 时间
	//sprite->setOpacity(0);
	auto fadeInAction = CCFadeIn::create(2);
	//sprite->runAction(fadeInAction);

	//CCFadeOut 渐变消失
	//参数 时间
	auto fadeOutAction = CCFadeOut::create(2);
	//sprite->runAction(fadeOutAction);

	//CCTintTo 色彩变换
	//参数 时间,r,g,b
	auto tintToAction = CCTintTo::create(2, 255, 255, 0);
	//sprite->runAction(tintToAction);

	//CCBlink 闪烁
	//参数 时间,次数
	auto blinkAction = CCBlink::create(2, 5);
	//sprite->runAction(blinkAction);

	//CCDelayTime 延迟动作
	//参数 延迟时间(秒)
	auto delayAction = CCDelayTime::create(1);
	//sprite->runAction(delayAction);

	//CCOrbitCamera 旋转(例如用两个旋转模拟翻牌)
	//参数 时间,起始半径,变化半径,起始z角度,变化z角度,起始x角度,变化x角度
	auto orbitCameraAction = CCOrbitCamera::create(5, 0, 0, 0, 180, 0, 0);
	//sprite->runAction(orbitCameraAction);

	//CCCardinalSpineTo 运动轨迹(曲线)
	//参数 时间,数组,柔和度(0最柔和)
	auto array = CCPointArray::create(5);
	array->addControlPoint(Vec2(0, 0));
	array->addControlPoint(Vec2(0, 100));
	array->addControlPoint(Vec2(100, 200));
	array->addControlPoint(Vec2(300, 0));
	array->addControlPoint(Vec2(300, -200));
	auto cardinalSpineAction = CCCardinalSplineBy::create(5, array, 0);
	//sprite->runAction(cardinalSpineAction);

	//CCCatmullRomTo 插值轨迹(直线)
	//参数 时间,轨迹数组
	auto catmullRomBy = CCCatmullRomBy::create(5, array);
	//sprite->runAction(catmullRomBy);

	//CCFollow 镜头跟随
	//参数 参照物,跟随范围(默认无限跟随)
	auto master = Sprite::create("CloseNormal.png");
	master->setPosition(VisibleRect::center() + Vec2(200, 0));
	//this->addChild(master);

	master->runAction(CCMoveBy::create(2, Vec2(200, 0)));
	//this->runAction(CCFollow::create(master));

	//动作修饰

	//EaseBounceIn 
	auto move = CCMoveBy::create(2, Vec2(200, 0));
	auto easeBounceInAction = EaseBounceIn::create(move);
	//sprite->runAction(easeBounceInAction);

	//EaseBounceOut
	auto easeBounceOutAction = EaseBounceOut::create(move);
	//sprite->runAction(easeBounceOutAction);

	//EaseBounceInOut
	auto easeBounceInOutAction = EaseBounceInOut::create(move);
	//sprite->runAction(easeBounceInOutAction);

	//EaseBackIn
	auto easeBackInAction = EaseBackIn::create(move);
	//sprite->runAction(easeBackInAction);

	//EaseBackOut
	auto easeBackOutAction = EaseBackOut::create(move);
	//sprite->runAction(easeBackOutAction);

	//EaseBackInOut
	auto easeBackInOutAction = EaseBackInOut::create(move);
	//sprite->runAction(easeBackInOutAction);

	//EaseElasticIn
	auto easeElasticInAction = EaseElasticIn::create(move);
	//sprite->runAction(easeElasticInAction);

	//EaseElasticOut
	auto easeElasticOutAction = EaseElasticOut::create(move);
	//sprite->runAction(easeElasticOutAction);
	
	//EaseElasticInOut
	auto easeElasticInOutAction = EaseElasticInOut::create(move);
	//sprite->runAction(easeElasticInOutAction);
	
	//EaseExponentialIn
	auto easeExponentialInAction = EaseExponentialIn::create(move);
	//sprite->runAction(easeExponentialInAction);

	//EaseExponentialOut
	auto easeExpontialOutAction = EaseExponentialOut::create(move);
	//sprite->runAction(easeExpontialOutAction);

	//EaseExpontialInOut
	auto easeExpontialInOutAction = EaseExponentialInOut::create(move);
	//sprite->runAction(easeExpontialInOutAction);

	//EaseSineIn 动作由慢变快
	auto easeSineInAction = EaseSineIn::create(move);
	//sprite->runAction(easeSineInAction);

	//EaseSineOut 动作由快变慢
	auto easeSineOutAction = EaseSineOut::create(move);
	//sprite->runAction(easeSineOutAction);

	//EaseSineInOut 动作由慢到快再快到慢
	auto easeSineInOutAction = EaseSineInOut::create(move);
	//sprite->runAction(easeSineInOutAction);

	//Speed 动作速度倍数
	auto speedAction = Speed::create(move, 10);
	//sprite->runAction(speedAction);

	//Spawn 多个动作同时执行
	auto scale = ScaleTo::create(2, 2);
	auto rotate = RotateTo::create(5, 90);
	auto spawnAction = Spawn::create(move, scale, rotate, nullptr);
	//sprite->runAction(spawnAction);
	
	//Sequence 多个动作顺序执行(如果需要reverse,那么所有动作都应该支持reverse,不然会出现异常)
	auto sequenceAction = Sequence::create(move, scale, rotate, nullptr);
	//sprite->runAction(sequenceAction);

	//Repeat 重复动作
	//参数 动作,次数
	auto repeatAction = Repeat::create(move, 5);
	//sprite->runAction(repeatAction);

	//RepeatForever 永远重复动作
	auto repeatForeverAction = RepeatForever::create(move);
	//sprite->runAction(repeatForeverAction);

	//CCCallFunc 不带参数的回调
	auto callBack0 = [](){log("This is callback0.");};
	auto func0 = CCCallFunc::create(callBack0);
	
	//CCCallFuncN 带一个参数的回调
	auto callBack1 = [](Ref* sender){log("This is callBack1");};
	auto func1 = CCCallFuncN::create(callBack1);
	
	//CCCallFuncD 带两个参数的回调
	auto data = nullptr;
	//auto callBack2 = [](CCNode* sender, void* data){log("This is callBack2");};
	auto func2 = CCCallFuncND::create(this, callfuncND_selector(ActionTest::callBack2), data);

	return true;
}

void ActionTest::callBack2(CCNode* sender, void* data)
{
	log("This is callBack2.");
}

