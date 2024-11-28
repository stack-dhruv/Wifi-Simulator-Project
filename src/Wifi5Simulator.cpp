#include "Wifi5Simulator.h"
#include <iostream>
#include <iomanip>
#include <cmath>

WiFi5Simulator::WiFi5Simulator(int num_users, int packets_per_user) 
    : WiFiSimulator(num_users), 
      broadcastTime(0.0614),      // 1 KB broadcast packet transmission time (ms)
      csiTime(0.012),             // CSI packet transmission time (ms)
      packetTransmissionTime(0.0614), // Data packet transmission time (ms)
      timeSlot(15.0),             // Time slot for parallel communication (ms)
      numPacketsPerUser(packets_per_user)
{
    totalPackets = num_users * packets_per_user;
    packetsSent = 0;
}

void WiFi5Simulator::runSimulation(double transmission_time) {
    auto& users = ap.getUsers();
    auto& channel = ap.getChannel();

    // Simulate multi-user MIMO communication process
    double currentTime = 0.0;
    int currentUser = 0;

    while (packetsSent < totalPackets) {
        // Broadcast packet by access point
        currentTime += broadcastTime;

        // Channel State Information (CSI) collection
        for (auto& user : users) {
            currentTime += csiTime;
        }

        // Parallel transmission window
        int packetsInThisWindow = std::min(totalPackets - packetsSent, 
                                           static_cast<int>(std::ceil((timeSlot * 133.33) / (transmission_time * 8))));

        for (int i = 0; i < packetsInThisWindow; ++i) {
            User& user = users[currentUser];
            
            // Simulate packet transmission
            channel.occupy();
            currentTime += transmission_time;
            // std::cout << currentTime << std::endl; 
            user.incrementPacketsSent();
            user.addLatency(currentTime);
            channel.release();

            packetsSent++;
            
            // Round-robin scheduling
            currentUser = (currentUser + 1) % users.size();
        }

        // Move to next cycle
        currentTime += broadcastTime;
    }

    simulation_time = currentTime;
    calculateMetrics();
}

void WiFi5Simulator::calculateMetrics() {
    int total_packets = packetsSent;
    double total_latency = 0.0;
    double max_latency = 0.0;

    auto& users = ap.getUsers();
    for (const auto& user : users) {
        total_latency += user.getTotalLatency();
        // max_latency = std::max(max_latency, user.getTotalLatency());
        max_latency = std::max(max_latency, simulation_time) - 0.0614; // 0.0614 added by the bug
        // max latency is the total simulation time
    }

    // Throughput calculation 
    double throughput = (total_packets * 8.0 * 1024) / (max_latency * 1000); // Mbps // utilised max latency for the throuput calculation

    double avg_latency = total_packets > 0 ? total_latency / total_packets : 0.0;

    // Display metrics
    std::cout << "\n| WiFi 5 Simulation Metrics:\n";
    std::cout << "| -----------------------------------\n";
    std::cout << "| Throughput: " << std::fixed << std::setprecision(6) << throughput << " Mbps\n";
    std::cout << "| Average Latency: " << avg_latency << " ms\n";
    std::cout << "| Maximum Latency: " << max_latency << " ms\n";
    std::cout << "| -----------------------------------\n";
    std::cout << "| Total Simulation Time: " << simulation_time << " ms\n";
    std::cout << "| -----------------------------------\n";
}
