#include "StringUtil.h"
#include <iomanip>
#include <string>
#include "deprecated/CCString.h"
#include "base/ccUTF8.h"

//临时用的
#define lang

std::vector<string> StringUtil::splite(const std::string& source, const std::string& delimiters /*= " \t\n"*/)
{
	std::vector<string> container;
	const std::string::size_type len = source.length();
	std::string::size_type i = 0;

	while (i < len)
	{
		i = source.find_first_not_of(delimiters, i);
		if (i == std::string::npos)
		{
			container.push_back(source);
			break;
		}
		// find the end of the token
		std::string::size_type j = source.find_first_of(delimiters, i);

		// push token
		if (j == std::string::npos) 
		{
			container.push_back(source.substr(i));
			break;
		}
		else
		{
			container.push_back(source.substr(i, j - i));
		}
		// set up for next loop
		i = j + 1;
	}
	return container;
}

std::string StringUtil::fraction(std::string str, int decplaces /*= 1*/)
{
	char DECIMAL_POINT = '.';  
	size_t n = str.find(DECIMAL_POINT);
	if ((n != string::npos) && (str.size() > n + decplaces)) //后面至少还有decplaces位
	{
		str[n + decplaces] = '\0';							 //覆盖第一个多余的数
	}
	str = str.c_str();							 //删除nul之后的多余字符

	return str;
}

std::string StringUtil::fraction(float value, int decplaces /*= 1*/)
{
	std::string str = std::to_string(value);
	return fraction(str, decplaces);
}

std::string StringUtil::replace(const std::string& source, const std::string search, const std::string replace)
{
	std::string ret = source;
	size_t pos = 0;

	pos = ret.find(search, pos);
	while (pos != string::npos)
	{
		ret.replace(pos, search.length(), replace);
		pos += replace.length();
		pos = ret.find(search, pos);
	}
	return ret;
}

std::string StringUtil::arabic2Chinese(int num)
{
	switch (num)
	{
		case 0:
			return lang("chn_zero");

		case 1:
			return lang("chn_one");

		case 2:
			return lang("chn_two");

		case 3:
			return lang("chn_three");

		case 4:
			return lang("chn_four");

		case 5:
			return lang("chn_five");

		case 6:
			return lang("chn_six");

		case 7:
			return lang("chn_seven");

		case 8:
			return lang("chn_eight");

		case 9:
			return lang("chn_nine");
	}

	return "";
}

std::string StringUtil::secToDay(int second, int mode)
{
	time_t rawtime = second;
	struct tm* timeinfo = gmtime(&rawtime);
	std::string format = "";
	switch (mode)
	{
	case 0:
		format = "%d-%d-%d";
		break;
	case 1:
		format = "%d" + std::string(lang("year")) + "%d" + lang("month") + "%d" + lang("date");
		break;
	default:
		break;
	}
	std::string str = StringUtils::format(format.c_str(), timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	return str;
}

std::string StringUtil::secToStr(int second)
{
	std::string str = "";
	int day = second / (3600 * 24);
	int hour = second % (3600 * 24) / 3600;
	int minute = second % 3600 / 60;
	int sec = second % 60;
	str += day > 0 ? to_string(day) + lang("day") : "";
	str += hour > 0 ? to_string(hour) + lang("hour") : "";
	str += minute > 0 ? to_string(minute) + lang("minute") : "";
	str += sec > 0 ? to_string(sec) + lang("second") : "";
	str += str == "" ? to_string(0) + lang("second") : "";
	return str;
}

time_t StringUtil::StringToDatetime(const char *str)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	sscanf(str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	time_t t_ = mktime(&tm_); //已经减了8个时区  
	return t_; //秒时间  
}

std::string StringUtil::sec2vtm(int seconds, int mode)
{
	std::string str = "";
	int hour = seconds % (3600 * 24) / 3600;
	int minute = seconds % 3600 / 60;
	int sec = seconds % 60;
	//
	std::string hourStr = (hour < 10) ? ('0' + to_string(hour)) : to_string(hour);
	std::string minStr = (minute < 10) ? ('0' + to_string(minute)) : to_string(minute);
	std::string secStr = (sec < 10) ? ('0' + to_string(sec)) : to_string(sec);
	switch (mode) {
	case 1:
		str = hourStr;
		break;
	case 2:
		str = minStr;
		break;
	case 3:
		str = secStr;
		break;
	case 5:
		str = hourStr + ":" + minStr;
		break;
	case 6:
		str = minStr + ":" + secStr;
		break;
	default:
		str = hourStr + ":" + minStr + ":" + secStr;
	}
	return str;
}
