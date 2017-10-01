#include "Preferences.h"

const std::string PREFERENCES_FILE_NAME = "input.txt";
const char KEY_VAL_SEPARATOR = '=';

Preferences& Preferences::Instance()
{
	static Preferences instance;
	return instance;
}

Preferences::Preferences()
{
	Init();
	Log::log.WriteDebug("Singltone references has been constructed");
}

Preferences::~Preferences()
{
	Log::log.WriteDebug("Singltone references has been destructed");
}

void Preferences::Init()
{
	IO::InputStreamPtr streamPtr = Core::fileSystem.OpenRead(PREFERENCES_FILE_NAME);
	if(!streamPtr) {
		Log::log.WriteWarn("Preferences file has not found!");
		return;
	}
	
	IO::TextReader reader(streamPtr.get());
	std::string fileLine;
	do {
		fileLine = reader.ReadAsciiLine();
		ParsePreferencesLine(fileLine);
	}
	while( !fileLine.empty() );
}

void Preferences::ParsePreferencesLine(const std::string& line)
{
	if(line.empty()) {
		return;
	}
	
	size_t findPos = line.find(KEY_VAL_SEPARATOR);
	if(findPos == std::string::npos) {
		return;
	}
	
	std::string key(line.begin(), line.begin() + findPos);
	std::string val(line.begin() + findPos + 1, line.end());
	
	// Удаляем все пробелы
	key.erase( remove_if(key.begin(), key.end(), isspace), key.end());
	val.erase( remove_if(val.begin(), val.end(), isspace), val.end());
	Log::log.WriteInfo("Read preference: " + key + " = " + val);
	
	prefsMap[key] = val;
}

int Preferences::getIntValue(const std::string& key, int defaultVal) const
{
	std::string strValue = getStringValue(key, std::string());
	if(strValue.empty()) {
		return defaultVal;
	}
	
	return utils::lexical_cast<int>(strValue);
}

float Preferences::getFloatValue(const std::string& key, float defaultVal) const
{
	std::string strValue = getStringValue(key, std::string());
	if(strValue.empty()) {
		return defaultVal;
	}
	
	return utils::lexical_cast<float>(strValue);
}

std::string Preferences::getStringValue(const std::string& key, const std::string& defaultVal) const
{
	StringDict::const_iterator findIt = prefsMap.find(key);
	if(findIt == prefsMap.end()) {
		Log::log.WriteInfo("Pref " + key + " doesn't found. Return default value");
		return defaultVal;
	}
	
	return findIt->second;
}
