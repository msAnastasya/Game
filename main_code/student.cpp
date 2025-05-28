#include "student.hpp"
#include <iostream>

Student::Student() : joy(50), energy(50), knowledge(50) {}

void Student::changeJoy(int delta) {
    joy += delta;
    if (joy > 100) joy = 100;
    if (joy < 0) joy = 0;
}

void Student::changeEnergy(int delta) {
    energy += delta;
    if (energy > 100) energy = 100;
    if (energy < 0) energy = 0;
}

void Student::changeKnowledge(int delta) {
    knowledge += delta;
    if (knowledge > 100) knowledge = 100;
    if (knowledge < 0) knowledge = 0;
}

int Student::getJoy() const { return joy; }
int Student::getEnergy() const { return energy; }
int Student::getKnowledge() const { return knowledge; }

void Student::printStatus() const {
    std::cout << "Статус студента:\n";
    std::cout << "Радость: " << joy << "/100\n";
    std::cout << "Бодрость: " << energy << "/100\n";
    std::cout << "Знания: " << knowledge << "/100\n";
}

bool Student::isFailed() const {
    return joy == 0 || energy == 0 || knowledge == 0;
}
