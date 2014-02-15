#ifndef SHEET_H
#define SHEET_H

#include <initializer_list>
#include <iostream>
#include <vector>
#include "line.h"

class Sheet
{
public:
   Sheet &add_line(const Line &line);
   bool empty() const;
   int line_count() const;
   bool operator==(const Sheet &rhs) const;
   Line &operator[](int line_index);
   const Line &operator[](int line_index) const;
private:
   friend std::ostream& operator<<(std::ostream& os, const Sheet &sheet);
   std::vector<Line> m_lines;
};

#endif
