#ifndef OE_DATE_HPP
#define OE_DATE_HPP

#include "../Config.hpp"
#include <ctime>

namespace oe
{

class OE_API Date
{
	public:
		Date();

		Date(const std::string& str, const std::string& format = "%d-%m-%Y %H-%M-%S");

		int getYear() const;
		void setYear(int year);

		int getMonth() const;
		void setMonth(int month);

		int getDay() const;
		void setDay(int day);

		int getHours() const;
		void setHours(int hours);

		int getMinutes() const;
		void setMinutes(int minutes);

		int getSeconds() const;
		void setSeconds(int seconds);

		std::string toString(const std::string& format = "%d-%m-%Y %H-%M-%S") const;
		void fromString(const std::string& str, const std::string& format = "%d-%m-%Y %H-%M-%S");

		bool passed() const;

		static Date getCurrentDate();

	private:
		void update();

	private:
		std::tm mTime;
};

bool operator==(const Date& left, const Date& right);
bool operator!=(const Date& left, const Date& right);
bool operator<(const Date& left, const Date& right);
bool operator>(const Date& left, const Date& right);
bool operator>=(const Date& left, const Date& right);
bool operator<=(const Date& left, const Date& right);

// TODO : Operator Date & Time

std::string toString(const Date& value);

Date fromString(const std::string& string);

} // namespace oe

#endif // OE_DATE_HPP