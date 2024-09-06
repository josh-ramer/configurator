#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using std::unique_ptr, std::string, std::ifstream, std::ofstream, std::vector, std::cout, std::endl;
using json = nlohmann::json;

constexpr int SUCCESS = 0;
constexpr int FAILURE = 1;
const string SPACER = "\n--------------------------------------";

template<typename S>
class ConfigParser {
public:
  virtual S parse() = 0;
};

template<typename S, typename P>
class Configurator {
public:
  Configurator(unique_ptr<P> config_parser) {
    parser = std::move(config_parser);
    config = config_parser->parse();
  }
  string set_value(string key, string value);
  string get_value(string key);
  int print();
private:
  unique_ptr<P> parser;
  S config;
};

class JsonParser : ConfigParser<json> {
public:
  JsonParser(string file_path)
  : istream(file_path), ostream(file_path) {
  if (!istream.is_open() || !ostream.is_open()) {
    throw std::runtime_error("Failed to open file: " + file_path);
  }
  cout << "file_path: " << file_path << endl;
}

  json parse() {
    return json::parse(istream);
  }

private:
  ifstream istream;
  ofstream ostream;
};


