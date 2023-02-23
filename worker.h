#pragma once
#include "task.h"
#include <future>

class Worker {

public:

using TaskType = Task<void()>;

void doTask(TaskType);

bool working();


private:

std::future<void> future ;


};