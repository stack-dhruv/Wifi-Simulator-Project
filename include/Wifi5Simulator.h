#ifndef WIFI5SIMULATOR_H
#define WIFI5SIMULATOR_H

#include "WifiSimulator.h"

class WiFi5Simulator : public WiFiSimulator {
private:
    double broadcastTime;     // 1 KB broadcast packet transmission time (ms)
    double csiTime;           // CSI packet transmission time (ms)
    double packetTransmissionTime; // Data packet transmission time (ms)
    double timeSlot;          // Time slot for parallel communication (ms)
    int totalPackets;         // Total packets to be sent
    int packetsSent;          // Count of sent packets
    int numPacketsPerUser;    // Packets per user

public:
    WiFi5Simulator(int num_users, int packets_per_user);

    void runSimulation(double transmission_time) override;
    void calculateMetrics();
};

#endif