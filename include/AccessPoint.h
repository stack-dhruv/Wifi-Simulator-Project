#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "User.h"
#include "FrequencyChannel.h"
#include <vector>

class AccessPoint {
private:
    std::vector<User> users;
    FrequencyChannel channel;

public:
    AccessPoint(int num_users);

    std::vector<User>& getUsers();
    FrequencyChannel& getChannel();
};

#endif
