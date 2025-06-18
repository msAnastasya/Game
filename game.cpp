#include "game.hpp"
#include "events.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>

Game::Game() : student(), day(1), semesterLength(0), events(getAllEvents()) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::start() {
    std::cout << "\n=== Добро пожаловать в симулятор выживания студента ===\n";
    while (true) {
        std::cout << "1. Новая игра\n"
                     "2. Загрузить игру\n"
                     "Выберите опцию: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Повторите.\n";
            continue;
        }
        if (choice == 1) {   // Новая игра
            day = 1;
            student = Student();
            while (true) {
                std::cout << "Введите длительность семестра (1-200): ";
                if (std::cin >> semesterLength && semesterLength >= 1 && semesterLength <= 200) {
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неверный ввод.\n";
            }
            break;
        } else if (choice == 2) {  // Загрузка сохранения
            if (loadGame("save.txt")) {
                std::cout << "Сохранение успешно загружено.\n";
                break;
            } else {
                std::cout << "Не удалось загрузить сохранение.\n";
            }
        } else {
            std::cout << "Неверная опция.\n";
        }
    }

    playLoop();
    saveGame("save.txt");
    showEnding();
}

void Game::playLoop() {
    while (day <= semesterLength && !student.isFailed()) {
        std::cout << "\nДень " << day << "\n";
        student.printStatus();
        showEvent();
        ++day;
        saveGame("save.txt"); // автосохранение после каждого дня
    }
}

bool Game::saveGame(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Ошибка при сохранении в файл " << filename << "\n";
        return false;
    }
    out << day << '\n';
    out << semesterLength << '\n';
    out << student.getJoy() << ' '
        << student.getEnergy() << ' '
        << student.getKnowledge() << ' '
        << student.getMoney() << '\n';
    out.close();
    return true;
}

bool Game::loadGame(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Ошибка при открытии файла сохранения " << filename << "\n";
        return false;
    }
    int joy, energy, knowledge, money;
    if (!(in >> day >> semesterLength >> joy >> energy >> knowledge >> money)) {
        std::cerr << "Ошибка чтения данных из файла.\n";
        in.close();
        return false;
    }
    student = Student(joy, energy, knowledge, money);
    in.close();
    return true;
}

void Game::showEvent() {
    int index = std::rand() % events.size();
    const Event& e = events[index];

    std::cout << "\n" << e.description << "\n";
    for (size_t i = 0; i < e.options.size(); ++i) {
        std::cout << i + 1 << ". " << e.options[i].description << "\n";
    }
    int choice = 0;
    while (true) {
        std::cout << "Выбор (1-" << e.options.size() << "): ";

        if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(e.options.size())) {
            processChoice(e.options[choice - 1]);
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный выбор.\n";
    }
}

void Game::processChoice(const EventOption& option) {
    student.changeKnowledge(option.knowledgeChange);
    student.changeEnergy(option.energyChange);
    student.changeJoy(option.joyChange);
    student.changeMoney(option.moneyChange);
}

void Game::showEnding() const {
    if (student.getJoy() == 0) {
        std::cout << "\nТы больше не ощущаете смысла в учебе. Каждый день — серый. Утром ты просто не встал на пары.\n"
                     "Слово 'отчисление' больше не пугает. Ты эмоционально выгорел.\n";
        std::cout << "Концовка: ВЫГОРАНИЕ\n";
        std::cout << "\nФинальное состояние:\n";
        student.printStatus();
        return;
    }

    if (student.getEnergy() == 0) {
        std::cout << "\nТы упал прямо на паре. Госпитализация. Диагноз — переутомление.\n"
                     "Учёба не важнее здоровья. Временно отчислен.\n";
        std::cout << "Концовка: ИСТОЩЕНИЕ\n";
        std::cout << "\nФинальное состояние:\n";
        student.printStatus();
        return;
    }

    if (student.getKnowledge() == 0) {
        std::cout << "\nДеградация. Три экзамена подряд ты провалил. Не пришёл на пересдачи. Академическая неуспеваемость.\n"
                     "Приказ об отчислении подписан.\n";
        std::cout << "Концовка: ОТЧИСЛЕН ЗА НЕУСПЕВАЕМОСТЬ\n";
        std::cout << "\nФинальное состояние:\n";
        student.printStatus();
        return;
    }

    if (student.getMoney() == 0) {
        std::cout << "\nТы не можешь оплатить проезд, еду и общежитие. На учебу нет ни сил, ни средств.\n"
                     "Тебя исключают по финансовым причинам.\n";
        std::cout << "Концовка: ФИНАНСОВЫЙ КРАХ\n";
        std::cout << "\nФинальное состояние:\n";
        student.printStatus();
        return;
    }

    // Победные концовки
    if ( student.getJoy() >= 30 && student.getEnergy() >= 20 && student.getKnowledge() >= 80) {
        std::cout << "\nТы стал легендой потока! Зачёты, экзамены — всё сдал на 'отлично'.\n"
                     "Преподы тобой гордятся. Фото — на доске почета.\n";
        std::cout << "Концовка: ЛУЧШИЙ СТУДЕНТ СЕМЕСТРА!\n";
    }
    else if (student.getJoy() > 80 && student.getEnergy() >= 30) {
        std::cout << "\nТы смеялся, жил, любил. Семестр прошёл не под знаком зубрёжки — ты строил воспоминания.\n"
                 "Да, иногда пропускал дедлайны, но каждое утро вставал с желанием жить.\n"
                 "Вряд ли ты стал звездой потока, но ты точно стал героем своего сердца.\n";
        std::cout << "Концовка: ЖИЗНЬ ПРЕКРАСНА\n";
    }
    else if ( student.getJoy() >= 30 && student.getEnergy() >= 20 && student.getMoney() >= 80) {
        std::cout << "\nТы стал блогером, торгуешь шпаргалками, записываешь курсы и успеваешь учиться.\n"
                     "Теперь у тебя MacBook и 50к подписчиков. Учёба на втором плане.\n";
        std::cout << "Концовка: СТУДЕНТ-ИНФЛЮЕНСЕР\n";
    }
    else if (student.getJoy() >= 25 && student.getEnergy() >= 25 && student.getKnowledge() >= 40 && student.getMoney() >= 20) {
        std::cout << "\nТы не герой и не жертва. Ты — тот самый студент, который не выделяется,\n"
                 "но всё всегда делает вовремя. Преподаватели не запомнили тебя, но зачёты стоят.\n"
                 "Продолжай в том же духе — и всё будет.\n";
        std::cout << "Концовка: ВСЁ СТАБИЛЬНО\n";
    }
    else if (student.getJoy() >= 30 && student.getEnergy() >= 20 && student.getKnowledge() >= 30 && student.getMoney() >= 10) {
        std::cout << "\nТы держался молодцом. Без провалов, но и без прорывов.\n"
                 "Семестр был как марафон: ни отдыха, ни финишной ленточки, просто выживание.\n"
                 "Ты научился балансировать между хаосом дедлайнов и бессонницей.\n";
        std::cout << "Концовка: ВЫЖИВАЮЩИЙ ПЕРФОРМЕР\n";
    }
    else if (student.getJoy() >= 20 && student.getEnergy() >= 20 && student.getKnowledge() >= 20) {
        std::cout << "\nТы справился. Сессия позади, нервы целы. Всё в пределах нормы.\n"
                     "Ты выжил. Гордимся!\n";
        std::cout << "Концовка: ВЫЖИЛ\n";
    }
    else {
        std::cout << "\nТы не провалился полностью, но и выдающимся семестр не стал.\n"
                     "Набрались и хвосты, и нервы сдали. Но ты остался в игре. Стань лучше в следующем семестре.\n";
        std::cout << "Концовка: СТУДЕНТ НА ГРАНИ\n";
    }

    // Показываем финальные параметры
    std::cout << "\nФинальное состояние:\n";
    student.printStatus();
}
