#include "creditcalc.h"
#include <QDate>
#include <cmath>

double CreditCalculator::calculateSimple(double startSum, double ratePercent, int days) {
    return startSum * (1.0 + ratePercent * days / 36500.0);
}

double CreditCalculator::calculateAnnuityPayment(double principal, double monthlyRate, int months) {
    if (monthlyRate == 0) return principal / months;
    double factor = pow(1 + monthlyRate, months);
    return principal * monthlyRate * factor / (factor - 1);
}

double CreditCalculator::calculateDiffPayment(double principal, double monthlyRate, int month, int totalMonths) {
    double principalPart = principal / totalMonths;
    double interestPart = (principal - principalPart * (month - 1)) * monthlyRate;
    return principalPart + interestPart;
}

double CreditCalculator::calculatePenalty(double remainingSum, double penaltyPercent, int daysLate) {
    return remainingSum * penaltyPercent * daysLate / 36500.0;
}

double CreditCalculator::recalculateAfterEarlyPayment(BankRecord& record, double paymentAmount) {
    if (paymentAmount >= record.endSum) {
        record.endSum = 0;
        return 0;
    }
    // Упрощённый перерасчёт: уменьшаем конечную сумму пропорционально
    record.endSum -= paymentAmount;
    return record.endSum;
}
