#ifndef DATOSUSUARIOSCINE_H
#define DATOSUSUARIOSCINE_H

#include <iostream>
using std::string;

class datosUsuariosCine
{
    public:
        virtual ~datosUsuariosCine();
        datosUsuariosCine( int = 0, int = 0 );

        void establecerUsuario( int );
        int obtenerUsuario() const;

        void establecerContra( int );
        int obtenerContra() const;

    protected:

    private:
        int usuario;
        int contra;
};

#endif // DATOSUSUARIO_H


