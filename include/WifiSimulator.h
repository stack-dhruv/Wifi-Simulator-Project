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
