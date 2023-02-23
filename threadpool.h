#pragma once
#include <vector>
#include <future>
#include <queue>
#include "task.h"
#include "worker.h"

class Threadpool {

public:
using TaskType = Task<void()>;

Threadpool(std::size_t workersCount);

void addTask(const TaskType& task);

void process() {
    while(isThereAnyTask() && isThereAvailableWorker()) {
        auto task = getNextTask();
        auto worker = getAvailableWorker();
        worker->doTask(task);

    }
}

Worker* getAvailableWorker();
TaskType getNextTask();
bool isThereAvailableWorker() const;
bool isThereAnyTask() const;

private:

std::vector<Worker*> availableWorkers;
std::vector<Worker> workers;
std::queue<TaskType> tasks;


};