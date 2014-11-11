//=============================================================================
// Source for Path
// Path is a utility class for this repository, so it has the source included.

#include <fstream>

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
  std::ifstream ifile(m_path);
  return !!ifile;
}

//=============================================================================
std::ostream& operator<<(std::ostream& os, const Path& path)
{
  os << path.path();
  return os;
}
