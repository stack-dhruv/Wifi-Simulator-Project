#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

class FrequencyChannel {
private:
    bool busy;

public:
    FrequencyChannel();

    bool isBusy() const;
    void occupy();
    void release();
};

#endif
