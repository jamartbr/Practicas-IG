// Nombre: Jaime, Apellidos: Martínez Bravo, Titulación: GIM
// email: jamartbr@correo.ugr.es, DNI o pasaporte: 18090959X

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"

class P1MallaPiramide : public MallaInd
{
   public:
      P1MallaPiramide();
};

class P2Barrido : public MallaInd
{
   public:
      P2Barrido
   (
      const int m,      // número de vértices del perfil original
      const unsigned n  // número de perfiles
   ) ;
};

class P3Mesa : public NodoGrafoEscena
{
   protected:
      glm::mat4 * pm_tras_vert = nullptr;
      glm::mat4 * pm_altura_patas = nullptr;
      glm::mat4 * pm_rot1 = nullptr;
      glm::mat4 * pm_rot2 = nullptr;

   public:
      P3Mesa();
      unsigned leerNumParametros() const ;
      void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

};

#endif