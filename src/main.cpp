#include "Wifi4Simulator.h"
#include "Wifi5Simulator.h"
#include <iostream>
using namespace std;

void printMenu() {
    cout << "\n| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n";
    cout << "| \t WiFi 4/5 Simulator    |\n";
    cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n";
    cout << "| 1. Run WiFi 4 Simulation     |\n";
    cout << "| 2. Run WiFi 5 Simulation     |\n";
    cout << "| 0. ❌ Exit \n";
    cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n";
}

int main() {
    int choice;
    int num_users;
    int num_packets_per_user;
    double transmission_time = 0.0614; // 1 KB packet transmission time

    while (true) {
        printMenu();
        cout << "| Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "↦ Enter the number of users: ";
            cin >> num_users;

            WiFi4Simulator sim(num_users);
            sim.runSimulation(transmission_time);
        } else if (choice == 2) {
            cout << "Enter the number of users: ";
            cin >> num_users;
            
            cout << "Enter number of packets per user: ";
            cin >> num_packets_per_user;

            WiFi5Simulator sim(num_users, num_packets_per_user);
            sim.runSimulation(transmission_time);
        } else if (choice == 0) {
            cout << "Exiting... ❌\n";
            break;
        } else {
            cout << "Invalid choice! Please try again. ⚠️\n";
        }
    }

    return 0;
}