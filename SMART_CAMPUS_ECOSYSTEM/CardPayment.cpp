#include "CardPayment.h"
#include <exception>
#include <cctype>

class InvalidCardNumber : public exception {
public:

    const char* what() const noexcept override {
        return "Card number must be exactly 16 digits!";
    }
};

class InvalidCardFormat : public exception {
public:

    const char* what() const noexcept override {
        return "Card must contain digits only!";
    }
};

CardPayment::CardPayment(string cardNumber) {
    this->cardNumber = cardNumber;
}

void CardPayment::validateCard() const {

    if (cardNumber.length() != 16) {
        throw InvalidCardNumber();
    }

    for (char c : cardNumber) {

        if (!isdigit(c)) {
            throw InvalidCardFormat();
        }
    }
}

void CardPayment::pay(double amount) {

    validateCard();

    cout << "Paid " << amount << " using Card" << endl;
}