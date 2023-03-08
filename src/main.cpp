#include "Store.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
static const std::string PHONE_FILE="data/phones.txt";
static const std::string INVOICE_FILE="data/invoices.txt";
void printHeader(){ std::cout<<std::left<<std::setw(10)<<"Ma"<<std::setw(28)<<"Ten"<<std::setw(14)<<"Hang"<<std::setw(16)<<"Gia"<<std::setw(8)<<"Ton"<<"\n"; std::cout<<std::string(76,'-')<<"\n"; }
void listPhones(Store& s){ if(s.getPhones().empty()){std::cout<<"Danh sach trong.\n";return;} printHeader(); for(auto& p:s.getPhones()) p.display(); }
int main(){
    Store store; std::string err;
    if(store.loadPhones(PHONE_FILE,err)) std::cout<<"Da tai "<<store.getPhones().size()<<" san pham tu "<<PHONE_FILE<<"\n";
    else std::cout<<"Chua co du lieu: "<<err<<" (bat dau voi danh sach trong)\n";
    store.loadInvoices(INVOICE_FILE,err);
    while(true){
        std::cout<<"\n===== QUAN LY CUA HANG DIEN THOAI =====\n"
                 <<"1. Xem danh sach dien thoai\n2. Them dien thoai\n3. Sua dien thoai\n4. Xoa dien thoai\n"
                 <<"5. Tim kiem (ten / ma / hang)\n6. Tao hoa don ban hang\n7. Xem hoa don & Thong ke doanh thu\n"
                 <<"8. Luu du lieu\n9. Tai lai du lieu\n0. Thoat\n";
        int choice; if(!readInt("Chon chuc nang: ",choice)){ std::cout<<"Lua chon khong hop le!\n"; continue; }
        if(choice==0){ store.savePhones(PHONE_FILE,err); store.saveInvoices(INVOICE_FILE,err); std::cout<<"Da luu du lieu. Tam biet!\n"; break; }
        else if(choice==1) listPhones(store);
        else if(choice==2){
            std::string id=readLinePrompt("Ma SP: "); std::string name=readLinePrompt("Ten: "); std::string brand=readLinePrompt("Hang: ");
            long long price; int stock; if(!readLongLong("Gia (VND): ",price)){std::cout<<"Gia khong hop le!\n";continue;} if(!readInt("Ton kho: ",stock)){std::cout<<"Ton kho khong hop le!\n";continue;}
            Phone p(id,name,brand,price,stock); if(store.addPhone(p,err)) std::cout<<"Them thanh cong!\n"; else std::cout<<"Loi: "<<err<<"\n";
        }
        else if(choice==3){
            std::string id=readLinePrompt("Ma SP can sua: "); Phone* old=store.findById(id); if(!old){std::cout<<"Khong tim thay!\n";continue;}
            std::string name=readLinePrompt("Ten moi: "); std::string brand=readLinePrompt("Hang moi: "); long long price; int stock;
            if(!readLongLong("Gia moi: ",price)){std::cout<<"Gia khong hop le!\n";continue;} if(!readInt("Ton moi: ",stock)){std::cout<<"Ton khong hop le!\n";continue;}
            if(store.updatePhone(id,Phone(id,name,brand,price,stock),err)) std::cout<<"Sua thanh cong!\n"; else std::cout<<"Loi: "<<err<<"\n";
        }
        else if(choice==4){
            std::string id=readLinePrompt("Ma SP can xoa: "); std::string cf=readLinePrompt("Xac nhan xoa? (y/n): ");
            if(cf=="y"||cf=="Y"){ std::cout<<(store.removePhone(id)?"Xoa thanh cong!\n":"Khong tim thay!\n"); } else std::cout<<"Da huy xoa.\n";
        }
        else if(choice==5){
            std::string kw=readLinePrompt("Nhap tu khoa (ten/ma/hang): "); bool found=false; printHeader();
            if(auto* p=store.findById(kw)){p->display(); found=true;}
            for(auto& p:store.searchByName(kw)) if(p.getId()!=kw){p.display(); found=true;}
            for(auto& p:store.searchByBrand(kw)) if(p.getId()!=kw && !containsIgnoreCase(p.getName(),kw)){p.display(); found=true;}
            if(!found) std::cout<<"Khong tim thay ket qua.\n";
        }
        else if(choice==6){
            std::string cust=readLinePrompt("Ten khach hang: "); std::string date=readLinePrompt("Ngay (YYYY-MM-DD): ");
            std::vector<std::pair<std::string,int>> lines; while(true){ std::string id=readLinePrompt("Ma SP (rong de ket thuc): "); if(id.empty())break; int q; if(!readInt("So luong: ",q)){std::cout<<"So luong khong hop le!\n";continue;} lines.push_back({id,q}); }
            Invoice inv; if(store.createInvoice(cust,date,lines,inv,err)){ inv.display(); std::cout<<"Tao hoa don thanh cong!\n"; } else std::cout<<"Loi: "<<err<<"\n";
        }
        else if(choice==7){
            if(store.getInvoices().empty()) std::cout<<"Chua co hoa don.\n"; for(auto& i:store.getInvoices()) i.display();
            std::cout<<"--- THONG KE ---\nTong hoa don: "<<store.getInvoices().size()<<"\nTong so may da ban: "<<store.totalSoldQuantity()
                     <<"\nTong doanh thu: "<<formatMoney(store.totalRevenue())<<"\nTong gia tri ton kho: ";
            long long invVal=0; for(auto& p:store.getPhones()) invVal+=p.getPrice()*p.getStock(); std::cout<<formatMoney(invVal)<<"\n";
        }
        else if(choice==8){ bool a=store.savePhones(PHONE_FILE,err); bool b=store.saveInvoices(INVOICE_FILE,err); std::cout<<((a&&b)?"Luu thanh cong!\n":"Loi luu: "+err+"\n"); }
        else if(choice==9){ if(store.loadPhones(PHONE_FILE,err)) std::cout<<"Tai lai thanh cong: "<<store.getPhones().size()<<" san pham.\n"; else std::cout<<"Loi: "<<err<<"\n"; store.loadInvoices(INVOICE_FILE,err); }
        else std::cout<<"Lua chon khong hop le!\n";
    }
    return 0;
}
