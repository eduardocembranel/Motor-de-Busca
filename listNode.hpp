#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <iostream>
#include <string>

class ListNode
{
   friend class ArquivoInvertido;

   private:
      int arquivo; //indice de arquivo
      int quantidade; //quantidade de aparicoes da palavra no arquivo
      int prox; //indice da proxima celula da lista

   public:
      ListNode();
      ListNode(int arq, int=1, int=-1);
      int getProx () const;
      friend std::ostream& operator<< (std::ostream&, const ListNode&);
};

#endif // !LISTNODE_HPP
