#include "salasCine.h"
#include "datosSalasCine.h"
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

int opcionDepa();
void crearArchivoCreditoDepa();
void imprimirRegistroDepa( fstream& );
void mostrarLineaDepa( ostream&, const datosSalasCine & );
void nuevoRegistroDepa( fstream& );
int obtenernCodigoDepa( const char * const );
void modificarRegistroDepa( fstream& );
void eliminarRegistroDepa( fstream& );
void consultarRegistroDepa( fstream& );
void mostrarLineaPantallaDepa( const datosSalasCine &);
using namespace std;

salasCine::salasCine()
{
    fstream creditoEntradaSalida( "SalasCineArch.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoDepa();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion1;
    while ( ( opcion1 = opcionDepa() ) != FIN ) {
        switch ( opcion1 ) {
            case agregar:
                imprimirRegistroDepa( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroDepa( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroDepa( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroDepa( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroDepa( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE

}
int opcionDepa(){

    cout<<"\n\t\t\t---------------------------------"<<endl;
    cout<<"\t\t\t\t------------------"<<endl;
	cout<<"\t\t\t\t|  Salas de Cine  |"<<endl;
	cout<<"\t\t\t\t------------------"<<endl;


    cout<< "\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar sala de cine" << endl
        << "\t\t\t 3. Modificar sala de cine" << endl
        << "\t\t\t 4. Eliminar sala de cine" << endl
        << "\t\t\t 5. Mostrar Lista sala de cine" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        << "\n\t\t\t---------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";

    int opciionMenu;
    cin >> opciionMenu;

    return opciionMenu;

}
void imprimirRegistroDepa( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirSalasCine.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Codigo" << setw( 16 )<< "Estatus" << right << setw( 10 ) << "Asientos" << endl;
    leerDeArchivo.seekg( 0 );

    datosSalasCine departamentos;
    leerDeArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );

    while ( !leerDeArchivo.eof() ) {
        if ( departamentos.obtenerCodigo() != 0 )
        mostrarLineaDepa( archivoImprimirSalida, departamentos );
        leerDeArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaDepa( ostream &salida, const datosSalasCine &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data() << endl;


}//FIN -MOSTRARLINEA-
void crearArchivoCreditoDepa()
{
    ofstream creditoSalida( "SalasCineArch.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosSalasCine empleadoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &empleadoEnBlanco ), sizeof( datosSalasCine ) );
}
void nuevoRegistroDepa( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoDepa( "\nEscriba el Codigo " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( datosSalasCine ) );
    datosSalasCine departamentos;
    insertarEnArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );

    if ( departamentos.obtenerCodigo() == 0 ) {
        char apellido[ 15 ];
        char nombre[ 10 ];

        cout<<"Escriba el Estatus de la sala de cine: ";
        cin>> setw( 15 ) >> apellido;
        cout<<"Escriba el Número de asientos: ";
        cin>> setw( 10 ) >> nombre;

        departamentos.establecerApellido( apellido );
        departamentos.establecerNombre( nombre );
        departamentos.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( datosSalasCine ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &departamentos ), sizeof( datosSalasCine ) );
        cout<<"\n Sala de Cine agregada Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "La Sala de cine con codigo #" << codigo << " ya contiene informacion.\n" << endl;

} //FIN REGISTRO
int obtenernCodigoDepa( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroDepa( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Asientos \n 2. Estatus\n   R - ";
    cin>>opcionAc;

     if (opcionAc== 1){
        int codigo = obtenernCodigoDepa( "\nEscriba el codigo de sala de cine que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosSalasCine ));

        datosSalasCine departamentos;
        actualizarArchivo.read( reinterpret_cast< char * >( &departamentos), sizeof( datosSalasCine ) );

        //ACTUALIZAR EL REGISTRO
        if (departamentos.obtenerCodigo() != 0 ) {
            mostrarLineaDepa( cout, departamentos );
            cout << "\nEscriba el Nuevo Número de asientos: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = departamentos.obtenerNombre();
            departamentos.establecerNombre( nombre );
            mostrarLineaDepa( cout, departamentos );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosSalasCine ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &departamentos ), sizeof( datosSalasCine ) );
        }
    }else if(opcionAc == 2){
        int codigo = obtenernCodigoDepa( "Escriba el codigo de sala de cine que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosSalasCine ));

        datosSalasCine departamentos;
        actualizarArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );

        if (departamentos.obtenerCodigo() != 0 ) {
                mostrarLineaDepa( cout, departamentos );
                cout << "\nEscriba el nuevo Estatus: ";
                string apellido;
                cin >> apellido;

                string apellidoAnterior = departamentos.obtenerApellido();
                departamentos.establecerApellido( apellido );
                mostrarLineaDepa( cout, departamentos );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosSalasCine ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &departamentos ), sizeof( datosSalasCine ) );
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroDepa( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoDepa( "\nEscriba el codigo de la sala de cine a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( datosSalasCine ) );
    datosSalasCine departamentos;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );

    if ( departamentos.obtenerCodigo() != 0 ) {
        datosSalasCine clienteEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( datosSalasCine ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &clienteEnBlanco ), sizeof( datosSalasCine ) );

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-
void consultarRegistroDepa( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 16 ) << "Estatus" << right << setw( 10 ) << " Asientos" << endl;
    leerDeArchivo.seekg( 0 );
    datosSalasCine departamentos;
    leerDeArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );
    while ( !leerDeArchivo.eof() ) {
        if ( departamentos.obtenerCodigo() != 0 )
            mostrarLineaPantallaDepa(departamentos);
            leerDeArchivo.read( reinterpret_cast< char * >( &departamentos ), sizeof( datosSalasCine ) );

   } //FIN WHILE

} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaDepa( const datosSalasCine &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()<< endl;

} //FIN -MOSTRARLINEAENOANTALLA-
salasCine::~salasCine()
{
    //dtor
}
