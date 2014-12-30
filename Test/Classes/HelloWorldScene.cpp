#include "HelloWorldScene.h"
#include "base/ZipUtils.h"
#include "CCImage.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
 
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename("atlas_compress.png");
	auto zip = new ZipFile(fullpath);
	fullpath = fullpath.substr(fullpath.rfind('/') + 1, fullpath.length());
	auto data = getImageFromZip(zip, "atlas_data");
	auto mask = getImageFromZip(zip, "atlas_mask");

	ssize_t png_size = mask->getDataLen() * 4;

	unsigned char* buffer = {}; 
	buffer = (unsigned char*)malloc(sizeof(unsigned char) * png_size);
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
	atlas->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(atlas, 0);
    
	free(buffer);
	CC_SAFE_DELETE(zip);

    return true;
}

Image* HelloWorld::getImageFromZip(ZipFile* zip, const std::string& value)
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

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
