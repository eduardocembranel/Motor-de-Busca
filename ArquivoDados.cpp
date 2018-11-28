#include "ArquivoDados.hpp"

ArquivoDados::ArquivoDados (const std::string &fileName) : Arquivo(fileName)
{
   this->posTopo = 0;
}

void ArquivoDados::insereNo (ListNode *elem, int pos)
{
   this->out.seekp(pos * sizeof(ListNode));
   this->out.write((char*)elem, sizeof(ListNode));
   this->out.flush();
}

void ArquivoDados::insere (int arquivo, int pos)
{
   if (pos == this->posTopo)
   {
      ListNode novo(arquivo);
      this->insereNo(&novo, pos);
      ++this->posTopo;
   }
   else
   {
      int posAtual  = pos;
      ListNode elem = getData(pos);
      while (elem.arquivo != arquivo && elem.prox != -1)
      {
         posAtual = elem.prox;
         elem = getData(elem.prox);
      }

      if (elem.arquivo == arquivo)
      {
         ++elem.quantidade;
         this->insereNo(&elem, posAtual);
      }
      else
      {
         elem.prox = this->posTopo;
         this->insereNo(&elem, posAtual);

         ListNode novo(arquivo);
         this->insereNo(&novo, this->posTopo);
         ++this->posTopo;
      }
   }   
}

ListNode ArquivoDados::getData (int pos)
{
   ListNode x;
   
   this->in.seekg(pos * sizeof(ListNode));
   this->in.read((char*)&x, sizeof(ListNode));

   return x;
}

int ArquivoDados::getPosTopo () const
{
   return this->posTopo;
}

std::vector<int> ArquivoDados::getTodosArquivos (int pos)
{
   std::vector<int> arquivos;

   while (pos != -1)
   {
      ListNode node = getData(pos);
      arquivos.push_back(node.arquivo);
      pos = node.getProx();
   }
   return arquivos;
}

std::string ArquivoDados::getName () const
{
   return this->fileName;
}