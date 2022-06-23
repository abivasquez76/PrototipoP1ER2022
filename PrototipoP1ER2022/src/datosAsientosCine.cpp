#include "datosAsientosCine.h"
#include "asientosCine.h"

#include <cstring>
#include <iostream>

using std::string;

datosAsientosCine::datosAsientosCine(int valorCodigo, string valorNombre, int valorCelular)
{
    establecerCodigo( valorCodigo );
    establecerNombre( valorNombre );
    establecerCelular( valorCelular );
}
int datosAsientosCine::obtenerCodigo() const
{
   return codigo;
}
void datosAsientosCine::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
string datosAsientosCine::obtenerNombre() const
{
   return nombre;
}
void datosAsientosCine::establecerNombre( string nombreEmpre )
{
    const char *valorNombre = nombreEmpre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 20 ? longitud : 19 );
    strncpy( nombre, valorNombre, longitud );

    nombreEmpre[ longitud ] = '\0';

}
int datosAsientosCine::obtenerCelular() const
{
   return celular;
}
void datosAsientosCine::establecerCelular( int valorCelular )
{
   celular = valorCelular;
}
datosAsientosCine::~datosAsientosCine()
{
    //dtor
}
