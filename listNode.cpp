#include "listNode.hpp"

ListNode::ListNode()
{

}

ListNode::ListNode(int arq, int qnt, int prox)
{
   this->arquivo = arq;
   this->quantidade = qnt;
   this->prox = prox;
}

void ListNode::toString ()
{
   std::cout << this->arquivo + 1 << "," << this->quantidade << "  ";
}

int ListNode::getProx () const
{
   return this->prox;
}