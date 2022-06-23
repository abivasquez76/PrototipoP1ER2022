#ifndef DATOSSALAS_H
#define DATOSSALAS_H

#include <iostream>

using std::string;

class datosSalas
{
    public:
        virtual ~datosSalas();

        datosSalas( int = 0, string = "", string = "");

        void establecerCodigoP( int );
        int obtenerCodigoP() const;

        void establecerEstatus( string );
        string obtenerEstatus() const;

        void establecerNombrePuestos( string );
        string obtenerNombre() const;

    protected:

    private:
        int codigoP;
        char Estatus[ 15 ];
        char nombreP[ 10 ];
};

#endif // DATOSPUESTOS_H
