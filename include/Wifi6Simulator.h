#ifndef WIFI6SIMULATOR_H
#define WIFI6SIMULATOR_H

#include "WifiSimulator.h"
#include <vector>

class WiFi6Simulator : public WiFiSimulator {
private:
    // Simulation parameters
    int bandwidth;
    int subChannelWidth;
    double dataRate;
    
    // Metrics tracking
    std::vector<double> latencies;
    std::vector<double> timestamps;

    // Helper methods for metrics calculation
    double calculateThroughput();
    double calculateAverageLatency();
    double calculateMaxLatency();

public:
    WiFi6Simulator(int num_users, int bandwidth = 20);

    void runSimulation(double transmission_time) override;
    void calculateMetrics(const std::vector<double>& frameTimestamps);
};

#endif // WIFI6SIMULATOR_H