#ifndef DATOSASIENTOSCINE_H
#define DATOSASIENTOSCINE_H


#include <iostream>
using std::string;

class datosAsientosCine
{
    public:
        virtual ~datosAsientosCine();

        datosAsientosCine( int = 0, string = "", int = 0 );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerNombre( string );
        string obtenerNombre() const;

        void establecerCelular( int );
        int obtenerCelular() const;

    protected:

    private:
        int codigo;
        char nombre[ 20 ];
        int celular;
};

#endif

