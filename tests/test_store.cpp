#include "../src/Store.h"
#include <iostream>
#include <cassert>
#include <cstdio>
static int passed=0, failed=0;
#define CHECK(name,cond) do{ if(cond){passed++; std::cout<<"[PASS] "<<name<<"\n";} else {failed++; std::cout<<"[FAIL] "<<name<<"\n";} }while(0)
int main(){
    Store s; std::string err;
    CHECK("add valid phone", s.addPhone(Phone("DT001","iPhone 14","Apple",20000000,10),err));
    CHECK("duplicate id rejected", !s.addPhone(Phone("DT001","Dup","Apple",1000,1),err));
    CHECK("negative price rejected", !s.addPhone(Phone("DT002","X","Y",-1,1),err));
    CHECK("negative stock rejected", !s.addPhone(Phone("DT002","X","Y",1000,-1),err));
    CHECK("empty id rejected", !s.addPhone(Phone("","X","Y",1000,1),err));
    CHECK("add second phone", s.addPhone(Phone("DT002","Galaxy S23","Samsung",25000000,5),err));
    CHECK("findById found", s.findById("DT001")!=nullptr);
    CHECK("findById not found", s.findById("XX")==nullptr);
    CHECK("search by name", s.searchByName("iphone").size()==1);
    CHECK("search by brand", s.searchByBrand("samsung").size()==1);
    CHECK("search empty result", s.searchByName("NokiaXYZ").size()==0);
    CHECK("update phone", s.updatePhone("DT001",Phone("DT001","iPhone 14 Pro","Apple",22000000,9),err) && s.findById("DT001")->getPrice()==22000000);
    CHECK("update missing rejected", !s.updatePhone("XX",Phone("XX","A","B",1,1),err));
    // Invoice: buy 2 x DT001 -> stock 9-2=7, total 44,000,000
    Invoice inv; std::vector<std::pair<std::string,int>> lines={{"DT001",2}};
    CHECK("create invoice", s.createInvoice("Khach A","2023-03-25",lines,inv,err));
    CHECK("invoice total", inv.total()==44000000);
    CHECK("stock decreased", s.findById("DT001")->getStock()==7);
    CHECK("invoice over-stock rejected", !s.createInvoice("B","2023-03-25",{{"DT002",99}},inv,err));
    CHECK("stock unchanged after failed invoice", s.findById("DT002")->getStock()==5);
    CHECK("invoice empty lines rejected", !s.createInvoice("B","2023-03-25",{},inv,err));
    CHECK("revenue", s.totalRevenue()==44000000);
    CHECK("save phones", s.savePhones("test_phones_tmp.txt",err));
    Store s2; CHECK("load phones", s2.loadPhones("test_phones_tmp.txt",err) && s2.getPhones().size()==2);
    std::remove("test_phones_tmp.txt");
    CHECK("remove phone", s.removePhone("DT002"));
    CHECK("remove missing returns false", !s.removePhone("DT002"));
    std::cout<<"\nResult: "<<passed<<" passed, "<<failed<<" failed\n";
    return failed?1:0;
}
