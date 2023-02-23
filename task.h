#pragma once
#include <functional>

template<typename FunctionType>
class Task {

public:

Task(const std::function<FunctionType>& work);

void doWork();


private:

std::function<FunctionType> workToDo;



};

template <typename FunctionType>
Task<FunctionType>::Task(const std::function<FunctionType>& work) : workToDo(work)
{
}

template <typename FunctionType>
void Task<FunctionType>::doWork() 
{ 
    workToDo(); 
}