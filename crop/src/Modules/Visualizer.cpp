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

void TextVisualizer::display(const std::vector<Text_sPtr>& sortedContent, const bool&, const CTimestamp&)
{
  std::cout << "display Text: \n";
  std::cout << "-------------------------------------------------------\n";

  std::vector<Text_sPtr>::const_iterator it = sortedContent.begin();
  for(; it != sortedContent.end(); ++it)
    std::cout << (*it)->text;

  std::cout << "\n\n";
}





SensorVisualizer::SensorVisualizer()
{

}

SensorVisualizer::~SensorVisualizer()
{

}

void SensorVisualizer::display(const std::vector<Sensor_sPtr>& sortedContent, const bool& usingTimestamp, const CTimestamp& timestamp)
{
  std::cout << "display Sensor: \n";
  std::cout << "-------------------------------------------------------\n";

  std::vector<Sensor_sPtr>::const_iterator it = sortedContent.begin();
  for(; it != sortedContent.end(); ++it)
  {
    if(usingTimestamp)
      std::cout << "timestamp: " << timestamp.to_ulong() << " value: " << (*it)->value << "\n";
    else
      std::cout << "value: " << (*it)->value << "\n";
  }

  std::cout << "\n";
}
