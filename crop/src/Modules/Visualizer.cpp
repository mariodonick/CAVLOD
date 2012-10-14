/*
 * @brief Visualizer.cpp implementation of member functions
 */

#include "Visualizer.h"
#include "../Tools/Log.h"

TextVisualizer::TextVisualizer()
{

}
TextVisualizer::~TextVisualizer()
{

}

void TextVisualizer::display(const std::vector<Text_sPtr>& sortedContent, const bool&, const CTimestamp&)
{
  INFO() << "display Text: \n";
  INFO() << "-------------------------------------------------------\n";

  std::vector<Text_sPtr>::const_iterator it = sortedContent.begin();
  for(; it != sortedContent.end(); ++it)
    INFO() << (*it)->text;

  INFO() << "\n\n";
}





SensorVisualizer::SensorVisualizer()
{

}

SensorVisualizer::~SensorVisualizer()
{

}

void SensorVisualizer::display(const std::vector<Sensor_sPtr>& sortedContent, const bool& usingTimestamp, const CTimestamp& timestamp)
{
  INFO() << "display Sensor: \n";
  INFO() << "-------------------------------------------------------\n";

  std::vector<Sensor_sPtr>::const_iterator it = sortedContent.begin();
  for(; it != sortedContent.end(); ++it)
  {
    if(usingTimestamp)
      INFO() << "timestamp: " << timestamp.to_ulong() << " value: " << (*it)->value << "\n";
    else
      INFO() << "value: " << (*it)->value << "\n";
  }

  INFO() << "\n";
}
