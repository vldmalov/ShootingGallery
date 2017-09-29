#pragma once

#include "unordered_map"
typedef std::unordered_map<std::string, std::string> StringDict;

class Preferences {
	
public:
	static Preferences& Instance();
	
	int getIntValue(const std::string& key, int defaultVal) const;
	float getFloatValue(const std::string& key, float defaultVal) const;
	std::string getStringValue(const std::string& key, const std::string& defaultVal) const;
	
private:
	Preferences();
	~Preferences();
	
	void Init();
	void ParsePreferencesLine(const std::string& line);
	
	Preferences(const Preferences&) = delete;
	Preferences& operator=(const Preferences&) = delete;

private:
	StringDict prefsMap;
};
