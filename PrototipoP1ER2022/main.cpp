#include <iostream>
#include "usuariosCine.h"
#include "datosUsuariosCine.h"

using namespace std;
int escribirOpcion();
int escribirOpcionCatalogo();
int escribirOpcionInforme();
enum Opciones { catalogos = 1, procesos, informes, FIN };

int main()
{
    usuariosCine usuariosDeCine;
    int opcion=0;



}
int escribirOpcionCatalogo(){
    system("cls");
    cout<<"\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t |    Abigail Elizabeth Vasquez Herrera 9959-21-13777  |"<<endl;
    cout<<"\t\t\t---------------------------------"<<endl;
    cout<< "\n\n\t\t\t  1. Peliculas" << endl
    << "\t\t\t  2. Salas" << endl
    << "\t\t\t  3. Asientos" << endl
    << "\t\t\t  4. cines" << endl
    << "\t\t\t  5. clientes" << endl
    << "\t\t\t  6. Regresar al menu principal" << endl
    <<"\n\t\t\t---------------------------------"<<endl
    << "\n\t\t\tIngrese su opcion: ";
    int opcionMenuCat;
    cin >> opcionMenuCat;

    return opcionMenuCat;
}
int escribirOpcionInforme(){
    system("cls");
    cout<<"\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t |    Abigail Elizabeth Vasquez Herrera 9959-21-13777  |"<<endl;
    cout<<"\t\t\t---------------------------------"<<endl;
    cout<< "\n\n\t\t\t  1. Peliculas" << endl
    << "\t\t\t  2. Salas" << endl
    << "\t\t\t  3. Asientos" << endl
    << "\t\t\t  4. cines" << endl
    << "\t\t\t  5. clientes" << endl
    << "\t\t\t  6. Regresar al menu principal" << endl
    <<"\n\t\t\t---------------------------------"<<endl
    << "\n\t\t\tIngrese su opcion: ";
    int opcionMenuC;
    cin >> opcionMenuC;

    return opcionMenuC;
}
