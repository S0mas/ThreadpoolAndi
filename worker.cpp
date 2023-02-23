#include "worker.h"


void Worker::doTask(TaskType task)
{
    future = std::async(std::launch::async, [](auto task){task.doWork();}, task);
}
