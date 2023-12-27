// Nombre: Jaime, Apellidos: Martínez Bravo, Titulación: GIM
// email: jamartbr@correo.ugr.es, DNI o pasaporte: 18090959X

#include "examen-ec-p123.h"

using namespace std;
using namespace glm;

P1MallaPiramide::P1MallaPiramide()
:  MallaInd( "pirámide con base cuadrada" )
{

   vertices =
      {  { 0.0, 0.0, 0.0 }, // 0
         { -1.0, 0.0, -1.0 }, // 1
         { -1.0, 0.0, 1.0 }, // 2
         { 1.0, 0.0, -1.0 }, // 3
         { 1.0, 0.0, 1.0 }, // 4
         { 0.0, 2.0, 0.0 }, // 5
      } ;


   triangulos =
      {  {0,2,1}, {0,4,2},
         {0,3,4}, {0,1,3},

         {1,2,5}, {2,4,5},
         {3,5,4}, {1,3,5}
      } ;

   col_ver.push_back({0.6, 0.0, 0.1});
   for (unsigned i=1; i<5; i++) {
      col_ver.push_back({1.0, 1.0, 0.0});
   }
   col_ver.push_back({0.0, 1.0, 1.0});

}

P2Barrido::P2Barrido(
      const int m,      // número de vértices del perfil original (m)
      const unsigned n  // número de perfiles (n)
   )
:  MallaInd()
{
   vector<glm::vec3>  perfil;
   for (float i=0; i<m; i++) {
      float angulo = i*M_PI/(m-1);
      perfil.push_back({sin(angulo), cos(angulo), 0.0});
   }
   
   double desp = 2.0/m;
   for (unsigned i=0; i<n; i++) {
      for (unsigned j=0; j<m; j++) {
         vertices.push_back({perfil[j].x, perfil[j].y, desp*i*(-1)});
      }
   }

   for (unsigned i=0; i<n-1; i++) {
      for (unsigned j=0; j<m-1; j++) {
         int k = i*m+j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }

   for (unsigned i=0; i<n-1; i++) {
        triangulos.push_back({i*m+m-1, i*m, i*m+m});
        triangulos.push_back({i*m+m-1, i*m+m+m-1, i*m+m});
   }
}

P3Mesa::P3Mesa()
:  NodoGrafoEscena()
{  
    NodoGrafoEscena * cubo = new NodoGrafoEscena();
    cubo->agregar(translate(vec3(1.0,1.0,1.0)));
    cubo->agregar(new Cubo());

    NodoGrafoEscena * patas = new NodoGrafoEscena();
    patas->agregar(translate(vec3(0.8,0.0,0.8)));
    patas->agregar(scale(vec3(0.1,0.5,0.1)));

    unsigned ind_altura_patas = patas->agregar(scale(vec3(1.0,1.0,1.0)));

    patas->agregar(cubo);
    patas->agregar(translate(vec3(-18.0,0.0,0.0)));
    patas->agregar(cubo);
    patas->agregar(translate(vec3(0.0,0.0,-18.0)));
    patas->agregar(cubo);
    patas->agregar(translate(vec3(18.0,0.0,0.0)));
    patas->agregar(cubo);

    agregar(patas);

    unsigned ind_tras_vert = agregar(translate(vec3(0.0,0.0,0.0)));

    agregar(translate(vec3(-1.0,1.0,-1.0)));
    agregar(scale(vec3(1.0,0.1,1.0)));
    agregar(cubo);

    agregar(scale(vec3(1.0,10.0,1.0)));
    agregar(translate(vec3(0.9,0.2,0.9)));
    agregar(scale(vec3(0.1,0.3,0.1)));
    agregar(cubo);

    unsigned ind_rot1 = agregar(rotate(0.0f, vec3(0.0,0.0,1.0)));

    agregar(translate(vec3(0.0,2.0,0.0)));
    agregar(cubo);

    unsigned ind_rot2 = agregar(rotate(0.0f, vec3(0.0,0.0,1.0)));

    agregar(translate(vec3(0.0,2.0,0.0)));
    agregar(cubo);

    pm_altura_patas = patas->leerPtrMatriz(ind_altura_patas);
    pm_tras_vert = leerPtrMatriz(ind_tras_vert);
    pm_rot1 = leerPtrMatriz(ind_rot1);
    pm_rot2 = leerPtrMatriz(ind_rot2);
}

unsigned P3Mesa::leerNumParametros() const {
    return 2;
};

void P3Mesa::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    float v;
    switch (iParam)
    {
    case 0:
        v = 1.0+0.5*sin(M_PI*(1/1.3)*t_sec);
        *pm_altura_patas = scale(vec3(1.0,v,1.0));
        *pm_tras_vert = translate(vec3(0.0,v-1,0.0));
        break;
    case 1:
        *pm_rot1 =  (translate(vec3(1.0,2.0,0.0))) * 
                    (rotate(float(2*M_PI*0.3)*t_sec, vec3(0.0,0.0,1.0))) *
                    (translate(vec3(-1.0,-2.0,0.0)));
        *pm_rot2 =  (translate(vec3(1.0,2.0,0.0))) * 
                    (rotate(float(2*M_PI*0.3)*t_sec, vec3(0.0,0.0,-1.0))) *
                    (translate(vec3(-1.0,-2.0,0.0)));
        break;
    default:
        break;
    }
};