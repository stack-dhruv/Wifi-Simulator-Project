#include "Packet.h"

Packet::Packet(int size, double data_rate)
    : size(size), transmission_time((size * 8.0 * 1024) / (data_rate * 1e6)) {}

int Packet::getSize() const {
    return size;
}

double Packet::getTransmissionTime() const {
    return transmission_time;
}
