#include "2d/CCLayer.h"
#ifndef __COMPRESS__PNG__H__
#define __COMPRESS__PNG__H__

#include "BaseTest.h"
#include "renderer/CCTexture2D.h"
#include "base/ZipUtils.h"

class CompressPngTest : public BaseTest
{
public:
	CompressPngTest();
	~CompressPngTest();

	virtual bool init();
	
	CREATE_FUNC(CompressPngTest);
protected:
	
private:
	void loadCallBack(cocos2d::Texture2D* texture);
	Image* getImageFromZip(ZipFile* zip, const std::string& value);
};

#endif