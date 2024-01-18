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
// **     + Clase 'Peon' (derivada de 'NodoGrafoEscena')
// **     + Clase 'Lata' (derivada de 'NodoGrafoEscena')
// **     + Clase 'LataPeones' (derivada de 'NodoGrafoEscena')
// **     + Clase 'VariasLatasPeones' (derivada de 'NodoGrafoEscena')
// **
// **
// *********************************************************************

#include "latapeones.h"  

using namespace std ;
using namespace glm ;

Peon::Peon(const int &id, Material *mat) {
    ponerIdentificador(id);

    unsigned ind = agregar(translate(vec3(0.0, 0.0, 0.0)));
    agregar(mat);
    agregar(new MallaRevolPLY("peon.ply", 50));

    pm_tras = leerPtrMatriz(ind);
}

bool Peon::cuandoClick(const glm::vec3 & centro_wc) {
    cout << "Click en peón" << endl;
    *pm_tras = (*pm_tras) * (translate(vec3(0.0, 0.0, 2.0)));
    return true;
}

Lata::Lata(Material *mat) {
    agregar(new Material(0.4, 0.5, 0.8, 50));
    agregar(new MallaRevolPLY("lata-psup.ply", 50));
    agregar(new MallaRevolPLY("lata-pinf.ply", 50));
    agregar(mat);
    agregar(new MallaRevolPLY("lata-pcue.ply", 50));
}

LataPeones::LataPeones() {
    ponerNombre("LataPeones");

    NodoGrafoEscena *lata = new NodoGrafoEscena();
    NodoGrafoEscena *peon1 = new NodoGrafoEscena();
    NodoGrafoEscena *peon2 = new NodoGrafoEscena();
    NodoGrafoEscena *peon3 = new NodoGrafoEscena();

    lata->ponerNombre("Lata de Coca-Cola");
    lata->ponerIdentificador(1);
    lata->agregar(new Lata(new Material(new Textura("lata-coke.jpg"), 0.4, 1.0, 2.0, 50)));

    peon1->ponerNombre("Peón de madera");
    peon1->ponerIdentificador(2);
    peon1->agregar(scale(vec3(0.16, 0.16, 0.16)));
    peon1->agregar(translate(vec3(0.0, 1.4, 5.0)));
    peon1->agregar(new Peon(22, new Material(new TexturaXY("text-madera.jpg"), 0.25, 1.5, 1.5, 50)));

    peon2->ponerNombre("Peón de blanco");
    peon2->ponerIdentificador(3);
    peon2->agregar(scale(vec3(0.16, 0.16, 0.16)));
    peon2->agregar(translate(vec3(2.5, 1.4, 5.0)));
    peon2->agregar(new Peon(33, new Material(0.5, 0.5, 0.0, 1)));

    peon3->ponerNombre("Peón negro");
    peon3->ponerIdentificador(4);
    peon3->agregar(scale(vec3(0.16, 0.16, 0.16)));
    peon3->agregar(translate(vec3(5.0, 1.4, 5.0)));
    peon3->agregar(new Peon(44, new Material(0.0, 0.01, 0.8, 10)));

    agregar(lata);
    agregar(peon1);
    agregar(peon2);
    agregar(peon3);
}

VariasLatasPeones::VariasLatasPeones() {
    ponerNombre("VariasLatasPeones");

    NodoGrafoEscena *lata2 = new NodoGrafoEscena;
    NodoGrafoEscena *lata3 = new NodoGrafoEscena;

    lata2->ponerNombre("Lata de Pepsi");
    lata2->ponerIdentificador(5);
    lata2->agregar(translate(vec3(0.8, 0.0, 0.0)));
    lata2->agregar(new Lata(new Material(new Textura("lata-pepsi.jpg"), 0.4, 1.0, 2.0, 50)));

    lata3->ponerNombre("Lata de la UGR");
    lata3->ponerIdentificador(6);
    lata3->agregar(translate(vec3(1.6, 0.0, 0.0)));
    lata3->agregar(new Lata(new Material(new Textura("window-icon.jpg"), 0.4, 1.0, 2.0, 50)));

    agregar(new LataPeones);
    agregar(lata2);    
    agregar(lata3);

}