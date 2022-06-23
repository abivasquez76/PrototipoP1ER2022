#include "datosUsuariosCine.h"
#include "usuariosCine.h"
#include <cstring>
#include <iostream>

using std::string;

datosUsuariosCine::datosUsuariosCine(int valorUsuario, int valorContra)
{
    establecerUsuario( valorUsuario );
    establecerContra( valorContra );
}
int datosUsuariosCine::obtenerUsuario() const
{
   return usuario;
}
void datosUsuariosCine::establecerUsuario( int valorUsuario )
{
   usuario = valorUsuario;
}
int datosUsuariosCine::obtenerContra() const
{
   return contra;
}
void datosUsuariosCine::establecerContra( int valorContra )
{
    contra=valorContra;
}

datosUsuariosCine::~datosUsuariosCine()
{
    //dtor
}



