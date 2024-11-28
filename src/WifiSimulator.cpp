#include "WiFiSimulator.h"
#include <iostream>
#include <numeric>
#include <iomanip>

WiFiSimulator::WiFiSimulator(int num_users) : ap(num_users), simulation_time(0.0) {}

void WiFiSimulator::calculateMetrics() {
    int total_packets = 0;
    double total_latency = 0.0;
    double max_latency = 0.0;

    auto& users = ap.getUsers();
    for (const auto& user : users) {
        total_packets += user.getPacketsSent();
        total_latency += user.getTotalLatency();
        max_latency = std::max(max_latency, user.getTotalLatency());
    }

    double throughput = (total_packets * 8.0 * 1024) / (simulation_time / 1000.0); // Mbps
    double avg_latency = total_latency / total_packets;

    // Display metrics
    std::cout << "\nSimulation Metrics:\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Throughput: " << std::fixed << std::setprecision(2) << throughput << " Mbps\n";
    std::cout << "Average Latency: " << avg_latency << " ms\n";
    std::cout << "Maximum Latency: " << max_latency << " ms\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Gantt Chart:\n";

    for (const auto& user : users) {
        std::cout << "User " << user.getId() << " completed at " << user.getTotalLatency() << " ms.\n";
    }

    std::cout << "Total Simulation Time: " << simulation_time << " ms\n";
}
