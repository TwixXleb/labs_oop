#ifndef LAB0_OBSERVER_V2_H
#define LAB0_OBSERVER_V2_H

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <iostream>
#include <fstream>

extern std::mutex cout_mutex_v2;

class Observer_v2 {
public:
    virtual ~Observer_v2() {}
    virtual void OnKill_v2(const std::string &killerType, const std::string &killerName,
                           const std::string &victimType, const std::string &victimName) = 0;
};

class Subject_v2 {
    std::vector<Observer_v2*> observers_v2;
public:
    void Attach_v2(Observer_v2* obs);
    void Detach_v2(Observer_v2* obs);
    void NotifyKill_v2(const std::string &killerType, const std::string &killerName,
                       const std::string &victimType, const std::string &victimName);
};

class ConsoleLoggerObserver_v2 : public Observer_v2 {
public:
    void OnKill_v2(const std::string &killerType, const std::string &killerName,
                   const std::string &victimType, const std::string &victimName) override;
};

class FileLoggerObserver_v2 : public Observer_v2 {
public:
    void OnKill_v2(const std::string &killerType, const std::string &killerName,
                   const std::string &victimType, const std::string &victimName) override;
};

#endif //LAB0_OBSERVER_V2_H
