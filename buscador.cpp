#include <iostream>
#include <fstream>

#include "Buscador.hpp"
#include "Util.hpp"

Buscador::Buscador (const std::string &fileCaminhos, const char *fileStopWords)
{
   carregaCaminhos(fileCaminhos);
   carregaStopWords(fileStopWords);
   arqIndice     = new ArquivoIndice("invertido.bin");
   arqInvertido  = new ArquivoInvertido("dados.bin");

   carregaDados();
}

void Buscador::run ()
{
   int escolha;
   do
   {
      mostraMenu();
      std::cin >> escolha; 
      Util::flushInput();
      switch (escolha)
      {
         case IMPRIME_INDICE:
            imprimeIndice();
            break;
         case IMPRIME_STOPWORD:
            imprimeStopWords();
            break;
         case CONSULTAR:
            consulta();
            break;
         case SAIR:
            break;
         default:
            std::cout << "\nOpcao invalida!\n";
            Util::pressRetornar();  
            break;
         
      } 
   } while (escolha != SAIR);
}

void Buscador::imprimeStopWords ()
{
   Util::clear();
   std::cout << "[Imprimir stopwords]\n\n"
             << "Lista de stopwords ordenadas por ordem lexicografica:\n\n";
   
   for (auto &it : stopWords)
      std::cout << it << "\n";

   Util::pressRetornar();
}

void Buscador::imprimeIndice ()
{
   Util::clear();
   std::cout << "[Imprimir Indice]\n\n";

   std::vector<std::pair<std::string, int>> elems = arqIndice->getChavesEIndices();
   std::ifstream file(arqInvertido->getName(), std::ios::in);

   for (size_t i = 0; i < elems.size(); ++i)
   {
      //imprime a chave junto com uma serie de espacos em branco
      std::cout << elems[i].first;
      for (int j = 0; j < 30 - elems[i].first.length(); ++j) { std::cout << " "; }

      ListNode temp;
      int pos = elems[i].second;

      //imprime quais arquivos e quantidade
      for (pos = elems[i].second; pos != -1; pos = temp.getProx())
      {
         temp = arqInvertido->getData(pos);
         std::cout << temp;
      }
      std::cout << "\n";
   }
      
   Util::pressRetornar();
   file.close();
}

void Buscador::consulta ()
{
   Util::clear();
   std::cout << "[Consultar]\n\n"
             << "Insira as palavras a serem consultadas: ";

   std::string entrada;
   std::getline(std::cin, entrada);

   std::vector<char> delimitador = {' ', '\n'};
   std::vector<std::string> palavras = Util::splitString(entrada, delimitador); 

   std::vector<std::vector<int>> arquivos;
   for (auto &it : palavras)
   {
      int pos = arqIndice->busca(it.c_str());
      arquivos.push_back(arqInvertido->getTodosArquivos(pos));
   }

   std::vector<int> intersec = Util::intersecao(arquivos);

   std::cout << "\nqnt: " << intersec.size() << "\n";
   if (intersec.size() > 0) std::cout << "\ndocumentos:\n";

   for (auto &it : intersec)
      std::cout << caminhoArquivos[it] << "\n";

   Util::pressRetornar();
}

void Buscador::mostraMenu () const
{
   Util::clear();
   std::cout << "[Motor de Busca]\n\n"
             << "[1]Imprimir indices\n"
             << "[2]Imprimir stopwords\n" 
             << "[3]Consultar\n"
             << "[4]Sair\n\n"
             << ">> ";
}

void Buscador::carregaCaminhos (const std::string &fileName)
{
   std::ifstream fBuffer(fileName, std::ios::in);

   if (fBuffer.fail()) 
      throw "Falha ao abrir o arquivo de caminhos!";

   std::string linha;
   while (std::getline(fBuffer, linha))
   {
      //verifica se eh um arquivo existente
      std::ifstream temp(linha, std::ios::in);
      if (!temp.fail()) 
         caminhoArquivos.push_back(linha);
      temp.close();
   }

   fBuffer.close();
}

void Buscador::carregaStopWords (const std::string &fileName)
{
   std::ifstream fBuffer(fileName, std::ios::in);

   if (fBuffer.fail()) 
      throw "Falha ao abrir o arquivo de stopwords!";

   std::string stopWord;
   while (std::getline(fBuffer, stopWord))
      if (!Util::isBlank(stopWord))
         stopWords.insert(stopWord);

   fBuffer.close();
}

void Buscador::carregaDados ()
{
   std::vector<char> delimitadores{' ', '\n', ',', '.', '!', '?', ';', ':'};

   //carrega as palavras para cada arquivo de dados
   for (int i = 0; i < caminhoArquivos.size(); ++i)
   {
      std::ifstream fBuffer(caminhoArquivos[i], std::ios::in);

      while (true)
      {
         std::string linha;
         std::getline(fBuffer, linha);
         Util::removePontuacao(linha);
   
         std::vector<std::string> palavras = Util::splitString(linha, delimitadores);
         for (auto it : palavras)
         {            
            if (!ehStopWord(it) && it.length() > 1)
            {
               int posDados;
               
               arqIndice->insere(it.c_str(), arqInvertido->getPosTopo(), posDados);
               arqInvertido->insere(i, posDados);
            }
         }
         //fim de arquivo
         if (fBuffer.eof()) break;
      }
      fBuffer.close();
   }
}

bool Buscador::ehStopWord (const std::string &str) const
{
   return (stopWords.find(str) != stopWords.end());
}

Buscador::~Buscador ()
{
   delete arqInvertido;
   delete arqIndice;
}