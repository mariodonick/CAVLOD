/**
 * @brief 			NumericalLoader.cpp Member Function Implementations
 */

#include "NumericalLoader.h"

#include <iostream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

NumericalLoader::NumericalLoader(const std::string& path)
: file(path, std::ifstream::in)
{
  verifyOpenFile(path);
}

NumericalLoader::~NumericalLoader()
{
}

void NumericalLoader::verifyOpenFile(const std::string& path)
{
  if(!file.is_open())
  {
    std::cerr << "error open file: " + path + "\n";
    throw;
  }
}

void NumericalLoader::loadValuesFromFile(const char* separator)
{
  if(separator[0] == ' '){ std::cerr <<"do not use spaces as separator\n"; throw; }

  unsigned int index = 0;

  while( !file.eof() )
  {
    std::string line;
    std::getline(file, line);

    std::size_t comment_start = line.find("#");

    if(comment_start != std::string::npos)
      line.erase(line.begin()+comment_start, line.end());

    for(std::string::iterator it = line.begin(); it <= line.end(); )
    {
      if(*it == ' ' || *it == '\t' || *it == '\n')
        line.erase(it);
      else
        it++;
    }

    if(line.empty()) continue;

    std::vector<double> vec;
    value_matrix.push_back(vec);

    boost::char_separator<char> sep(separator);
    Tokenizer tok(line, sep);
    for (Tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    {
      try
      {
        double value = boost::lexical_cast<double>(*it);
        value_matrix[index].push_back(value);
      }
      catch(boost::bad_lexical_cast& e)
      {
        std::cerr << "error inside valueloader: " << e.what() << " -> "  << *it << "\n";
        std::cerr << "maybe you add a wrong value?\n";
      }
    }

    // if there are only bad inputs in this line. remove it
    if(value_matrix[index].empty())
    {
      value_matrix.pop_back();
    }
    else
      ++index;
  }
}

const std::vector<std::vector<double> >& NumericalLoader::getValueMatrix() const
{
  return value_matrix;
}

void NumericalLoader::reload(const std::string& path, const char* separator)
{
  value_matrix.clear();
  reopenFile(path);
  loadValuesFromFile(separator);
}

void NumericalLoader::reopenFile(const std::string& path)
{
  file.close();
  file.open(path, std::ifstream::in);
  verifyOpenFile(path);
}

void NumericalLoader::dump() const
{
  for(std::vector<std::vector<double> >::const_iterator i = value_matrix.begin(); i != value_matrix.end(); ++i)
  {
    std::cout << "| ";
    for(std::vector<double>::const_iterator j = i->begin(); j != i->end(); ++j)
      std::cout << std::setw(11) << std::setprecision(10) << *j << " | ";

    std::cout << "\n";
  }
  std::cout << "\n";
}
