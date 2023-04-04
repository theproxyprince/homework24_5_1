#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <string>

void begin(std::map<std::string, bool>& tasksNamesAndFlags, std::vector<std::time_t>& tasksTimeBegin,
           std::vector<std::time_t>& tasksTimeEnd) {
    std::string taskName;
    std::cout << "Введите название задачи: ";
    std::getline(std::cin, taskName);

    for (auto it = tasksNamesAndFlags.begin(); it != tasksNamesAndFlags.end(); ++it) {
        if (it->second) {
            it->second = false;
            std::cout << "Задача " << it->first << " остановлена!\n";
            tasksTimeEnd.push_back(time(nullptr));
            break;
        }
    }

    tasksNamesAndFlags[taskName] = true;
    tasksTimeBegin.push_back(time(nullptr));

}

void end(std::map<std::string, bool>& tasksNamesAndFlags, std::vector<std::time_t>& tasksTimeBegin,
         std::vector<std::time_t>& tasksTimeEnd) {

    for (auto it = tasksNamesAndFlags.begin(); it != tasksNamesAndFlags.end(); ++it) {
        if (it->second) {
            it->second = false;
            tasksTimeEnd.push_back(time(nullptr));
            std::cout << "Задача " << it->first << " остановлена!\n";
            break;
        }
    }

}

void status(std::map<std::string, bool>& tasksNamesAndFlags, std::vector<std::time_t>& tasksTimeBegin,
            std::vector<std::time_t>& tasksTimeEnd) {
    int count = 0;

    for (auto it = tasksNamesAndFlags.begin(); it != tasksNamesAndFlags.end(); ++it) {
        if (it->second) {
            std::cout << "Сейчас активное такое задание: " << it->first << std::endl;
            break;
        }
    }

    for (auto it = tasksNamesAndFlags.begin(); it != tasksNamesAndFlags.end(); ++it) {
        if (!it->second) {
            std::cout << "На задание \"" << it->first << "\" было потрачено " <<
                         std::difftime(tasksTimeEnd[count], tasksTimeBegin[count]) << " сек." << std::endl;
            count++;
        }
    }
}

//менеджер учёта времени
int main() {
    std::map<std::string, bool> tasksNamesAndFlags;
    std::vector<std::time_t> tasksTimeBegin;
    std::vector<std::time_t> tasksTimeEnd;
    std::string input;
    while (true) {
        std::cout << "Введите команду(begin/end/status/exit): " << std::endl;
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        } else if (input == "begin") {
            begin(tasksNamesAndFlags, tasksTimeBegin, tasksTimeEnd);
        } else if (input == "end") {
            end(tasksNamesAndFlags, tasksTimeBegin, tasksTimeEnd);
        } else if (input == "status") {
            status(tasksNamesAndFlags, tasksTimeBegin, tasksTimeEnd);
        }
    }
    return 0;
}
