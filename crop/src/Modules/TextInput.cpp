/*
 * @brief TextInput.cpp implementation of member functions
 */

#include "TextInput.h"

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
    sleep(5);

    text.clear();
    text = "Es folgt ein Beispieltext:\n";
    text.append("Hallo ich bin ein Beispieltext und komme vom Mars.\n");
    text.append("Dabei wurde ich zuerst zerstückelt, dann priorisiert, einzeln versendet und auf der Erde wieder zusammengesetzt.\n");

    callback(id);
    id += 1;
  }
  std::cout << "text input thread finished" << std::endl;
}

const std::string& TextInput::getInput()
{
// with the following lines you can insert spaces
//  std::cout << "Bitte einen Text eingeben:\n";
//  std::string text;

//  std::cin.clear(); //clean cin and wait for input
//  std::cin.sync();
//  std::cin.get();
//  std::getline(std::cin, text);
//  std::cout << "Eingabe text: " << text << "\n";

  return text;
}
