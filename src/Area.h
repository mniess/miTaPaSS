#ifndef SRC_AREA_H_
#define SRC_AREA_H_

#include <vector>
#include <mutex>

struct Area{
  std::vector< std::vector< int > > area;
  std::mutex area_mutex;

  Area() { }

  Area(int width, int length) {
    std::vector< std::vector< int > > a(width, std::vector<int>(length, 0));
    area = a;
  }

  Area& operator=(const Area &a) {
    if (this == &a) {
      return *this;
    }
    area = a.area;
    return *this;
  }

  Area(const Area &a) {
    if (this == &a) {
      return;
    }
    area = a.area;
  }

  int size() {
    return area.size();
  }


  std::vector< int >& operator[](const int i) {
    std::lock_guard<std::mutex> lock(area_mutex);
    return area[i];
  }

  const std::vector< int >& operator[](const int i) const{
    return area[i];
  }
};

#endif  // SRC_AREA_H_
