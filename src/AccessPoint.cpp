#include "AccessPoint.h"

AccessPoint::AccessPoint(int num_users) {
    for (int i = 0; i < num_users; ++i) {
        users.emplace_back(i);
    }
}

std::vector<User>& AccessPoint::getUsers() { return users; }
FrequencyChannel& AccessPoint::getChannel() { return channel; }
