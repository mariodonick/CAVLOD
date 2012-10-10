/*
 * @brief FileSystem.h
 *
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <boost/filesystem.hpp>
#include <iostream>

// return true if creation was successful otherwise false
inline const bool createFolder(const std::string& path)
{
  try
  {
    if (boost::filesystem::create_directory(path))
    {
      return true;
    }
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return false;
}

inline void renameFolderbyPath(const std::string& old_path, const std::string& new_path)
{
  try
  {
    boost::filesystem::rename(old_path, new_path);
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

inline void renameFolderByName(const std::string& path, const std::string& new_name)
{
  boost::filesystem::path p = path;

  std::string new_path = path;
  size_t pos = new_path.find( p.filename().string() );
  std::string ext = p.extension().string();
  std::string n =  new_name + ext;
  new_path.replace(pos, std::string::npos, n );

  renameFolderbyPath(path, new_path);
}

inline void removeFolder(const std::string& path)
{
  try
  {
    boost::filesystem::remove(path);
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}

// return true if the folder exists otherwise false
inline const bool existFolder(const std::string& path)
{
  try
  {
    boost::filesystem::file_status s = boost::filesystem::status(path);
    return boost::filesystem::is_directory(s);
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cerr << e.what() << std::endl;
    return false;
  }
}

#endif /* FILESYSTEM_H_ */
