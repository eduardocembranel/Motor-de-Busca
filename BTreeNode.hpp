#ifndef BTREENODE_HPP
#define BTREENODE_HPP

#include <fstream>

class BTreeNode
{
   friend class ArquivoIndice;
   
   private:
      static const int ORDEM    = 5;
      static const int MINIMO   = 2;
      static const int STR_SIZE = 50; 
      int  numChaves;
      char chaves[ORDEM][STR_SIZE];
      int  filhos[ORDEM + 1];
      int  indices[ORDEM];

   public:
      BTreeNode ();
      BTreeNode (const char *, int);
      bool isLeaf();
      bool underflow();
      bool overflow();
      static BTreeNode getNode (std::ifstream &, int);
      void setNode (std::ofstream &, int);
      static BTreeNode split (BTreeNode &, char *, int *);

};

#endif // !BTREENODE_HPP