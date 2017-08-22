#ifndef SRC_VISUALIZATION_H_
#define SRC_VISUALIZATION_H_

#include <gtkmm.h>

#include <vector>
#include "src/Area.h"
#include "src/Robot.h"

class Visualization : public Gtk::DrawingArea{
 public:
  Visualization();
  void step(Area a, std::vector<Robot> r);
 private:
  Area area;
  std::vector<Robot> robots;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif  // SRC_VISUALIZATION_H_
