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

      //qual arquivo, posicao do registro
      void insere (int, int);
      void insereNo (ListNode *, int);

      //dada a posicao de inicio, retorna todos os arquivos presentes na lista
      std::vector<int> getTodosArquivos (int);
      ListNode getData (int);
      int getPosTopo () const;
      void teste ();
      std::string getName () const;
};

#endif // !ARQUIVODADOS_HPP