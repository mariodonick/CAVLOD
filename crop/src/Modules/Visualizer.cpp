///*
// * @brief Visualizer.cpp implementation of member functions
// */
//
//#include "Visualizer.h"
//#include "../Tools/Log.h"
//#include "../DataManagement/ContentProcess.h"
//
//TextVisualizer::TextVisualizer()
//{
//
//}
//TextVisualizer::~TextVisualizer()
//{
//
//}
//
//void TextVisualizer::display(const std::vector<TextProcess_sPtr>& sortedContent, const bool&, const CTimestamp&)
//{
//  INFO() << "display Text: \n";
//  INFO() << "-------------------------------------------------------\n";
//
//  std::vector<TextProcess_sPtr>::const_iterator it = sortedContent.begin();
//  for(; it != sortedContent.end(); ++it)
//    INFO() << (*it)->content;
//
//  INFO() << "\n\n";
//}
//
//
//
//
//
//SensorVisualizer::SensorVisualizer()
//{
//
//}
//
//SensorVisualizer::~SensorVisualizer()
//{
//
//}
//
//void SensorVisualizer::display(const std::vector<SensorProcess_sPtr>& sortedContent, const bool& usingTimestamp, const CTimestamp& timestamp)
//{
//  INFO() << "display Sensor: \n";
//  INFO() << "-------------------------------------------------------\n";
//
//  std::vector<SensorProcess_sPtr>::const_iterator it = sortedContent.begin();
//  for(; it != sortedContent.end(); ++it)
//  {
//    if(usingTimestamp)
//      INFO() << "timestamp: " << timestamp.to_ulong() << " value: " << (*it)->content << "\n";
//    else
//      INFO() << "value: " << (*it)->content << "\n";
//  }
//
//  INFO() << "\n";
//}
