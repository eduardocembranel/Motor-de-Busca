#include <cstring>

#include "BTreeNode.hpp"

BTreeNode::BTreeNode (const char *chave, int indice)
{
   numChaves  = 1;
   strcpy(chaves[0], chave);
   indices[0] = indice;
   for (int i = 0; i < ORDEM + 1; ++i)
      filhos[i] = -1;
}

/* brief: construtor da clase, inicializa com os valores padroes
* pre: nenhum
* pos: arvore ser criada
*/
BTreeNode::BTreeNode ()
{
   for (int i = 0; i < ORDEM + 1; ++i)
      filhos[i] = -1;
   numChaves = 0;
}

/* brief: Faz a verificação de excesso de chaves no nó
* pre: nenhuma
* pos: passar se há ou não excesso de chaves
*/
bool BTreeNode::overflow () const
{
   return (numChaves == ORDEM);
}

/* brief: Faz a verificação se ha menos chaves que o minimo no nó
* pre: nenhuma
* pos: passar se há ou não menos chaves que o minimo
*/
bool BTreeNode::underflow () const
{
   return (numChaves < MINIMO);
}

/* brief: Verifica se o nó é uma folha 
* pre: nenhuma
* pos: passar para a chamada se é ou não uma folha
*/
bool BTreeNode::isLeaf () const
{
   return (filhos[0] == -1);
}

/* brief: Get da posição do nó 
* param: um ponteiro para o arquivo e um inteiro para a posição desejada
* pre: nenhuma
* pos: passagem do nó
*/
BTreeNode BTreeNode::getNode (std::ifstream &file, int pos)
{
   BTreeNode node;
   file.seekg(pos * sizeof(BTreeNode));
   file.read((char*)&node, sizeof(BTreeNode));
   return node;
}

/* brief: Set do nó desejado
* pre: nenhuma
* pos: nó definido 
*/
void BTreeNode::setNode (std::ofstream &file, int pos)
{
   file.seekp(pos * sizeof(BTreeNode));
   file.write((char*)this, sizeof(BTreeNode));
   file.flush();
}

/* brief: Faz o split em um nó com overflow
* pre: nó ter overflow
* pos: nó dividido em dois
*/
BTreeNode BTreeNode::split (BTreeNode &node, char *medChave, int *medIndice)
{
   BTreeNode novo;
   int posMed = 2; // -> numChave / 2
   int i, j, fim = node.numChaves;

   for (i = posMed + 1, j = 0; i < fim; ++i, ++j)
   {
      novo.filhos[j]  = node.filhos[i];
      strcpy(novo.chaves[j], node.chaves[i]);
      novo.indices[j] = node.indices[i];
      node.filhos[i]  = -1;
      ++novo.numChaves;
      --node.numChaves;
   }

   novo.filhos[j] = node.filhos[i];
   node.filhos[i] = -1;
   strcpy(medChave, node.chaves[posMed]);
   *medIndice = node.indices[posMed];
   --node.numChaves;

   return novo;
}