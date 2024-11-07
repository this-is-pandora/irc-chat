#pragma once
#include <vector>

class Channel
{
private:
    vector<int> members; // set of users in this channel
    int id;              // channel id
    char *name;          // channel name
    char *creator;       // creator name
    bool inviteOnly;
    bool topicRestriction;
    int user_limit;

public:
    Channel(char *name);
    void removeUser();
    void addUser();
    void getUsers();
};