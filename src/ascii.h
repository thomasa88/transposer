#ifndef ASCII_H
#define ASCII_H

#include <string>
#include "sheet.h"

Sheet sheet_from_ascii(const std::string &ascii);
std::string sheet_to_ascii(const Sheet &sheet);

#endif
