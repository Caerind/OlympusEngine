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

		U32 getYear() const;
		void setYear(U32 year);

		U32 getMonth() const;
		void setMonth(U32 month);

		U32 getDay() const;
		void setDay(U32 day);

		U32 getHours() const;
		void setHours(U32 hours);

		U32 getMinutes() const;
		void setMinutes(U32 minutes);

		U32 getSeconds() const;
		void setSeconds(U32 seconds);

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