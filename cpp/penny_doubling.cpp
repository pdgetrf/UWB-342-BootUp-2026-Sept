#include <iomanip>
#include <iostream>

int main() {
    long double pennies = 1.0L; // keep the amount in pennies while it doubles

    for (int day = 0; day <= 30; ++day) {
        std::cout << "Day " << std::setw(2) << day
                  << ": $" << std::fixed << std::setprecision(2)
                  << static_cast<double>(pennies / 100.0L) << '\n'; // pennies to dollars
        pennies *= 2.0L;
    }

    const long double doubledChoice = pennies / 2.0L / 100.0L; // last displayed amount
    std::cout << "Final doubled amount: $"
              << static_cast<double>(doubledChoice) << '\n';
    std::cout << (doubledChoice > 1000000.0L
                      ? "Choose the doubling penny.\n"
                      : "Choose the $1,000,000.\n");
}
