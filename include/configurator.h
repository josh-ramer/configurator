#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using std::unique_ptr, std::string, std::ifstream, std::ofstream, std::vector,
    std::cout, std::endl, std::stringstream, std::getline;
using json = nlohmann::json;

constexpr int SUCCESS = 0;
constexpr int FAILURE = 1;
const string SPACER = "\n--------------------------------------\n";

template <typename S> class ConfigParser {
public:
  virtual S parse() = 0;
};

template <typename S, typename P> class Configurator {
public:
  Configurator(unique_ptr<P> config_parser)
      : parser(std::move(config_parser)), config(parser->parse()) {}
  string set_value(string key, string value);
  template <typename T> T get_value(string key);
  void print();

private:
  unique_ptr<P> parser;
  S config;
};

class JsonParser : ConfigParser<json> {
public:
  JsonParser(string file_path) : istream(file_path) {}
  json parse() { return json::parse(istream); }

private:
  ifstream istream;
};

template <typename S, typename P> void Configurator<S, P>::print() {
  cout << SPACER;
  cout << config.dump(4);
  cout << SPACER;
}

template <typename S, typename P>
template <typename T>
T Configurator<S, P>::get_value(string key) {
  stringstream ss(key);
  string token;

  vector<string> key_parts;
  while (getline(ss, token, '.')) {
    key_parts.push_back(token);
  }

  json config_part(config);
  for (int i = 0; i < key_parts.size() - 1; i++) {
    config_part = config_part[key_parts[i]];
  }
  return config_part[key_parts.back()];
}
