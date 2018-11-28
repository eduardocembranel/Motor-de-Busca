#ifndef ARQUIVODADOS_HPP
#define ARQUIVODADOS_HPP

#include <vector>
#include <cstring>

#include "Arquivo.hpp"
#include "BTreeNode.hpp"
#include "listNode.hpp"

class ArquivoDados : public Arquivo
{
   private:
      int posTopo;

   public:
      ArquivoDados (const std::string &);
      void insere (int, int);
      void insereNo (ListNode *, int);
      std::vector<int> getTodosArquivos (int);
      ListNode getData (int);
      int getPosTopo () const;
      std::string getName () const;
};

#endif // !ARQUIVODADOS_HPP