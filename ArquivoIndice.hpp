#ifndef ARQUIVOINDICE_HPP
#define ARQUIVOINDICE_HPP

#include <vector>
#include <string>

#include "Arquivo.hpp"
#include "BTreeNode.hpp"

class ArquivoIndice : public Arquivo
{
   private:
      int posRaiz;
      int posTopo;

   public:
      ArquivoIndice (const std::string &);
      void insere (const char *, int, int &);
      int busca (const char *);
      std::vector<std::pair<std::string, int>> getChavesEIndices ();

   private:
      bool insereAux (int, const char *, int, int &);
      void insereRaiz (BTreeNode);
      int buscaAux (int, const char *);
      int insereNaoRaiz (BTreeNode);
      void getChavesEIndicesAux (int, std::vector<std::pair<std::string, int>> &);

};

#endif // !ARQUIVOINDICE_HPP