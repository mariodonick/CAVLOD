/*
 * @brief TextInput.h
 *
 */

#ifndef TEXTINPUT_H_
#define TEXTINPUT_H_

#include "ContentInput.h"

#include <string>

class TextInput : public ContentInput<std::string>, public ContentThreadModule
{
public:
  TextInput(const bool& running, const ReadyCallback& function);
  virtual ~TextInput();

private:
  void run();
  const std::string& getInput();

private:
  std::string text;
};

#endif /* TEXTINPUT_H_ */
