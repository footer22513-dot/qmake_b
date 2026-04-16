#ifndef CREDITCALC_H
#define CREDITCALC_H

#include "bankrecord.h"

class CreditCalculator {
public:
    // Расчёт конечной суммы по простой формуле (для учебной версии)
    static double calculateSimple(double startSum, double ratePercent, int days);

    // Аннуитетный платёж (равные платежи)
    static double calculateAnnuityPayment(double principal, double monthlyRate, int months);

    // Дифференцированный платёж (убывающие платежи)
    static double calculateDiffPayment(double principal, double monthlyRate, int month, int totalMonths);

    // Штраф за просрочку
    static double calculatePenalty(double remainingSum, double penaltyPercent, int daysLate);

    // Перерасчёт при досрочном погашении
    static double recalculateAfterEarlyPayment(BankRecord& record, double paymentAmount);
};

#endif // CREDITCALC_H
