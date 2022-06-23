#include "datosPeliculas.h"
#include "peliculas.h"
#include <cstring>
#include <iostream>

using std::string;

datosPeliculas::datosPeliculas(int valorCodigo, string valorApellido, string valorNombre, string valorCorreo, double valorSueldo )
{
    establecerCodigo( valorCodigo );
    establecerApellido( valorApellido );
    establecerNombre( valorNombre );
    establecerCorreo( valorCorreo );
    establecerSueldo( valorSueldo );

}
int datosPeliculas::obtenerCodigo() const
{
   return codigo;
}
void datosPeliculas::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
string datosPeliculas::obtenerApellido() const
{
   return apellido;

}
void datosPeliculas::establecerApellido( string apellidoString )
{
    const char *valorApellido = apellidoString.data();
    int longitud = strlen( valorApellido );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( apellido, valorApellido, longitud );

    apellido[ longitud ] = '\0';

}
string datosPeliculas::obtenerNombre() const
{
   return nombre;
}
void datosPeliculas::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 10 ? longitud : 9 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';

}
double datosPeliculas::obtenerSueldo() const
{
   return sueldo;
}
void datosPeliculas::establecerSueldo( double valorSueldo )
{
   sueldo = valorSueldo;
}
string datosPeliculas::obtenerCorreo() const
{
   return correo;
}
void datosPeliculas::establecerCorreo( string correostring )
{
    const char *valorCorreo = correostring.data();
    int longitud = strlen( valorCorreo );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( correo, valorCorreo, longitud );

    correostring[ longitud ] = '\0';

}
datosPeliculas::~datosPeliculas()
{
    //dtor
}
