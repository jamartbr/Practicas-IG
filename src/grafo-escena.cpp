// Nombre: Jaime, Apellidos: Martínez Bravo, Titulación: GIM
// email: jamartbr@correo.ugr.es, DNI o pasaporte: 18090959X

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
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
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 

using namespace std ;
using namespace glm ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( apl != nullptr );

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = apl->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = apl->pila_materiales ; assert( pila_materiales != nullptr );

   if (apl->iluminacion)
         pila_materiales->push();

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   if (tieneColor()) {
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();

   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
      for (unsigned i=0; i<entradas.size(); i++) {
         if (entradas[i].tipo==TipoEntNGE::objeto) {
            entradas[i].objeto->visualizarGL();
         } else if (entradas[i].tipo==TipoEntNGE::transformacion) {
            cauce->compMM(*(entradas[i].matriz));
         } else if (entradas[i].tipo==TipoEntNGE::material) {
            if (apl->iluminacion) {
               pila_materiales->activar(entradas[i].material);
            }
         }
      }

   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();

   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if (tieneColor()) {
      cauce->popColor();
   }



   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   if (apl->iluminacion) {
      pila_materiales->pop();
   }


}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();

   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
      for (unsigned i=0; i<entradas.size(); i++) {
         if (entradas[i].tipo==TipoEntNGE::objeto) {
            entradas[i].objeto->visualizarGeomGL();
         } else if (entradas[i].tipo==TipoEntNGE::transformacion) {
            cauce->compMM(*entradas[i].matriz);
         }
      }

   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   cauce->pushMM();
   for (unsigned i=0; i<entradas.size(); i++) {
      if (entradas[i].tipo==TipoEntNGE::objeto) {
         entradas[i].objeto->visualizarNormalesGL();
      } else if (entradas[i].tipo==TipoEntNGE::transformacion) {
         cauce->compMM(*entradas[i].matriz);
      }
   }
   cauce->popMM();

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   int identificador = leerIdentificador();
   if (identificador != -1) {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(identificador));
   }

   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   cauce->pushMM();

   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   for (unsigned i=0; i<entradas.size(); i++) {
      if (entradas[i].tipo==TipoEntNGE::objeto) {
         entradas[i].objeto->visualizarModoSeleccionGL();
      } else if (entradas[i].tipo==TipoEntNGE::transformacion) {
         cauce->compMM(*entradas[i].matriz);
      }
   }

   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   cauce->popMM();

   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   if (identificador != -1) {
      cauce->popColor();
   }


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   entradas.push_back(entrada);

   return entradas.size()-1;

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   assert( indice < entradas.size() );
   assert( entradas[indice].tipo == TipoEntNGE::transformacion );
   assert( entradas[indice].matriz != nullptr );

   return entradas[indice].matriz ;
   
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   if (!centro_calculado) {
      vec3 centro = vec3(0.0,0.0,0.0);
      int cont = 0;
      mat4 matrizModelado(1.0f);

      for (unsigned i=0; i<entradas.size(); i++) {
         if (entradas[i].tipo==TipoEntNGE::objeto) {
            entradas[i].objeto->calcularCentroOC();
            vec3 aux = entradas[i].objeto->leerCentroOC();
            centro += vec3(matrizModelado*vec4(entradas[i].objeto->leerCentroOC(), 1.0f));
            cont++;
         } else if (entradas[i].tipo==TipoEntNGE::transformacion) {
            matrizModelado = matrizModelado*(*entradas[i].matriz);
         }
      }
      centro /= cont;
      ponerCentroOC(centro);
      centro_calculado = true;
   }

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   calcularCentroOC();


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   if (leerIdentificador() == ident_busc) {
      *objeto = this;
      centro_wc = leerCentroOC();
      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   mat4 matrizmod = mmodelado;

   for(unsigned i=0; i<entradas.size(); i++){
        if(entradas[i].tipo == TipoEntNGE::objeto){
            if(entradas[i].objeto->buscarObjeto(ident_busc, matrizmod, objeto, centro_wc)) 
               return true;
        }
        else if(entradas[i].tipo == TipoEntNGE::transformacion) matrizmod = matrizmod*(*entradas[i].matriz);
   }


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

// ****************************************************************************
// Clase GrafoEstrellaX

GrafoEstrellaX::GrafoEstrellaX(unsigned n)
:  NodoGrafoEscena()
{
   using namespace glm;

   unsigned ind = agregar(rotate(radians(alpha), vec3{ 0.0,1.0,0.0 }));

   agregar(rotate(radians(-90.0f), vec3{ 0.0,1.0,0.0 }));
   agregar(translate(vec3(-0.5,-0.5,0.0)));

   EstrellaZ * estrella = new EstrellaZ(n);
   Cono * cono = new Cono(2,20);
      
   agregar(estrella);

   agregar(translate(vec3(0.5,0.5,0.0)));
   //agregar(rotate(radians(90.0f), vec3{ 0.0,0.0,1.0 }));

   float angulo = radians(360.0f/n);
   for (unsigned i=0; i<n; i++) {
      NodoGrafoEscena * punta = new NodoGrafoEscena();
      punta->agregar(translate(vec3(cos(angulo*i)*0.5,sin(angulo*i)*0.5,0.0)));
      punta->agregar(scale(vec3(0.05,0.05,0.05)));
      punta->agregar(rotate(radians(-90.0f)+angulo*i, vec3{ 0.0,0.0,1.0 }));
      punta->agregar(cono);
      agregar(punta);
   }
   
   pm_rot_alpha = leerPtrMatriz(ind);
}

unsigned GrafoEstrellaX::leerNumParametros() const
{
   return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro( const unsigned iParam, const float t_sec )
{
   using namespace glm ;

   alpha += 2*M_PI*2.5*t_sec/10.0f;

   *pm_rot_alpha = (rotate(radians(alpha), vec3{ 1.0,0.0,0.0 }));
}

// ****************************************************************************
// Clase GrafoCubos

GrafoCubos::GrafoCubos()
:  NodoGrafoEscena()
{
   using namespace glm;

   NodoGrafoEscena * lateral = new NodoGrafoEscena();
   lateral->agregar(translate(vec3(0.5,-0.5,-0.5)));
   lateral->agregar(rotate(radians(90.0f), vec3{ 0.0,0.0,1.0 }));
   lateral->agregar(new RejillaY(7,7));
   lateral->agregar(translate(vec3(0.5,-0.25,0.5)));
   lateral->agregar(scale(vec3(0.1,0.25,0.1)));
   unsigned ind = lateral->agregar(rotate(0.0f, vec3{ 0.0,-1.0,0.0 }));
   lateral->agregar(new Cubo());
   for(int i=0; i<4; i++) {
      agregar(lateral);
      agregar(rotate(radians(90.0f), vec3{ 0.0,0.0,1.0 }));
   }
   agregar(rotate(radians(90.0f), vec3{ 0.0,1.0,0.0 }));
   agregar(lateral);
   agregar(rotate(radians(180.0f), vec3{ 0.0,1.0,0.0 }));
   agregar(lateral);
   
   pm_rot = lateral->leerPtrMatriz(ind);
}

unsigned GrafoCubos::leerNumParametros() const
{
   return 1;
}

void GrafoCubos::actualizarEstadoParametro( const unsigned iParam, const float t_sec )
{
   float alpha = float(2*M_PI*0.3*t_sec);
   *pm_rot = (rotate(alpha, glm::vec3{ 0.0,-1.0,0.0 }));
}

// ****************************************************************************
// Clase NodoCubo24

NodoCubo24::NodoCubo24()
:  NodoGrafoEscena()
{   
   agregar(new Material(new Textura("window-icon.jpg"), 0.2f, 0.8f, 0.0f, 1.0f));
   agregar(new Cubo24());
}

// ****************************************************************************
// Clase NodoDiscoP4

NodoDiscoP4::NodoDiscoP4()
{
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   agregar( new Material( new Textura("cuadricula.jpg"), 0.5, 0.5, 0.0, 1));
   agregar( new MallaDiscoP4() );
}

// ****************************************************************************
// Clase GrafoEsferasP5

GrafoEsferasP5::GrafoEsferasP5()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 0.4/n_esferas_x_fila ;

   agregar(scale(vec3(e,e,e)));

   unsigned id = 1;
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;

      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MiEsferaE1 * esfera = new MiEsferaE1(i,j) ;
         fila_esferas->agregar(translate(vec3(2.2, 0.0, 0.0)));
         fila_esferas->agregar( esfera );

         esfera->ponerIdentificador(id);
         id++;
      }
      agregar( fila_esferas );
      agregar(translate(vec3(0.0, 0.0, 5.0)));
   }
}

// ****************************************************************************
// Clase MiEsferaE1

MiEsferaE1::MiEsferaE1(unsigned i, unsigned j)
{
   fila = i+1;
   col = j+1;

   agregar( new Material(0.5, 0.5, 1.0, 50) );
   agregar(new Esfera(20, 20));
}

bool MiEsferaE1::cuandoClick(const glm::vec3 & centro_wc)
{
   cout << "Se ha seleccionado la esfera número " << col << " de la fila número " << fila << endl ;
   return true ;
}

// ****************************************************************************
// Clase GrafoEsferasP5_2

GrafoEsferasP5_2::GrafoEsferasP5_2()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 2.5/n_esferas_x_fila ;

   agregar(scale(vec3(e,e,e)));

   unsigned id = 1;
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      fila_esferas->agregar(translate(vec3(3.0, 0.0, 0.0)));

      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MiEsferaE2 * esfera = new MiEsferaE2() ;
         fila_esferas->agregar(translate(vec3(2.5, 0.0, 0.0)));
         fila_esferas->agregar( esfera );


         esfera->ponerIdentificador(id);
         id++;
      }
      agregar( fila_esferas );
      agregar(rotate(radians(360.0f/n_filas_esferas),vec3(0.0, 1.0, 0.0)));
   }
}

// ****************************************************************************
// Clase MiEsferaE2

MiEsferaE2::MiEsferaE2()
{
   agregar( new Material(0.5, 0.5, 1.0, 50) );
   agregar(new Esfera(20, 20));
   ponerColor({1.0, 1.0, 1.0});
}

bool MiEsferaE2::cuandoClick(const glm::vec3 & centro_wc)
{
   if (leerColor()==vec3(1.0, 1.0, 1.0))
      ponerColor({1.0, 0.0, 0.0});
   else
      ponerColor({1.0, 1.0, 1.0});

   return true ;
}

