#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include "Handler.h"

void WriteOutEntries(std::string fileName, Handler &myHandler);
std::string* ReadInputData(std::ifstream &file);

#endif