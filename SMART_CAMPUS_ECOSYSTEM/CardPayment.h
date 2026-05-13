#pragma once
#include "Payment.h"
#include <string>

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string cardNumber);

    void validateCard() const;

    void pay(double amount) override;
};