#include "peliculas.h"
#include "datosPeliculas.h"
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

int opcionEmp();
void imprimirRegistroEmp( fstream& );
void crearArchivoCreditoEmp();
void mostrarLineaEmp( ostream&, const datosPeliculas & );
void nuevoRegistroEmp( fstream& );
int obtenernCodigoEmp( const char * const );
void modificarRegistroEmp( fstream& );
void eliminarRegistroEmp( fstream& );
void consultarRegistroEmp( fstream& );
void mostrarLineaPantallaEmp( const datosPeliculas &);

using namespace std;

peliculas::peliculas()
{
    fstream creditoEntradaSalida( "peli.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoEmp();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    enum Opciones { agregar = 1, nuevo, modificar, eliminar, mostrar, FIN };
    int opcion;
    while ( ( opcion = opcionEmp() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroEmp( creditoEntradaSalida );
            break;
            case nuevo:
                nuevoRegistroEmp( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroEmp( creditoEntradaSalida );
            break;
            case eliminar:
                eliminarRegistroEmp( creditoEntradaSalida );
            break;
            case mostrar:
                consultarRegistroEmp( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionEmp(){
    cout<<"\n\t\t\t---------------------------------"<<endl;
    cout<<"\n\t\t\t\t------------------"<<endl;
	cout<<"\t\t\t\t |   peliculas  |"<<endl;
	cout<<"\t\t\t\t------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Agregar pelicula" << endl
        << "\t\t\t 3. Modificar pelicula" << endl
        << "\t\t\t 4. Eliminar pelicula" << endl
        << "\t\t\t 5. Mostrar Lista de peliculas" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl
        <<"\n\t\t\t---------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu;
    cin >> opcionMenu;

   return opcionMenu;
}
void imprimirRegistroEmp( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirPelicula.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Codigo" << setw( 16 )<< "Nombre" << setw( 14 ) << "Clasificacion" << setw( 16 ) << "genero"<< right
       << setw( 10 ) << "precio" << endl;
    leerDeArchivo.seekg( 0 );

    datosPeliculas empleados;
    leerDeArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

    while ( !leerDeArchivo.eof() ) {
        if ( empleados.obtenerCodigo() != 0 )
        mostrarLineaEmp( archivoImprimirSalida, empleados );
        leerDeArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaEmp( ostream &salida, const datosPeliculas &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerCorreo().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed<< showpoint << registro.obtenerSueldo() << endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoEmp()
{
    ofstream creditoSalida( "peli.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosPeliculas empleadoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &empleadoEnBlanco ), sizeof( datosPeliculas ) );
}
void nuevoRegistroEmp( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoEmp( "\nEscriba el Codigo de la Pelicula " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( datosPeliculas ) );
    datosPeliculas empleados;
    insertarEnArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

    if ( empleados.obtenerCodigo() == 0 ) {
        char apellido[ 15 ];
        char nombre[ 10 ];
        char correo[ 15 ];
        double sueldo;
        cout<<"Escriba el Nombre de la pelicula: ";
        cin>> setw( 15 ) >> apellido;
        cout<<"Escriba la clasificacion de la pelicula: ";
        cin>> setw( 10 ) >> nombre;
        cout<<"Escriba el Genero de la pelicula: ";
        cin>> setw( 15 ) >> correo;
        cout<<"Escriba el Precio de la pelicula: ";
        cin>> sueldo;
        empleados.establecerApellido( apellido );
        empleados.establecerNombre( nombre );
        empleados.establecerCorreo( correo );
        empleados.establecerSueldo( sueldo );
        empleados.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( datosPeliculas ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &empleados ), sizeof( datosPeliculas ) );
        cout<<"\n Pelicula agregada Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "La Pelicula con codigo #" << codigo << " ya contiene informacion.\n" << endl;

} //FIN REGISTRO
int obtenernCodigoEmp( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroEmp( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. precio\n 2. Clasificación\n 3. Nombre \n 4. Genero\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo del Empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPeliculas ));

        datosPeliculas empleados;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

        if (empleados.obtenerCodigo() != 0 ) {
            mostrarLineaEmp( cout, empleados );
            cout << "\nEscriba aumento (+) o descuento (-): ";
            double cambiosu;
            cin >> cambiosu;
            double sueldoAnterior = empleados.obtenerSueldo();
            empleados.establecerSueldo( sueldoAnterior + cambiosu );
            mostrarLineaEmp( cout, empleados );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPeliculas ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &empleados ), sizeof( datosPeliculas ) );
        }

    }else if (opcionAc== 2){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo de la pelicula que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPeliculas ));

        datosPeliculas empleados;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

        //ACTUALIZAR EL REGISTRO
        if (empleados.obtenerCodigo() != 0 ) {
            mostrarLineaEmp( cout, empleados );
            cout << "\nEscriba la nueva clasificacion: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = empleados.obtenerNombre();
            empleados.establecerNombre( nombre );
            mostrarLineaEmp( cout, empleados );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPeliculas ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &empleados ), sizeof( datosPeliculas ) );
        }
    }else if(opcionAc == 3){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo de la pelicula que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPeliculas ));

        datosPeliculas empleados;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

        if (empleados.obtenerCodigo() != 0 ) {
                mostrarLineaEmp( cout, empleados );
                cout << "\nEscriba el nuevo Nombre: ";
                string apellido;
                cin >> apellido;

                string apellidoAnterior = empleados.obtenerApellido();
                empleados.establecerApellido( apellido );
                mostrarLineaEmp( cout, empleados );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPeliculas ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &empleados ), sizeof( datosPeliculas ) );
        }
    }else if(opcionAc == 4){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo de la pelicula que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPeliculas ));

        datosPeliculas empleados;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

        if (empleados.obtenerCodigo() != 0 ) {
                mostrarLineaEmp( cout, empleados );
                cout << "\nEscriba el nuevo Genero: ";
                string correo;
                cin >> correo;

                string correoAnterior = empleados.obtenerCorreo();
                empleados.establecerCorreo( correo );
                mostrarLineaEmp( cout, empleados );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPeliculas ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &empleados ), sizeof( datosPeliculas ) );
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroEmp( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoEmp( "\nEscriba el codigo de la pelicula a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( datosPeliculas ) );
    datosPeliculas empleados;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

    if ( empleados.obtenerCodigo() != 0 ) {
        datosPeliculas clienteEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( datosPeliculas ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &clienteEnBlanco ), sizeof( datosPeliculas ) );

      cout << " Cuenta #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "La cuenta #" << codigo << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-
void consultarRegistroEmp( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 16 ) << " Nombre" << setw( 14 ) << " Clasificacion" << setw( 16 ) << " Genero" << right << setw( 10 ) << " Sueldo" << endl;
    leerDeArchivo.seekg( 0 );
    datosPeliculas empleados;
    leerDeArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );
    while ( !leerDeArchivo.eof() ) {
        if ( empleados.obtenerCodigo() != 0 )
            mostrarLineaPantallaEmp(empleados);
            leerDeArchivo.read( reinterpret_cast< char * >( &empleados ), sizeof( datosPeliculas ) );

   } //FIN WHILE

} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaEmp( const datosPeliculas &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerCorreo().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed
          << showpoint << registro.obtenerSueldo() << endl;

} //FIN -MOSTRARLINEAENOANTALLA-

peliculas::~peliculas()
{
    //dtor
}

