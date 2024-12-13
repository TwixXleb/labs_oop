#ifndef LAB0_OBSERVER_H
#define LAB0_OBSERVER_H

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <iostream>
#include <fstream>

extern std::mutex cout_mutex;

class Observer {
public:
    virtual ~Observer() {}
    virtual void OnKill(const std::string &killerType, const std::string &killerName,
                        const std::string &victimType, const std::string &victimName) = 0;
};

class Subject {
    std::vector<Observer*> observers;
public:
    void Attach(Observer* obs);
    void Detach(Observer* obs);
    void NotifyKill(const std::string &killerType, const std::string &killerName,
                    const std::string &victimType, const std::string &victimName);
};

class ConsoleLoggerObserver : public Observer {
public:
    void OnKill(const std::string &killerType, const std::string &killerName,
                const std::string &victimType, const std::string &victimName) override;
};

class FileLoggerObserver : public Observer {
public:
    void OnKill(const std::string &killerType, const std::string &killerName,
                const std::string &victimType, const std::string &victimName) override;
};

#endif //LAB0_OBSERVER_H
