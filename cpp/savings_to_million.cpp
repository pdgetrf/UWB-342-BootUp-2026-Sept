#include <iomanip>
#include <iostream>

int main() {
    const double target = 1000000.0;
    const double initialDeposit = 500.0;
    const double monthlyContribution = 500.0;
    const double annualInterestRate = 7.0;
    double invested = initialDeposit;
    double total = initialDeposit;
    int years = 0;

    std::cout << std::fixed << std::setprecision(2);

    for (; total < target; ++years) {
        total = total * (1.0 + annualInterestRate / 100.0)
              + monthlyContribution * 12;
        invested += monthlyContribution * 12;

        std::cout << "After year " << years + 1
                  << ": value = $" << total
                  << " vs. invested = $" << invested << '\n';
    }

    std::cout << "\nIt takes " << years << " years to reach $1,000,000.\n";
    std::cout << "Final value: $" << total << '\n';
    std::cout << "Total invested: $" << invested << '\n';

    if (total >= target) {
        std::cout << "Goal reached: $1M!\n";
    }
}
