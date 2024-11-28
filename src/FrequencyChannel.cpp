#include "FrequencyChannel.h"

FrequencyChannel::FrequencyChannel() : busy(false) {}

bool FrequencyChannel::isBusy() const { return busy; }
void FrequencyChannel::occupy() { busy = true; }
void FrequencyChannel::release() { busy = false; }
