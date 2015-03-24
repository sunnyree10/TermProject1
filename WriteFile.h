#ifndef __WRITEFILE_H__
#define __WRITEFILE_H__

#include "Contacts.h"
#include "Message.h"
#include "Call.h"

void WriteOutContacts(ContactHandler &myContacts);
void WriteOutSMS(SMSHandler &myMessages);
void WriteOutCallLogs(CallHandler &myCalls);

#endif