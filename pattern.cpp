#include <fstream>
#include <iostream>
#include <stack>
#include <cmath>
#include <iomanip>

using std::cout;
using std::endl;
using std::cerr;
using std::stack;
using std::min;
using std::max;

using coord = struct { float x,y; };
using state = struct {
  coord pos;
  float direction;
  float dist;
  float ang;
};

stack<state> st;
state current;
coord maxBound;
coord minBound;

void push()
{
  st.push(current);
}

void pop()
{
  if(st.empty()){
    cerr << "Cant pop empty stack" << endl;
    exit(2);
  }
  current = st.top();
  st.pop();
}

void output()
{
  cout << std::fixed << current.pos.x << "," << current.pos.y;
}

void updateBounds()
{
  minBound.x = min(minBound.x,current.pos.x);
  minBound.y = min(minBound.y,current.pos.y);
  maxBound.x = max(maxBound.x,current.pos.x);
  maxBound.y = max(maxBound.y,current.pos.y);
}

void forward()
{
  output();
  cout << " -> ";
  current.pos.x += sin(current.direction) * current.dist;
  current.pos.y += cos(current.direction) * current.dist;
  updateBounds();
  output();
  cout << endl;
}

void left()
{
  current.direction -= current.ang;
}

void right()
{
  current.direction += current.ang;
}

int main(int argc, char const *argv[]) {
  std::fstream f;
  f.open(argv[1], std::fstream::in);

  current.ang = 0.174533;
  current.dist = 1.0;
  current.direction = 0.0;
  current.pos.x = 0.0;
  current.pos.y = 0.0;

  maxBound.x = maxBound.y = 0.0;
  minBound.x = minBound.y = 0.0;

  char c;
  while (f >> c)
  {
    switch (c){
      case '[':
        push();
        break;
      case ']':
        pop();
        break;
      case 'F':
        forward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      default:
        cerr << "Unexpected instruction " << c << endl;
        exit(1);
    }
  }

  cout << "[(" << minBound.x << "," << minBound.y << "),(" << maxBound.x << "," << maxBound.y << ")]" << endl;

  return 0;
}
