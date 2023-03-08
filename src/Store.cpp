#include "Store.h"
#include "utils.h"
#include <fstream>
#include <algorithm>
bool Store::addPhone(const Phone& p,std::string& err){ if(!p.isValid(err))return false; if(findById(p.getId())){err="Trung ma san pham: "+p.getId();return false;} phones.push_back(p); return true; }
bool Store::updatePhone(const std::string& id,const Phone& d,std::string& err){ Phone* p=findById(id); if(!p){err="Khong tim thay ma: "+id;return false;} if(!d.isValid(err))return false; p->setName(d.getName()); p->setBrand(d.getBrand()); p->setPrice(d.getPrice()); p->setStock(d.getStock()); return true; }
bool Store::removePhone(const std::string& id){ auto it=std::remove_if(phones.begin(),phones.end(),[&](const Phone& p){return p.getId()==id;}); if(it==phones.end())return false; phones.erase(it,phones.end()); return true; }
Phone* Store::findById(const std::string& id){ for(auto& p:phones) if(p.getId()==id) return &p; return nullptr; }
const Phone* Store::findById(const std::string& id) const { for(auto& p:phones) if(p.getId()==id) return &p; return nullptr; }
std::vector<Phone> Store::searchByName(const std::string& kw) const { std::vector<Phone> r; for(auto& p:phones) if(containsIgnoreCase(p.getName(),kw)) r.push_back(p); return r; }
std::vector<Phone> Store::searchByBrand(const std::string& kw) const { std::vector<Phone> r; for(auto& p:phones) if(containsIgnoreCase(p.getBrand(),kw)) r.push_back(p); return r; }
const std::vector<Phone>& Store::getPhones() const {return phones;}
const std::vector<Invoice>& Store::getInvoices() const {return invoices;}
bool Store::createInvoice(const std::string& customer,const std::string& date,const std::vector<std::pair<std::string,int>>& lines,Invoice& out,std::string& err){
    if(customer.empty()){err="Ten khach khong duoc rong";return false;}
    if(lines.empty()){err="Hoa don khong co san pham";return false;}
    // Validate all lines first (atomic: no stock change if any line fails)
    for(auto& ln: lines){ Phone* p=findById(ln.first); if(!p){err="Khong tim thay ma: "+ln.first;return false;} if(ln.second<=0){err="So luong phai > 0";return false;} if(ln.second>p->getStock()){err="Khong du ton kho cho "+ln.first+" (con "+std::to_string(p->getStock())+")";return false;} }
    char buf[16]; snprintf(buf,sizeof(buf),"HD%03d",nextInvoiceSeq++);
    Invoice inv(buf,customer,date.empty()?"2023-03-25":date);
    for(auto& ln: lines){ Phone* p=findById(ln.first); inv.addItem({p->getId(),p->getName(),p->getPrice(),ln.second}); p->setStock(p->getStock()-ln.second); }
    invoices.push_back(inv); out=inv; return true;
}
long long Store::totalRevenue() const { long long s=0; for(auto& i:invoices)s+=i.total(); return s; }
int Store::totalSoldQuantity() const { int s=0; for(auto& i:invoices) for(auto& it:i.getItems()) s+=it.quantity; return s; }
bool Store::savePhones(const std::string& path,std::string& err) const { std::ofstream f(path); if(!f){err="Khong mo duoc file: "+path;return false;} for(auto& p:phones) f<<p.toCSV()<<"\n"; return true; }
bool Store::loadPhones(const std::string& path,std::string& err){ std::ifstream f(path); if(!f){err="Khong mo duoc file: "+path;return false;} phones.clear(); std::string line; while(std::getline(f,line)){ if(trim(line).empty())continue; Phone p; if(Phone::fromCSV(line,p)){ std::string e; addPhone(p,e); } } return true; }
bool Store::saveInvoices(const std::string& path,std::string& err) const { std::ofstream f(path); if(!f){err="Khong mo duoc file: "+path;return false;} for(auto& i:invoices){ auto c=i.toCSV(); if(!c.empty()) f<<c<<"\n"; } return true; }
bool Store::loadInvoices(const std::string& path,std::string& err){ std::ifstream f(path); if(!f){err="Khong mo duoc file: "+path;return false;} invoices.clear(); std::string line; while(std::getline(f,line)){ if(trim(line).empty())continue; Invoice inv; InvoiceItem it; if(!Invoice::fromCSV(line,inv,it))continue; Invoice* ex=nullptr; for(auto& x:invoices) if(x.getId()==inv.getId()) ex=&x; if(!ex){ invoices.push_back(inv); ex=&invoices.back(); } ex->addItem(it); int n=0; try{n=std::stoi(inv.getId().substr(2));}catch(...){} if(n>=nextInvoiceSeq) nextInvoiceSeq=n+1; } return true; }
void Store::addInvoiceDirect(const Invoice& inv){ invoices.push_back(inv); }
