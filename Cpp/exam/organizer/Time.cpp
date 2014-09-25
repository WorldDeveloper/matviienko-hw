#include "Time.h"

bool Time::SetTime(const short hour, const short min)
{
	if (hour >= 0 && hour < 24) 	{ mHour = hour; }
	else	return false;

	if (min >= 0 && min < 60) { mMin = min; }
	else { return false; }

	return true;
}


int Time::ConvertToMinutes(const Time& source) const
{
	return source.mMin + source.mHour * 60;
}


bool Time::operator==(const Time& operand2) const
{
	if (mHour == operand2.mHour &&
		mMin == operand2.mMin)
	{
		return true;
	}

	return false;
}

bool Time::operator!=(const Time& operand2) const
{
	return !(*this == operand2);
}


bool Time::operator>(const Time& operand2) const
{
	if (ConvertToMinutes(*this) - ConvertToMinutes(operand2) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Time::operator<(const Time& operand2) const
{
	if (ConvertToMinutes(*this) - ConvertToMinutes(operand2) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Time::operator>=(const Time& operand2) const
{
	return !(*this < operand2);
}


bool Time::operator<=(const Time& operand2) const
{
	return !(*this > operand2);
}

string Time::GetTime() const
{
	string hour = to_string(mHour);
	if (mHour < 10) hour.insert(0, "0");

	string min = to_string(mMin);
	if (mMin < 10) min.insert(0, "0");

	return hour + ":" + min;
}