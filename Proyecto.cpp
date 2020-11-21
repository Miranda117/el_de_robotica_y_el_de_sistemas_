//							Proyecto final
//							Elaborado por:
//Angel Nolasco Serrano A01365726|| Anatanael Jesús Miranda Faustino

//ESTRUCTURA DE ARCHIVO DE PRODUCTOS		"productos.txt"
//--------------------------------------------------------------------------------------
//clave			int 5		1-99999			clave del producto			        clave
//nombre		char 20						nombre de producto			        nom
//familia		char 20						familia: frutas,verduras,etc        fam
//medida		char 20						Unidad de medida: litros,etc        medida
//precio		int 6		1-999999		precio unitario				        precio
//existencia_i 	int 6		1-999999		existencia de registro inicial      ex_i
//existencia_a  int 6		1-999999		existencia de registro actual       ex_a
//stock mínimo 	int 6		1-999999		unidades requeridas en el almacen   min
//stock máximo  int 6		1-999999		unidades permitidas en el almacen   max


//ARCHIVO DE MOVIMIENTOS		"movimientos.txt"
//---------------------------------------------------------------------------------------
//clave			int 5		1-99999							clave del producto involucrado			clave_m
//fecha			char 10		dd/mm/aaaa						fecha de movimiento			            fecha
//cantidad		int 6		1-999999						unidades involucradas			        cantidad
//Tipo de mov	char 1		S Salida E Entrada				Tipo de movimiento			            tipo_mov
//Sub-tipo mov	char 1		C,D(entrada) || V,P,M(salida)	clasificación de mov			        sub_mov

//C=Compra
//D=Devolución del cliente
//V=Venta del producto
//P=Devolución al proovedor
//M=Merma


#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <String.h>
#include <fstream>

using namespace std;

char falso[2];
//Variables productos
int clave, precio, ex_i, ex_a, minP, maxP;
char nom[21], fam[21], medida[21];
//Variables movimientos
int clave_m,cantidad;
char fecha[11], tipo_mov, sub_mov;

struct NodoProductos{
	int clave, precio, ex_i, ex_a, minP, maxP;
	char nom[21], fam[21], medida[21];
	NodoProductos *next, *prev;
};
NodoProductos *nuevop, *actualp, *primerop, *ultimop;

struct NodoMovimientos{
	int clave_m,cantidad;
	char fecha[11], tipo_mov, sub_mov;
	NodoMovimientos *next, *prev;
};
NodoMovimientos *nuevom, *actualm, *primerom, *ultimom;

char *obtiene_fecha(){
	time_t tiempo;
	struct tm *tm;
	char fechayhora[11];

	tiempo=time(NULL);
	tm=localtime(&tiempo);
	strftime(fechayhora, 11, "%d/%m/%Y",tm);
	return(fechayhora);
}

void pausa(){
	printf("\n[[ENTER]] para continuar\n"); getche();
}

void inserta_fin(){
	if (primerop==NULL){
		primerop=nuevop;
		ultimop=nuevop;
	}
	else{
		ultimop->next=nuevop;
		nuevop->next=ultimop;
		ultimop=nuevop;
	}

}

void carga_archivos(){
	//Arch productos
	ifstream archp;
	archp.open("productos.txt",ios::in);
	while(!archp.eof()){
		archp >>clave >>nom >>fam >>medida >>precio >>ex_i >>ex_a >>minP >>maxP;
		if(!archp.eof()){
			nuevop=new NodoProductos;
			nuevop->clave=clave;
			strcpy(nuevop->nom,nom);
			strcpy(nuevop->fam,fam);
			strcpy(nuevop->medida,medida);
			nuevop->precio=precio;
			nuevop->ex_i=ex_i;
			nuevop->ex_a=ex_a;
			nuevop->minP=minP;
			nuevop->maxP=maxP;
			nuevop->next=NULL;
			if(primerop==NULL){
				primerop=nuevop;
				ultimop=nuevop;
			}else{
				ultimop->next=nuevop;
				nuevop->prev=ultimop;
				ultimop=nuevop;
			}
		}
	}
	archp.close();

	//Archivo de movimientos
	ifstream archm;
	archm.open("movimientos.txt",ios::in);
	while(!archm.eof()){
		archm >>clave_m >>fecha >>cantidad >>tipo_mov >>sub_mov;
		if(!archm.eof()){
			nuevom=new NodoMovimientos;
			nuevom->clave_m=clave_m;
			strcpy(nuevom->fecha,fecha);
			nuevom->cantidad=cantidad;
			nuevom->tipo_mov=tipo_mov;
			nuevom->sub_mov=sub_mov;
			//strcpy(nuevom->cel,cel);
			//strcpy(nuevom->cor,cor);
			//nuevom->saldo_inicial=saldo_inicial;
			//nuevom->saldo_actual=saldo_actual;
			//nuevom->next=NULL;
			if(primerom==NULL){
				primerom=nuevom;
				ultimom=nuevom;
			}else{
				ultimom->next=nuevom;//nuevop
				nuevom->prev=ultimom;
				ultimom=nuevom;

			}
		}
	}
	archm.close();
}

void descarga_productos(){
	actualp=primerop;
	ofstream archp;
	archp.open("productos.txt",ios::out);
	while(actualp!=NULL){
		for (int i=0;i<strlen(actualp->nom);i++) if (actualp->nom[i]==' ') actualp->nom[i]='_';
		for (int i=0;i<strlen(actualp->fam);i++) if (actualp->fam[i]==' ') actualp->fam[i]='_';
		for (int i=0;i<strlen(actualp->medida);i++) if (actualp->medida[i]==' ') actualp->medida[i]='_';
		archp <<actualp->clave <<" " <<actualp->nom <<" " <<actualp->fam <<" " <<actualp->medida <<" " <<actualp->precio <<" " <<actualp->ex_i <<" " <<actualp->ex_a <<" " <<actualp->minP <<" " <<actualp->maxP <<"\n";
		actualp=actualp->next;
	}
	archp.close();
}

void descarga_movimientos(){
	actualm=primerom;
	ofstream archm;
	archm.open("movimientos.txt",ios::out);
	while(actualm!=NULL){
		for(int i=0;i<strlen(actualm->fecha);i++) if(actualm->fecha[i]==' ') actualm->fecha[i]=='_';
		archm <<actualm->clave_m <<" " <<actualm->fecha <<" " <<actualm->cantidad<<" "<<actualm->tipo_mov <<" " <<actualm->sub_mov <<"\n";
		actualm=actualm->next;
	}
	archm.close();
}

bool busca_clave(){
	printf("Indica la clave del producto: "); scanf("%d",&clave); gets(falso);
	bool existe_clave=false;

	actualp=primerop;
	while(actualp!=NULL){
		if(actualp->clave==clave){
			return (true);
		}
		actualp=actualp->next;
	}
	return(false);
}

void consulta_fam(){
	bool existe_fam=false;
	printf("Indica la familia de productos a consultar: "); gets(falso); gets(fam);
	actualp=primerop;
	printf(fam);
	while(actualp!=NULL){
		if(strcmp(actualp->fam,fam)==0){
			existe_fam=true;
			break;
		}
		actualp=actualp->next;
	}
	if(!existe_fam){
		printf("Error, familia de productos inexistente en la base de datos");
		pausa();
	}else{
		while(actualp!=NULL){
			if(strcmp(actualp->fam,fam)==0){
				for(int i=0;i<strlen(actualp->nom);i++) if(actualp->nom[i]=='_') actualp->nom[i]==' ';
				for(int i=0;i<strlen(actualp->fam);i++) if(actualp->fam[i]=='_') actualp->fam[i]==' ';
				for(int i=0;i<strlen(actualp->medida);i++) if(actualp->medida[i]=='_') actualp->medida[i]==' ';

				printf("\n");
				printf("\nClave: %d",actualp->clave);
				printf("\nNombre: %s",actualp->nom);
				printf("\nUnidad de medida: %s",actualp->medida);
				printf("\nPrecio: %d",actualp->precio);
				printf("\nExistencia inicial: %d",actualp->ex_i);
				printf("\nExistencia actual: %d",actualp->ex_a);
				printf("\nUnidades requeridas: %d",actualp->minP);
				printf("\nUnidades permitidas: %d",actualp->maxP);
				printf("\n-----------------------------------------\n");

				actualp=actualp->next;
			}
		}
	}
}

void alta_productos(){
	int l;
	if (busca_clave()){
		printf("Error, clave se duplica en la base de datos...\n");
		pausa();
	}else{
		do{
			printf("\nIndica el nombre del produco: "); gets(nom);
			l=strlen(nom);
			if((l<1) || (l>20)){
				printf("Error, cadena entre 1 y 20 caracteres...\n");
				pausa();
			}
		}while((l<1) || (l>20));
		do{
			printf("\nIndica la familia del producto: "); gets(fam);
			l=strlen(fam);
			if((l<1) || (l>20)){
				printf("Error, cadena entre 1 y 20 caracteres...\n");
				pausa();
			}
		}while((l<1) || (l>20));
		do{
			printf("\nIndica la unidad de medida del producto: "); gets(medida);
			l=strlen(medida);
			if((l<1) || (l>20)){
				printf("Error, cadena entre 1 y 15 caracteres...\n");
				pausa();
			}
		}while((l<1) || (l>15));
		do{
			printf("\nIndica el precio unitario del producto: "); scanf("%d",&precio); gets(falso);
			if((precio<1) || (precio>999999)){
				printf("Error, el precio sobrepasa el limite...\n");
				pausa();
			}
		}while((precio<1) || (precio>999999));
		do{
			printf("\nIndica la existencia inicial del producto: "); scanf("%d",&ex_i); gets(falso);
			if((ex_i<1) || (ex_i>999999)){
				printf("Error, la existencia sobrepasa el limite...\n");
				pausa();
			}
		}while((ex_i<1) || (ex_i>999999));
		do{
			printf("\nIndica el stock minimo del producto: "); scanf("%d",&minP); gets(falso);
			if((minP<1) || (minP>999999)){
				printf("Error, la existencia sobrepasa el limite...\n");
				pausa();
			}
		}while((minP<1) || (minP>999999));
		do{
			printf("\nIndica el stock maximo del producto: "); scanf("%d",&maxP); gets(falso);
			if((maxP<1) || (maxP>999999)){
				printf("Error, el stock sobrepasa el limite...\n");
				pausa();
			}
		}while((maxP<1) || (maxP>999999));

		for(int i=0;i<strlen(nom);i++) if(nom[i]==' ') nom[i]=='_';
		for(int i=0;i<strlen(fam);i++) if(fam[i]==' ') fam[i]=='_';
		for(int i=0;i<strlen(medida);i++) if(medida[i]==' ') medida[i]=='_';

		nuevop=new NodoProductos;
		nuevop->clave=clave;
		strcpy(nuevop->nom,nom);
		strcpy(nuevop->fam,fam);
		strcpy(nuevop->medida,medida);
		nuevop->precio=precio;
		nuevop->ex_i=ex_i;
		nuevop->ex_a=ex_i;
		nuevop->minP=minP;
		nuevop->maxP=maxP;
		nuevop->next=NULL;
		if(primerop==NULL){
			primerop=nuevop;
			ultimop=nuevop;
		}else{
			ultimop->next=nuevop;
			ultimop=nuevop;
		}
	carga_archivos();
	}
}

void consulta_clave(){
	if(!busca_clave()){
		printf("Error, clave inexistente en la base de datos...\n");
		pausa();
	}
	else{
		for(int i=0;i<strlen(actualp->nom);i++) if(actualp->nom[i]=='_') actualp->nom[i]==' ';
		for(int i=0;i<strlen(actualp->fam);i++) if(actualp->fam[i]=='_') actualp->fam[i]==' ';
		for(int i=0;i<strlen(actualp->medida);i++) if(actualp->medida[i]=='_') actualp->medida[i]==' ';

		printf("\nNombre: %s",actualp->nom);
		printf("\nFamilia del producto: %s",actualp->fam);
		printf("\nUnidad de medida: %s",actualp->medida);
		printf("\nPrecio: %d",actualp->precio);
		printf("\nExistencia inicial: %d",actualp->ex_i);
		printf("\nExistencia actual: %d",actualp->ex_a);
		printf("\nUnidades requeridas: %d",actualp->minP);
		printf("\nUnidades permitidas: %d",actualp->maxP);
	}
}

void entradas_por_compras(){
if (!busca_clave()){
		printf("Error, clave no existe en la base de datos...\n");
		pausa();
}
else {
    strcpy(fecha,obtiene_fecha());
    tipo_mov='E';
    sub_mov='C';
    printf("Seleccione la cantidad que va a comprar: ");scanf("%d", &cantidad);gets(falso);
    actualp->ex_a=actualp->ex_a+cantidad;
    nuevom =new NodoMovimientos;
    nuevom -> cantidad = cantidad;
    nuevom->clave_m=clave;
    nuevom->tipo_mov=tipo_mov;
    nuevom->sub_mov=sub_mov;
    strcpy(nuevom->fecha,fecha);
    nuevom->next=NULL ;
    nuevom->prev=NULL;
    if (primerom==NULL){
        primerom=nuevom;
        ultimom=nuevom;
        }
    else{
        ultimom->next=nuevom;
        nuevom->prev=ultimom;
        ultimom=nuevom;
    }
    descarga_movimientos();
    descarga_productos();

}
}


void entradas_por_devolci(){
if (!busca_clave()){
		printf("Error, clave no existe en la base de datos...\n");
		pausa();
}
else {
    strcpy(fecha,obtiene_fecha());
    tipo_mov='E';
    sub_mov='D';
    printf("Seleccione la cantidad que fue devulta comprador: ");scanf("%d", &cantidad);gets(falso);
    actualp->ex_a=actualp->ex_a+cantidad;
    nuevom =new NodoMovimientos;
    nuevom->clave_m=clave;
    nuevom -> cantidad = cantidad;
    nuevom->tipo_mov=tipo_mov;
    nuevom->sub_mov=sub_mov;
    strcpy(nuevom->fecha,fecha);
    nuevom->next=NULL ;
    nuevom->prev=NULL;
    if (primerom==NULL){
        primerom=nuevom;
        ultimom=nuevom;
        }
    else{
        ultimom->next=nuevom;
        nuevom->prev=ultimom;
        ultimom=nuevom;
    }
    descarga_movimientos();
    descarga_productos();

}
}

void salidas_por_ventas(){
if (!busca_clave()){
		printf("Error, clave no existe en la base de datos...\n");
		pausa();
}
else {
    strcpy(fecha,obtiene_fecha());
    tipo_mov='S';
    sub_mov='V';
    printf("Seleccione la cantidad que fue comprada por el cliente: ");scanf("%d", &cantidad);gets(falso);
    actualp->ex_a=actualp->ex_a-cantidad;
    nuevom = new NodoMovimientos;
    nuevom->clave_m=clave;
    nuevom -> cantidad = cantidad;
    nuevom->tipo_mov=tipo_mov;
    nuevom->sub_mov=sub_mov;
    strcpy(nuevom->fecha,fecha);
    nuevom->next=NULL ;
    nuevom->prev=NULL;
    if (primerom==NULL){
        primerom=nuevom;
        ultimom=nuevom;
        }
    else{
        ultimom->next=nuevom;
        nuevom->prev=ultimom;
        ultimom=nuevom;
    }
    descarga_movimientos();
    descarga_productos();

}
}

void salida_por_devo_prove(){
if (!busca_clave()){
		printf("Error, clave no existe en la base de datos...\n");
		pausa();
}
else {
    strcpy(fecha,obtiene_fecha());
    tipo_mov='S';
    sub_mov='P';
    printf("Seleccione la cantidad que fue devuenta al proveedor: ");scanf("%d", &cantidad);gets(falso);
    actualp->ex_a=actualp->ex_a-cantidad;
    nuevom = new NodoMovimientos;
    nuevom->clave_m=clave;
    nuevom->tipo_mov=tipo_mov;
    nuevom -> cantidad = cantidad;
    nuevom->sub_mov=sub_mov;
    strcpy(nuevom->fecha,fecha);
    nuevom->next=NULL ;
    nuevom->prev=NULL;
    if (primerom==NULL){
        primerom=nuevom;
        ultimom=nuevom;
        }
    else{
        ultimom->next=nuevom;
        nuevom->prev=ultimom;
        ultimom=nuevom;
    }
    descarga_movimientos();
    descarga_productos();

}
}

void salidas_por_devo_merma(){
if (!busca_clave()){
		printf("Error, clave no existe en la base de datos...\n");
		pausa();
}
else {
    strcpy(fecha,obtiene_fecha());
    tipo_mov='S';
    sub_mov='M';
    printf("Seleccione la cantidad de merma: ");scanf("%d", &cantidad);gets(falso);
    actualp->ex_a=actualp->ex_a-cantidad;
    nuevom = new NodoMovimientos;
    nuevom->clave_m=clave;
    nuevom->tipo_mov=tipo_mov;
    nuevom -> cantidad = cantidad;
    nuevom->sub_mov=sub_mov;
    strcpy(nuevom->fecha,fecha);
    nuevom->next=NULL ;
    nuevom->prev=NULL;
    if (primerom==NULL){
        primerom=nuevom;
        ultimom=nuevom;
        }
    else{
        ultimom->next=nuevom;
        nuevom->prev=ultimom;
        ultimom=nuevom;
    }
    descarga_movimientos();
    descarga_productos();

}
}

int menu_archivo(){
	char op ;

	while (true){
		printf("\n**********************************\n");
		printf("********* MENU ARCHIVOS *********\n");
		printf("**********************************\n");
		printf("a) Alta nuevos productos \n");
		printf("b) Baja productos obsoletos \n");
		printf("c) Consulta productos por clave\n");
		printf("d) Consulta productos por familia \n");
		printf("x) Terminar\n");
		cout<< "ingrese la opcion: ";cin>>op;

        switch (op){
		case 'a' :
		    alta_productos();
		    break;
        case 'b' :
   		    cout<<"b\n";
           break;
        case 'c' :
   		    consulta_clave();
           break;
        case 'd' :
   		    consulta_fam();
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
		printf("*** MENU ENTRADAS/SALIDAS DE PRODUCTOS***\n");
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
		    entradas_por_compras();
		    break;
        case 'b' :
   		    entradas_por_devolci();
           break;
        case 'c' :
   		    salidas_por_ventas();
           break;
        case 'd' :
   		    salida_por_devo_prove();
           break;
       case 'e' :
   		    salidas_por_devo_merma();
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
		printf("************** MENU DE REPORTES ********\n");
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
    ofstream archp;
	archp.open("productos.txt",ios::app);
	archp.close();
	ofstream archm;
	archm.open("movimientos.txt",ios::app);
	archm.close();
	carga_archivos();

	menu();
}
