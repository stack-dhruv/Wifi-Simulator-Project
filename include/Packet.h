#ifndef PACKET_H
#define PACKET_H

class Packet {
private:
    int size; // Packet size in KB
    double transmission_time; // Time required to transmit this packet (in ms)

public:
    Packet(int size, double data_rate);
    int getSize() const;
    double getTransmissionTime() const;
};

#endif
