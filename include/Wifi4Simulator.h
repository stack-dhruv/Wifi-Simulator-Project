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
