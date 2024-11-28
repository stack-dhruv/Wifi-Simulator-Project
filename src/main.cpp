#include "WiFi4Simulator.h"
#include <iostream>

int main() {
    int num_users;
    double transmission_time = 0.0614; // 1 KB packet transmission time

    std::cout << "Enter the number of users: ";
    std::cin >> num_users;

    WiFi4Simulator sim(num_users);
    sim.runSimulation(transmission_time);

    return 0;
}
