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

#include "modelo-jer.h"  

using namespace std ;
using namespace glm ;

Flexo::Flexo() {
    ponerNombre("Flexo");
    
    Sargento * sargento = new Sargento();
    unsigned ind_tras_tornillo = sargento->agregar(translate(vec3(0.0,0.0,0.0)));
    sargento->agregar(scale(vec3(0.5,1.0,1.0)));
    unsigned ind_rot_tornillo = sargento->agregar(rotate(0.0f,vec3(0.0,1.0,0.0)));
    sargento->agregar(new Tornillo());
    Base * base = new Base();
    base->agregar(sargento);
    agregar(base);

    agregar(translate(vec3(0.0,0.10,0.0)));
    unsigned ind_rot_inf = agregar(rotate(0.0f,vec3(0.0,0.0,1.0)));
    agregar(new CuerpoInf());

    unsigned ind_rot_sup = agregar(rotate(0.0f,vec3(0.0,0.0,1.0)));
    agregar(new CuerpoSup());

    unsigned ind_rot_cabezal = agregar(rotate(0.0f,vec3(1.0,1.0,0.0)));
    agregar(new Cabezal());

    pm_tras_tornillo = sargento->leerPtrMatriz(ind_tras_tornillo);
    pm_rot_tornillo = sargento->leerPtrMatriz(ind_rot_tornillo);
    pm_rot_inf = leerPtrMatriz(ind_rot_inf);
    pm_rot_sup = leerPtrMatriz(ind_rot_sup);
    pm_rot_cabezal = leerPtrMatriz(ind_rot_cabezal);
}

unsigned Flexo::leerNumParametros() const {
    return 5;
}

void Flexo::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    switch(iParam) {
        case 0:
            *pm_rot_inf = rotate(float(-M_PI/7)+float(M_PI/7)*sin(float(M_PI*0.3*t_sec)), vec3{ 0.0,0.0,1.0 });
            break;
        case 1:
            *pm_rot_sup = (translate(vec3(-0.68, 1.9, 0.0))) * 
                            (rotate(float(M_PI/3)+float(M_PI/3)*sin(float(M_PI*0.3*t_sec)), vec3{ 0.0,0.0,1.0 })) *
                            (translate(vec3(0.68, -1.9, 0.0)));
            break;
        case 2:
            *pm_rot_cabezal = (translate(vec3(-1.1,1.7,0.0))) * 
                            (rotate(float(2*M_PI*0.3)*t_sec, vec3{ 1.0,1.0,0.0 })) *
                            (translate(vec3(1.1,-1.7,0.0)));
            break;
        case 3:
            *pm_tras_tornillo = translate(vec3(0.0, -4-4*sin(2*M_PI*0.15*t_sec), 0.0));
            break;
        case 4:
            *pm_rot_tornillo = (translate(vec3(0.5, 4.5, 0.0))) * 
                            (rotate(float(2.5*M_PI)+float(2.5*M_PI)*sin(float(M_PI*0.3*t_sec)), vec3{ 0.0,1.0,0.0 })) *
                            (translate(vec3(-0.5, -4.5, 0.0)));
            break;
        default:
            break;
    }
   
}

Base::Base() {
    ponerColor({0.93,0.64,0.09});
    ponerNombre("Base del flexo");

    agregar(scale(vec3(1.0,0.2,1.0)));
    agregar(new Semiesfera(18,20));
    agregar(new Circulo());
}

Sargento::Sargento() {
    ponerColor({0.7,0.76,0.87});
    ponerNombre("Sargento de la base");

    agregar(translate(vec3(-0.5,-6.0,0.0)));
    agregar(scale(vec3(0.25,1.25,0.25)));
    agregar(new MallaTorre(5));

    agregar(scale(vec3(2.0,0.25,1.0)));
    agregar(translate(vec3(1.0,-1.0,0.5)));
    agregar(new Cubo());
}

Tornillo::Tornillo() {
    ponerNombre("Tornillo del sargento");

    agregar(translate(vec3(0.5,-5.0,0.0)));
    agregar(scale(vec3(0.25,20.0,0.25)));
    agregar(new Cilindro(15,20));
    agregar(new Circulo());

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(4.0,0.05,4.0)));
    agregar(new Circulo());
    agregar(new Cilindro(5,20));
    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(new Circulo());
    
    agregar(translate(vec3(0.0,-20.0,0.0)));
    agregar(scale(vec3(1.5,0.6,0.1875)));
    agregar(rotate(radians(90.0f),vec3(0.0,0.0,-1.0)));
    agregar(new Cilindro(10,20));
    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(new Circulo());
}

CuerpoInf::CuerpoInf() {
    ponerColor({0.0,0.75,1.0});
    ponerNombre("Cuerpo inferior del flexo");

    agregar(rotate(radians(20.0f),vec3(0.0,0.0,1.0)));
    agregar(scale(vec3(0.15,2.0,0.15)));
    agregar(new Cilindro(10,20));

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(1.1,0.08,1.1)));
    agregar(new Esfera(18,20));
}

CuerpoSup::CuerpoSup() {
    ponerColor({0.0,0.75,1.0});
    ponerNombre("Cuerpo superior del flexo");

    agregar(translate(vec3(-0.68,1.9,0.0)));
    agregar(rotate(radians(-40.0f),vec3(0.0,0.0,1.0)));

    agregar(scale(vec3(0.15,1.4,0.15)));
    agregar(new Cilindro(10,20));

    agregar(translate(vec3(0.0,1.0,0.0)));
    agregar(scale(vec3(1.0,0.09,1.0)));
    agregar(new Esfera(18,20));
}

Cabezal::Cabezal() {
    ponerColor({0.25,0.41,0.88});
    ponerNombre("Cabezal del flexo");

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
    ponerNombre("Bombilla del cabezal");

    agregar(scale(vec3(0.15,0.15,0.15)));
    agregar(rotate(radians(180.0f),vec3(1.0,0.0,1.0)));
    agregar(new Semiesfera(18,20));
    
    agregar(rotate(radians(180.0f),vec3(1.0,0.0,1.0)));
    agregar(scale(vec3(1.0,3.5,1.0)));
    agregar(new Cilindro(10,20));
}

// ---------------------------------------------------------------------

Circulo::Circulo() {
   vertices.push_back({0.0, 0.0, 0.0});
   for (float i=0; i<20; i++) {
      float angulo = i*2*M_PI/19;
      vertices.push_back({cos(angulo), 0.0, sin(angulo)});
   }

   for (unsigned i=1; i<20; i++) {
      triangulos.push_back({0,i,i+1});
   }
}

Semiesfera::Semiesfera(
      const int num_verts_per,  // número de vértices del perfil original (m)
      const unsigned nperfiles  // número de perfiles (n)
   )
:  MallaRevol()
{
   std::vector<glm::vec3>  perfil;
   for (float i=0; i<num_verts_per; i++) {
      float angulo = i*(M_PI/2)/(num_verts_per-1);
      perfil.push_back({sin(angulo), cos(angulo), 0.0});
   }

   inicializar(perfil, nperfiles);
}

