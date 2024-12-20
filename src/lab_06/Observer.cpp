#include "../../include/Observer.h"

void Subject::Attach(Observer* obs) {
    observers.push_back(obs);
}

void Subject::Detach(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Subject::NotifyKill(const std::string &killerType, const std::string &killerName,
                         const std::string &victimType, const std::string &victimName) {
    for (auto obs : observers) {
        obs->OnKill(killerType, killerName, victimType, victimName);
    }
}

void ConsoleLoggerObserver::OnKill(const std::string &killerType, const std::string &killerName,
                                   const std::string &victimType, const std::string &victimName) {
    std::cout << killerType << " " << killerName << " убил " << victimType << " " << victimName << std::endl;
}

void FileLoggerObserver::OnKill(const std::string &killerType, const std::string &killerName,
                                const std::string &victimType, const std::string &victimName) {
    std::ofstream ofs("log.txt", std::ios::app);
    if (ofs.is_open()) {
        ofs << killerType << " " << killerName << " убил " << victimType << " " << victimName << "\n";
    }
}