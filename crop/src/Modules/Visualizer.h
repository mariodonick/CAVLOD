/*
 * @brief Visualizer.h
 *
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "../DataManagement/Content.h"

#include <vector>

template<class T>
class Visualizer
{
public:
  virtual ~Visualizer(){}

  virtual void display(const std::vector<T*>& sortedContent) = 0;
};


class TextVisualizer : public Visualizer<Text>
{
public:
  TextVisualizer();
  virtual ~TextVisualizer();

protected:
  void display(const std::vector<Text*>& sortedContent);

private:
  unsigned int old_line;
};


class SensorVisualizer : public Visualizer<Sensor>
{
protected:
  SensorVisualizer();
  virtual ~SensorVisualizer();

protected:
  void display(const std::vector<Sensor*>& sortedContent);
};


class PictureVisualizer : public Visualizer<Picture>
{
protected:
  PictureVisualizer();
  virtual ~PictureVisualizer();

protected:
  void display(const std::vector<Picture*>& sortedContent);
};


#endif /* VISUALIZER_H_ */
