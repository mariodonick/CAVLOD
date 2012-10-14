/*
 * @brief Log.cpp implementation of member functions
 */

#include "Log.h"

#include <boost/program_options.hpp>

using namespace dbg;

std::mutex Log::Stream::logMutex;

Log::Stream::Stream()
: os(std::cout)
{

}

Log::Stream::~Stream()
{
  file.close();
}

void Log::Stream::endl()
{
  os << "\n";
  if(file.is_open())
  {
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



Log::Log(const Verbosity& level)//, const std::string& path)
: stream(new Stream)
, local(level)
, out(false)
{
  setVerboseColor();

  try
   {
     std::string stdLogPath = Config::instance()->homePath + "/CAVLOD/output.log";
     std::string log_filename = Config::instance()->homePath + "/CAVLOD/log.conf";
     boost::program_options::options_description my_options("log");

     my_options.add_options()
       ("Output.verbosity", boost::program_options::value<unsigned int>()->default_value(4), "level to configure outputs")
       ("Output.logPath", boost::program_options::value<std::string>()->default_value(stdLogPath), "path to store the outputs")
     ;

     std::ifstream log_config_stream(log_filename.c_str());

     boost::program_options::variables_map vm;
     boost::program_options::store(boost::program_options::parse_config_file(log_config_stream, my_options), vm);
     boost::program_options::notify(vm);

     verbosity = static_cast<Verbosity>( vm["Output.verbosity"].as<unsigned int>() );
     standardOutputPath = vm["Output.logPath"].as<std::string>();
   }
   catch (std::exception& e)
   {
     std::cerr << e.what() << std::endl;
   }
   out = checkVerbosity();
   openLogFile();
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
  if(verbosity == NONE)
    return false;
  else if(verbosity ==  LOW && local <= LOW)
    return true;
  else if(verbosity == MEDIUM && local <= MEDIUM)
    return true;
  else if(verbosity == HIGH && local <= HIGH)
    return true;
  else if(verbosity == VERY_HIGH && local <= VERY_HIGH)
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

void Log::openLogFile()
{
  stream->openFile(standardOutputPath);
}
