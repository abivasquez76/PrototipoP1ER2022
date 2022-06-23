#include "datosClientesCine .h"
#include "clientesCine.h"
#include <cstring>
#include <iostream>

using std::string;
datosClientesCine::datosClientesCine(int valorCodigo, string valorNombre, double valorCantidad)
{
     establecerCodigo( valorCodigo );
    establecerNombre( valorNombre );
    establecerCantidad( valorCantidad );

    //ctor
}
int datosClientesCine::obtenerCodigo() const
{
   return codigo;
}
void datosClientesCine::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
string datosClientesCine::obtenerNombre() const
{
   return nombre;
}
void datosClientesCine::establecerNombre(string nombreString)
{
    const char *valorNombre = nombreString.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( nombre, valorNombre, longitud );

    nombreString[ longitud ] = '\0';

}

double datosClientesCine::obtenerCantidad() const
{
   return cantidad;
}
void datosClientesCine::establecerCantidad( double valorCantidad )
{
   cantidad = valorCantidad;
}
datosClientesCine::~datosClientesCine()
{
    //dtor
}
