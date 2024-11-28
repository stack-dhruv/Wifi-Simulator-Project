#include "User.h"

User::User(int id)
    : id(id), packets_sent(0), total_latency(0.0), next_attempt(0.0) {}

int User::getId() const { return id; }
int User::getPacketsSent() const { return packets_sent; }
double User::getTotalLatency() const { return total_latency; }
double User::getNextAttempt() const { return next_attempt; }

void User::incrementPacketsSent() { packets_sent++; }
void User::addLatency(double latency) { total_latency += latency; }
void User::setNextAttempt(double time) { next_attempt = time; }

int User::randomBackoff() const { return rand() % 10 + 1; } // Random backoff between 1-10 ms
