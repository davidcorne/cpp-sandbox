#include "Path.h"
#include "dgc_getenv.h"

#include <sys/stat.h>

#ifndef _MSC_VER
// Non-windows stdlib stuff
#include <dirent.h>
#define DGC_MKDIR(dir) mkdir((dir), S_IRWXU)
#else
#include <windows.h>
#include <direct.h>
#define DGC_MKDIR(dir) _mkdir((dir))
#endif

//----- FileSystem source.

//=============================================================================
Path FileSystem::temporary_directory() const
{
  static std::string variables[] = {"TMPDIR", "TMP", "TEMP", "TEMPDIR"};
  Path temp_dir("");
  for (const std::string& variable : variables) {
    auto pair = DGC::getenv(variable.c_str());
    if (pair.first) {
      temp_dir = Path(pair.second);
      if (temp_dir.exists()) {
        break;
      }
    }
  }
  return temp_dir;
}

//=============================================================================
FileSystemError FileSystem::create_directory(Path directory)
{
  FileSystemError error(FileSystemErrorType::DIRECTORY_ALREADY_EXISTS);
  if (!directory.exists()) {
    int res = DGC_MKDIR(directory.path().c_str());
    if (res != 0) {
      error = FileSystemErrorType::UNKNOWN;
    } else {
      error = FileSystemErrorType::OK;
    }
  }
  return error;
}

//=============================================================================
FileSystemError FileSystem::delete_directory(Path directory)
{
  FileSystemError error(FileSystemErrorType::DIRECTORY_NOT_EXISTS);
  if (directory.exists()) {
    bool success = false;
#ifdef _MSC_VER
    success = !!RemoveDirectory(directory.path().c_str());
#else
    success = std::remove(directory.path().c_str()) == 0;
#endif
    if (!success) {
      error = FileSystemErrorType::UNKNOWN;
    } else {
      error = FileSystemErrorType::OK;
    }
  }
  return error;
}





// <nnn> //=============================================================================
// <nnn> std::vector<Path> FileSystem::list_contents(Path path) const
// <nnn> {
// <nnn>   std::vector<Path> list;
// <nnn> #ifndef _MSC_VER
// <nnn>   DIR* dp = nullptr;
// <nnn>   struct dirent* dirp = nullptr;
// <nnn>   if ((dp  = opendir(path.path().c_str())) == NULL) {
// <nnn>     // error
// <nnn>     return list;
// <nnn> // <nnn> // <nnn>     cout << "Error(" << errno << ") opening " << dir << endl;
// <nnn> // <nnn>     return errno;
// <nnn>   }

// <nnn>   while ((dirp = readdir(dp)) != NULL) {
// <nnn>     Path path(dirp->d_name);
// <nnn>     if (path != Path(".") && path != Path("..")) {
// <nnn>       list.push_back(path);
// <nnn>     }
// <nnn>   }
// <nnn>   closedir(dp);
// <nnn> #endif
// <nnn>   return list;  
// <nnn> }

// <nnn> //=============================================================================
// <nnn> bool FileSystem::delete_tree(Path directory)
// <nnn> {
// <nnn>   bool result = false;
// <nnn>   if (directory.exists()) {
// <nnn>     // <nnn> // directory should be empty
// <nnn>     // <nnn> int i_res = nftw(
// <nnn>     // <nnn>   directory.path().c_str(),
// <nnn>     // <nnn>   remove_path_callback,
// <nnn>     // <nnn>   64,                  // The limit of recursion
// <nnn>     // <nnn>   FTW_DEPTH | FTW_PHYS // Depth first, don't follow symbolic links
// <nnn>     // <nnn> );
// <nnn>     // <nnn> result = i_res == 0;
// <nnn>     std::vector<Path> paths = list_contents(directory);
// <nnn>     for (const Path& path : paths) {
// <nnn>       if (path.is_directory()) {
// <nnn>         // Recurse
// <nnn>         delete_directory
// <nnn>       }
// <nnn>     }
// <nnn>   }
// <nnn>   return result;
// <nnn> }

//----- FileSystemError source.

//=============================================================================
FileSystemError::FileSystemError(FileSystemErrorType type)
  : m_type(type)
{
}

//=============================================================================
FileSystemError::operator bool() const
{
  return m_type != FileSystemErrorType::OK;
}

//=============================================================================
std::string FileSystemError::message() const
{
  static std::map<FileSystemErrorType, std::string> error_map = {
    {FileSystemErrorType::OK, "No error."},
    {FileSystemErrorType::DIRECTORY_NOT_EXISTS, "Given directory does not exist."},
    {FileSystemErrorType::DIRECTORY_ALREADY_EXISTS, "Directory exists, and should not.."},
    {FileSystemErrorType::UNKNOWN, "Unknown error."}
  };
  return error_map[m_type];
}

#undef DGC_MKDIR
