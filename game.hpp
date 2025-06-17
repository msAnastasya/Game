#pragma once
#include "student.hpp"
#include "events.hpp"
#include <vector>
#include <fstream>

class Game {
public:
    Game();
    void start();
    bool saveGame(const std::string& filename) const;
    bool loadGame(const std::string& filename);

private:
    Student student;
    size_t day;
    size_t semesterLength;
    std::vector<Event> events;

    void playLoop();
    void showEvent();
    void processChoice(const EventOption& option);
    void showEnding() const;
};
