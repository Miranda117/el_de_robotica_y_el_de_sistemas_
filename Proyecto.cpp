#include <iostream>
#include <conio.h>
# include <String.h>
# include <fstream>
# include <time.h>
# include <stdio.h>
using namespace std;



int menu_archivo(){


	char op ;

	while (true){
		printf("\n**********************************\n");
		printf("********* MENU ARDIVOS *********\n");
		printf("**********************************\n");
		printf("a) Alta nuevos productos \n");
		printf("b) Baja productos obsoletos \n");
		printf("c) Consulta productos por clave\n");
		printf("d) Consulta productos pro familia \n");
		printf("x) Terminar\n");
		cout<< "ingrese la opcion: ";cin>>op;

        switch (op){
		case 'a' :
		    cout<<"A\n";
		    break;
        case 'b' :
   		    cout<<"b\n";
           break;
        case 'c' :
   		    cout<<"c\n";
           break;
        case 'd' :
   		    cout<<"d\n";
           break;
        case 'x':
            return 0;
        break;
        }
	}
}
int menu_ent_sal(){
	char op ;

	while (true){
		printf("\n***************************************\n");
		printf("** Menu Entradas/salidas de productos**\n");
		printf("**********************************\n");
		printf("a) Entradas por compras\n");
		printf("b) Entradas por devolucion de clientes\n");
		printf("c) Salidas por ventas\n");
		printf("d) Salidas por devolucion a proveedores\n");
		printf("e) Salidas por mermas\n");
		printf("x) Terminar\n");
		cout<< "ingrese la opcion: ";cin>>op;

        switch (op){
		case 'a' :
		    cout<<"A\n";
		    break;
        case 'b' :
   		    cout<<"b\n";
           break;
        case 'c' :
   		    cout<<"c\n";
           break;
        case 'd' :
   		    cout<<"d\n";
           break;
       case 'e' :
   		    cout<<"e\n";
           break;
        case 'x':
            return 0;
        break;
        }
	}
}
int menu_reportesl(){
	char op ;

	while (true){
		printf("\n***************************************\n");
		printf("** Menu de reportes**\n");
		printf("**********************************\n");
		printf("a) General de productos ordenado por clave\n");
		printf("b) General de productos ordenado por nombre\n");
		printf("c) Productos por familia\n");
		printf("d) Productos a ordenar ordenado por existencia\n");
		printf("e) Productos a ofertar ordenado por existencia\n");
		printf("f) Listado de movimientos de un producto ordenado por fecha\n");
		printf("x) Terminar\n");
		cout<< "ingrese la opcion: ";cin>>op;

        switch (op){
		case 'a' :
		    cout<<"A\n";
		    break;
        case 'b' :
   		    cout<<"b\n";
           break;
        case 'c' :
   		    cout<<"c\n";
           break;
        case 'd' :
   		    cout<<"d\n";
           break;
        case 'e' :
   		    cout<<"e\n";
           break;
        case 'f' :
   		    cout<<"f\n";
           break;
        case 'x':
            return 0;
        break;
        }
	}
}
int menu(){
	char op ;

	while (true){
		printf("**********************************\n");
		printf("********* MENU PRINCIPAL *********\n");
		printf("**********************************\n");
		printf("a) Archivo de productos\n");
		printf("b) Entradas/Salidas de Productos\n");
		printf("c) Reportes\n");
		printf("x) Terminar\n");
		cout<< "ingrese la opcion: ";cin>>op;

        switch (op){
		case 'a' :
		    menu_archivo();
		    break;
        case 'b' :
   		    menu_ent_sal();
           break;
           case 'c':
            menu_reportesl();
        break;

        case 'x':
            return 0;
        break;
        }
	}
}
int main(){
menu();





}
