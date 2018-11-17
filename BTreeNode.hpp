#ifndef BTREENODE_HPP
#define BTREENODE_HPP

class BTreeNode
{
   private:
      static const int ORDEM    = 5;
      static const int MINIMO   = 2;
      static const int STR_SIZE = 50; 
      int  numChaves;
      char chaves[ORDEM][STR_SIZE];
      int  filhos[ORDEM + 1];
      int  indices[ORDEM];
};

#endif // !BTREENODE_HPP