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
    lata->agregar(new MallaRevolPLY("lata-pinf.ply", 50));
    lata->agregar(new Material(0.4, 0.5, 0.8, 50));
    lata->agregar(new MallaRevolPLY("lata-psup.ply", 50));
    lata->agregar(new Material(new Textura("lata-coke.jpg"), 0.4, 1.0, 2.0, 50));
    lata->agregar(new MallaRevolPLY("lata-pcue.ply", 50));
    agregar(lata);
    
    NodoGrafoEscena *peon = new NodoGrafoEscena();
    peon->agregar(new MallaRevolPLY("peon.ply", 50));
    agregar(scale(vec3(0.16, 0.16, 0.16)));
    agregar(translate(vec3(2.5, 1.4, 5.0)));
    // peón sin textura, con un material puramente difuso (sin brillos especulares), de color blanco
    agregar(new Material(1.0, 1.0, 0.0, 1));
    agregar(peon);
    // peón negro, sin textura, con un material especular sin apenas reflectividad difusa
    agregar(new Material(0.0, 0.1, 2.0, 10));
    agregar(translate(vec3(2.5, 0.0, 0.0)));
    agregar(peon);
    agregar(translate(vec3(-5.0, 0.0, 0.0)));
    agregar(new Material(new Textura("text-madera.jpg"), 0.25, 1.5, 1.5, 100));
    agregar(peon);
}