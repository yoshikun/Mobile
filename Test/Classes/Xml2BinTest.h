#ifndef __XML__TWO__BIN__H__
#define __XML__TWO__BIN__H__

#include "BaseTest.h"

class Xml2BinTest : public BaseTest
{
public:
	Xml2BinTest();
	~Xml2BinTest();
	
	virtual bool init();

	CREATE_FUNC(Xml2BinTest);
	void decodeXsd(const std::string& fileName);
	void decodeXml(const std::string& fileName);
protected:
	
private:
	//保存类属性名和类型
	std::map<std::string, std::string> _propertyMap;

};

#endif