#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::map;
using std::regex;
using std::stringstream;

using ruleDef = string;
using ruleKey = char;
using rules = map<ruleKey,ruleDef>;

const auto DEBUG = false;

string
processRule(string input,const rules &rs)
{
  stringstream out;

  for(const auto &ch : input)
  {
    if(rs.count(ch)==1){
      out << rs.at(ch);
    }else{
      out << ch;
    }
  }

  return out.str();
}

int
main(int argc, char const *argv[]) {
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  int processing = 10;

  if(argc >=2)
    processing = std::stoi(argv[2]);

  rules r;
  const regex linePattern ("\\s*([a-zA-Z])\\s*->\\s*([a-zA-Z\\[\\]]*)\\s*");
  for (std::string line; std::getline(f, line);){
    std::smatch matches;
    if(regex_match(line,matches,linePattern)){
      ruleKey key = matches[1].str()[0];
      ruleDef def = matches[2].str();
      r[key] = def;
    }else{
      cerr << "Unexpected input line: " << line << endl;
      exit(1);
    }
  }

  f.close();

  if(DEBUG)
    cout << "Successfully read " << r.size() << " rules" << endl;

  if(r.count('S')!=1){
    cerr << "Starting rule S not found" << endl;
    exit(1);
  }

  auto processed = string("S");
  for(int i=0;i<processing;i++)
    processed = processRule(processed,r);

  cout << processed << endl;

  return 0;
}
