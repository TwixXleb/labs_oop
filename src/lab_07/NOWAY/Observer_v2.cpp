#include "../../../include/NOWAY/Observer_v2.h"

std::mutex cout_mutex_v2;

void Subject_v2::Attach_v2(Observer_v2* obs) {
    observers_v2.push_back(obs);
}

void Subject_v2::Detach_v2(Observer_v2* obs) {
    observers_v2.erase(std::remove(observers_v2.begin(), observers_v2.end(), obs), observers_v2.end());
}

void Subject_v2::NotifyKill_v2(const std::string &killerType, const std::string &killerName,
                               const std::string &victimType, const std::string &victimName) {
    for (auto obs : observers_v2) {
        obs->OnKill_v2(killerType, killerName, victimType, victimName);
    }
}

void ConsoleLoggerObserver_v2::OnKill_v2(const std::string &killerType, const std::string &killerName,
                                         const std::string &victimType, const std::string &victimName) {
    std::lock_guard<std::mutex> lg(cout_mutex_v2);
    std::cout << "[V2] " << killerType << " " << killerName << " убил "
              << victimType << " " << victimName << std::endl;
}

void FileLoggerObserver_v2::OnKill_v2(const std::string &killerType, const std::string &killerName,
                                      const std::string &victimType, const std::string &victimName) {
    std::lock_guard<std::mutex> lg(cout_mutex_v2);
    std::ofstream ofs("log_v2.txt", std::ios::app);
    if (ofs.is_open()) {
        ofs << "[V2] " << killerType << " " << killerName << " убил "
            << victimType << " " << victimName << "\n";
    }
}
