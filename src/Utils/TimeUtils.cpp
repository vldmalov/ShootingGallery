#include "TimeUtils.h"

namespace Utils {

std::string FormatTime(int sec)
{
	if(sec < 0) {
		sec = 0;
	}

	std::stringstream result;
	result << std::setw(2) << std::setfill('0') << (sec / 60) << ":";
	result << std::setw(2) << std::setfill('0') << (sec % 60);
	
	return result.str();
}

}
