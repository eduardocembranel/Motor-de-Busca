#ifndef BUSCADOR_HPP
#define BUSCADOR_HPP

#include <string>
#include <vector>
#include <set>

#include "ArquivoIndice.hpp"

class Buscador
{
   private:
      std::set<std::string> stopWords;
      std::vector<std::string> caminhoArquivos;
      ArquivoIndice *arqIndice;
      

      void carregaCaminhos(const std::string &);
      void carregaStopWords(const std::string &);
      void carregaDados();

   public:
      Buscador(const std::string &, const char *);
      ~Buscador();

};

#endif // !BUSCADOR_HPP