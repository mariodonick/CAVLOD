/*
 * @brief TextInput.cpp implementation of member functions
 */

#include "TextInput.h"
#include "../TypesConfig/Config.h"

#include <iostream>

TextInput::TextInput(const bool& running, const ReadyCallback& function)
: ContentThreadModule(running, function)
{
}

TextInput::~TextInput()
{
}

void TextInput::run()
{
  while(running)
  {
    usleep(5000 * 1000);

    text.clear();
    text = "Es folgt ein Beispieltext:\n";
    text.append("Hallo ich bin ein Beispieltext und komme vom Mars.\n");
    text.append("Dabei wurde ich zuerst zerstückelt, dann priorisiert, einzeln versendet und auf der Erde wieder zusammengesetzt.\n");

    bool usingTimestamp = true;
    callback(id, usingTimestamp);
    id += 1;
  }
}

const std::string& TextInput::getInput()
{
  return text;
}
