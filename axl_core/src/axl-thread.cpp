
#include "../include/axl-thread.h"

void axl::simple_thread::set(std::function<void()> func)
{
	this->no_arg_func = func;
}

void axl::simple_thread::start()
{
	_tr = std::thread(this->no_arg_func);
}

void axl::simple_thread::join()
{
	_tr.join();
}

void axl::simple_thread::abort()
{
}


bool axl::simple_thread::is_alive()
{
	return true;
}


