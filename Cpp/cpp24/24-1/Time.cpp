#include "Time.h"

bool Time::SetTime(short hour, short min, short sec, bool american)
{
	if (hour >= 0 && hour < 24 ) 
	{
		mHour = hour; 
	}
	else
	{ 
		return false;
	}

	if (min >= 0 && min < 60) { mMin = min; }
	else { return false; }

	if (sec >= 0 && sec < 60) { mSec = sec; }
	else { return false; }

	mAmerican = american;
	return true;
}


Time::Time(short hour, short min, short sec, bool american)
{
	if (!SetTime(hour, min, sec, american)) { exit(1); }
}


bool Time::operator()(short hour, short min, short sec, bool american)
{
	if (SetTime(hour, min, sec, american)) 	{ return true; }

	return false;
}


int Time::ConvertToSeconds(Time source)
{
	return source.mSec + source.mMin * 60 + source.mHour * 3600;
}


Time Time::MakeTime(int seconds)
{
	Time tmp;
	tmp.mSec = seconds % 60;
	seconds /= 60;
	tmp.mMin = seconds % 60;
	seconds /= 60;
	tmp.mHour = seconds % 24;
	return tmp;
}


Time Time::operator+(Time operand2)
{
	int resultInSeconds = ConvertToSeconds(*this) + ConvertToSeconds(operand2);
	return MakeTime(resultInSeconds);
}


Time Time::operator-(Time operand2)
{
	int resultInSeconds = ConvertToSeconds(*this) - ConvertToSeconds(operand2);
	if (resultInSeconds < 0)
	{
		const int secondsInHour = 86400;
		resultInSeconds += secondsInHour;
	}
	return MakeTime(resultInSeconds);
}


Time Time::operator=(Time result)
{
	mHour = result.mHour;
	mMin = result.mMin;
	mSec = result.mSec;
	return *this;
}


bool Time::operator==(Time operand2)
{
	if (mHour == operand2.mHour &&
		mMin == operand2.mMin &&
		mSec == operand2.mSec)
	{
		return true;
	}

	return false;
}


bool Time::operator!=(Time operand2)
{
	return !(*this == operand2);
}


bool Time::operator>(Time operand2)
{
	if (ConvertToSeconds(*this) - ConvertToSeconds(operand2) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Time::operator<(Time operand2)
{
	if (ConvertToSeconds(*this) - ConvertToSeconds(operand2) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Time::operator>=(Time operand2)
{
	return !(*this < operand2);
}


bool Time::operator<=(Time operand2)
{
	return !(*this > operand2);
}