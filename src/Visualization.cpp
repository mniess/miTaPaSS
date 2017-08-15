#include "src/Visualization.h"

#include <gtkmm.h>

#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::cout, std::endl;
using std::min, std::max;

Visualization::Visualization() {
  vector<vector<int>  > a(10, std::vector<int>(20, 0));
  a[0][0] = 1;
  a[1][1] = 2;
  a[1][2] = 10;
  a[9][9] = 10;
  area = a;
}

bool Visualization::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  cr->set_source_rgb(1, 0, 0.5);
  cr->set_line_width(1.0);
  if (width > 0 && height > 0) {
    long unsigned int space = 1;
    const int size = max(space, min(width/area.size(), height/area[0].size() ));

    for (int i = 0; i < area.size(); i += 1) {
      for (int j = 0; j < area[i].size(); j += 1) {
        double tokens = area[i][j];
        if (tokens != 0) {
          float col = 0.5 + (min(10.0, tokens)/20);
          col < 0 ? 0 : col;
          cr->set_source_rgb(col, 0, 0);
        } else {
          cr->set_source_rgb(0.8, 0.8, 0.8);
        }

        cr->rectangle(i*size, j*size, size-space, size-space);
        cr->fill();
      }
    }
  }
  return true;
}


void Visualization::step(vector<vector<int> > area) {
  this->area = area;
}
