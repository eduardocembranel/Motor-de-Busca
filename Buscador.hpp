#ifndef BUSCADOR_HPP
#define BUSCADOR_HPP

#include <vector>
#include <set>
#include <string>

#include "ArquivoIndice.hpp"
#include "ArquivoDados.hpp"

class Buscador
{
   public:
      Buscador(const std::string &, const char *);
      void run ();
      ~Buscador();
   
   private:
      std::set<std::string>     stopWords;
      std::vector<std::string>  caminhoArquivos;
      ArquivoIndice             *arqIndice;
      ArquivoDados              *arqDados;

      void carregaCaminhos(const std::string &);
      void carregaStopWords(const std::string &);
      void carregaDados();
      bool ehStopWord (const std::string &) const;
      void mostraMenu () const;
   
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

};

#endif // !BUSCADOR_HPP