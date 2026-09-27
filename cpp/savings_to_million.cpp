#include <iomanip>
#include <iostream>

int main() {
    const double target = 1000000.0;
    double balance = 1000.0;
    const double monthlyDeposit = 500.0;
    const double annualRate = 0.08;
    int months = 0;

    while (balance < target) {
        balance += monthlyDeposit;
        balance *= 1.0 + annualRate / 12.0;
        ++months;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance: $" << balance << '\n';
    std::cout << "Months: " << months << '\n';
    std::cout << "Years: " << months / 12.0 << '\n';
}
