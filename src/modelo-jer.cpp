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
// **     + Clase 'Flexo' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Base' (derivada de 'NodoGrafoEscena')
// **     + Clase 'CuerpoInf' (derivada de 'NodoGrafoEscena')
// **     + Clase 'CuerpoSup' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Cabeza' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Bombilla' (derivada de 'NodoGrafoEscena')
// **
// *********************************************************************

#include "modelo-jer.h"  

using namespace std ;
using namespace glm ;

Flexo::Flexo() {
    agregar(new Base());
    agregar(translate(vec3(0.0,0.15,0.0)));
    int ind1 = agregar(rotate(radians(rot_inf),vec3(0.0,0.0,1.0)));
    agregar(new CuerpoInf());
    int ind2 = agregar(rotate(radians(rot_sup),vec3(0.0,0.0,1.0)));
    agregar(new CuerpoSup());
    int ind3 = agregar(rotate(radians(rot_sup),vec3(1.0,0.0,0.0)));
    agregar(new Cabeza());

    pm_rot_inf = leerPtrMatriz(ind1);
    pm_rot_sup = leerPtrMatriz(ind2);
    pm_rot_cabeza = leerPtrMatriz(ind3);
}

unsigned Flexo::leerNumParametros() const {
    return 3;
}

void Flexo::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    switch(iParam) {
        case 0:
            rot_inf += radians(60.0f) * sin(2*M_PI*t_sec);
            *pm_rot_inf = (rotate(radians(rot_inf), vec3{ 0.0,0.0,1.0 }));
            break;
        case 1:
            rot_sup += radians(90.0f) * sin(2*M_PI*t_sec);
            *pm_rot_sup = (rotate(radians(rot_sup), vec3{ 0.0,0.0,1.0 }));
            break;
        case 2:
            rot_cabeza += radians(90.0f) * sin(2*M_PI*t_sec);
            *pm_rot_cabeza = (rotate(radians(rot_cabeza), vec3{ 1.0,0.0,0.0 }));
            break;
        default:
            break;
    }
   
}

Base::Base() {
    agregar(scale(vec3(1.0,0.2,1.0)));
    agregar(new Semiesfera(18,50));
    agregar(new Circulo());
}

CuerpoInf::CuerpoInf() {
    ponerColor({1.0,0.0,0.0});

    agregar(rotate(radians(10.0f),vec3(0.0,0.0,1.0)));
    agregar(scale(vec3(0.15,2.0,0.15)));
    agregar(new Cilindro(10,50));

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(1.1,0.08,1.1)));
    agregar(new Esfera(18,50));
}

CuerpoSup::CuerpoSup() {
    ponerColor({0.0,1.0,0.0});

    agregar(translate(vec3(-0.3,2.0,0.0)));
    agregar(rotate(radians(-80.0f),vec3(0.0,0.0,1.0)));
    agregar(scale(vec3(1.0,0.7,1.0)));

    agregar(rotate(radians(10.0f),vec3(0.0,0.0,1.0)));
    agregar(scale(vec3(0.15,2.0,0.15)));
    agregar(new Cilindro(10,50));

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(1.0,0.09,1.0)));
    agregar(new Esfera(18,50));

    // agregar(new CuerpoInf());
}

Cabeza::Cabeza() {
    ponerColor({0.0,0.0,1.0});

    agregar(translate(vec3(1.5,2.1,0.0)));
    agregar(rotate(radians(45.0f),vec3(0.0,0.0,1.0)));

    agregar(new Bombilla());

    agregar(scale(vec3(0.5,0.5,0.5)));
    agregar(translate(vec3(0.0,0.5,0.0)));
    agregar(new Cono(16,50));

    agregar(scale(vec3(2.0,1.0,2.0)));
    agregar(translate(vec3(0.0,-0.5,0.0)));
    agregar(new Cono(16,50));    
    
}

Bombilla::Bombilla() {
    agregar(scale(vec3(0.15,0.15,0.15)));
    agregar(rotate(radians(180.0f),vec3(1.0,0.0,1.0)));
    agregar(new Semiesfera(18,50));
    
    agregar(rotate(radians(180.0f),vec3(1.0,0.0,1.0)));
    agregar(scale(vec3(1.0,4.0,1.0)));
    agregar(new Cilindro(10,50));
}

