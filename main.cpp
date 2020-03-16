#include "Graph.h"
#include "Simple_window.h"
#include "Window.h"

int main() {
  Simple_window sw(Point(0, 0), 500, 500, "simple window");

  Polygon p;
  Circle c1({200, 200}, 100);
  c1.set_fill_color(Color::red);
  c1.set_color(Color::black);
  sw.attach(c1);
  sw.wait_for_button();
  return 0;
}