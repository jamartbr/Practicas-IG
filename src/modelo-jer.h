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
// **     + Clase 'Flexo' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Base' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Sargento' (derivada de 'NodoGrafoEscena')
// **     + Clase 'CuerpoInf' (derivada de 'NodoGrafoEscena')
// **     + Clase 'CuerpoSup' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Cabeza' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Bombilla' (derivada de 'NodoGrafoEscena')
// **
// *********************************************************************

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"  

class Flexo : public NodoGrafoEscena
{
   protected:
      glm::mat4 * rot_inf = nullptr;
      glm::mat4 * rot_sup = nullptr;
      glm::mat4 * rot_cabeza = nullptr;
      glm::mat4 * tras_sarg = nullptr;
      glm::mat4 * rot_sarg = nullptr;

   public:
      Flexo() ;
      unsigned leerNumParametros() const ;
      void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
} ;

class Base : public NodoGrafoEscena
{
   public:
      Base(glm::mat4 * &matriz_tras, glm::mat4 * &matriz_rot) ;
} ;

class Sargento : public NodoGrafoEscena
{
   public:
      Sargento(glm::mat4 * &matriz_tras, glm::mat4 * &matriz_rot) ;
} ;

class CuerpoInf : public NodoGrafoEscena
{
   public:
      CuerpoInf(glm::mat4 * &matriz) ;
} ;

class CuerpoSup : public NodoGrafoEscena
{
   public:
      CuerpoSup(glm::mat4 * &matriz) ;
} ;

class Cabeza : public NodoGrafoEscena
{
   public:
      Cabeza(glm::mat4 * &matriz) ;
} ;

class Bombilla : public NodoGrafoEscena
{
   public:
      Bombilla() ;
} ;


#endif // MODELO_JER_HPP
