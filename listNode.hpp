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
      ListNode(int arq, int=1, int=-1);
      int getProx () const;
      friend std::ostream& operator<< (std::ostream&, const ListNode&);
};

#endif // !LISTNODE_HPP
