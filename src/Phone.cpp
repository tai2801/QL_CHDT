#include "Phone.h"
#include "utils.h"
#include <sstream>
#include <iomanip>
Phone::Phone():price(0),stock(0){}
Phone::Phone(std::string i,std::string n,std::string b,long long p,int s):id(i),name(n),brand(b),price(p),stock(s){}
std::string Phone::getId() const {return id;}
std::string Phone::getName() const {return name;}
std::string Phone::getBrand() const {return brand;}
long long Phone::getPrice() const {return price;}
int Phone::getStock() const {return stock;}
void Phone::setName(const std::string& v){name=v;}
void Phone::setBrand(const std::string& v){brand=v;}
void Phone::setPrice(long long v){price=v;}
void Phone::setStock(int v){stock=v;}
bool Phone::isValid(std::string& err) const {
    if(id.empty()){err="Ma san pham khong duoc rong";return false;}
    if(name.empty()){err="Ten khong duoc rong";return false;}
    if(brand.empty()){err="Hang khong duoc rong";return false;}
    if(price<0){err="Gia khong duoc am";return false;}
    if(stock<0){err="Ton kho khong duoc am";return false;}
    return true;
}
std::string Phone::toCSV() const { return id+","+name+","+brand+","+std::to_string(price)+","+std::to_string(stock); }
bool Phone::fromCSV(const std::string& line, Phone& out){
    auto p=splitCSV(line); if(p.size()!=5) return false;
    try{ out=Phone(trim(p[0]),trim(p[1]),trim(p[2]),std::stoll(p[3]),std::stoi(p[4])); }catch(...){return false;}
    std::string e; return out.isValid(e);
}
void Phone::display() const {
    std::cout<<std::left<<std::setw(10)<<id<<std::setw(28)<<name<<std::setw(14)<<brand
             <<std::setw(16)<<formatMoney(price)<<std::setw(8)<<stock<<"\n";
}
