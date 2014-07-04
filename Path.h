//=============================================================================
//
// 

#ifndef Path_H
#define Path_H

#include <string>

//=============================================================================
class Path {
public:

  Path(std::string path);

  ~Path();

  std::string path() const;
  // Returns the path
  
  std::string extension() const;
  // Returns the file extension including the dot.
  // Examples:
  //   Path("t.txt").extension() == ".txt"
  //   Path("t.md.txt").extension() == "md.txt"
  //   Path("t.").extension() == "."
  //   Path("t").extension() == ""

  bool is_file() const;
  // Returns if it's a file or not.

  bool is_directory() const;
  // Returns if it's a directory.

  bool exists() const;
  // Return whether this path exists or not.

  bool operator==(Path path) const;

  bool operator!=(Path path) const;

private:
  
  friend class utest_Path;
  std::string m_path;
};

//=============================================================================
std::ostream& operator<<(std::ostream& os, const Path& path);

#include "Path_source.h"
#endif
