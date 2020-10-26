#include <iostream>
#include <thread>
#include <mutex>

/*
	Will guard std::cout
*/
std::mutex m;

void func()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Executing func()." << "\n";
	}
}

void func2(const std::string& param)
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Executing func2(), " << param << "\n";
	}
}

void func3(const std::string& param)
{
	for (int i = 0; i < 10; i++)
	{
		/*
			lock_guard will go out of scope and unlock the mutex
			automatically.
		*/
		std::lock_guard<std::mutex> lg(m);
		std::cout << "Executing function from a " << param << "\n";
	}
}

int main()
{
	/*
		Create and start thread and wait for the t1 thread
		to finish it's work. Without join() the main thread
		would complete before t1.

		t2 will wait for t1 to complete and then initialize.
	*/
	std::thread t1{ func };
	std::thread t2{ func2, "Thread called." };

	t2.join();
	t1.join();
	std::cout << "\n\n";

	/*
		Using lock_guard for t3 and t4 since they are both accessing
		the global std::cout object. This can lead to synchronization
		problems. Hence, the lock.
	*/
	std::thread t3{ func3, "Thread 3" };
	std::thread t4{ func3, "Thread 4" };

	t3.join();
	t4.join();
	std::cout << "\n\n";	
}
