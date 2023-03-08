#include "Invoice.h"
#include "utils.h"
#include <iostream>
Invoice::Invoice(){}
Invoice::Invoice(std::string i,std::string c,std::string d):id(i),customer(c),date(d){}
std::string Invoice::getId() const {return id;}
std::string Invoice::getCustomer() const {return customer;}
std::string Invoice::getDate() const {return date;}
const std::vector<InvoiceItem>& Invoice::getItems() const {return items;}
void Invoice::addItem(const InvoiceItem& it){items.push_back(it);}
long long Invoice::total() const { long long s=0; for(auto&i:items)s+=i.lineTotal(); return s; }
void Invoice::display() const {
    std::cout<<"Hoa don "<<id<<" | Khach: "<<customer<<" | Ngay: "<<date<<"\n";
    for(auto&i:items) std::cout<<"  - "<<i.phoneId<<" "<<i.phoneName<<" x"<<i.quantity<<" = "<<formatMoney(i.lineTotal())<<"\n";
    std::cout<<"  Tong: "<<formatMoney(total())<<"\n";
}
std::string Invoice::toCSV() const {
    std::string r; for(auto&i:items){ if(!r.empty())r+="\n"; r+=id+","+customer+","+date+","+i.phoneId+","+i.phoneName+","+std::to_string(i.unitPrice)+","+std::to_string(i.quantity); } return r;
}
bool Invoice::fromCSV(const std::string& line, Invoice& inv, InvoiceItem& item){
    auto p=splitCSV(line); if(p.size()!=7) return false;
    try{ inv=Invoice(trim(p[0]),trim(p[1]),trim(p[2])); item={trim(p[3]),trim(p[4]),std::stoll(p[5]),std::stoi(p[6])}; }catch(...){return false;}
    return item.quantity>0 && item.unitPrice>=0;
}
