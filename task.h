#pragma once
#include <functional>

template<typename MetaDataType>
class Task
{
public:
  Task(int id, const std::function<void(MetaDataType&)>& work);

  void doWork(MetaDataType& metadata);

  int getId() const;

private:
  int id;
  std::function<void(MetaDataType&)> workToDo;
};

template<typename MetaDataType>
Task<MetaDataType>::Task(const int id, const std::function<void(MetaDataType&)>& work)
  : id(id), workToDo(work)
{
}

template<typename MetaDataType>
void Task<MetaDataType>::doWork(MetaDataType& metadata)
{
  workToDo(metadata);
}

template<typename MetaDataType>
int Task<MetaDataType>::Task::getId() const
{
  return id;
}
