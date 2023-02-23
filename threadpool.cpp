#include "threadpool.h"

Threadpool::Threadpool(const std::size_t workersCount) : workers{workersCount}
{
    for(auto& worker : workers) {
        availableWorkers.push_back(&worker);
    }
    
}

void Threadpool::addTask(const TaskType& task)
{
    tasks.push(task);
}

Worker *Threadpool::getAvailableWorker()
{
    auto worker = availableWorkers.back();
    availableWorkers.pop_back();
    
    return worker;

}

Threadpool::TaskType Threadpool::getNextTask()
{
    auto task = tasks.front();
    tasks.pop();

    return task;
}

bool Threadpool::isThereAvailableWorker() const
{
    return !availableWorkers.empty();
}

bool Threadpool::isThereAnyTask() const
{
    return !tasks.empty();
}
