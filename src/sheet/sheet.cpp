#include "sheet.h"
#include "stream_join.tpp"

Sheet &Sheet::add_line(const Line &line)
{
   m_lines.push_back(line);
   return *this;
}

bool Sheet::empty() const
{
   return m_lines.empty();
}

int Sheet::line_count() const
{
   return m_lines.size();
}

bool Sheet::operator==(const Sheet &rhs) const
{
   return m_lines == rhs.m_lines;
}

Line &Sheet::operator[](int line_index)
{
   return m_lines.at(line_index);
}

const Line &Sheet::operator[](int line_index) const
{
   return m_lines.at(line_index);
}

std::ostream& operator<<(std::ostream& os, const Sheet &sheet)
{
   const auto &lines = sheet.m_lines;
   os << "Sheet{";
   stream_join(os, lines);
   os << "}";
   return os;
}
