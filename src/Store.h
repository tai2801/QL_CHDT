#pragma once
#include "Phone.h"
#include "Invoice.h"
#include <vector>
#include <string>
class Store {
private:
    std::vector<Phone> phones;
    std::vector<Invoice> invoices;
    int nextInvoiceSeq = 1;
public:
    bool addPhone(const Phone& p, std::string& err);
    bool updatePhone(const std::string& id, const Phone& data, std::string& err);
    bool removePhone(const std::string& id);
    Phone* findById(const std::string& id);
    const Phone* findById(const std::string& id) const;
    std::vector<Phone> searchByName(const std::string& kw) const;
    std::vector<Phone> searchByBrand(const std::string& kw) const;
    const std::vector<Phone>& getPhones() const;
    const std::vector<Invoice>& getInvoices() const;
    bool createInvoice(const std::string& customer, const std::string& date,
                        const std::vector<std::pair<std::string,int>>& lines,
                        Invoice& out, std::string& err);
    long long totalRevenue() const;
    int totalSoldQuantity() const;
    bool savePhones(const std::string& path, std::string& err) const;
    bool loadPhones(const std::string& path, std::string& err);
    bool saveInvoices(const std::string& path, std::string& err) const;
    bool loadInvoices(const std::string& path, std::string& err);
    void addInvoiceDirect(const Invoice& inv);
};
