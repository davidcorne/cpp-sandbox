//=============================================================================
// Source for Path
// Path is a utility class for this repository, so it has the source included.

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

//=============================================================================
Path::Path(std::string path)
  : m_path(path)
{
}

//=============================================================================
Path::~Path()
{
}

//=============================================================================
std::string Path::path() const
{
  return m_path;
}

//=============================================================================
std::string Path::extension() const
{
  size_t index = m_path.find_first_of('.');
  std::string ext("");
  if (index != std::string::npos) {
    ext = std::string(m_path, index, m_path.length() - index);
  }
  return ext;
}

//=============================================================================
bool Path::operator==(Path other) const
{
  return other.path() == path();
}

//=============================================================================
bool Path::operator!=(Path other) const
{
  return !(*this == other);
}


//=============================================================================
bool Path::exists() const
{
  struct stat info;
  return stat(m_path.c_str(), &info) == 0;
}

//=============================================================================
bool Path::is_file() const
{
  bool l_is_file = false;
  if (exists()) {
    struct stat info;
    stat(m_path.c_str(), &info);
    l_is_file = !!(info.st_mode & S_IFREG);
  }
  return l_is_file;
}

//=============================================================================
bool Path::is_directory() const
{
  bool l_is_file = false;
  if (exists()) {
    struct stat info;
    stat(m_path.c_str(), &info);
    l_is_file = !!(info.st_mode & S_IFDIR);
  }
  return l_is_file;
}

//=============================================================================
std::ostream& operator<<(std::ostream& os, const Path& path)
{
  os << path.path();
  return os;
}
