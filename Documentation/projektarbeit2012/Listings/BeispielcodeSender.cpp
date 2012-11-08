
#include <unistd.h> // for the sleep function
#include <crodt.h>

int main()
{
  crodt::SenderModuleIF* sender = new crodt::SenderModule; // creates the senderModule
  sender->initialize();   // call initialization

  // send the text string with using the timestamp flag
  sender->sendText("abcdefghijklmnopqrstuvwxyz", true);

  sleep(20); // wait until the data was sent

  delete c; // delete the sender module

  return 0;
}
