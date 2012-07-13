/*
 * @brief Visualizer.cpp implementation of member functions
 */

#include "Visualizer.h"
#include <iostream>

TextVisualizer::TextVisualizer()
{

}
TextVisualizer::~TextVisualizer()
{

}

void TextVisualizer::display(const std::vector<Text*>& sortedContent)
{
  std::vector<Text*>::const_iterator it = sortedContent.begin();
  for(; it != sortedContent.end(); ++it)
    std::cout << (*it)->text;
}





SensorVisualizer::SensorVisualizer()
{

}

SensorVisualizer::~SensorVisualizer()
{

}

void SensorVisualizer::display(const std::vector<Sensor*>& )
{

}
