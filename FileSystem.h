//=============================================================================
//
// 

#ifndef FileSystem_H
#define FileSystem_H

#include <UnitCpp.h>

class Path;

//=============================================================================
class FileSystem {
public:

  bool create_directory(Path directory);
  // Creates and empty directory on the file system.
  // directory should not already exist.

  bool delete_directory(Path directory);
  // Removes an empty directory, directory.
  // directory should exist.
  // directory should be empty.

  bool delete_tree(Path directory);
  // Removes a directory and all it's subdirectories and files.
  // directory should empty

  bool delete_path(Path path);
  // Delete the file or directory.
  // If path is a directory, it deletes the contents recursivly.

  std::vector<Path> list_contents(Path path) const;
  // Lists the contents of the path.
  // If path is a directory it returns a vector of it's contents. (not
  // including "." or "..")
  // If path is a file, it returns a vector containing the file.
  
  Path temporary_directory() const;
  // Returns a temporary directory, should be able to write to.
  
private:

  // <nnn> static int remove_path_callback(
  // <nnn>   const char* path,
  // <nnn>   const struct stat* sb,
  // <nnn>   int typeflag,
  // <nnn>   struct FTW* ftwbuf
  // <nnn> );

};

#include "FileSystem_source.h"

#endif
