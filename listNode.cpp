#include "listNode.hpp"

ListNode::ListNode() {}

ListNode::ListNode(int arq, int qnt, int prox)
{
   this->arquivo = arq;
   this->quantidade = qnt;
   this->prox = prox;
}

int ListNode::getProx () const
{
   return this->prox;
}

std::ostream& operator<< (std::ostream &out, const ListNode &node)
{
   out << node.arquivo + 1 << "," << node.quantidade << "  ";

   return out;
}