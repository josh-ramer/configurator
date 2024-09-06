#include "configurator.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using std::string, std::vector, std::cout, std::endl;
using json = nlohmann::json;

vector<string> parse_args(int argc, char *argv[]) {
  vector<string> input_files({string(argv[2])});
  // for (int i = 2; i < argc; i++) { // skip program name & flag
  //   input_files.push_back(string(argv[i]));
  // }
  return input_files; // move semantics
}

int help(int argc, char *argv[]) {
  string second_arg(argv[1]);
  if (argc == 1 ||
      (argc == 2 && (second_arg == "--help" || (second_arg == "-h")))) {
    cout << SPACER << endl;
    cout << "Usage: " << argv[0] << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "  --help     Display help menu" << endl;
    cout << "  --files    /path/file1 /path/file2 ... /path/fileN" << endl;
    cout << SPACER << endl;
    return FAILURE;
  } else if (second_arg != "--files") {
    cout << SPACER << endl;
    cout << "Improper flag, see usage." << endl;
    return FAILURE;
  }
  return SUCCESS;
}

int test_config(vector<string> file_paths) {
  cout << file_paths[0] << endl;
  Configurator<json, JsonParser> config(make_unique<JsonParser>(file_paths[0]));
  return SUCCESS;
}

int main(int argc, char *argv[]) {
  if (help(argc, argv))
    return SUCCESS;

  if (test_config(parse_args(argc, argv)))
    return FAILURE;
}
