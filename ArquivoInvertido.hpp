#ifndef ARQUIVOINVERTIDO_HPP
#define ARQUIVOINVERTIDO_HPP

#include <vector>
#include <string>

#include "Arquivo.hpp"
#include "BTreeNode.hpp"
#include "listNode.hpp"

class ArquivoInvertido : public Arquivo
{
   private:
      int posTopo;

   public:
      ArquivoInvertido (const std::string &);
      void insere (int, int);
      void insereNo (ListNode *, int);
      int getPosTopo () const;
      ListNode getData (int);
      std::vector<int> getTodosArquivos (int);
};

#endif // !ARQUIVOINVERTIDO_HPP