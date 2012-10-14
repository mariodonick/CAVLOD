/*
 * @brief Log.cpp implementation of member functions
 */

#include "Log.h"

using namespace dbg;

const Verbosity Log::global = static_cast<Verbosity>(Config::instance()->verbosity);
const std::string Log::standardOutputPath = Config::instance()->logPath;

Log::Stream::Stream(const std::string& path)
: os(std::cout)
{

}

Log::Stream::~Stream()
{
  file.close();
}

void Log::Stream::endl()
{
  if(file.is_open())
  {
    os << "\n";
    file << "\n";
    file.flush();
  }
}

void Log::Stream::openFile(const std::string& path)
{
  // clear file
  file.open(path, std::ios::trunc);
  file.close();
  //open file
  file.open(path, std::ios::out | std::ios::app);

  if(!file.is_open())
    std::cout << "ERROR: Class Log: Cannot open standard Log-File!" << std::endl;
}



Log::Log(const Verbosity& level, const std::string& path)
: stream(new Stream(path))
, local(level)
, out(0)
{
  setVerboseColor();
}

Log::~Log()
{
  delete stream;
}

Log& Log::operator<<(StreamManipulator manip)
{
  // call the function, and return it's value
  return manip(*this);
}

Log& Log::operator<<(StandardEndLine manip)
{
  // call the function, but we cannot return it's value
  color = verboseColor; // reset color
  if(out)
  {
    stream->input("\033[m", true); // set normal color
    stream->endl();
  }
  return *this;
}

Log& Log::endl(Log& log)
{
  // print a new line
  log << std::endl;
  return log;
}

const bool Log::checkOutput()
{
  return( checkVerbosity() );
}

bool Log::checkVerbosity()
{
  if(global == NONE)
    return false;
  else if(global ==  LOW && local <= LOW)
    return true;
  else if(global == MEDIUM && local <= MEDIUM)
    return true;
  else if(global == HIGH && local <= HIGH)
    return true;
  else if(global == VERY_HIGH && local <= VERY_HIGH)
    return true;
  return false;
}

void Log::setVerboseColor()
{
  switch(local)
  {
    case NONE: verboseColor = ""; break;
    case LOW:  verboseColor = "\033[31m"; break; //red
    case MEDIUM: verboseColor = "\033[33m"; break; //yellow
    case HIGH: verboseColor = "\033[36m"; break; //cyan
    case VERY_HIGH: verboseColor = "\033[m"; break; // normal
  }
  color = verboseColor;
}

void Log::openLogFile(const std::string& path)
{
  stream->openFile(path);
}

void Log::computeVerbosity()
{
  out = checkVerbosity();
}
