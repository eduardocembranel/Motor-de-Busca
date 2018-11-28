#include <iostream>
#include <cstring>

#include "ArquivoIndice.hpp"

ArquivoIndice::ArquivoIndice (const std::string &fileName) : Arquivo(fileName)
{
   posTopo = 0;
   posRaiz = -1;
}

//chave, indice(posicao do arquivo de dados), pos= posFinal
void ArquivoIndice::insere (const char *chave, int indice, int &pos)
{
   //arvore vazia
   if (posRaiz == -1)
   {
      BTreeNode raiz(chave, indice);
      pos = indice;
      insereRaiz(raiz);
   }

   //insere e se deu overflow na raiz
   else if (insereAux(posRaiz, chave, indice, pos) == true)
   {
      int medIndice;
      char medChave[50];
      BTreeNode raiz = BTreeNode::getNode(in, posRaiz);
      BTreeNode novo = BTreeNode::split(raiz, medChave, &medIndice);

      raiz.setNode(out, posRaiz); //recoloca a raiz antiga
      int posNovo = insereNaoRaiz(novo); //coloca o novo No (direito dosplit)
   
      BTreeNode novaRaiz(medChave, medIndice);
      novaRaiz.filhos[0] = posRaiz;
      novaRaiz.filhos[1] = posNovo;
      insereRaiz(novaRaiz);
   }
}

bool ArquivoIndice::insereAux (int pos, const char *chave, int indice, int &posDados)
{
   BTreeNode atual = BTreeNode::getNode(in, pos);

   int i; //posicao do vetor-chave ou vetor-filhos que a chave deve pertencer
   for (i = 0; i < atual.numChaves && strcmp(chave, atual.chaves[i]) > 0; ++i)
      {}

   //chave ja existe
   if (strcmp(chave, atual.chaves[i]) == 0)
   {
      posDados = atual.indices[i];
      return false;
   }

   //insere a chave na posicao correta do vetor
   if (atual.isLeaf())
   {
      for (int j = atual.numChaves; j > i ; --j)
      {
         strcpy(atual.chaves[j], atual.chaves[j - 1]);
         atual.indices[j] = atual.indices[j - 1];
      }  
      strcpy(atual.chaves[i], chave);
      atual.indices[i] = indice;
      ++atual.numChaves;
      atual.setNode(out, pos);
      posDados = indice;
   }

   //overflow no No filhos
   else if (insereAux(atual.filhos[i], chave, indice, posDados))
   {
      int medIndice;
      char medChave[50];
      int posOverflow = i; //index do filho q sofreu overflow
      BTreeNode cheio = BTreeNode::getNode(in, atual.filhos[i]);
      BTreeNode novo  = BTreeNode::split(cheio, medChave, &medIndice);

      //insere de volta o antigo No cheio
      cheio.setNode(out, atual.filhos[i]);

      //inserir o mediano na posicao correta
      for (i = 0; i < atual.numChaves && strcmp(medChave, atual.chaves[i]) > 0; ++i)
      {}
      for (int j = atual.numChaves; j > i ; --j)
      {
         strcpy(atual.chaves[j], atual.chaves[j - 1]);
         atual.indices[j] = atual.indices[j - 1];
      }
      strcpy(atual.chaves[i], medChave);
      atual.indices[i] = medIndice;
      ++atual.numChaves;

      //inserir o novo No filho na posicao correta
      int j;
      for (j = atual.numChaves; j > posOverflow + 1; --j)
         atual.filhos[j] = atual.filhos[j - 1];

      int posNovo = insereNaoRaiz(novo);
      atual.filhos[j] = posNovo;
      atual.setNode(out, pos);
   }
   return atual.overflow();
}

void ArquivoIndice::insereRaiz (BTreeNode node)
{
   node.setNode(out, posTopo);
   posRaiz = posTopo;
   ++posTopo;
}

int ArquivoIndice::insereNaoRaiz (BTreeNode node)
{
   node.setNode(out, posTopo);
   ++posTopo;
   return posTopo - 1;
}

std::vector<std::pair<std::string, int>> ArquivoIndice::getChavesEIndices ()
{
   std::vector<std::pair<std::string, int>> elems;

   if (posRaiz != -1)
      getChavesEIndicesAux(posRaiz, elems);

   return elems;
}

int ArquivoIndice::busca (const char *str)
{
   //arvore vazia
   if (posRaiz == -1) return -1;

   return buscaAux(posRaiz, str);
}

int ArquivoIndice::buscaAux (int pos, const char *str)
{
   BTreeNode atual = BTreeNode::getNode(in, pos);

   int i; //posicao do vetor-chave ou vetor-filhos que a chave esta
   for (i = 0; i < atual.numChaves && strcmp(str, atual.chaves[i]) > 0; ++i)
      {}

   //chave presente neste No
   if (strcmp(str, atual.chaves[i]) == 0)
      return atual.indices[i];
   
   //enquanto nao for folha, busca recursivamente
   if (!atual.isLeaf())
      return buscaAux(atual.filhos[i], str);
   
   //chave inexistente
   return -1;
}

void ArquivoIndice::getChavesEIndicesAux (int pos, std::vector<std::pair<std::string, int>> &elems)
{
   BTreeNode atual = BTreeNode::getNode(in, pos);

   int i;
   for (i = 0; i < atual.numChaves; ++i)
   {
      if (!atual.isLeaf())
         getChavesEIndicesAux(atual.filhos[i], elems);
      
      std::string chave = atual.chaves[i];
      elems.push_back(std::make_pair(chave, atual.indices[i]));
   }
   if (!atual.isLeaf())
      getChavesEIndicesAux(atual.filhos[i], elems);
}