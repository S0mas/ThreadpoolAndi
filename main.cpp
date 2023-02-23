#include "threadpool.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using MetadataType = int;
using ThreadpoolType = Threadpool<MetadataType>;
using TaskType = typename ThreadpoolType::TaskType;

void printer(MetadataType&);

int main(int argc, char* argv[])
{
  ThreadpoolType threadpool(4);

  for(int i = 0; i < 5; ++i)
  {
    threadpool.addTask({i, [](MetadataType& metadata) { printer(metadata); }});
  }

  return 0;
}

void printer(MetadataType& metadata)
{
  for(int i = 0; i < 5; ++i)
  {
    std::this_thread::sleep_for(std::chrono::seconds(metadata + 1));
    std::cout << "Working... metadata: " << metadata << std::endl;
  }
}
