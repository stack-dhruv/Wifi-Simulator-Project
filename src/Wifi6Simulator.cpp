#include "Wifi6Simulator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <vector>

WiFi6Simulator::WiFi6Simulator(int num_users, int bandwidth)
    : WiFiSimulator(num_users), 
      bandwidth(bandwidth), 
      subChannelWidth(4),  // Default sub-channel width
      dataRate(133.33)     // Default data rate in Mbps
{}

void WiFi6Simulator::runSimulation(double transmission_time) {

    // Ask the user for sub-channel width
    int userInputSubChannelWidth;
    std::cout << "Enter sub-channel width (2 MHz, 4 MHz, or 10 MHz): ";
    std::cin >> userInputSubChannelWidth;

    // Validate sub-channel width
    if (userInputSubChannelWidth != 2 && 
        userInputSubChannelWidth != 4 && 
        userInputSubChannelWidth != 10) {
        throw std::invalid_argument("Invalid sub-channel width! Only 2, 4, or 10 MHz are allowed.");
    }
    
    subChannelWidth = userInputSubChannelWidth;

    // Calculate simulation parameters
    int numSubChannels = bandwidth / subChannelWidth;
    double dataRatePerSubChannel = (dataRate * subChannelWidth) / 20.0;  // Mbps per sub-channel
    
    // Calculate transmission time based on sub-channel width
    double transmissionTime = (1024 * 8) / ((subChannelWidth * 8 * (5.0/6.0) * 1000));

    std::cout << "Total Bandwidth: " << bandwidth << " MHz\n";
    std::cout << "Sub-channel Width: " << subChannelWidth << " MHz\n";
    std::cout << "Number of Sub-channels: " << numSubChannels << "\n";
    std::cout << "Transmission Time per Packet: " 
              << std::fixed << std::setprecision(4) << transmissionTime << " ms\n\n";

    // Reset metrics
    latencies.clear();
    timestamps.clear();
    simulation_time = 0.0;

    auto& users = ap.getUsers();
    auto& channel = ap.getChannel();

    int remainingUsers = users.size();
    double currentTime = 0.0;
    int packetsPerUser = 10;  // Configurable number of packets

    std::vector<double> frameTimestamps;

    while (remainingUsers > 0) {
        std::cout << "\t↦ Parallel Lines opened at " << std::fixed << std::setprecision(4) << currentTime << " ms\n";

        int usersThisFrame = std::min(numSubChannels, remainingUsers);
        
        // Vector to store transmission details for this frame
        std::vector<std::pair<User*, int>> frameTransmissions;
        
        // Select users for this frame
        for (int i = 0; i < usersThisFrame; ++i) {
            int userIndex = users.size() - remainingUsers + i;
            User& currentUser = users[userIndex];
            
            // Add user and their assigned sub-channel
            frameTransmissions.push_back({&currentUser, i});
        }

        // Parallel transmission for this frame
        for (const auto& transmission : frameTransmissions) {
            User* currentUser = transmission.first;
            int subChannel = transmission.second;
            
            // Simulate packet transmission
            channel.occupy();
            
            // All users transmit at the same time in their respective sub-channels
            double transmissionCompleteTime = currentTime + transmissionTime;
            
            // Update user metrics
            currentUser->incrementPacketsSent();
            currentUser->addLatency(transmissionCompleteTime);
            
            // Store metrics for overall simulation
            timestamps.push_back(transmissionCompleteTime);
            latencies.push_back(transmissionCompleteTime);
            frameTimestamps.push_back(transmissionCompleteTime);

            std::cout << "User " << currentUser->getId() 
                      << " transmitted successfully on sub-channel " << subChannel 
                      << " at time " << std::fixed << std::setprecision(4) 
                      << transmissionCompleteTime << " ms.\n";

            channel.release();
        }

        // Move to next frame
        currentTime += 5.0;  // 5 ms frame duration
        remainingUsers -= usersThisFrame;
    }

    simulation_time = currentTime;
    calculateMetrics(frameTimestamps);
}

void WiFi6Simulator::calculateMetrics(const std::vector<double>& frameTimestamps) {
    std::cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "| Simulation Results\n";
    std::cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
    // Calculate and display metrics
    // Display metrics
    std::cout << "\n| WiFi 5 Simulation Metrics:\n";
    std::cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "| Throughput: " << std::fixed << std::setprecision(6) << calculateThroughput() << " Mbps\n";
    std::cout << "| Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "| Maximum Latency: " << calculateMaxLatency() << " ms\n";
    std::cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    // std::cout << "1. Throughput: " << std::fixed << std::setprecision(4) 
    //           << calculateThroughput() << " Mbps\n";
    // std::cout << "2. Average Latency: " 
    //           << calculateAverageLatency() << " ms\n";
    // std::cout << "3. Max Latency: " 
    //           << calculateMaxLatency() << " ms\n";

    // Timestamps for transmission verification
    std::cout << "\nUsers transmissions\n";
    for (size_t i = 0; i < frameTimestamps.size(); ++i) {
        std::cout << "User " << i+1 << " transmitted at " 
                  << std::fixed << std::setprecision(4) 
                  << frameTimestamps[i] << " ms\n";
    }
    std::cout << "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

double WiFi6Simulator::calculateThroughput() {
    if (latencies.empty()) return 0.0;
    double totalData = latencies.size() * 8192.0;  // Total data in bits (1 KB = 8192 bits)
    // std::cout << "\nNums User" << totalData << std::endl;
    return (totalData / (*std::max_element(latencies.begin(), latencies.end())*1000));  // Throughput in Mbps
}

double WiFi6Simulator::calculateAverageLatency() {
    if (latencies.empty()) return 0.0;

    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi6Simulator::calculateMaxLatency() {
    if (latencies.empty()) return 0.0;

    return *std::max_element(latencies.begin(), latencies.end());
}