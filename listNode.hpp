#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <iostream>
#include <string>

class ListNode
{
   friend class ArquivoDados;

   private:
      int arquivo;
      int quantidade;
      int prox;

   public:
      ListNode();
      ListNode(int arq, int qnt=1, int prox=-1);
      void toString ();
      int getProx () const;
};

#endif // !LISTNODE_HPP
