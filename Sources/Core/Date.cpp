#include "Date.hpp"

#include <sstream> // fromString
#include <iomanip> // fromString

namespace oe
{

Date::Date()
{
	std::time_t t = std::time(nullptr);
	#ifdef _MSC_VER
		localtime_s(&mTime, &t);
	#else
		mTime = *localtime(&t);
	#endif
	update();
}

Date::Date(const std::string& str, const std::string& format)
{
	fromString(str, format);
}

U32 Date::getYear() const
{
	return mTime.tm_year + 1900;
}

void Date::setYear(U32 year)
{
	mTime.tm_year = year - 1900;
	update();
}

U32 Date::getMonth() const
{
	return mTime.tm_mon + 1;
}

void Date::setMonth(U32 month)
{
	mTime.tm_mon = month - 1;
	update();
}

U32 Date::getDay() const
{
	return mTime.tm_mday;
}

void Date::setDay(U32 day)
{
	mTime.tm_mday = day;
	update();
}

U32 Date::getHours() const
{
	return mTime.tm_hour;
}

void Date::setHours(U32 hours)
{
	mTime.tm_hour = hours;
	update();
}

U32 Date::getMinutes() const
{
	return mTime.tm_min;
}

void Date::setMinutes(U32 minutes)
{
	mTime.tm_min = minutes;
	update();
}

U32 Date::getSeconds() const
{
	return mTime.tm_sec;
}

void Date::setSeconds(U32 seconds)
{
	mTime.tm_sec = seconds;
	update();
}

std::string Date::toString(const std::string& format) const
{
	char buffer[30];
	strftime(buffer, 30, format.c_str(), &mTime);
	return std::string(buffer);
}

void Date::fromString(const std::string& str, const std::string& format)
{
	std::istringstream iss(str);
	iss >> std::get_time(&mTime, format.c_str());
	// TODO : Find cross compile alternative (Support on MinGW)
	update();
}

bool Date::passed() const
{
	return *this < getCurrentDate();
}

Date Date::getCurrentDate()
{
	return Date();
}

void Date::update()
{
	mktime(&mTime);
}

bool operator==(const Date& left, const Date& right)
{
	return (left.getYear() == right.getYear()
		&& left.getMonth() == right.getMonth()
		&& left.getDay() == right.getDay()
		&& left.getHours() == right.getHours()
		&& left.getMinutes() == right.getMinutes()
		&& left.getSeconds() == right.getSeconds());
}

bool operator!=(const Date& left, const Date& right)
{
	return !(left == right);
}

bool operator<(const Date& left, const Date& right)
{
	// Year
	if (left.getYear() < right.getYear())
		return true;
	else if (left.getYear() > right.getYear())
		return false;

	// Month
	if (left.getMonth() < right.getMonth())
		return true;
	else if (left.getMonth() > right.getMonth())
		return false;

	// Day
	if (left.getDay() < right.getDay())
		return true;
	else if (left.getDay() > right.getDay())
		return false;

	// Hours
	if (left.getHours() < right.getHours())
		return true;
	else if (left.getHours() > right.getHours())
		return false;

	// Minutes
	if (left.getMinutes() < right.getMinutes())
		return true;
	else if (left.getMinutes() > right.getMinutes())
		return false;

	// Seconds
	if (left.getSeconds() < right.getSeconds())
		return true;
	else if (left.getSeconds() > right.getSeconds())
		return false;

	return false;
}

bool operator>(const Date& left, const Date& right)
{
	return (left != right && !(left < right));
}

bool operator>=(const Date& left, const Date& right)
{
	return !(left < right);
}

bool operator<=(const Date& left, const Date& right)
{
	return !(left > right);
}

std::string toString(const Date& value)
{
	std::ostringstream oss;
	oss << value.toString();
	return oss.str();
}

Date fromString(const std::string& string)
{
	return Date(string);
}

} // namespace oe