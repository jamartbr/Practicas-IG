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
// **     + Clase 'Pinza' (derivada de 'NodoGrafoEscena')
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
    // agregar(new Pinza(pm_rot_pinza));
    agregar(new Base(pm_tras_pinza, pm_rot_pinza));
    agregar(translate(vec3(0.0,0.10,0.0)));
    agregar(new CuerpoInf(pm_rot_inf));
    agregar(new CuerpoSup(pm_rot_sup));
    agregar(new Cabeza(pm_rot_cabeza));
}

unsigned Flexo::leerNumParametros() const {
    return 5;
}

void Flexo::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    float v;
    switch(iParam) {
        case 0:
            *pm_rot_inf = rotate(float(-M_PI/7)+float(M_PI/7)*sin(float(M_PI*0.3*t_sec)), vec3{ 0.0,0.0,1.0 });
            break;
        case 1:
            *pm_rot_sup = (*pm_rot_inf) * (translate(vec3(-0.68, 1.9, 0.0))) * 
                            (rotate(float(M_PI/3)+float(M_PI/3)*sin(float(M_PI*0.3*t_sec)), vec3{ 0.0,0.0,1.0 })) *
                            (translate(vec3(0.68, -1.9, 0.0)));
            break;
        case 2:
            *pm_rot_cabeza = (*pm_rot_sup) * (translate(vec3(-1.1,1.7,0.0))) * 
                            (rotate(float(2*M_PI*0.2)*t_sec, vec3{ 1.0,1.0,0.0 })) *
                            (translate(vec3(1.1,-1.7,0.0)));
            break;
        case 3:
            v = 4 + 4 * sin( M_PI * 0.15 * t_sec*2);
            *pm_tras_pinza = translate( glm::vec3( 0.0, -v, 0.0));
            break;
        case 4:
            *pm_rot_pinza = rotate(float(2.5*M_PI)+float(2.5*M_PI)*sin(float(M_PI*0.3*t_sec)), vec3{ 0.0,1.0,0.0 });
            break;
        default:
            break;
    }
   
}

Base::Base(glm::mat4 * &pm_matriz_tras, glm::mat4 * &pm_matriz_rot) {
    ponerColor({0.93,0.64,0.09});

    agregar(scale(vec3(1.0,0.2,1.0)));
    agregar(new Semiesfera(18,20));
    agregar(new Circulo());
    agregar(translate(vec3(-0.5,-6.0,0.0)));
    agregar(scale(vec3(0.25,1.25,0.25)));
    agregar(new Pinza(pm_matriz_tras, pm_matriz_rot));
}

Pinza::Pinza(glm::mat4 * &pm_matriz_tras, glm::mat4 * &pm_matriz_rot) {
    ponerColor({0.7,0.76,0.87});

    agregar(new MallaTorre(5));

    agregar(scale(vec3(2.0,0.25,1.0)));
    agregar(translate(vec3(1.0,-1.0,0.5)));
    agregar(new Cubo());

    agregar(translate(vec3(0.5,-5.0,0.0)));
    unsigned ind1 = agregar(translate(vec3(0.0,0.0,0.0)));
    agregar(scale(vec3(0.1,20.0,0.2)));
    agregar(new Cilindro(15,20));
    agregar(new Circulo());

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(4.0,0.05,4.0)));
    agregar(new Circulo());
    agregar(new Cilindro(5,20));
    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(new Circulo());

    unsigned ind2 = agregar(rotate(0.0f,vec3(0.0,1.0,0.0)));
    agregar(translate(vec3(0.0,-20.0,0.0)));
    agregar(scale(vec3(2.5,0.6,0.1875)));
    agregar(rotate(radians(90.0f),vec3(0.0,0.0,-1.0)));
    agregar(new Cilindro(10,20));
    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(new Circulo());

    pm_matriz_tras = leerPtrMatriz(ind1);
    pm_matriz_rot = leerPtrMatriz(ind2);
}

CuerpoInf::CuerpoInf(glm::mat4 * &pm_matriz) {
    ponerColor({0.0,0.75,1.0});

    unsigned ind = agregar(rotate(0.0f,vec3(0.0,0.0,1.0)));
    pm_matriz = leerPtrMatriz(ind);

    agregar(rotate(radians(20.0f),vec3(0.0,0.0,1.0)));
    agregar(scale(vec3(0.15,2.0,0.15)));
    agregar(new Cilindro(10,20));

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(1.1,0.08,1.1)));
    agregar(new Esfera(18,20));
}

CuerpoSup::CuerpoSup(glm::mat4 * &pm_matriz) {
    ponerColor({0.0,0.75,1.0});

    unsigned ind = agregar(rotate(0.0f,vec3(0.0,0.0,1.0)));
    pm_matriz = leerPtrMatriz(ind);

    agregar(translate(vec3(-0.68,1.9,0.0)));
    agregar(rotate(radians(-40.0f),vec3(0.0,0.0,1.0)));

    agregar(scale(vec3(0.15,1.4,0.15)));
    agregar(new Cilindro(10,20));

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(1.0,0.09,1.0)));
    agregar(new Esfera(18,20));
}

Cabeza::Cabeza(glm::mat4 * &pm_matriz) {
    ponerColor({0.25,0.41,0.88});

    unsigned ind = agregar(rotate(0.0f,vec3(1.0,0.0,0.0)));
    pm_matriz = leerPtrMatriz(ind);

    agregar(translate(vec3(0.98,2.8,0.0)));
    agregar(rotate(radians(70.0f),vec3(0.0,0.0,1.0)));

    agregar(new Bombilla());

    agregar(scale(vec3(0.5,0.5,0.5)));
    agregar(translate(vec3(0.0,0.5,0.0)));
    agregar(new Cono(16,20));

    agregar(scale(vec3(2.0,1.0,2.0)));
    agregar(translate(vec3(0.0,-0.5,0.0)));
    agregar(new Cono(16,20));    
    
}

Bombilla::Bombilla() {
    ponerColor({1.0,1.0,0.0});

    agregar(scale(vec3(0.15,0.15,0.15)));
    agregar(rotate(radians(180.0f),vec3(1.0,0.0,1.0)));
    agregar(new Semiesfera(18,20));
    
    agregar(rotate(radians(180.0f),vec3(1.0,0.0,1.0)));
    agregar(scale(vec3(1.0,3.5,1.0)));
    agregar(new Cilindro(10,20));
}

