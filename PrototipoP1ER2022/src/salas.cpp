#include "salas.h"
#include "datosSalas.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

void nuevoRegistroPuesto( fstream& );
int obtenernCodigoPuesto( const char * const );
void mostrarLineaP( ostream&, const datosSalas & );
void imprimirRegistroPuesto( fstream& );
void crearArchivoPuesto();
void modificarRegistroPuesto( fstream& );
void eliminarRegistroPuesto( fstream& );
void consultarRegistroPuesto( fstream& );
void mostrarLineaPantallaP( const datosSalas &);

enum Optios { imprim = 1, nuevo = 2, leer, eliminar, editar, regresar};

salas::salas()
{
    cout<<"\n\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t----------------"<<endl;
	cout<<"\t\t\t\t |   CINES  |"<<endl;
	cout<<"\t\t\t\t----------------"<<endl;

	fstream puestoEntradaSalida( "Cin.dat", ios::in | ios::out | ios::binary);
    if ( !puestoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoPuesto();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
   int opcionP=0;

    while ( ( opcionP = escribirOption() ) != regresar ) {

        switch ( opcionP ) {

         case imprim:
            {
                imprimirRegistroPuesto( puestoEntradaSalida );
            }
            break;
         case nuevo:
            {
                nuevoRegistroPuesto( puestoEntradaSalida );
            }
            break;
         case leer:
            {
                consultarRegistroPuesto( puestoEntradaSalida );

            }
            break;
          case eliminar:
            {
                eliminarRegistroPuesto( puestoEntradaSalida );
            }
            break;
          case editar:
            {
                modificarRegistroPuesto( puestoEntradaSalida );
            }
            break;
            break;
        }
        puestoEntradaSalida.clear();
    }
}



int salas::escribirOption()
{
    cout<<"\n\t\t\t   --------------------------"<<endl;
	cout<<"\t\t\t    | ||||||||  CINES    |||||||| |"<<endl;
	cout<<"\t\t\t   --------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Crear un archivo de texto para imprimir" << endl
        << "\t\t\t 2. Crear un nuevo cine" << endl
        << "\t\t\t 3. Ver los Cines" << endl
        << "\t\t\t 4. Eliminar cine" << endl
        << "\t\t\t 5. Editar cine" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        << "\n\t\t\t---------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
   int opcionMenuP;
   cin >> opcionMenuP; // recibir opción del usuario

   return opcionMenuP;

}

void imprimirRegistroPuesto( fstream &leerDeArchivoP )
{
    ofstream archivoImprimirSalidaP( "ImprimirCines.txt", ios::out );
    if ( !archivoImprimirSalidaP ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalidaP << left << setw( 10 ) << "Codigo" << setw( 16 )<< "Direccion" << setw( 14 ) << "Nombre" << endl;
    leerDeArchivoP.seekg( 0 );

    datosSalas puestos;
    leerDeArchivoP.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );

    while ( !leerDeArchivoP.eof() ) {
        if ( puestos.obtenerCodigoP() != 0 )
        mostrarLineaP( archivoImprimirSalidaP, puestos );
        leerDeArchivoP.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );
    } //FIN DE WHILE
cout << "archivo creado exitosamente"<<endl;
}

void mostrarLineaP( ostream &salida, const datosSalas &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigoP()
          << setw( 16 ) << registro.obtenerEstatus().data()
          << setw( 14 ) << registro.obtenerNombre().data()<< endl;

}

void crearArchivoPuesto()
{
    ofstream creditoSalida( "Cin.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosSalas puestoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &puestoEnBlanco ), sizeof( datosSalas ) );
}

void nuevoRegistroPuesto( fstream &insertarEnArchivo )
{
    int codigoP = obtenernCodigoPuesto( "\nEscriba el Codigo del cine " );
    insertarEnArchivo.seekg( ( codigoP - 1 ) * sizeof( datosSalas ) );
    datosSalas puestos;
    insertarEnArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );

    if ( puestos.obtenerCodigoP() == 0 ) {
        char Estatus[ 15 ];
        char nombreP[ 10 ];
        cout<<"Escriba la Direccion del cine: ";
        cin>> setw( 15 ) >> Estatus;
        cout<<"Escriba el Nombre del cine: ";
        cin>> setw( 10 ) >> nombreP;

        puestos.establecerEstatus( Estatus );
        puestos.establecerNombrePuestos( nombreP );
        puestos.establecerCodigoP( codigoP );

        insertarEnArchivo.seekp( ( codigoP - 1 ) * sizeof( datosSalas ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &puestos ), sizeof( datosSalas ) );
        cout<<"\n cine agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El cine con codigo #" << codigoP << " ya contiene informacion.\n" << endl;

}

int obtenernCodigoPuesto( const char * const indicador )
{
   int codigoP;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigoP;

    } while ( codigoP < 1 || codigoP > 100 );

   return codigoP;

}

void modificarRegistroPuesto( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Nombre\n 2. Direccion\n  R - ";
    cin>>opcionAc;

    if (opcionAc== 1){
        int codigoP = obtenernCodigoPuesto( "\nEscriba el codigo del cine que desea Modifcar" );

        actualizarArchivo.seekg(( codigoP - 1 ) * sizeof( datosSalas ));

        datosSalas puestos;
        actualizarArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );

        //ACTUALIZAR EL REGISTRO
        if (puestos.obtenerCodigoP() != 0 ) {
            mostrarLineaP( cout, puestos );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombreP;
            cin >> nombreP;

            string nombreAnterior = puestos.obtenerNombre();
            puestos.establecerNombrePuestos( nombreP );
            mostrarLineaP( cout, puestos );

            actualizarArchivo.seekp(( codigoP - 1 ) * sizeof( datosSalas ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &puestos ), sizeof( datosSalas ) );
        }
    }else if(opcionAc == 2){
        int codigoP = obtenernCodigoPuesto( "Escriba el codigo del Cine que desea Modifcar" );

        actualizarArchivo.seekg(( codigoP - 1 ) * sizeof( datosSalas ));

        datosSalas puestos;
        actualizarArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );

        if (puestos.obtenerCodigoP() != 0 ) {
                mostrarLineaP( cout, puestos );
                cout << "\nEscriba la nueva Direccion: ";
                string Estatus;
                cin >> Estatus;

                string apellidoAnterior = puestos.obtenerEstatus();
                puestos.establecerEstatus( Estatus );
                mostrarLineaP( cout, puestos );

                actualizarArchivo.seekp(( codigoP - 1 ) * sizeof( datosSalas ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &puestos ), sizeof( datosSalas ) );
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-

void eliminarRegistroPuesto( fstream &eliminarDeArchivo )
{
    int codigoP = obtenernCodigoPuesto( "\nEscriba el codigo del Cine a Eliminar" );
    eliminarDeArchivo.seekg( ( codigoP - 1 ) * sizeof( datosSalas ) );
    datosSalas puestos;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );

    if ( puestos.obtenerCodigoP() != 0 ) {
        datosSalas puestoEnBlanco;
        eliminarDeArchivo.seekp( ( codigoP - 1 ) * sizeof( datosSalas ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &puestoEnBlanco ), sizeof( datosSalas ) );

      cout << " codigo #" << codigoP << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "El codigo #" << codigoP << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-

void consultarRegistroPuesto( fstream &leerDeArchivoP )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 16 ) << "Direccion" << setw( 14 ) << " Nombre" << endl;
    leerDeArchivoP.seekg( 0 );
    datosSalas puestos;
    leerDeArchivoP.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );
    while ( !leerDeArchivoP.eof() ) {
        if ( puestos.obtenerCodigoP() != 0 )
            mostrarLineaPantallaP(puestos);
            leerDeArchivoP.read( reinterpret_cast< char * >( &puestos ), sizeof( datosSalas ) );

   } //FIN WHILE

} //FIN CONSULTAR REGISTRO

void mostrarLineaPantallaP( const datosSalas &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigoP()
          << setw( 16 ) << registro.obtenerEstatus().data()
          << setw( 14 ) << registro.obtenerNombre().data()<< endl;

} //FIN -MOSTRARLINEAENOANTALLA-


salas::~salas()
{
    //dtor
}

