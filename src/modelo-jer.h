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
// **     + Clase 'Tornillo' (derivada de 'NodoGrafoEscena')
// **     + Clase 'CuerpoInf' (derivada de 'NodoGrafoEscena')
// **     + Clase 'CuerpoSup' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Cabezal' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Bombilla' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Circulo' (derivada de 'MallaInd')
// **     + Clase 'Semiesfera' (derivada de 'MallaRevol')
// **
// **
// *********************************************************************

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"  

class Flexo : public NodoGrafoEscena
{
   protected:
      glm::mat4 * pm_rot_inf = nullptr;
      glm::mat4 * pm_rot_sup = nullptr;
      glm::mat4 * pm_rot_cabezal = nullptr;
      glm::mat4 * pm_tras_tornillo = nullptr;
      glm::mat4 * pm_rot_tornillo = nullptr;

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

class Sargento : public NodoGrafoEscena
{
   public:
      Sargento() ;
} ;

class Tornillo : public NodoGrafoEscena
{
   public:
      Tornillo() ;
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

class Cabezal : public NodoGrafoEscena
{
   public:
      Cabezal() ;
} ;

class Bombilla : public NodoGrafoEscena
{
   public:
      Bombilla() ;
} ;

// ---------------------------------------------------------------------

class Circulo : public MallaInd
{
   public:
      Circulo();
};

class Semiesfera : public MallaRevol
{
   public:
   // Constructor: crea el perfil original y llama a inicializar
   // La esfera tiene el centro en el origen, el radio es la unidad
   Semiesfera
   (
      const int num_verts_per,  // número de vértices del perfil original (m)
      const unsigned nperfiles  // número de perfiles (n)
   ) ;
};


#endif // MODELO_JER_HPP
