#include <iostream>
#include <fstream>

#include "Buscador.hpp"

Buscador::Buscador (const std::string &fileCaminhos, const char *fileStopWords)
{
   this->carregaCaminhos(fileCaminhos);
   this->carregaStopWords(fileStopWords);
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
         this->caminhoArquivos.push_back(linha);
      temp.close();
   }
}

void Buscador::carregaStopWords (const std::string &fileName)
{
   std::ifstream fBuffer(fileName, std::ios::in);

   if (fBuffer.fail()) 
      throw "Falha ao abrir o arquivo de stopwords!";

   std::string stopWord;
   while (std::getline(fBuffer, stopWord))
      if (stopWord != "\n")
         this->stopWords.insert(stopWord);
}

void Buscador::carregaDados ()
{
   
}

Buscador::~Buscador ()
{
   
}