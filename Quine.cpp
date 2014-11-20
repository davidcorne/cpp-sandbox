#include<string>
#include<iostream>
#include <algorithm>

std::string a("#include<string>\n#include<iostream>\n#include <algorithm>\n\nstd::string a(\"X\");\nint main(){\n  std::string b=a;\n  b.reserve(b.length()*3);\n  for (auto it = begin(b); it != end(b); ++it) {\n    if (*it == '\\n') {\n      *it = 'n';\n      b.insert(it, '\\\\');\n      ++it;\n    }\n    if (*it == '\"') {\n      b.insert(it, '\\\\');\n      ++it;\n    }\n    if (*it == '\\\\') {\n      b.insert(it, '\\\\');\n      ++it;\n    }\n  }\n  auto it = std::find(a.begin(), a.end(), 'X');\n  a.replace(it, it + 1, b.begin(), b.end());\n  std::cout << a;\n}\n");
int main(){
  std::string b=a;
  b.reserve(b.length()*3);
  for (auto it = begin(b); it != end(b); ++it) {
    if (*it == '\n') {
      *it = 'n';
      b.insert(it, '\\');
      ++it;
    }
    if (*it == '"') {
      b.insert(it, '\\');
      ++it;
    }
    if (*it == '\\') {
      b.insert(it, '\\');
      ++it;
    }
  }
  auto it = std::find(a.begin(), a.end(), 'X');
  a.replace(it, it + 1, b.begin(), b.end());
  std::cout << a;
}
