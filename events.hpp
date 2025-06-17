#pragma once
#include <string>
#include <vector>

struct EventOption {
    std::string description;
    int knowledgeChange;
    int energyChange;
    int joyChange;
    int moneyChange;
};

class Event {
public:
    std::string description;
    std::vector<EventOption> options;

    Event(std::string desc, std::vector<EventOption> opts);
};

std::vector<Event> getAllEvents();
