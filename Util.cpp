#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "Util.hpp"

std::vector<std::string> Util::splitString (std::string s, std::vector<char> c)
{
   int tam = s.length();
   std::vector<std::string> separado;

   for (int j = 0, k = 0; j < tam; ++j) 
   {
      if (std::find(c.begin(), c.end(), s[j]) != c.end())
      {
         std::string ch = s.substr(k, j - k);
         k = j + 1;
         separado.push_back(ch);
      }
      if (j == tam - 1) 
      {
         std::string ch = s.substr(k, j - k + 1);
         separado.push_back(ch);
      }
   }
   return separado;
}

std::vector<int> Util::intersecao (std::vector<std::vector<int>> &vecs) 
{
   if (vecs.size() == 0) 
      return std::vector<int>{};
   if (vecs.size() == 1) 
      return vecs[0];

   std::vector<int> aux = vecs[0];
   std::vector<int> r;

   for (size_t i = 1; i < vecs.size(); ++i, aux = r)
   {
      std::sort(aux.begin(), aux.end());
      std::sort(vecs[i].begin(), vecs[i].end());

      r.clear();
      std::set_intersection(aux.begin(), aux.end(), vecs[i].begin(), 
         vecs[i].end(), std::back_inserter(r));
   }

   return r;
}

bool Util::isBlank (const std::string &str)
{
   if (str.length() == 0) return true;

   for (size_t i = 0; i < str.length(); ++i)
      if (str[i] != ' ') return false;

   return true;
}

void Util::removePontuacao (std::string &str)
{
   for (size_t i = 0; i < str.size(); ++i)
   {
      if (str[i] == '"' || str[i] == '(' || str[i] == ')')
      {
         str.erase(i, 1);
         --i;
      }
   }
}

/* brief: limpa a tela do console
* pre: nenhuma
* pos: tela limpada do console
*/
void Util::clear ()
{
   system("cls");
}

/* brief: exibe a mensagem esperando por um ENTER e aguarda o mesmo
* pre: buffer de entrada esta limpo
* pos: nenhuma
*/
void Util::pressRetornar ()
{
   std::cout << "\nPressione ENTER para retornar...";
   Util::flushInput();
}

/* brief: limpa os dados de entrada, para tirar espaços desnescessários
* pre: nenhuma
* pos:ter retirado os espaços desnecessários
*/
void Util::flushInput ()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}