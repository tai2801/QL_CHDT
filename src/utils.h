#pragma once
#include <string>
#include <vector>
std::string trim(const std::string& s);
std::string toLowerStr(std::string s);
bool containsIgnoreCase(const std::string& hay, const std::string& needle);
std::vector<std::string> splitCSV(const std::string& line);
std::string formatMoney(long long v);
bool readInt(const std::string& prompt, int& out);
bool readLongLong(const std::string& prompt, long long& out);
std::string readLinePrompt(const std::string& prompt);
