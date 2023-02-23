#pragma once
#include "task.h"
#include "worker.h"
#include <future>
#include <queue>
#include <vector>

template<typename MetaDataType>
class Threadpool
{
public:
  using SizeType = int;
  using WorkerType = Worker<MetaDataType>;
  using TaskType = typename WorkerType::TaskType;
  using OptionalTaskType = typename WorkerType::OptionalTaskType;

  Threadpool(SizeType workersCount);
  ~Threadpool();

  void addTask(const TaskType& task);

private:
  void initCallbackForWorkers();
  void initWorkers(SizeType workersCount);
  OptionalTaskType takeNextTask();
  bool isThereAnyTask() const;

private:
  std::queue<TaskType> tasks; // could be replaced with thread safe implementation of queue (ex. from boost), the
  mutable std::mutex tasksAccessLock; // tasksAccessLock could be removed

  // this needs to be last -> all workesr will join main thread but task queue and other stuff needs to be available
  std::vector<std::shared_ptr<WorkerType>> workers;
};

template<typename MetaDataType>
Threadpool<MetaDataType>::Threadpool(const SizeType workersCount)
{
  initWorkers(workersCount);
  initCallbackForWorkers();
}

template<typename MetaDataType>
Threadpool<MetaDataType>::~Threadpool()
{
  while(isThereAnyTask())
  {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // could be replaced with conditional variable
  }
}

template<typename MetaDataType>
void Threadpool<MetaDataType>::addTask(const TaskType& task)
{
  auto lock = std::lock_guard(tasksAccessLock);
  tasks.push(task);
}

template<typename MetaDataType>
void Threadpool<MetaDataType>::initCallbackForWorkers()
{
  for(auto& worker : workers)
  {
    worker->setTaskTakerCallback([this]() { return takeNextTask(); });
  }
}

template<typename MetaDataType>
void Threadpool<MetaDataType>::initWorkers(const SizeType workersCount)
{
  for(SizeType i = 0; i < workersCount; ++i)
  {
    workers.push_back(std::make_shared<WorkerType>(i, "[Worker " + std::to_string(i) + "]"));
  }
}

template<typename MetaDataType>
Threadpool<MetaDataType>::OptionalTaskType Threadpool<MetaDataType>::Threadpool::takeNextTask()
{
  if(isThereAnyTask())
  {
    auto task = tasks.front();
    tasks.pop();
    return task;
  }

  return std::nullopt;
}

template<typename MetaDataType>
bool Threadpool<MetaDataType>::isThereAnyTask() const
{
  auto lock = std::lock_guard(tasksAccessLock);
  return !tasks.empty();
}
