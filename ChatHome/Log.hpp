#pragma once

#include <iostream>
#include <string>

#define NORMAL 0
#define WARNING 1
#define ERROR 2

const char *log_level[] = {
	"Normal",
	"Warning",
	"Error",
	NULL,
};

//level: 日志的级别
void Log(std::string msg, int level, std::string file, int line)
{
	std::cout << '[' << msg << ']' << '[' << level << ']' << " : " << \
		file << " : " << line << std::endl;
}

#define LOG(msg,level) Log(msg,level, __FILE__, __LINE__)
