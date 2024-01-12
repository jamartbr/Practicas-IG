// Nombre: Jaime, Apellidos: Martínez Bravo, Titulación: GIM
// email: jamartbr@correo.ugr.es, DNI o pasaporte: 18090959X

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// **
// ** Autor: Jaime Martínez Bravo
// ** 
// ** Grafo de escena parametrizado (declaraciones)
// **
// ** Declaraciones de: 
// **     + Clase 'Peon' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Lata' (derivada de 'NodoGrafoEscena')
// **     + Clase 'LataPeones' (derivada de 'NodoGrafoEscena')
// **     + Clase 'VariasLatasPeones' (derivada de 'NodoGrafoEscena')
// **
// **
// *********************************************************************

#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP

#include "grafo-escena.h" 

using namespace std;

class Peon : public NodoGrafoEscena
{
   public:
      Peon(Material *mat) ;
} ;

class Lata : public NodoGrafoEscena
{
   public:
      Lata(Material *mat) ;
} ;

class LataPeones : public NodoGrafoEscena
{
   public:
      LataPeones() ;
} ;

class VariasLatasPeones : public NodoGrafoEscena
{
   public:
      VariasLatasPeones() ;
} ;


#endif // LATAPEONES_HPP
