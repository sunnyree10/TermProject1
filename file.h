#ifndef __FILE_H__
#define __FILE_H__

#include <string>

#include "Handler.h"
#include "message.h"

std::string* ReadInputData(std::ifstream &file);
void WriteOutEntries(Handler &myHandler);

std::string* ReadSMSFromFile(std::ifstream &file);
void WriteOutSMS(SMSHandler &mySMSbox);

#endif