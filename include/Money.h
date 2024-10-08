#ifndef LAB_2_MONEY_H
#define LAB_2_MONEY_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include "Currency.h"

class Money {
private:
    static const size_t MAX_BALANCE = 15;
    unsigned char balance[MAX_BALANCE];
    size_t size;
    Currency currency_type;

    void delete_element(size_t index);
    bool parse_amount(const std::string& amount, long long& total_cents) const;
    long long get_total_cents() const;
    void set_total_cents(long long total_cents);

public:
    Money(const std::string& amount = "0.00", Currency currency = Currency::RUB);
    Money(Currency currency);
    std::string check_balance() const;
    void convert_to(Currency target_currency);

    void add(const std::string& amount);
    void withdraw(const std::string& amount);
};

#endif
