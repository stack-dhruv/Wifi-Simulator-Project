#include "Wifi4Simulator.h"
#include <iostream>
using namespace std;

void printMenu() {
    cout << "\n| --------------------------\n";
    cout << "| WiFi 4 Simulator 🖧\n";
    cout << "| --------------------------\n";
    cout << "| 1. Run WiFi 4 Simulation 🚀\n";
    cout << "| 0. Exit ❌\n";
    cout << "--------------------------\n";
}

int main() {
    int choice;
    int num_users;
    double transmission_time = 0.0614; // 1 KB packet transmission time

    while (true) {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the number of users: ";
            cin >> num_users;

            WiFi4Simulator sim(num_users);
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
