#ifndef __STRING__UTIL__H__
#define __STRING__UTIL__H__

#include <vector>
#include <string>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class StringUtil
{
public:
	//拆分字符串
	static std::vector<std::string> splite(const std::string& source, const std::string& delimiters = " \t\n");
	//替换字符串
	static std::string replace(const std::string& source, const std::string search, const std::string replace);
	//保留包括小数点的几位
	static std::string fraction(std::string str, int decplaces = 2);
	static std::string fraction(float value, int decplaces = 2);

	static std::string arabic2Chinese(int num);

	static std::string secToDay(int second, int mode = 0);
	static std::string secToStr(int second);
	static time_t StringToDatetime(const char *str);
	static std::string sec2vtm(int seconds, int mode = 0);
protected:
	
private:
	
};

#endif