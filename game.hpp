#pragma once
#include "student.hpp"
#include "events.hpp"
#include <vector>

class Game {
public:
    Game();
    void start();
    int semesterLength;

private:
    Student student;
    int day;
    std::vector<Event> events;

    void showEvent();
    void processChoice(const EventOption& option);
    void showEnding() const;
};
