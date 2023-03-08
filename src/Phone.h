#pragma once
#include <string>
#include <iostream>
class Phone {
private:
    std::string id, name, brand;
    long long price;
    int stock;
public:
    Phone();
    Phone(std::string id, std::string name, std::string brand, long long price, int stock);
    std::string getId() const; std::string getName() const; std::string getBrand() const;
    long long getPrice() const; int getStock() const;
    void setName(const std::string& v); void setBrand(const std::string& v);
    void setPrice(long long v); void setStock(int v);
    bool isValid(std::string& err) const;
    std::string toCSV() const;
    static bool fromCSV(const std::string& line, Phone& out);
    void display() const;
};
