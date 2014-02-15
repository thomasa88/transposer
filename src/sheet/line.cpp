#include "line.h"
#include "stream_join.tpp"

Line &Line::operator+=(const LinePart &rhs)
{
   m_parts.push_back(rhs);
   return *this;
}

Line::Line()
{
}

Line::Line(std::initializer_list<LinePart> parts)
   : m_parts(parts)
{
}

std::ostream& operator<<(std::ostream& os, const Line &line)
{
   const auto &parts = line.parts();
   os << "Line{";
   stream_join(os, parts);
   os << "}";
   return os;
}

const std::vector<LinePart> &Line::parts() const
{
   return m_parts;
}

bool operator==(const Line &lhs, const Line &rhs)
{
   return lhs.parts() == rhs.parts();
}
