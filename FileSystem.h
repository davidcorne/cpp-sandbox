//=============================================================================
//
// 

#ifndef FileSystem_H
#define FileSystem_H

#include <UnitCpp.h>

class Path;
class FileSystemError;

//=============================================================================
class FileSystem {
public:

  FileSystemError create_directory(Path directory);
  // Creates and empty directory on the file system.
  // directory should not already exist.

  FileSystemError delete_directory(Path directory);
  // Removes an empty directory, directory.
  // directory should exist.
  // directory should be empty.

  FileSystemError delete_tree(Path directory);
  // Removes a directory and all it's subdirectories and files.
  // directory should empty

  FileSystemError delete_path(Path path);
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

};

//=============================================================================
enum class FileSystemErrorType {
  OK,
  DIRECTORY_NOT_EXISTS,
  DIRECTORY_ALREADY_EXISTS,
  UNKNOWN
};

//=============================================================================
class FileSystemError {
public:

  FileSystemError(FileSystemErrorType type);

  explicit operator bool() const;
  // Ask if (error) or !error;

  std::string message() const;
  // What has gone wrong?
  
private:

  FileSystemErrorType m_type;
};

#include "FileSystem_source.h"

#endif
