#include "asientosCine.h"
#include "datosAsientosCine.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ios;
using std::left;
using std::right;
using std::fixed;
using std::showpoint;

#include <fstream>
using std::ofstream;
using std::ostream;
using std::fstream;

#include <iomanip>
using std::setw;
using std::setprecision;
#include <cstdlib>

int opcionEmpre();
void imprimirRegistroEmpre( fstream& );
void crearArchivoCreditoEmpre();
void mostrarLineaEmpre( ostream&, const datosAsientosCine & );
void nuevoRegistroEmpre( fstream& );
int obtenerCodigoEmpre( const char * const );
void modificarRegistroEmpre( fstream& );
void eliminarRegistroEmpre( fstream& );
void consultarRegistroEmpre( fstream& );
void mostrarLineaPantallaEmpre( const datosAsientosCine &);

using namespace std;

asientosCine::asientosCine()
{
    fstream creditoEntradaSalida( "Asient.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoEmpre();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionEmpre() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroEmpre( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroEmpre( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroEmpre( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroEmpre( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroEmpre( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();
   } //FIN WHILE
}
int opcionEmpre(){
    cout<<"\n\t\t\t---------------------------------"<<endl;
    cout<<"\n\t\t\t\t-----------------"<<endl;
	cout<<"\t\t\t\t |   ASIETOS  |"<<endl;
	cout<<"\t\t\t\t-----------------"<<endl;

    cout<< "\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar Asiento" << endl
        << "\t\t\t 3. Modificar Asiento" << endl
        << "\t\t\t 4. Eliminar Asiento" << endl
        << "\t\t\t 5. Mostrar Lista de Asientos" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        << "\n\t\t\t---------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";

   int opcionMenu;
   cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroEmpre( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "Imprimirasientos.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Codigo" << setw( 20 )<< right << "Fila" << setw( 10 ) << "Columna" << endl;
    leerDeArchivo.seekg( 0 );

    datosAsientosCine empresas;
    leerDeArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );

    while ( !leerDeArchivo.eof() ) {
        if ( empresas.obtenerCodigo() != 0 )
        mostrarLineaEmpre( archivoImprimirSalida, empresas );
        leerDeArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaEmpre( ostream &salida, const datosAsientosCine &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigo()
          << setw( 20 ) << registro.obtenerNombre().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed<< showpoint << registro.obtenerCelular() << endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoEmpre()
{
    ofstream creditoSalida( "Asient.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosAsientosCine empresaEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &empresaEnBlanco ), sizeof( datosAsientosCine ) );
}
void nuevoRegistroEmpre( fstream &insertarEnArchivo )
{
    int codigo = obtenerCodigoEmpre( "\nEscriba el Codigo del asiento " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( datosAsientosCine ) );
    datosAsientosCine empresas;
    insertarEnArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );

    if ( empresas.obtenerCodigo() == 0 ) {
        char nombre[ 20 ];
        int celular;
        cout<<"Escriba la fila del Asiento: ";
        cin>> setw( 20 ) >> nombre;
        cout<<"Escriba la columna del Asiento: ";
        cin>> celular;
        empresas.establecerNombre( nombre );
        empresas.establecerCelular( celular );
        empresas.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( datosAsientosCine ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &empresas ), sizeof( datosAsientosCine ) );
        cout<<"\n Asiento agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Asiento con codigo #" << codigo << " ya contiene informacion.\n" << endl;
}
int obtenerCodigoEmpre( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;
}
void modificarRegistroEmpre( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Fila\n 2. Columna\n  R - ";
    cin>>opcionAc;

    if (opcionAc== 1){
        int codigo = obtenerCodigoEmpre( "\nEscriba el codigo del Asiento que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosAsientosCine ));

        datosAsientosCine empresas;
        actualizarArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );

        //ACTUALIZAR EL REGISTRO
        if (empresas.obtenerCodigo() != 0 ) {
            mostrarLineaEmpre( cout, empresas );
            cout << "\nEscriba la nueva Fila: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = empresas.obtenerNombre();
            empresas.establecerNombre( nombre );
            mostrarLineaEmpre( cout, empresas );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosAsientosCine ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &empresas ), sizeof( datosAsientosCine ) );
        }
    }else if(opcionAc == 2){
        int codigo = obtenerCodigoEmpre( "Escriba el codigo del Asiento que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosAsientosCine ));

        datosAsientosCine empresas;
        actualizarArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );

        if (empresas.obtenerCodigo() != 0 ) {
                mostrarLineaEmpre( cout, empresas );
                cout << "\nEscriba la nueva Columna: ";
                int celular;
                cin >> celular;

                int celularAnterior = empresas.obtenerCelular();
                empresas.establecerCelular( celular );
                mostrarLineaEmpre( cout, empresas );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosAsientosCine ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &empresas ), sizeof( datosAsientosCine ) );
                cout << "\nColumna Modificada Exitosamente...";
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroEmpre( fstream &eliminarDeArchivo )
{
    int codigo = obtenerCodigoEmpre( "\nEscriba el codigo del Asiento que desea Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( datosAsientosCine ) );
    datosAsientosCine empresas;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );

    if ( empresas.obtenerCodigo() != 0 ) {
        datosAsientosCine empresaEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( datosAsientosCine ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &empresaEnBlanco ), sizeof( datosAsientosCine ) );

      cout << " \nCuenta #" << codigo << " se elimino Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-
void consultarRegistroEmpre( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 20 ) << " Fila" << right << setw( 10 ) << "Columna" << endl;
    leerDeArchivo.seekg( 0 );
    datosAsientosCine empresas;
    leerDeArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );
    while ( !leerDeArchivo.eof() ) {
        if ( empresas.obtenerCodigo() != 0 )
            mostrarLineaPantallaEmpre(empresas);
            leerDeArchivo.read( reinterpret_cast< char * >( &empresas ), sizeof( datosAsientosCine ) );

   } //FIN WHILE

} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaEmpre( const datosAsientosCine &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 20 ) << registro.obtenerNombre().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed
          << showpoint << registro.obtenerCelular() << endl;

} //FIN -MOSTRARLINEAENOANTALLA-

asientosCine::~asientosCine()
{
    //dtor
}
