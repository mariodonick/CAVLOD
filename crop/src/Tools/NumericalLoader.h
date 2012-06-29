/**
 * @brief NumericalLoader.h
 */

#ifndef NUMERICALLOADER_H_
#define NUMERICALLOADER_H_

#include <fstream>
#include <string>
#include <vector>

class NumericalLoader
{
public:
  explicit NumericalLoader(const std::string& path);
  virtual ~NumericalLoader();

  void loadValuesFromFile(const char* separator = ",");
  const std::vector<std::vector<double> >& getValueMatrix() const;
  void reload(const std::string& path, const char* separator);
  void dump() const;

private:
  void reopenFile(const std::string& path);
  void verifyOpenFile(const std::string& path);

private:
  std::ifstream file;
  std::vector<std::vector<double> > value_matrix;
};

#endif /* NUMERICALLOADER_H_ */
