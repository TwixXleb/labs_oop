#include "../../include/Money.h"

void Money::delete_element(size_t index) {
    if(index >= size) throw std::out_of_range("Index is out of the array range");

    for(size_t i = index; i < size - 1; i++) {
        balance[i] = balance[i + 1];
    }

    balance[size - 1] = 0;
    size--;
}

void Money::deleting_zeroes() {
    if(size <= 2) return;

    size_t last_int_pos = size - 1;

    while(last_int_pos >= 2 && balance[last_int_pos] == 0) {
        delete_element(last_int_pos);
        if(last_int_pos == 2) break;
        last_int_pos--;
    }

    if(size == 2) balance[size++] = 0;
}

bool Money::parse_amount(const std::string& amount, long long& total_cents) const {
    size_t pointer_pos = amount.find('.');
    if(pointer_pos == std::string::npos) pointer_pos = amount.find(',');

    std::string int_amount = amount.substr(0, pointer_pos);
    std::string frac_amount = (pointer_pos != std::string::npos) ? amount.substr(pointer_pos + 1) : "00";

    if(frac_amount.length() < 2) {
        frac_amount += std::string(2 - frac_amount.length(), '0');
    } else if(frac_amount.length() > 2) {
        frac_amount = frac_amount.substr(0, 2);
    }

    try {
        long long integer_part = std::stoll(int_amount);
        long long fractional_part = std::stoll(frac_amount);
        total_cents = integer_part * 100 + fractional_part;
    } catch(...) {
        return false;
    }

    return true;
}

long long Money::get_total_cents() const {
    long long total = 0;
    for(size_t i = 2; i < size; ++i) {
        total = total * 10 + balance[i];
    }
    total = total * 100 + balance[1] * 10 + balance[0];
    return total;
}

void Money::set_total_cents(long long total_cents) {
    balance[0] = total_cents % 10;
    balance[1] = (total_cents / 10) % 10;
    long long integer = total_cents / 100;
    size = 2;
    while(integer > 0 && size < MAX_BALANCE) {
        balance[size++] = integer % 10;
        integer /= 10;
    }
    deleting_zeroes();
}

Money::Money(const std::string& amount, Currency currency) : size(2), currency_type(currency) {
    balance[0] = 0;
    balance[1] = 0;
    for(size_t i = 2; i < MAX_BALANCE; ++i) balance[i] = 0;

    long long total_cents = 0;
    if(!parse_amount(amount, total_cents)) {
        throw std::invalid_argument("Unsupported format.");
    }

    set_total_cents(total_cents);
}

Money::Money(Currency currency) : size(2), currency_type(currency) {
    balance[0] = 0;
    balance[1] = 0;
    for(size_t i = 2; i < MAX_BALANCE; ++i) balance[i] = 0;
}

void Money::check_balance() const {
    std::string integer_part = "";
    long long total_cents = get_total_cents();
    long long integer = total_cents / 100;

    if(integer == 0) {
        integer_part = "0";
    } else {
        std::string temp = "";
        while(integer > 0) {
            temp += std::to_string(integer % 10);
            integer /= 10;
        }

        for(int i = temp.length() - 1, count = 0; i >=0; --i, ++count) {
            integer_part += temp[i];
            if((count +1) %3 ==0 && i !=0) integer_part += " ";
        }
    }

    std::string fraction_part = std::to_string(balance[1]) + std::to_string(balance[0]);

    std::string currency_str;
    switch(currency_type) {
        case Currency::RUB: currency_str = "RUB"; break;
        case Currency::USD: currency_str = "USD"; break;
        case Currency::EUR: currency_str = "EUR"; break;
        case Currency::GBP: currency_str = "GBP"; break;
        case Currency::JPY: currency_str = "JPY"; break;
        case Currency::CNY: currency_str = "CNY"; break;
        default: currency_str = "UNKNOWN";
    }

    std::string str_balance = integer_part + "." + fraction_part + " " + currency_str;
    return str_balance;
}

void Money::convert_to(Currency target_currency) {
    if (currency_type == target_currency) return;

    std::unordered_map<Currency, double> rates_to_usd = {
            {Currency::USD, 1.0},
            {Currency::RUB, 92.50},
            {Currency::EUR, 0.90},
            {Currency::GBP, 0.75},
            {Currency::JPY, 144.69},
            {Currency::CNY, 7.03}
    };

    double total_usd = 0.0;
    long long current_total_cents = get_total_cents();
    total_usd = static_cast<double>(current_total_cents) / 100.0;

    if (currency_type != Currency::USD) {
        auto it = rates_to_usd.find(currency_type);
        if(it == rates_to_usd.end()) throw std::invalid_argument("Unsupported source currency.");
        total_usd /= it->second;
    }

    auto it_target = rates_to_usd.find(target_currency);
    if(it_target == rates_to_usd.end()) throw std::invalid_argument("Unsupported target currency.");
    double converted_amount = total_usd * it_target->second;

    long long new_total_cents = static_cast<long long>(round(converted_amount * 100));
    set_total_cents(new_total_cents);

    currency_type = target_currency;
}

void Money::add(const std::string& amount) {
    long long add_cents = 0;
    if(!parse_amount(amount, add_cents)) {
        throw std::invalid_argument("Unsupported format.");
    }

    long long current_cents = get_total_cents();
    long long new_cents = current_cents + add_cents;

    set_total_cents(new_cents);
}

void Money::withdraw(const std::string& amount) {
    long long withdraw_cents = 0;
    if(!parse_amount(amount, withdraw_cents)) {
        throw std::invalid_argument("Unsupported format.");
    }

    long long current_cents = get_total_cents();
    if(withdraw_cents > current_cents) {
        throw std::invalid_argument("Not enough money. Haha you little brokey.");
    }

    long long new_cents = current_cents - withdraw_cents;
    set_total_cents(new_cents);
}