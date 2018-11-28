#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

class Util
{
   public:
      static std::vector<std::string> splitString (std::string s, std::vector<char>);
      static std::vector<int> intersecao (std::vector<std::vector<int>> &);
      static void pressRetornar ();
      static void flushInput ();
      static void clear ();
};

#endif // !UTIL_HPP