# Project

## Question 1

**(Q)** WiFi 4 Communication WiFi communication happens via a single access point and a set of users. A single transmission consists of sniffing of the channel, and transmission of the data packet if the channel is free. If the channel is not free, the transmission is deferred by a random unit of time (subject to a maximum limit of backoff time), followed by repetition of the above process. Simulate this above process of transmission to find out the throughput, average and maximum latency if a total of (i) 1 user and 1 AP is communicating, (ii) 10 users and 1 AP is communicating, and (iii) 100 users and 1 AP are communicating. You may assume that a total of 20 MHz being used as bandwidth, modulation of 256-QAM and coding rate of 5/6 is used for transmission and that each packet has size of 1 KB. You may ignore the other periods of time wastage such as DIFS, CIFS and guard intervals.

Let's start fresh, start coding the structure for the below things. Design of class structure, modeling of access point, user, packet, frequency channel is a must.

1. Data Rate (R):
    - The data rate in WiFi is determined using the formula: $R=Bandwidth×log_2(M)×Coding Rate$
    - $R = (20 * 10^6) * 8 * (5/6) = 133.33 \text{Mbps}$

2. Packet Transmission Time (T):
    - $T = Data Rate (R) / Packet Size (in bits)$
    - $T = (8192)/(133.33 * 10^6) \approx 61.44 \text{ }\mu s$

3. Throughput (S):
    - Throughput is defined as the total data successfully transmitted divided by the total simulation time: $S = \text{Total data transmitted (in bits)}/\text{Simulation Time}$
    - For 𝑛 users, collisions and backoff delays affect throughput. The more users, the higher the likelihood of collisions, which reduces throughput.

4. Average Latency:
    - Average latency is the mean time a packet takes from its first transmission attempt to its successful transmission. It includes:
        - Backoff delays due to collisions.
        - Actual transmission time.

5. Maximum Latency:
    - Maximum latency is the longest delay experienced by any packet, which depends on:
        - Maximum backoff time.
        - Number of retries before successful transmission.

## References

- `.gitignore` file gist taken from: <https://gist.github.com/Yousha/3830712334ac30a90eb6041b932b68d7>
- <https://www.perplexity.ai/>: LLM used for research about the terms and wireless networks
- Bandwidth vs Throughput vs Latency, What is the Difference in Computer Networking?-QSFPTEK. (n.d.). <https://www.qsfptek.com/qt-news/bandwidth-vs-throughput-vs-latency-what-is-the-difference-in-computer-networking.html>
- Latency vs Throughput vs Bandwidth: Unraveling the Complexities of Network Speed. (2024, October 31). Kentik. <https://www.kentik.com/kentipedia/latency-vs-throughput-vs-bandwidth/>
- Darah, D. (2022, August 25). Network bandwidth vs. throughput: What’s the difference? Search Networking. <https://www.techtarget.com/searchnetworking/feature/Network-bandwidth-vs-throughput-Whats-the-difference>
- GeeksforGeeks. (2023, June 2). Performance of a network. GeeksforGeeks. <https://www.geeksforgeeks.org/performance-of-a-network/>
- Magnat. (2024, July 11). Bandwidth, speed, latency and throughput. V500 Systems. <https://www.v500.com/bandwidth/>
- Contributor, S. (2022, February 17). Network Latency vs. Throughput vs. Bandwidth Guide - DNSstuff. Software Reviews, Opinions, and Tips - DNSstuff. <https://www.dnsstuff.com/latency-throughput-bandwidth>
- Writer, T. P. S. C. (2020, March 19). What are bandwidth, latency and throughput, and what is right for your business? Ecessa, a Product of OneNet Global. <https://www.ecessa.com/blog/what-are-bandwidth-latency-and-throughput-and-what-is-right-for-your-business/>

## ASCII Art

Ignore this, I did this for fun...

```sh
############################################################################
# $$\      $$\ $$$$$$$$\  $$$$$$\  $$\   $$\  $$$$$$\   $$$$$$\   $$$$$$\  #
# $$$\    $$$ |\__$$  __|$$  __$$\ $$ |  $$ |$$$ __$$\ $$ ___$$\ $$  __$$\ #
# $$$$\  $$$$ |   $$ |   \__/  $$ |$$ |  $$ |$$$$\ $$ |\_/   $$ |\__/  $$ |#
# $$\$$\$$ $$ |   $$ |    $$$$$$  |$$$$$$$$ |$$\$$\$$ |  $$$$$ /  $$$$$$  |#
# $$ \$$$  $$ |   $$ |   $$  ____/ \_____$$ |$$ \$$$$ |  \___$$\ $$  ____/ #
# $$ |\$  /$$ |   $$ |   $$ |            $$ |$$ |\$$$ |$$\   $$ |$$ |      #
# $$ | \_/ $$ |   $$ |   $$$$$$$$\       $$ |\$$$$$$  /\$$$$$$  |$$$$$$$$\ #
# \__|     \__|   \__|   \________|      \__| \______/  \______/ \________|#
############################################################################
```

## Grading criteria

Grading criteria:

- Design of class structure, modeling of access point, user, packet, frequency channel is a must.
- Proper functioning of each class
- Use of appropriate data structure
- Modeling of CSMA/CA
- Computation of throughput, average and maximum latency in each case
- Additional cases of code cleanliness, such as use of Makefile (both for building library and test program), git commits and proper function/variable names.
- Extra functionality based on the student’s understanding.
- The C++ program sources. Templates and exception handling must be utilized.
- Makefile to compile the sources and generate the running binary for the shell. The Makefile should generate two versions of the binary – one for debugging and another for optimized execution.


---

The below is the codebase we've created so far. And now we want to simulate the Wifi5Simulator based on this question: WiFi 5 Communication WiFi 5 allowed a new type of communication, using multi-user MIMO. In this case, parallel transmission was allowed. However, parallel communication could be done only after (i) a single broadcast packet was sent by the access point, and (ii) each user would sequentially send their channel state information, which would be a single packet of 200 bytes. Once this was done, each user could communicate in parallel for a total of 15 ms. After 15 ms, the above process is repeated. Find out the throughput, average and maximum latency in each of the above cases once again, assuming round-robin scheduling of the users.

// Simulation parameters
double currentTime = 0.0;
double broadcastTime = 0.0614;          // 1 KB broadcast packet transmission time (ms)
double csiTime = 0.012;                 // CSI packet transmission time (ms)
double packetTransmissionTime = 0.0614; // Data packet transmission time (ms)
double timeSlot = 15.0;                 // Time slot for parallel communication (ms)

int totalPackets = numUsers * numPacketsPerUser; // Total packets to be sent
int packetsSent = 0;                             // Count of sent packets

AccessPoint.h
```
#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "User.h"
#include "FrequencyChannel.h"
#include <vector>

class AccessPoint {
private:
    std::vector<User> users;
    FrequencyChannel channel;

public:
    AccessPoint(int num_users);

    std::vector<User>& getUsers();
    FrequencyChannel& getChannel();
};

#endif

```

FrequencyChannel.h
```
#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

class FrequencyChannel {
private:
    bool busy;

public:
    FrequencyChannel();

    bool isBusy() const;
    void occupy();
    void release();
};

#endif

```

Packet.h
```
#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int size; // Packet size in KB
    double transmission_time; // Time required to transmit this packet (in ms)

public:
    Packet(int size, double data_rate);
    int getSize() const;
    double getTransmissionTime() const;
};

#endif

```

User.h
```
#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <iostream>

class User {
private:
    int id;               // User ID
    int packets_sent;     // Total packets sent by the user
    double total_latency; // Total latency experienced by the user
    double next_attempt;  // Next attempt time (in ms)

public:
    User(int id);

    int getId() const;
    int getPacketsSent() const;
    double getTotalLatency() const;
    double getNextAttempt() const;

    void incrementPacketsSent();
    void addLatency(double latency);
    void setNextAttempt(double time);

    int randomBackoff() const; // Returns random backoff time in milliseconds
};

#endif

```

Wifi4Simulator.h
```
#ifndef WIFI4SIMULATOR_H
#define WIFI4SIMULATOR_H

#include "WifiSimulator.h"

class WiFi4Simulator : public WiFiSimulator {
public:
    WiFi4Simulator(int num_users);

    void runSimulation(double transmission_time) override;
    void calculateMetrics();
};

#endif

```

WifiSimulator.h
```
#ifndef WIFISIMULATOR_H
#define WIFISIMULATOR_H

#include "AccessPoint.h"

class WiFiSimulator {
protected:
    AccessPoint ap;
    double simulation_time;

public:
    WiFiSimulator(int num_users);

    virtual void runSimulation(double transmission_time) = 0; // Pure virtual method
    virtual ~WiFiSimulator() = default;
    void calculateMetrics();
};

#endif

```

WifiSimulator.cpp
```
#include "Wifi4Simulator.h"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>

WiFi4Simulator::WiFi4Simulator(int num_users) : WiFiSimulator(num_users) {}

void WiFi4Simulator::runSimulation(double transmission_time) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random generator
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> events;

    auto& users = ap.getUsers();
    auto& channel = ap.getChannel();

    // Initialize simulation and backoff times
    for (auto& user : users) {
        double initial_backoff = (user.getId() == 0) ? 0.0 : user.randomBackoff();
        events.push({initial_backoff, user.getId()});
        user.setNextAttempt(initial_backoff);
    }

    std::cout << "-----" << std::endl;

    // Run simulation loop
    while (!events.empty()) {
        auto [time, user_id] = events.top();
        events.pop();

        User& user = users[user_id];

        // Wait until the user's next attempt
        if (time < user.getNextAttempt()) continue;

        if (!channel.isBusy()) {
            // Occupy the channel and transmit
            channel.occupy();
            double start_time = std::max(simulation_time, time);
            simulation_time = start_time + transmission_time;

            user.incrementPacketsSent();
            user.addLatency(simulation_time);

            std::cout << "✅ User " << user.getId() << " transmitted at time " << simulation_time << " ms.\n";

            channel.release();
        } else {
            // Channel busy, apply backoff
            double backoff = user.randomBackoff();
            double retry_time = time + backoff;

            std::cout << "⛔️ User " << user.getId() << " backoff for " << backoff << " ms. Retry at time " << retry_time << " ms.\n";

            user.setNextAttempt(retry_time);
            events.push({retry_time, user.getId()});
        }

        // Conflict Resolution: Check for conflict in same backoff times
        while (!events.empty() && events.top().first == time) {
            auto [conflict_time, conflict_user_id] = events.top();
            if (conflict_time == time) {
                // Conflict: Two users have the same backoff time
                User& conflict_user = users[conflict_user_id];
                double new_backoff = conflict_user.randomBackoff(); // Generate new backoff for the second user
                double new_retry_time = time + new_backoff;

                std::cout << "⛔️ User " << conflict_user.getId() << " has the same backoff as User " << user.getId() 
                          << " | New BackOff: " << new_backoff 
                          << ", (Scheduled next attempt: " << new_retry_time << "ms)\n";

                conflict_user.setNextAttempt(new_retry_time);
                events.push({new_retry_time, conflict_user.getId()});
                events.pop(); // Remove the conflicting user from the queue temporarily
            }
        }
    }

    // Display metrics after simulation
    calculateMetrics();
}

void WiFi4Simulator::calculateMetrics() {
    int total_packets = 0;
    double total_latency = 0.0;
    double max_latency = 0.0;

    auto& users = ap.getUsers();
    for (const auto& user : users) {
        total_packets += user.getPacketsSent();
        total_latency += user.getTotalLatency();
        max_latency = std::max(max_latency, user.getTotalLatency());
    }

    // Throughput calculation considering maximum data rate (133.33 Mbps)
    double throughput = (total_packets * 8.0 * 1024) / (simulation_time * 1000); // Mbps

    double avg_latency = total_packets > 0 ? total_latency / total_packets : 0.0;

    // Display metrics
    std::cout << "\n| Simulation Metrics:\n";
    std::cout << "| -----------------------------------\n";
    std::cout << "| Throughput: " << std::fixed << std::setprecision(6) << throughput << " Mbps\n";
    std::cout << "| Average Latency: " << avg_latency << " ms\n";
    std::cout << "| Maximum Latency: " << max_latency << " ms\n";
    std::cout << "| -----------------------------------\n";
    std::cout << "| Total Simulation Time: " << simulation_time << " ms\n";
    std::cout << "| -----------------------------------\n";
}

```

Wifi4Simulator.cpp
```
#include "Wifi4Simulator.h"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>

WiFi4Simulator::WiFi4Simulator(int num_users) : WiFiSimulator(num_users) {}

void WiFi4Simulator::runSimulation(double transmission_time) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random generator
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> events;

    auto& users = ap.getUsers();
    auto& channel = ap.getChannel();

    // Initialize simulation and backoff times
    for (auto& user : users) {
        double initial_backoff = (user.getId() == 0) ? 0.0 : user.randomBackoff();
        events.push({initial_backoff, user.getId()});
        user.setNextAttempt(initial_backoff);
    }

    std::cout << "-----" << std::endl;

    // Run simulation loop
    while (!events.empty()) {
        auto [time, user_id] = events.top();
        events.pop();

        User& user = users[user_id];

        // Wait until the user's next attempt
        if (time < user.getNextAttempt()) continue;

        if (!channel.isBusy()) {
            // Occupy the channel and transmit
            channel.occupy();
            double start_time = std::max(simulation_time, time);
            simulation_time = start_time + transmission_time;

            user.incrementPacketsSent();
            user.addLatency(simulation_time);

            std::cout << "✅ User " << user.getId() << " transmitted at time " << simulation_time << " ms.\n";

            channel.release();
        } else {
            // Channel busy, apply backoff
            double backoff = user.randomBackoff();
            double retry_time = time + backoff;

            std::cout << "⛔️ User " << user.getId() << " backoff for " << backoff << " ms. Retry at time " << retry_time << " ms.\n";

            user.setNextAttempt(retry_time);
            events.push({retry_time, user.getId()});
        }

        // Conflict Resolution: Check for conflict in same backoff times
        while (!events.empty() && events.top().first == time) {
            auto [conflict_time, conflict_user_id] = events.top();
            if (conflict_time == time) {
                // Conflict: Two users have the same backoff time
                User& conflict_user = users[conflict_user_id];
                double new_backoff = conflict_user.randomBackoff(); // Generate new backoff for the second user
                double new_retry_time = time + new_backoff;

                std::cout << "⛔️ User " << conflict_user.getId() << " has the same backoff as User " << user.getId() 
                          << " | New BackOff: " << new_backoff 
                          << ", (Scheduled next attempt: " << new_retry_time << "ms)\n";

                conflict_user.setNextAttempt(new_retry_time);
                events.push({new_retry_time, conflict_user.getId()});
                events.pop(); // Remove the conflicting user from the queue temporarily
            }
        }
    }

    // Display metrics after simulation
    calculateMetrics();
}

void WiFi4Simulator::calculateMetrics() {
    int total_packets = 0;
    double total_latency = 0.0;
    double max_latency = 0.0;

    auto& users = ap.getUsers();
    for (const auto& user : users) {
        total_packets += user.getPacketsSent();
        total_latency += user.getTotalLatency();
        max_latency = std::max(max_latency, user.getTotalLatency());
    }

    // Throughput calculation considering maximum data rate (133.33 Mbps)
    double throughput = (total_packets * 8.0 * 1024) / (simulation_time * 1000); // Mbps

    double avg_latency = total_packets > 0 ? total_latency / total_packets : 0.0;

    // Display metrics
    std::cout << "\n| Simulation Metrics:\n";
    std::cout << "| -----------------------------------\n";
    std::cout << "| Throughput: " << std::fixed << std::setprecision(6) << throughput << " Mbps\n";
    std::cout << "| Average Latency: " << avg_latency << " ms\n";
    std::cout << "| Maximum Latency: " << max_latency << " ms\n";
    std::cout << "| -----------------------------------\n";
    std::cout << "| Total Simulation Time: " << simulation_time << " ms\n";
    std::cout << "| -----------------------------------\n";
}

```

User.cpp
```
#include "Packet.h"

Packet::Packet(int size, double data_rate)
    : size(size), transmission_time((size * 8.0 * 1024) / (data_rate * 1e6)) {}

int Packet::getSize() const {
    return size;
}

double Packet::getTransmissionTime() const {
    return transmission_time;
}

```

Packet.cpp
```
#include "Packet.h"

Packet::Packet(int size, double data_rate)
    : size(size), transmission_time((size * 8.0 * 1024) / (data_rate * 1e6)) {}

int Packet::getSize() const {
    return size;
}

double Packet::getTransmissionTime() const {
    return transmission_time;
}

```

main.cpp
```
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

```

FrequencyChannel.cpp
```
#include "FrequencyChannel.h"

FrequencyChannel::FrequencyChannel() : busy(false) {}

bool FrequencyChannel::isBusy() const { return busy; }
void FrequencyChannel::occupy() { busy = true; }
void FrequencyChannel::release() { busy = false; }

```

AccessPoint.cpp
```
#include "AccessPoint.h"

AccessPoint::AccessPoint(int num_users) {
    for (int i = 0; i < num_users; ++i) {
        users.emplace_back(i);
    }
}

std::vector<User>& AccessPoint::getUsers() { return users; }
FrequencyChannel& AccessPoint::getChannel() { return channel; }

```

The logic behind the Wifi5Simulator is: 
double currentTime = 0.0;
double broadcastTime = 0.0614;          // 1 KB broadcast packet transmission time (ms)
double csiTime = 0.012;                 // CSI packet transmission time (ms)
double packetTransmissionTime = 0.0614; // Data packet transmission time (ms)
double timeSlot = 15.0;                 // Time slot for parallel communication (ms)

int totalPackets = numUsers * numPacketsPerUser; // Total packets to be sent
int packetsSent = 0;

Now loop through the totalPackets till all the packets are exhausted. In 15ms time slot we can send total (15*R)/N, after each 15ms cycle, connection procedure will be trigerred and it'll take N*csiTime+broadcastTime to establish 15ms window. So total simulation time required will end up to $= \text{Number of loops} * ({(N*csiTime)+broadcastTime})$. Now you can calculate the average throughput by totalPackets/total_time, and average latency and maximum latency in similar way. If you can't use the existing class functionality to achive this then directly create new methods over here in the class.

=> Just Create the Wifi5Simulator.h and Wifi5Simulator.cpp -- Create a makefile for building the binaries Wifi5Simulator and Wifi4Simulator.