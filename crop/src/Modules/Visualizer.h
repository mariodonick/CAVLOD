/*
 * @brief Visualizer.h
 *
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "../DataManagement/Content.h"
#include "../TypesConfig/Pointer.h"

#include <vector>

template<class T>
class Visualizer
{
public:
  virtual ~Visualizer(){}

  virtual void display(const std::vector<T>& sortedContent) = 0;
};


class TextVisualizer : public Visualizer<Text_sPtr>
{
public:
  TextVisualizer();
  virtual ~TextVisualizer();

protected:
  void display(const std::vector<Text_sPtr>& sortedContent);

};


class SensorVisualizer : public Visualizer<Sensor_sPtr>
{
protected:
  SensorVisualizer();
  virtual ~SensorVisualizer();

protected:
  void display(const std::vector<Sensor_sPtr>& sortedContent);
};


#endif /* VISUALIZER_H_ */
