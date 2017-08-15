#ifndef SRC_VISUALIZATION_H_
#define SRC_VISUALIZATION_H_

#include <gtkmm.h>

#include <vector>

class Visualization : public Gtk::DrawingArea{
 public:
  Visualization();
  void step(std::vector<std::vector<int> > area);
 private:
  std::vector<std::vector<int> > area;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif  // SRC_VISUALIZATION_H_
