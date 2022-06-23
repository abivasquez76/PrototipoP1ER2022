#ifndef DATOSSALASCINE_H
#define DATOSSALASCINE_H
#include <iostream>

using std::string;

class datosSalasCine
{
    public:
        virtual ~datosSalasCine();

        datosSalasCine( int = 0, string = "", string = "" );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerApellido( string );
        string obtenerApellido() const;

        void establecerNombre( string );
        string obtenerNombre() const;

    protected:

    private:
        int codigo;
        char apellido[ 15 ];
        char nombre[ 10 ];

};

#endif

