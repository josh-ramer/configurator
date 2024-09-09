#include "configurator.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using std::string, std::vector, std::cout, std::endl;
using json = nlohmann::json;

vector<string> parse_args(int argc, char *argv[]) {
  vector<string> input_files;
  cout << SPACER;
  cout << "INPUT_FILES:" << endl;
  for (int i = 2; i < argc; i++) { // skip program name & flag
    string file(argv[i]);
    input_files.push_back(file);
    cout << "    " << file;
    if (i < argc - 1)
      cout << endl;
  }
  cout << SPACER;
  return input_files; // move semantics
}

int help(int argc, char *argv[]) {
  string second_arg(argv[1]);
  if (argc == 1 ||
      (argc == 2 && (second_arg == "--help" || (second_arg == "-h")))) {
    cout << SPACER;
    cout << "Usage: " << argv[0] << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "  --help     Display help menu" << endl;
    cout << "  --files    /path/file1 /path/file2 ... /path/fileN" << endl;
    cout << SPACER;
    return FAILURE;
  } else if (second_arg != "--files") {
    cout << SPACER;
    cout << "Improper flag, see usage." << endl;
    return FAILURE;
  }
  return SUCCESS;
}

int test_config(vector<string> file_paths) {
  Configurator<json, JsonParser> config(make_unique<JsonParser>(file_paths[0]));
  config.print();

  cout << SPACER;
  cout << config.get_value<string>("device") << endl;
  auto section = config.get_value<json>("section");
  cout << section.dump(4) << endl;
  cout << config.get_value<string>("section.model") << endl;
  cout << config.get_value<json>("section.section").dump(4) << endl;
  cout << config.get_value<string>("section.section.waferSize") << endl;
  cout << SPACER;
  return SUCCESS;
}

int main(int argc, char *argv[]) {
  if (help(argc, argv))
    return SUCCESS;

  if (test_config(parse_args(argc, argv)))
    return FAILURE;
}
