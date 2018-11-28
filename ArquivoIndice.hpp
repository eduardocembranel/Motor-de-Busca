#ifndef ARQUIVOINDICE_HPP
#define ARQUIVOINDICE_HPP

#include <string>
#include <vector>

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
      void teste ();
      int busca (const char *);
      int buscaAux (int, const char *);
      std::vector<std::pair<std::string, int>> getChavesEIndices ();

   private:
      bool insereAux (int, const char *, int, int &);
      void insereRaiz (BTreeNode);
      int insereNaoRaiz (BTreeNode);
      void getChavesEIndicesAux (int, std::vector<std::pair<std::string, int>> &);

};

#endif // !ARQUIVOINDICE_HPP