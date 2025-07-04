#include "Wifi4Simulator.h"
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "DisplayParser.h"

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
    DisplayParser<int> displayInt;

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
