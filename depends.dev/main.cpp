//=============================================================================
//
//
//

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <sys/stat.h>

//=============================================================================
std::string unitcpp() {
  return "D:/cygwin/usr/local/include/unitcpp_2.1.1/UnitCpp.h";
}

//=============================================================================
bool contains(const std::string& l, const std::string& r)
{
  return l.find(r) != std::string::npos;
}

//=============================================================================
bool contains(const std::set<std::string>& set, const std::string& str)
{
  return set.find(str) == end(set);
}

//=============================================================================
void get_recursive_dependencies(
  std::set<std::string>& existing_dependencies,
  std::string path
)
{
  std::ifstream file(path);
  std::string line;
  bool unitcpp_dependency = false;
  while (std::getline(file, line)) {
    if (contains(line, "#include")) {
      // It's an include line
      if (contains(line, "<UnitCpp.h>")) {
        // It is a dependency on UnitCpp
        unitcpp_dependency = true;
      } else {
        // Only systems headers will contain "<"
        if (!contains(line, "<")) {
          // get the middle out
          std::size_t pos_1 = line.find("\"");
          std::size_t pos_2 = line.rfind("\"");
          // Only add it if there are " marks.
          if (pos_1 != std::string::npos && pos_2 != std::string::npos) {
            std::string header(line, pos_1 + 1, pos_2 - pos_1 - 1);
            if (contains(existing_dependencies, header)) {
              existing_dependencies.insert(header);
              get_recursive_dependencies(existing_dependencies, header);
            }
          }
        }
      }
    }
  }
  if (unitcpp_dependency) {
    existing_dependencies.insert(unitcpp());
  }
}

//=============================================================================
std::set<std::string> get_dependencies(std::string path)
{
  std::set<std::string> dependencies;
  get_recursive_dependencies(dependencies, path);
  return dependencies;
}

//=============================================================================
void print_dependencies(std::string path)
{
  std::set<std::string> dependencies = get_dependencies(path);
  std::string header(path, 0, path.find("."));
  std::cout
    << "$(OBJ_DIRECTORY)/"
    << header
    << ".obj: "
    << header
    << ".cpp ";
  for (const std::string& dependency : dependencies) {
    std::cout << dependency << " ";
  }
  std::cout << "\n";
}

//=============================================================================
int main(int argc, char** argv)
{
  for (int i = 1; i < argc; ++i) {
    print_dependencies(argv[i]);
  }
  return 0;
}

