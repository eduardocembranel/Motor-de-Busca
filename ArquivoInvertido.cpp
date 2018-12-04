#include "ArquivoInvertido.hpp"

ArquivoInvertido::ArquivoInvertido (const std::string &fileName) : Arquivo(fileName)
{
   posTopo = 0;
}

void ArquivoInvertido::insere (int arquivo, int pos)
{
   if (pos == posTopo)
   {
      ListNode novo(arquivo);
      insereNo(&novo, pos);
      ++posTopo;
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
         insereNo(&elem, posAtual);
      }
      else
      {
         elem.prox = posTopo;
         insereNo(&elem, posAtual);

         ListNode novo(arquivo);
         insereNo(&novo, posTopo);
         ++posTopo;
      }
   }   
}

int ArquivoInvertido::getPosTopo () const
{
   return posTopo;
}

void ArquivoInvertido::insereNo (ListNode *elem, int pos)
{
   out.seekp(pos * sizeof(ListNode));
   out.write((char*)elem, sizeof(ListNode));
   out.flush();
}

ListNode ArquivoInvertido::getData (int pos)
{
   ListNode x;
   
   in.seekg(pos * sizeof(ListNode));
   in.read((char*)&x, sizeof(ListNode));

   return x;
}

std::vector<int> ArquivoInvertido::getTodosArquivos (int pos)
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