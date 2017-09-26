#pragma once

#include "map"
typedef std::map<std::string, std::string> StringMap;

class Preferences {
	
public:
	static Preferences& Instance();
	
	int getIntValue(const std::string& key, int defaultVal) const;
	std::string getStringValue(const std::string& key, const std::string& defaultVal) const;
	
private:
	Preferences();
	~Preferences();
	
	void Init();
	void ParsePreferencesLine(const std::string& line);
	
	Preferences(const Preferences&) = delete;
	Preferences& operator=(const Preferences&) = delete;

private:
	StringMap prefsMap;
};
