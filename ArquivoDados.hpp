#ifndef ARQUIVODADOS_HPP
#define ARQUIVODADOS_HPP

#include <vector>
#include <string>

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
      int getPosTopo () const;
      ListNode getData (int);
      std::vector<int> getTodosArquivos (int);
};

#endif // !ARQUIVODADOS_HPP