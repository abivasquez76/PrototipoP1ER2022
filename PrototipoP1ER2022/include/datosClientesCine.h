#ifndef DATOSCLIENTESCINE_H
#define DATOSCLIENTESCINE_H
#include <iostream>

using std::string;


class datosClientesCine
{
    public:

        virtual ~datosClientesCine();

        datosClientesCine( int = 0, string = "", double = 0.0 );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerNombre( string );
        string obtenerNombre() const;

        void establecerCantidad( double);
        double obtenerCantidad() const;
    protected:

    private:
        int codigo;
        char nombre[ 15 ];
        double cantidad;

};

#endif
