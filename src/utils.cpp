#include "utils.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
std::string trim(const std::string& s){ size_t a=0; while(a<s.size()&&isspace((unsigned char)s[a]))a++; size_t b=s.size(); while(b>a&&isspace((unsigned char)s[b-1]))b--; return s.substr(a,b-a); }
std::string toLowerStr(std::string s){ std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){return tolower(c);}); return s; }
bool containsIgnoreCase(const std::string& hay,const std::string& needle){ return toLowerStr(hay).find(toLowerStr(needle))!=std::string::npos; }
std::vector<std::string> splitCSV(const std::string& line){ std::vector<std::string> r; std::stringstream ss(line); std::string t; while(std::getline(ss,t,',')) r.push_back(t); return r; }
std::string formatMoney(long long v){ std::string s=std::to_string(v), r; int c=0; for(int i=(int)s.size()-1;i>=0;--i){ r.push_back(s[i]); if(++c==3&&i>0){r.push_back('.');c=0;} } std::reverse(r.begin(),r.end()); return r+" VND"; }
bool readInt(const std::string& prompt,int& out){ std::cout<<prompt; std::string l; if(!std::getline(std::cin,l)) return false; try{ size_t p; int v=std::stoi(trim(l),&p); if(p!=trim(l).size()) return false; out=v; return true;}catch(...){return false;} }
bool readLongLong(const std::string& prompt,long long& out){ std::cout<<prompt; std::string l; if(!std::getline(std::cin,l)) return false; try{ size_t p; long long v=std::stoll(trim(l),&p); if(p!=trim(l).size()) return false; out=v; return true;}catch(...){return false;} }
std::string readLinePrompt(const std::string& prompt){ std::cout<<prompt; std::string l; std::getline(std::cin,l); return trim(l); }
