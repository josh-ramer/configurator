#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using std::unique_ptr, std::string, std::ifstream, std::ofstream, std::vector,
    std::cout, std::endl;
using json = nlohmann::json;

constexpr int SUCCESS = 0;
constexpr int FAILURE = 1;
const string SPACER = "\n--------------------------------------";

template <typename S> class ConfigParser {
public:
  virtual S parse() = 0;
};

template <typename S, typename P> class Configurator {
public:
  Configurator(unique_ptr<P> config_parser)
      : parser(std::move(config_parser)), config(parser->parse()) {}
  string set_value(string key, string value);
  string get_value(string key);
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
  cout << SPACER << endl;
  cout << config << endl;
}

template <typename S, typename P>
string Configurator<S, P>::get_value(string key) {
  return config[key];
}
