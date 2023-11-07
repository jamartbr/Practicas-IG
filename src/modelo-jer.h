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
      glm::mat4 * pm_rot_inf = nullptr;
      float rot_inf = 0.0f;

      glm::mat4 * pm_rot_sup = nullptr;
      float rot_sup = 0.0f;

      glm::mat4 * pm_rot_cabeza = nullptr;
      float rot_cabeza = 0.0f;

   public:
      Flexo() ;
      unsigned leerNumParametros() const ;
      void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
} ;

class Base : public NodoGrafoEscena
{
   public:
      Base() ;
} ;

class CuerpoInf : public NodoGrafoEscena
{
   public:
      CuerpoInf() ;
} ;

class CuerpoSup : public NodoGrafoEscena
{
   public:
      CuerpoSup() ;
} ;

class Cabeza : public NodoGrafoEscena
{
   public:
      Cabeza() ;
} ;

class Bombilla : public NodoGrafoEscena
{
   public:
      Bombilla() ;
} ;


#endif // MODELO_JER_HPP
