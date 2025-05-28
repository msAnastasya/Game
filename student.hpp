#pragma once
#include <string>

class Student {
public:
    Student();

    // Изменить параметры студента
    void changeJoy(int delta);
    void changeEnergy(int delta);
    void changeKnowledge(int delta);

    // Получить текущее состояние
    int getJoy() const;
    int getEnergy() const;
    int getKnowledge() const;

    // Показать статус
    void printStatus() const;

    // Проверка на провал
    bool isFailed() const;

private:
    int joy;
    int energy;
    int knowledge;
};