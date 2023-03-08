#pragma once
#include <string>
#include <vector>
struct InvoiceItem { std::string phoneId; std::string phoneName; long long unitPrice; int quantity; long long lineTotal() const { return unitPrice*quantity; } };
class Invoice {
private:
    std::string id, customer, date;
    std::vector<InvoiceItem> items;
public:
    Invoice(); Invoice(std::string id,std::string customer,std::string date);
    std::string getId() const; std::string getCustomer() const; std::string getDate() const;
    const std::vector<InvoiceItem>& getItems() const;
    void addItem(const InvoiceItem& it);
    long long total() const;
    void display() const;
    std::string toCSV() const; // one line per item: invoiceId,customer,date,phoneId,phoneName,unitPrice,quantity
    static bool fromCSV(const std::string& line, Invoice& inv, InvoiceItem& item);
};
