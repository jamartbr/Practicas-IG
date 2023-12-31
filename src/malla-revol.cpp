// Nombre: Jaime, Apellidos: Martínez Bravo, Titulación: GIM
// email: jamartbr@correo.ugr.es, DNI o pasaporte: 18090959X

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;

   // COMPLETAR: práctica 4: calcular las normales de los vértices del perfil y guardarlas
   // en un vector; se usarán para crear las normales de los vértices de la malla completa
   vector<vec3> nor_ari;
   for (unsigned i=0; i<perfil.size()-1; i++) {
      vec3 mi = perfil[i+1]-perfil[i];

      //rotamos 90º en sentido horario al rededor del eje z
      vec3 mi_rot = {mi.y, -mi.x, mi.z};

      // normalizamos (si el vector es nulo, no se puede normalizar)
      if (length(mi_rot)>0.0)
         mi_rot = normalize(mi_rot);
      else
         mi_rot = {0.0, 0.0, 0.0};

      // en objetos cerrados, las normales deben apuntar hacia afuera
      if (mi_rot.x<0.0)
         mi_rot = -mi_rot;

      nor_ari.push_back(mi_rot);
   }
   
   vector<vec3> nor_ver_perfil;
   nor_ver_perfil.push_back(nor_ari[0]);
   for (unsigned i=1; i<perfil.size()-1; i++) {
      vec3 ni = normalize(nor_ari[i-1]+nor_ari[i]);
      nor_ver_perfil.push_back(ni);
   }
   nor_ver_perfil.push_back(nor_ari[perfil.size()-2]);

   // calculamos las coordenadas de textura de cada vértice del perfil
   vector<float> d;
   for (unsigned i=0; i<perfil.size()-1; i++) {
      vec3 v1 = perfil[i];
      vec3 v2 = perfil[i+1];
      d.push_back(length(v2-v1));
   }  

   vector<float> t;
   t.push_back(0.0);
   float suma = 0.0;
   for (unsigned i=0; i<perfil.size()-1; i++) {
      suma += d[i];
      t.push_back(suma);
   }

   for (unsigned i=0; i<t.size(); i++) {
      t[i] /= suma;
   }
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //

   unsigned n = num_copias;
   unsigned m = perfil.size();

   for (unsigned i=0; i<n; i++) {
      float angulo = (i*2*M_PI)/(n-1);
      for (unsigned j=0; j<m; j++) {
         vertices.push_back({perfil[j].x*cos(angulo), perfil[j].y, perfil[j].x*(-sin(angulo))});
         nor_ver.push_back({nor_ver_perfil[j].x*cos(angulo), nor_ver_perfil[j].y, nor_ver_perfil[j].x*(-sin(angulo))});
      }

      // calculamos las coordenadas de textura de cada vértice
      for (unsigned j=0; j<m; j++) {
         cc_tt_ver.push_back({float(i)/(n-1), 1-t[j]});
      }
   }

   for (unsigned i=0; i<n-1; i++) {
      for (unsigned j=0; j<m-1; j++) {
         int k = i*m+j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);


}



// -----------------------------------------------------------------------------------------------


// ****************************************************************************
// Clase Cilindro

Cilindro::Cilindro(
      const int num_verts_per,  // número de vértices del perfil original (m)
      const unsigned nperfiles  // número de perfiles (n)
   )
:  MallaRevol()
{
   std::vector<glm::vec3>  perfil;
   for (float i=0; i<num_verts_per; i++) {
      perfil.push_back({1.0, i/(num_verts_per-1), 0.0});
   }

   inicializar(perfil, nperfiles);
}

// ****************************************************************************
// Clase Cono

Cono::Cono(
      const int num_verts_per,  // número de vértices del perfil original (m)
      const unsigned nperfiles  // número de perfiles (n)
   )
:  MallaRevol()
{
   std::vector<glm::vec3>  perfil;
   for (float i=0; i<num_verts_per; i++) {
      perfil.push_back({1.0-(i/(num_verts_per-1)), i/(num_verts_per-1), 0.0});
   }

   inicializar(perfil, nperfiles);
}

// ****************************************************************************
// Clase Esfera

Esfera::Esfera(
      const int num_verts_per,  // número de vértices del perfil original (m)
      const unsigned nperfiles  // número de perfiles (n)
   )
:  MallaRevol()
{
   std::vector<glm::vec3>  perfil;
   for (float i=0; i<num_verts_per; i++) {
      float angulo = i*M_PI/(num_verts_per-1);
      perfil.push_back({sin(angulo), cos(angulo), 0.0});
   }

   inicializar(perfil, nperfiles);
}




