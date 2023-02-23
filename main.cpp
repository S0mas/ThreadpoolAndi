#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <thread>
#include "threadpool.h"

int main(int argc, char* argv[])
{
	Threadpool threadpool(4);
	Threadpool::TaskType task([](){std::cout << "work done" << std::endl;});
	threadpool.addTask(task);
	threadpool.process();

	return 0;
}
