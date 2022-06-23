#include "clientesCine.h"
#include "datosAsientosCine.h"
#include "datosClientesCine.h"
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


int opcionImp();
void imprimirRegistroImp( fstream& );
void crearArchivoCreditoImp();
void mostrarLineaImp( ostream&, const datosClientesCine & );
void nuevoRegistroImp( fstream& );
int obtenernCodigoImp( const char * const );
int obtenernCodigoImp( const char * const );
void modificarRegistroImp (fstream& );
void eliminarRegistroImp( fstream& );
void consultarRegistroImp( fstream& );
void mostrarLineaPantallaImp( const datosClientesCine &);

using namespace std;


clientesCine::clientesCine()
{
     fstream creditoEntradaSalida( "ClientesC.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoImp();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionImp() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroImp( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroImp( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroImp( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroImp( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroImp( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionImp(){
    //system("cls");
    cout<<"\n\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t------------------"<<endl;
	cout<<"\t\t\t\t|  CLIENTES  |"<<endl;
	cout<<"\t\t\t\t------------------"<<endl;


    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar Cliente" << endl
        << "\t\t\t 3. Modificar Cliente" << endl
        << "\t\t\t 4. Eliminar Cliente" << endl
        << "\t\t\t 5. Mostrar Lista de Clientes" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t---------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";

    int opcionMenu;
    cin >> opcionMenu;

    return opcionMenu;

}
void imprimirRegistroImp( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirClienesCine.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Codigo" << setw( 16 )<< "Nombre" << right << setw( 10 ) << "NIT" << endl;
    leerDeArchivo.seekg( 0 );

    datosClientesCine impuestos;
    leerDeArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );

    while ( !leerDeArchivo.eof() ) {
        if ( impuestos.obtenerCodigo() != 0 )
        mostrarLineaImp( archivoImprimirSalida, impuestos );
        leerDeArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaImp( ostream &salida, const datosClientesCine &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerNombre().data()
          << setw( 10 ) << registro.obtenerCantidad() << endl;


}//FIN -MOSTRARLINEA-
void crearArchivoCreditoImp()
{
    ofstream creditoSalida( "ClientesC.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosClientesCine impuestoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &impuestoEnBlanco ), sizeof( datosClientesCine ) );
}
void nuevoRegistroImp( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoImp( "\nEscriba el Codigo " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( datosClientesCine ) );
    datosClientesCine impuestos;
    insertarEnArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );

    if ( impuestos.obtenerCodigo() == 0 ) {
        char nombre[ 15 ];
        double cantidad;

        cout<<"Escriba el Nombre del Cliente: ";
        cin>> setw( 15 ) >> nombre;
        cout<<"Escriba el NIT del Cliente: ";
        cin>> setw( 10 ) >> cantidad;

        impuestos.establecerNombre( nombre );
        impuestos.establecerCantidad( cantidad );
        impuestos.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( datosClientesCine ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &impuestos ), sizeof( datosClientesCine ) );
        cout<<"\n Cliente agregado con excito..."<<endl;

    } //FIN IF
    else
        cerr << "El Cliente con codigo #" << codigo << " ya contiene informacion.\n" << endl;

} //FIN REGISTRO
int obtenernCodigoImp( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroImp( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Nombre\n 2. NIT\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoImp( "\nEscriba el codigo del Cliente que desea modificar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosClientesCine ));

        datosClientesCine impuestos;
        actualizarArchivo.read( reinterpret_cast< char * >( &impuestos), sizeof( datosClientesCine ) );

        if (impuestos.obtenerCodigo() != 0 ) {
            mostrarLineaImp( cout, impuestos );
            cout << "\nEscriba el nuevo nombre : ";
            string nombre;
            cin >> nombre;
            string nombreanterior = impuestos.obtenerNombre();
            impuestos.establecerNombre( nombre );
            mostrarLineaImp( cout, impuestos );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosClientesCine ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &impuestos ), sizeof( datosClientesCine ) );
        }

    }else if (opcionAc== 2){
        int codigo = obtenernCodigoImp( "\nEscriba el ccdigo del Cliente que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosClientesCine ));

        datosClientesCine impuestos;
        actualizarArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );

        //ACTUALIZAR EL REGISTRO
        if (impuestos.obtenerCodigo() != 0 ) {
            mostrarLineaImp( cout, impuestos );
            cout << "\nEscriba el nuevo NIT: ";
            double cantidad;
            cin >> cantidad;

            double cantidadAnterior = impuestos.obtenerCantidad();
            impuestos.establecerCantidad( cantidad );
            mostrarLineaImp (cout, impuestos );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosClientesCine));
            actualizarArchivo.write(reinterpret_cast< const char * >( &impuestos ), sizeof( datosClientesCine ) );
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroImp( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoImp( "\nEscriba el codigo del Cliente a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( datosClientesCine ) );
    datosClientesCine impuestos;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );

    if ( impuestos.obtenerCodigo() != 0 ) {
        datosClientesCine impuestosEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( datosClientesCine ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &impuestosEnBlanco ), sizeof( datosClientesCine));

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-
void consultarRegistroImp( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 16 ) << "Nombre " << right << setw( 10 ) << " NIT" << endl;
    leerDeArchivo.seekg( 0 );
    datosClientesCine impuestos;
    leerDeArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );
    while ( !leerDeArchivo.eof() ) {
        if ( impuestos.obtenerCodigo() != 0 )
            mostrarLineaPantallaImp(impuestos);
            leerDeArchivo.read( reinterpret_cast< char * >( &impuestos ), sizeof( datosClientesCine ) );

   } //FIN WHILE

} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaImp( const datosClientesCine &registro)
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerNombre().data()
          << setw( 14 ) << registro.obtenerCantidad()<< endl;

} //FIN -MOSTRARLINEAENOANTALLA-
clientesCine::~clientesCine()
{
    //dtor
}

