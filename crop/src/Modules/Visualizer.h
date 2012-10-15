///*
// * @brief Visualizer.h
// *
// */
//
//#ifndef VISUALIZER_H_
//#define VISUALIZER_H_
//
//#include "../DataManagement/Content.h"
//#include "../TypesConfig/Pointer.h"
//
//#include <vector>
//
//template<class T>
//class Visualizer
//{
//public:
//  virtual ~Visualizer(){}
//
//  virtual void display(const std::vector<T>& sortedContent, const bool& usingTimestamp, const CTimestamp& timestamp) = 0;
//};
//
//
//class TextVisualizer : public Visualizer<TextProcess_sPtr>
//{
//public:
//  TextVisualizer();
//  virtual ~TextVisualizer();
//
//protected:
//  void display(const std::vector<TextProcess_sPtr>& sortedContent, const bool& usingTimestamp, const CTimestamp& timestamp);
//
//};
//
//
//class SensorVisualizer : public Visualizer<SensorProcess_sPtr>
//{
//protected:
//  SensorVisualizer();
//  virtual ~SensorVisualizer();
//
//protected:
//  void display(const std::vector<SensorProcess_sPtr>& sortedContent, const bool& usingTimestamp, const CTimestamp& timestamp);
//};
//
//
//#endif /* VISUALIZER_H_ */
