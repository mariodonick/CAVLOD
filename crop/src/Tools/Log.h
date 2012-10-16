/*
 * @brief:   Log.h
 */
#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

#include "../TypesConfig/Config.h"

// todo performance optimieren: std::cout + std::endl ist doppelt so fix

/*
 * Example Usage
 *
 * first set your global verbosity: none means nothing is displayed
 *
 * usually you use one of the following statements:
 * DBG()    << "something you want to print" << ENDL;   // print the text in white - use it for debugging purpose
 * INFO()    << "something you want to print" << ENDL;   // print the text in cyan
 * WARNING()  << "something you want to print" << ENDL; // print the text in yellow
 * ERROR()    << "something you want to print" << ENDL; // print the text in red
 *
 * Colorful!
 * warning is printed in yellow, error in red and debug in normal(white).
 * You can change the color b< adding this: "<< dbg::blue <<".
 * The color reset automatically to white after ENDL.
 */

namespace dbg
{

enum Verbosity
{
  NONE = 0, // nothing
  LOW = 1, // error
  MEDIUM = 2, // error, warning
  HIGH = 3, // error, warning, info
  VERY_HIGH = 4 // error warning, info, debug
};

class Log
{
  class Stream
  {
  public:
    Stream();
    virtual ~Stream();

    void endl();

    // print no color by file output
    // set flag to true if a color input is expected
    template<typename T>
    void input(T in, bool color = false)
    {
      std::unique_lock<std::mutex> lock(logMutex);
      os << in;
      if(file.is_open())
      {
        if(!color)
          file << in;
      }
    }
    void openFile(const std::string& path);

  private:
    std::ofstream file;
    std::ostream& os;

    static std::mutex logMutex;
  }*stream;

public:
  Log(const Verbosity& level);
  virtual ~Log();

  typedef Log& (*StreamManipulator)(Log&); // function that takes a custom stream, and returns it
  // take in a function with the custom signature
  Log& operator<<(StreamManipulator manip);

  typedef std::basic_ostream<char, std::char_traits<char> > CoutType; // this is the type of std::cout
  typedef CoutType& (*StandardEndLine)(CoutType&); // this is the function signature of std::endl

  // define an operator<< to take in std::endl
  Log& operator<<(StandardEndLine manip);

  // define the custom endl for this stream.
  // note how it matches the 'StreamManipulator'
  // function signature
  static Log& endl(Log& log);

  template <typename T>
  inline Log& operator<<(const T& t)
  {
    if(out)
    {
      stream->input(color, true);
      stream->input(t);
    }
    return *this;
  }

  inline Log& operator<<(const bool& t)
  {
    if(out)
    {
      stream->input(color, true);
      stream->input( (t==true?"true":"false") );
    }
    return *this;
  }

  inline void black() { color = "\033[30m"; }
  inline void red() { color = "\033[31m"; }
  inline void green() { color = "\033[32m"; }
  inline void yellow() { color = "\033[33m"; }
  inline void blue() { color = "\033[34m"; }
  inline void purple() { color = "\033[35m"; }
  inline void cyan() { color = "\033[36m"; }
  inline void normal() { color = "\033[m"  ; }

  void openLogFile();

private:
  const bool checkOutput();
  void setVerboseColor();
  bool checkVerbosity();

private:
  std::string standardOutputPath; // path to logging file
  Verbosity verbosity; // the verbosity for all classes

  Verbosity local;        // the verbosity of this class
  std::string verboseColor; // hold the color of the actual verbosity
  std::string color;        // current color
  bool out;          // always place this variable at the last of all member declarations

}; // class Log

inline Log& black(Log& d) { d.black(); return d; }
inline Log& red(Log& d) { d.red(); return d; }
inline Log& green(Log& d) { d.green(); return d; }
inline Log& yellow(Log& d) { d.yellow(); return d; }
inline Log& blue(Log& d) { d.blue();  return d; }
inline Log& purple(Log& d) { d.purple(); return d; }
inline Log& cyan(Log& d) { d.cyan(); return d; }
inline Log& white(Log& d) { d.normal(); return d; }
inline Log& normal(Log& d) { d.normal(); return d; }

// default classes
static Log DBG( VERY_HIGH);//, Log::standardOutputPath );
static Log INFO( HIGH);//, Log::standardOutputPath );
static Log WARNING( MEDIUM);//, Log::standardOutputPath );
static Log ERROR( LOW);//, Log::standardOutputPath );

}; // namespace dbg

// use the default outputs
inline dbg::Log& DBG() { dbg::DBG << "Debug: "; return dbg::DBG; }
inline dbg::Log& INFO() { dbg::INFO << "Info: "; return dbg::INFO; }
inline dbg::Log& WARNING() { dbg::WARNING << "Warning: "; return dbg::WARNING; }
inline dbg::Log& ERROR() { dbg::ERROR << "Error: "; return dbg::ERROR; }

// make a new line, call flush and set the color back to normal
inline dbg::Log& ENDL(dbg::Log& d) { d << dbg::Log::endl; return d; }

#endif // LOG_H_
