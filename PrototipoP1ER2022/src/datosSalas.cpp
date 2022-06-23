#include "datosSalas.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

datosSalas::datosSalas(int valorCodigoP, string valorEstatus, string valorNombrePuestos)
{
    establecerCodigoP( valorCodigoP );
    establecerEstatus( valorEstatus );
    establecerNombrePuestos( valorNombrePuestos );
}
int datosSalas::obtenerCodigoP() const
{
   return codigoP;
}
void datosSalas::establecerCodigoP( int valorCodigoP )
{
   codigoP = valorCodigoP;
}
string datosSalas::obtenerEstatus() const
{
   return Estatus;

}
void datosSalas::establecerEstatus( string EstatusString )
{
    const char *valorEstatus = EstatusString.data();
    int longitudP = strlen( valorEstatus );
    longitudP = ( longitudP < 15 ? longitudP : 14 );
    strncpy( Estatus, valorEstatus, longitudP );

    Estatus[ longitudP ] = '\0';

}
string datosSalas::obtenerNombre() const
{
   return nombreP;
}
void datosSalas::establecerNombrePuestos( string nombrePuestos )
{
    const char *valorNombrePuestos = nombrePuestos.data();
    int longitudP = strlen( valorNombrePuestos );
    longitudP = ( longitudP < 10 ? longitudP : 9 );
    strncpy( nombreP, valorNombrePuestos, longitudP );

    nombrePuestos[ longitudP ] = '\0';

}


datosSalas::~datosSalas()
{
    //dtor
}
