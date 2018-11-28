#ifndef BUSCADOR_HPP
#define BUSCADOR_HPP

#include <string>
#include <vector>
#include <set>

#include "ArquivoIndice.hpp"
#include "ArquivoDados.hpp"

class Buscador
{
   private:
      std::set<std::string> stopWords;
      std::vector<std::string> caminhoArquivos;
      ArquivoIndice *arqIndice;
      ArquivoDados  *arqDados;

      void carregaCaminhos(const std::string &);
      void carregaStopWords(const std::string &);
      void carregaDados();
      bool ehStopWord (const std::string &) const;
      void mostraMenu ();
   
      void imprimeIndice ();
      void imprimeStopWords ();
      void consulta ();

      enum MenuEstado
      {
         IMPRIME_INDICE = 1,
         IMPRIME_STOPWORD,
         CONSULTAR,
         SAIR
      };

   public:
      Buscador(const std::string &, const char *);
      void run ();
      ~Buscador();

};

#endif // !BUSCADOR_HPP