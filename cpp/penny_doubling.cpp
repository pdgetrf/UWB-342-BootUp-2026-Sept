#include <iostream>

int main() {
    int pennies = 1; // Day 1 starts with one penny

    // Day 1 is already counted, so double on Days 2 through 30.
    for (int day = 2; day <= 30; ++day) {
        pennies *= 2; // amount on this day

        // Compare pennies directly: 100,000,000 pennies equals $1,000,000.
        if (pennies >= 100000000) {
            std::cout << "Day " << day << ": " << pennies
                      << " pennies, more than $1M!\n";
            break; // We found the first day, so no later days are needed.
        }
    }
}
