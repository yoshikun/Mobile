#include "Xml2BinTest.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "base/CCConsole.h"
#include "deprecated/CCString.h"
#include "io.h"
#include "StringUtil.h"
#include "ByteBuffer.h"

using namespace rapidxml;

const static std::string directory = "../Resources/data/";

Xml2BinTest::Xml2BinTest()
{

}

Xml2BinTest::~Xml2BinTest()
{

}

bool Xml2BinTest::init()
{
	if (!BaseTest::init())
	{
		return false;
	}
	std::string to_search = directory + std::string("*.xsd");

	//文件列表
	std::vector<std::string> fileListVec;

	//用于查找的句柄  
	long handle;					

	//文件信息的结构体  
	_finddata_t fileInfo;  

	//查找第一个文件
	handle = _findfirst(to_search.c_str(), &fileInfo);  
	if (handle == -1)
	{
		return true;
	}
	log(fileInfo.name);
	fileListVec.push_back(fileInfo.name);

	//查找其他的文件
	while(_findnext(handle, &fileInfo) == 0)
	{
		log(fileInfo.name);
		fileListVec.push_back(fileInfo.name);
	}
	//关闭句柄  
	_findclose(handle);   

	//解析文件列表中的xml
	int len = fileListVec.size();
	for (int i = 0; i < len; i++)
	{
		std::string fileName = fileListVec[i];
		decodeXsd(fileName);
	}
	return true;
}

void Xml2BinTest::decodeXsd(const std::string& fileName)
{
	std::string path = directory + fileName;

	rapidxml::file<> file(path.c_str());
	//log(file.data());

	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());

	rapidxml::xml_node<>* root = doc.first_node();
	root = root->first_node("xs:element");
	root = root->first_node("xs:complexType");
	root = root->first_node("xs:sequence");

	log("Start decode %s", fileName.c_str());

	_propertyMap.clear();

	//遍历xml节点
	for (rapidxml::xml_node<char> * node = root->first_node("xs:element"); node; node = node->next_sibling())
	{
		for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
		{
			//打印类属性的键和值
			//log("%s=%s", attr->name(), attr->value());
		}

		//属性名
		xml_attribute<>* attributeName = node->first_attribute("name");
		//类型名
		xml_attribute<>* attributeType = node->first_attribute("type");
		if (attributeName)
		{
			if (attributeType)
			{
				//属性名
				_propertyMap[attributeName->value()] = attributeType->value();
			}
			else
			{
				//默认使用int类型
				_propertyMap[attributeName->value()] = "xs:int";
			}
		}
	}
	std::string xmlFileName = StringUtil::replace(fileName, ".xsd", ".xml");
	//开始解析xml数据
	decodeXml(xmlFileName);
}

void Xml2BinTest::decodeXml(const std::string& fileName)
{
	ByteBuffer bytes;

	std::string path = directory + fileName;
	rapidxml::file<> xmlFile(path.c_str());
	//log(file.data());

	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	
	rapidxml::xml_node<>* root = doc.first_node();

	//类属性名
	std::string nodeName = root->first_node()->name();

	for (rapidxml::xml_node<char> * node = root->first_node(nodeName.c_str()); node; node = node->next_sibling())
	{
		rapidxml::xml_node<char>* propertyNode = node->first_node();
		for (propertyNode; propertyNode; propertyNode = propertyNode->next_sibling())
		{
			std::string name = propertyNode->name();
			std::string value = propertyNode->value();
			std::string type = _propertyMap[name];
			if (type == "xs:int")
			{
				bytes << std::atoi(value.c_str());
			}
			else if (type == "xs:string")
			{
				bytes << value.c_str();
			}
			else if (type == "xs:float")
			{
				float temp = std::atof(value.c_str());
				bytes << temp;
			}
			else if (type == "")
			{
				bytes << std::atoi(value.c_str());
			}
			else
			{
				log("Property %s is not defined", type);
			}
		}
	}

	//path = CCFileUtils::sharedFileUtils()->getWritablePath() + propertyName;
	path = directory + StringUtil::replace(fileName, ".xml", "");
	log("save file path = %s", path.c_str());

	//创建一个文件指针，注意要使用参数"wb"，w表示write，b表示二进制binary，之前我使用的是"w",ios上当时没有发现问题，但是win32上会有bug，改成"wb"就没有问题了
	FILE* file = fopen(path.c_str(), "wb");

	if (file)
	{
		fwrite(bytes.contents(), sizeof(unsigned char), bytes.size(), file);
		fclose(file);
	}
	else
	{
		log("save file error.");
	}
}
