// Nombre: Jaime, Apellidos: Martínez Bravo, Titulación: GIM
// email: jamartbr@correo.ugr.es, DNI o pasaporte: 18090959X

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// **
// ** Autor: Jaime Martínez Bravo
// ** 
// ** Grafo de escena parametrizado (implementación)
// **
// ** Implementación de: 
// **     + Clase 'LataPeones' (derivada de 'NodoGrafoEscena')
// **
// **
// *********************************************************************

#include "latapeones.h"  

using namespace std ;
using namespace glm ;

LataPeones::LataPeones() {
    ponerNombre("LataPeones");

    NodoGrafoEscena *lata = new NodoGrafoEscena();
    lata->agregar(new Material(0.5, 0.2, 1.0, 20));
    lata->agregar(new MallaRevolPLY("lata-pinf.ply", 50));
    lata->agregar(new MallaRevolPLY("lata-psup.ply", 50));
    lata->agregar(new Material(new Textura("lata-coke.jpg"), 0.5, 0.4, 1.0, 10));
    lata->agregar(new MallaRevolPLY("lata-pcue.ply", 50));
    
    Objeto3D *peon = new MallaRevolPLY("peon.ply", 50);

    // agregar(scale(vec3(0.5, 0.5, 0.5)));
    agregar(lata);
}