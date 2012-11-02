
#include <unistd.h> // for the sleep function
#include <iostream> // for output to the console
#include <functional> // used to store the callbacks
#include <crodt.h>

void callbackFuntion(const crodt::CrodtOutput<std::string>& co)
{
  std::cout << co.sortedContent.content << "\n"; // output the received text string
}

int main()
{
  // creates the receiver module
  crodt::ReceiverModuleIF* receiver = new crodt::ReceiverModule;

  crodt::TextCallback func = callbackFuntion;   // store the callbackfunction
  receiver->registerCallback(func); // set the callback functions

  receiver->start(); // non blocking call which starts the receive process

  sleep(300); //wait until all data is received

  delete receiver;  // delete the receiver module
  return 0;
}
