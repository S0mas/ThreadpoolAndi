#pragma once
#include "task.h"
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <optional>

template<typename MetadataType>
class Worker
{
public:
  using TaskType = Task<MetadataType>;
  using OptionalTaskType = std::optional<TaskType>;
  using TaskTakerType = std::function<OptionalTaskType()>;

public:

  Worker(int id, const std::string& name);
  ~Worker() noexcept;

  const std::vector<MetadataType>& getTasksResults() const;
  void setTaskTakerCallback(const TaskTakerType& newTaskTakerCallback);

private:
  void process();
  void doTask(TaskType);

private:
  int id;
  std::string name;
  std::vector<MetadataType> tasksResults;
  std::atomic<bool> stopProcessing;
  TaskTakerType taskTakerCallback{[](){ return std::nullopt; }};
  std::future<void> future;
};

template<typename MetadataType>
Worker<MetadataType>::Worker(const int id, const std::string& name)
  : id(id)
  , name(name)
  , stopProcessing(false)
{
  future = std::async(std::launch::async, &Worker::process, this);
}

template<typename MetadataType>
Worker<MetadataType>::~Worker() noexcept
{
  stopProcessing = true;
}

template<typename MetadataType>
void Worker<MetadataType>::process()
{
  std::cout << name << " starts processing.." << std::endl;
  while(!stopProcessing)
  {
    if (auto task = taskTakerCallback(); task.has_value())
    {
      doTask(*task);
    }
  }
  std::cout << name << "finished processing" << std::endl;
}

template<typename MetadataType>
const std::vector<MetadataType>& Worker<MetadataType>::getTasksResults() const
{
  return tasksResults;
}

template<typename MetadataType>
void Worker<MetadataType>::doTask(TaskType task)
{
  std::cout << name << " starts working on task: " << task.getId() << std::endl;
  MetadataType metadata = id;
  task.doWork(metadata);
  tasksResults.push_back(metadata);
  std::cout << name << " finished task: " << task.getId() << std::endl;
}

template<typename MetadataType>
void Worker<MetadataType>::setTaskTakerCallback(const TaskTakerType& newTaskTakerCallback)
{
  taskTakerCallback = newTaskTakerCallback;
}
