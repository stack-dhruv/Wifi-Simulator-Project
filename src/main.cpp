#include "Wifi4Simulator.h"
#include "Wifi5Simulator.h"
#include "Wifi6Simulator.h"
#include <iostream>
#include "DisplayParser.h"

using namespace std;

// Function to validate integer input
bool validateIntInput(int& input, const string& prompt) {
    while (true) {
        cout << prompt;
        if (cin >> input && input > 0) {
            return true;  // valid input
        } else {
            cout << "Invalid input! Please enter a positive integer.\n";
            cin.clear();  // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
        }
    }
}

// Function to validate double input (e.g., for transmission time)
bool validateDoubleInput(double& input, const string& prompt) {
    while (true) {
        cout << prompt;
        if (cin >> input && input > 0) {
            return true;  // valid input
        } else {
            cout << "Invalid input! Please enter a positive number.\n";
            cin.clear();  // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
        }
    }
}

void printMenu() {
    DisplayParser<int> displayInt;         // Integer display parser
    DisplayParser<std::string> displayStr; // String display parser

    std::string message = "Wifi 4/5/6 Simulator";
    int width = message.length() + 2; // +2 for the borders

    displayStr.display("+");
    for (int i = 0; i < width; ++i)
        displayStr.display("-");

    displayStr.display("+");
    std::cout << std::endl;
    displayStr.display("| ");
    displayStr.display(message);
    displayStr.display(" |\n");

    displayStr.display("+");

    for (int i = 0; i < width; ++i)
        displayStr.display("-");
    displayStr.display("+");
    std::cout << std::endl;
    displayStr.display("| 1. Run WiFi 4 Simulation     |\n");
    displayStr.display("| 2. Run WiFi 5 Simulation     |\n");
    displayStr.display("| 3. Run WiFi 6 Simulation     |\n");
    displayStr.display("| 0. ❌ Exit\n");
    displayStr.display("| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");
}

int main()
{
    int choice;
    int num_users;
    int num_packets_per_user;
    double transmission_time = 0.0614; // 1 KB packet transmission time

    while (true)
    {
        printMenu();
        cout << "| Enter your choice: ";
        cin >> choice;

        // Validate the main menu choice
        if (choice < 0 || choice > 3) {
            cout << "Invalid choice! Please try again. ⚠️\n";
            continue;
        }

        if (choice == 1)
        {
            std::string message = "Wifi 4 Simulator";
            int width = message.length() + 2; // +2 for the borders

            std::cout << "+";
            for (int i = 0; i < width; ++i)
                std::cout << "-";
            std::cout << "+" << std::endl;

            std::cout << "| " << message << " |" << std::endl;

            std::cout << "+";
            for (int i = 0; i < width; ++i)
                std::cout << "-";
            std::cout << "+" << std::endl;

            // Validate the number of users
            if (!validateIntInput(num_users, "↦ Enter the number of users: "))
                continue;

            WiFi4Simulator sim(num_users);
            sim.runSimulation(transmission_time);
        }
        else if (choice == 2)
        {
            std::string message = "Wifi 5 Simulator";
            int width = message.length() + 2; // +2 for the borders

            std::cout << "+";
            for (int i = 0; i < width; ++i)
                std::cout << "-";
            std::cout << "+" << std::endl;

            std::cout << "| " << message << " |" << std::endl;

            std::cout << "+";
            for (int i = 0; i < width; ++i)
                std::cout << "-";
            std::cout << "+" << std::endl;

            // Validate the number of users and packets per user
            if (!validateIntInput(num_users, "Enter the number of users: "))
                continue;

            if (!validateIntInput(num_packets_per_user, "Enter number of packets per user: "))
                continue;

            WiFi5Simulator sim(num_users, num_packets_per_user);
            sim.runSimulation(transmission_time);
        }
        else if (choice == 3)
        {
            std::string message = "Wifi 6 Simulator";
            int width = message.length() + 2; // +2 for the borders

            std::cout << "+";
            for (int i = 0; i < width; ++i)
                std::cout << "-";
            std::cout << "+" << std::endl;

            std::cout << "| " << message << " |" << std::endl;

            std::cout << "+";
            for (int i = 0; i < width; ++i)
                std::cout << "-";
            std::cout << "+" << std::endl;

            // Validate the number of users for WiFi 6
            if (!validateIntInput(num_users, "Enter the number of users for WiFi 6 Simulation: "))
                continue;

            WiFi6Simulator sim6(num_users); // Default bandwidth of 20 MHz
            sim6.runSimulation(transmission_time);
            break;
        }
        else if (choice == 0)
        {
            cout << "Exiting... ❌\n";
            break;
        }
    }

    return 0;
}
