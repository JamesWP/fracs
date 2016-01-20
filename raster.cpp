#include <SFML/Graphics.hpp>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>

using std::vector;
using std::regex;
using std::stof;
using std::cerr;
using std::cout;
using std::endl;

using coord = struct { float x,y; };
using line = struct { coord start, end; };
sf::RenderTexture tex;
coord minBounds;
coord maxBounds;
vector<line> lines;

void save()
{
  tex.getTexture().copyToImage().saveToFile("text.png");
}

void init()
{
  tex.create(800,600);
  tex.clear(sf::Color::Black);
}

float lerp(float nmin,float nmax,float omin, float omax, float val)
{
  auto amount = (val-omin) / (omax-omin);
  return nmin + (nmax - nmin) * amount;
}

coord project(coord p){
  return {
    lerp(0,800,minBounds.x,maxBounds.x,p.x),
    lerp(0,600,minBounds.y,maxBounds.y,p.y)
  };
}

void draw(coord s, coord e)
{
  s = project(s);
  e = project(e);
  const sf::Vertex line[] =
  {
      sf::Vertex(sf::Vector2f(s.x, s.y)),
      sf::Vertex(sf::Vector2f(e.x, e.y))
  };

  tex.draw(line, 2, sf::Lines);
}

void read(const char file[]){
  std::fstream f;
  f.open(file, std::fstream::in);

  const regex linePattern ("\\s*(-?\\d*(\\.\\d*)?)\\s*,\\s*(-?\\d*(\\.\\d*)?)\\s*->\\s*(-?\\d*(\\.\\d*)?)\\s*,\\s*(-?\\d*(\\.\\d*)?)\\s*");
  const regex boundsPattern ("\\[\\((-?\\d*(\\.\\d*)?),(-?\\d*(\\.\\d*)?)\\),\\((-?\\d*(\\.\\d*)?),(-?\\d*(\\.\\d*)?)\\)\\]");
  // 1,3 -> 5,7
  for (std::string line; std::getline(f, line);){
    std::smatch matches;
    if(regex_match(line,matches,linePattern)){
      coord start = {stof(matches[1].str()),stof(matches[3].str())};
      coord end = {stof(matches[5].str()),stof(matches[7].str())};
      lines.push_back({start,end});
    }else if(regex_match(line,matches,boundsPattern)){
      minBounds = {stof(matches[1].str()),stof(matches[3].str())};
      maxBounds = {stof(matches[5].str()),stof(matches[7].str())};
    }else{
      cerr << "Unexpected input line: " << line << endl;
      exit(1);
    }
  }
}

void output(){
  init();
  for(const auto &l : lines)
    draw(l.start, l.end);
  save();
}

int main(int argv, char* args[])
{
  read(args[1]);
  output();
}
