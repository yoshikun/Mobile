#include "CompressPngTest.h"
#include "2d/CCSprite.h"
#include "CCFileUtils.h"
#include "base/ZipUtils.h"
#include "CCImage.h"
#include "base/CCDirector.h"
#include "ui/UIScrollView.h"
#include "ui/UIDeprecated.h"
#include "2d/CCLayer.h"

using namespace ui;

CompressPngTest::~CompressPngTest()
{

}

CompressPngTest::CompressPngTest()
{

}

bool CompressPngTest::init()
{
	if (!BaseTest::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	auto bg = LayerGradient::create(Color4B::RED, Color4B::GREEN, Vec2(0.5f, 0.5f));
	bg->setContentSize(visibleSize);
	this->addChild(bg);

	auto scrollView = ScrollView::create();
	//设置显示区域大小
	scrollView->setContentSize(visibleSize);
	//设置内部实际大小
	scrollView->setInnerContainerSize(Size(2048, 2048));
	//设置可以回弹
	scrollView->setBounceEnabled(true);
	scrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->addChild(scrollView);

	std::string fullpath = FileUtils::getInstance()->fullPathForFilename("atlas_compress.png");
	auto zip = new ZipFile(fullpath);
	fullpath = fullpath.substr(fullpath.rfind('/') + 1, fullpath.length());
	auto data = getImageFromZip(zip, "atlas_data");
	auto mask = getImageFromZip(zip, "atlas_mask");

	ssize_t png_size = mask->getDataLen() * 4;

	unsigned char* buffer = {};
	buffer = (unsigned char*)malloc(sizeof(unsigned char)* png_size);
	memset(buffer, 0, png_size);

	for (int i = 0, j = 0, k = 0; j < png_size; i++, j += 4, k += 3)
	{
		buffer[j] = data->getData()[k];
		buffer[j + 1] = data->getData()[k + 1];
		buffer[j + 2] = data->getData()[k + 2];
		buffer[j + 3] = mask->getData()[i];
	}
	auto texture = new Texture2D();
	texture->initWithData(buffer, png_size, Texture2D::PixelFormat::RGBA8888, mask->getWidth(), mask->getHeight(), Size(mask->getWidth(), mask->getHeight()));

	auto atlas = Sprite::createWithTexture(texture);
	atlas->setAnchorPoint(Vec2::ZERO);
	scrollView->addChild(atlas, 0);

	free(buffer);
	CC_SAFE_DELETE(zip);

	return true;
}

Image* CompressPngTest::getImageFromZip(ZipFile* zip, const std::string& value)
{
	ssize_t size = 0;
	auto data = zip->getFileData(value, &size);
	if (!data)
	{
		return nullptr;
	}
	auto image = new Image();
	image->initWithImageData(data, size);
	image->autorelease();
	return image;
}