#include "game.hpp"
#include <iostream>
#include <cstdlib>

Game::Game() : day(1) {}

void Game::start() {
    while (day <= 30 && !student.isFailed()) {
        std::cout << "\nДень " << day << "\n";
        student.printStatus();
        showEvent();
        ++day;
    }

    showEnding();
}

void Game::showEvent() {
    std::cout << "\nВыберите событие:\n";
    std::cout << "1. Учиться в библиотеке (+Знания, -Радость, -Бодрость)\n";
    std::cout << "2. Пойти на тусовку (+Радость, -Знания, -Бодрость)\n";
    std::cout << "3. Поспать (+Бодрость, -Знания)\n";
    std::cout << "Выбор (1-3): ";

    int choice;
    std::cin >> choice;
    processChoice(choice);
}

void Game::processChoice(int choice) {
    switch (choice) {
        case 1:
            student.changeKnowledge(10);
            student.changeJoy(-5);
            student.changeEnergy(-10);
            break;
        case 2:
            student.changeJoy(10);
            student.changeKnowledge(-5);
            student.changeEnergy(-15);
            break;
        case 3:
            student.changeEnergy(20);
            student.changeKnowledge(-5);
            break;
        default:
            std::cout << "Неверный выбор. День пропущен.\n";
            break;
    }
}

void Game::showEnding() const {
    if (student.isFailed()) {
        std::cout << "\nВы проиграли. Вас отчислили или вы сломались.\n";
    } else {
        std::cout << "\nПоздравляем! Вы выжили до конца семестра!\n";
        student.printStatus();
    }
}
