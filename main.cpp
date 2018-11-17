#include <iostream>
#include "Buscador.hpp"

int main (int argc, char **argv)
{
   try
   {
      if (argc != 3)
         throw "Quantidade invalida de argumentos!";
         
      Buscador *motor = new Buscador(argv[1], argv[2]);
      
      delete motor;
   }
   catch (const char *erro)
   {
      std::cerr << "\n" << erro << "\n";
   }

   return 0;
}