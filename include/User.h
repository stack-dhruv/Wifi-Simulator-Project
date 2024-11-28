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
