#include "CardPayment.h"
#include <stdexcept>
#include <cctype>

CardPayment::CardPayment(string cardNumber) {
    this->cardNumber = cardNumber;
}

void CardPayment::validateCard() const {

    if (cardNumber.length() != 16) {
        throw invalid_argument("Invalid card number");
    }

    for (char c : cardNumber) {

        if (!isdigit(c)) {
            throw invalid_argument("Card must contain digits only");
        }
    }
}

void CardPayment::pay(double amount) {

    validateCard();

    cout << "Paid " << amount << " using Card" << endl;
}