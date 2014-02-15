#ifndef LINE_H
#define LINE_H

#include "sheet/line.h"
#include "sheet/line_part.h"
#include <initializer_list>
#include <iostream>
#include <vector>

class Line
{
public:
   using value_type = LinePart;
   Line();
   Line(std::initializer_list<LinePart> parts);
   Line &operator+=(const LinePart &rhs);
   const std::vector<LinePart> &parts() const;
private:
   std::vector<LinePart> m_parts;
};

bool operator==(const Line &lhs, const Line &rhs);
std::ostream& operator<<(std::ostream& os, const Line &line);

#endif
