#pragma once
#include "student.hpp"

class Game {
public:
    Game();
    void start();

private:
    Student student;
    int day;

    void showEvent();
    void processChoice(int choice);
    void showEnding() const;
};
