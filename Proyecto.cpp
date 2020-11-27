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
//stock mínimo 	int 6		1-999999		unidades requeridas en el almacen   minP
//stock máximo  int 6		1-999999		unidades permitidas en el almacen   maxP


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

//USO GENERAL
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
		//for(int i=0;i<strlen(actualm->fecha);i++) if(actualm->fecha[i]==' ') actualm->fecha[i]=='_';
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



//MENU 1
void elimina_fin(){
	if (primerop==NULL){
		printf("Error, la base de datos est%c vac%ca ...\n",160,161);
		pausa();
	}
	else{
		if (primerop==ultimop){
			primerop=NULL;
			ultimop=NULL;
		}
		else{
			actualp=ultimop;
			ultimop=actualp->prev;
			ultimop->next=NULL;
			delete(actualp);
		}
	}
}

void elimina_inicio(){
	if (primerop==NULL){
		printf("\nNo hay productos a eliminar...\n");
		pausa();
	}
	else{
		if (primerop==ultimop){
			primerop=NULL;
			ultimop=NULL;
		}
		else{
			actualp=primerop;
			primerop=primerop->next;
			primerop->prev=NULL;
			delete(actualp);
		}
	}
}

void registro_fin(){
	if (primerom==NULL){
		printf("Error, la base de datos est%c vac%ca ...\n",160,161);
		pausa();
	}
	else{
		if (primerom==ultimom){
			primerom=NULL;
			ultimom=NULL;
		}
		else{
			actualm=ultimom;
			ultimom=actualm->prev;
			ultimom->next=NULL;
			delete(actualm);
		}
	}
}

void registro_inicio(){
	if (primerom==NULL){
		printf("\nNo hay movimientos a eliminar...\n");
		pausa();
	}
	else{
		if (primerom==ultimom){
			primerom=NULL;
			ultimom=NULL;
		}
		else{
			actualm=primerom;
			primerom=primerom->next;
			primerom->prev=NULL;
			delete(actualm);
		}
	}
}

void elimina_producto(){
	NodoProductos *anterior, *siguiente;
	NodoMovimientos *ant, *sig;
	if (primerop==NULL){
		printf("Error, la base de datos est%c vac%ca ...\n",160,161);
		pausa();
	}
	else{
		if (!busca_clave()){
			printf("Error, clave inexistente en la base de datos ...\n");
			pausa();
		}
		else{
			if (actualp==primerop) elimina_inicio();
			else{
				if (actualp==ultimop) elimina_fin();
				else{
					anterior=actualp->prev;
					siguiente=actualp->next;
					anterior->next=siguiente;
					siguiente->prev=anterior;
					delete(actualp);
				}
			}
			descarga_productos();
			
			actualm=primerom;
			while(actualm!=NULL){
				if(actualm->clave_m==clave){
					if(actualm==primerom) registro_inicio();
					else{
						if(actualm==ultimom) registro_fin();
						else{
							ant=actualm->prev;
							sig=actualm->next;
							ant->next=sig;
							sig->prev=ant;
							delete(actualm);
						}
					}
				}
				actualm=actualm->next;
			}
			descarga_movimientos();
		}
	}
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
		printf("\nClave	 Nombre   U. de medida	Precio	Ex. inicial	Ex. actual	Stock MIN	Stock MAX");

		while(actualp!=NULL){
			if(strcmp(actualp->fam,fam)==0){
				for(int i=0;i<strlen(actualp->nom);i++) if(actualp->nom[i]=='_') actualp->nom[i]==' ';
				for(int i=0;i<strlen(actualp->fam);i++) if(actualp->fam[i]=='_') actualp->fam[i]==' ';
				for(int i=0;i<strlen(actualp->medida);i++) if(actualp->medida[i]=='_') actualp->medida[i]==' ';

				//printf("\n");
				//printf("\nClave: %d",actualp->clave);
				//printf("\nNombre: %s",actualp->nom);
				//printf("\nUnidad de medida: %s",actualp->medida);
				//printf("\nPrecio: %d",actualp->precio);
				//printf("\nExistencia inicial: %d",actualp->ex_i);
				//printf("\nExistencia actual: %d",actualp->ex_a);
				//printf("\nUnidades requeridas: %d",actualp->minP);
				//printf("\nUnidades permitidas: %d",actualp->maxP);
				//printf("\n-----------------------------------------\n");
				printf("\n%d %10s %14s %7d %12d %14d %18d %15d\n", actualp->clave, actualp->nom, actualp->medida, actualp->precio, actualp->ex_i, actualp->ex_a, actualp->minP, actualp->maxP);
			}
			actualp=actualp->next;
		}
	}
}

void alta_productos(){
	int l;
	bool c = busca_clave();
	if ((c==true)||(clave<1)||(clave>99999)){
		printf("Error, la clave no se puede registrar, revise que sea formato numerico y que no se duplique\n");
		pausa();
	}else{
		do{
			printf("\nIndica el nombre del producto: "); gets(nom);
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
			printf("\nIndica la existencia inicial del producto: "); scanf("%d", &ex_i); gets(falso);
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
	//carga_archivos();
	descarga_productos();
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

		printf("\nNombre:			%s",actualp->nom);
		printf("\nFamilia del producto:	%s",actualp->fam);
		printf("\nUnidad de medida:	%s",actualp->medida);
		printf("\nPrecio:			%d",actualp->precio);
		printf("\nExistencia inicial:	%d",actualp->ex_i);
		printf("\nExistencia actual:	%d",actualp->ex_a);
		printf("\nStock MIN:		%d",actualp->minP);
		printf("\nStock MAX:		%d",actualp->maxP);
	}
}

//MENU 2
void entradas_por_compras(){
if (!busca_clave()){
		printf("Error, clave no existe en la base de datos...\n");
		pausa();
}
else {
    strcpy(fecha,obtiene_fecha());
    tipo_mov='E';
    sub_mov='C';
    printf("Indique la cantidad que va a comprar: ");scanf("%d", &cantidad);gets(falso);
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
    printf("Seleccione la cantidad que fue devuelta al comprador: ");scanf("%d", &cantidad);gets(falso);
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
    printf("Indique la cantidad que fue comprada por el cliente: ");scanf("%d", &cantidad);gets(falso);
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
    printf("Seleccione la cantidad que fue devuelta al proveedor: ");scanf("%d", &cantidad);gets(falso);
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

//MENU 3
void ordenar_lista(char op){
	NodoProductos *actual_i, *actual_j, *auxiliar;
	actual_i=primerop;
	auxiliar=new NodoProductos;
	while (actual_i!=NULL){
		actual_j=actual_i->next;
		while (actual_j!=NULL){
			if(op=='a'){
				if (actual_i->clave>actual_j->clave){
				auxiliar->clave=actual_i->clave;
				strcpy(auxiliar->nom,actual_i->nom);
				strcpy(auxiliar->fam,actual_i->fam);
				strcpy(auxiliar->medida,actual_i->medida);
				auxiliar->precio=actual_i->precio;
				auxiliar->ex_a=actual_i->ex_a;
				auxiliar->minP=actual_i->minP;
				auxiliar->maxP=actual_i->maxP;
				//------------------------------
				actual_i->clave=actual_j->clave;
				strcpy(actual_i->nom,actual_j->nom);
				strcpy(actual_i->fam,actual_j->fam);
				strcpy(actual_i->medida,actual_j->medida);
				actual_i->precio=actual_j->precio;
				actual_i->ex_a=actual_j->ex_a;
				actual_i->minP=actual_j->minP;
				actual_i->maxP=actual_j->maxP;
				//------------------------------
				actual_j->clave=auxiliar->clave;
				strcpy(actual_j->nom,auxiliar->nom);
				strcpy(actual_j->fam,auxiliar->fam);
				strcpy(actual_j->medida,auxiliar->medida);
				actual_j->precio=auxiliar->precio;
				actual_j->ex_a=auxiliar->ex_a;
				actual_j->minP=auxiliar->minP;
				actual_j->maxP=auxiliar->maxP;
				}
			}
			if(op=='b'){
				if (strcmp(actual_i->nom,actual_j->nom)==1){
				
				strcpy(auxiliar->nom,actual_i->nom);
				auxiliar->clave=actual_i->clave;
				strcpy(auxiliar->fam,actual_i->fam);
				strcpy(auxiliar->medida,actual_i->medida);
				auxiliar->precio=actual_i->precio;
				auxiliar->ex_a=actual_i->ex_a;
				auxiliar->minP=actual_i->minP;
				auxiliar->maxP=actual_i->maxP;
				//------------------------------
				strcpy(actual_i->nom,actual_j->nom);
				actual_i->clave=actual_j->clave;
				strcpy(actual_i->fam,actual_j->fam);
				strcpy(actual_i->medida,actual_j->medida);
				actual_i->precio=actual_j->precio;
				actual_i->ex_a=actual_j->ex_a;
				actual_i->minP=actual_j->minP;
				actual_i->maxP=actual_j->maxP;
				//------------------------------
				strcpy(actual_j->nom,auxiliar->nom);
				actual_j->clave=auxiliar->clave;
				strcpy(actual_j->fam,auxiliar->fam);
				strcpy(actual_j->medida,auxiliar->medida);
				actual_j->precio=auxiliar->precio;
				actual_j->ex_a=auxiliar->ex_a;
				actual_j->minP=auxiliar->minP;
				actual_j->maxP=auxiliar->maxP;
				}
			}
			if(op=='d'){
				if (actual_i->ex_a>actual_j->ex_a){
				
				auxiliar->ex_a=actual_i->ex_a;
				auxiliar->clave=actual_i->clave;
				strcpy(auxiliar->nom,actual_i->nom);
				strcpy(auxiliar->fam,actual_i->fam);
				strcpy(auxiliar->medida,actual_i->medida);
				auxiliar->precio=actual_i->precio;
				auxiliar->ex_i=actual_i->ex_i;
				auxiliar->minP=actual_i->minP;
				auxiliar->maxP=actual_i->maxP;
				//------------------------------
				actual_i->ex_a=actual_j->ex_a;
				actual_i->clave=actual_j->clave;
				strcpy(actual_i->nom,actual_j->nom);
				strcpy(actual_i->fam,actual_j->fam);
				strcpy(actual_i->medida,actual_j->medida);
				actual_i->precio=actual_j->precio;
				actual_i->ex_i=actual_j->ex_i;
				actual_i->minP=actual_j->minP;
				actual_i->maxP=actual_j->maxP;
				//------------------------------
				actual_j->ex_a=auxiliar->ex_a;
				actual_j->clave=auxiliar->clave;
				strcpy(actual_j->nom,auxiliar->nom);
				strcpy(actual_j->fam,auxiliar->fam);
				strcpy(actual_j->medida,auxiliar->medida);
				actual_j->precio=auxiliar->precio;
				actual_j->ex_i=auxiliar->ex_i;
				actual_j->minP=auxiliar->minP;
				actual_j->maxP=auxiliar->maxP;
				}
			}
			if(op=='e'){
				if (actual_i->ex_a>actual_j->ex_a){
					
				auxiliar->ex_a=actual_i->ex_a;
				auxiliar->clave=actual_i->clave;
				strcpy(auxiliar->nom,actual_i->nom);
				strcpy(auxiliar->fam,actual_i->fam);
				strcpy(auxiliar->medida,actual_i->medida);
				auxiliar->precio=actual_i->precio;
				auxiliar->ex_i=actual_i->ex_i;
				auxiliar->minP=actual_i->minP;
				auxiliar->maxP=actual_i->maxP;
				//------------------------------
				actual_i->ex_a=actual_j->ex_a;
				actual_i->clave=actual_j->clave;
				strcpy(actual_i->nom,actual_j->nom);
				strcpy(actual_i->fam,actual_j->fam);
				strcpy(actual_i->medida,actual_j->medida);
				actual_i->precio=actual_j->precio;
				actual_i->ex_i=actual_j->ex_i;
				actual_i->minP=actual_j->minP;
				actual_i->maxP=actual_j->maxP;
				//------------------------------
				actual_j->ex_a=auxiliar->ex_a;
				actual_j->clave=auxiliar->clave;
				strcpy(actual_j->nom,auxiliar->nom);
				strcpy(actual_j->fam,auxiliar->fam);
				strcpy(actual_j->medida,auxiliar->medida);
				actual_j->precio=auxiliar->precio;
				actual_j->ex_i=auxiliar->ex_i;
				actual_j->minP=auxiliar->minP;
				actual_j->maxP=auxiliar->maxP;
				}
			}
			actual_j=actual_j->next;
		}
		actual_i=actual_i->next;
	}
}

void lista_reportes(char op){
	if (primerop==NULL) printf("Error, la lista est%c vac%ca ...\n",160,161);
	else{
		if(op=='a'){
			ordenar_lista(op);
			actualp=primerop;
			printf("clave       nombre         familia   U. de medida    Precio	Existencia a. Stock MIN Stock MAX\n");
			while (actualp!=NULL){
				printf("%d	%10s %15s %9s %12d %18d %10d %9d\n", actualp->clave, actualp->nom, actualp->fam, actualp->medida, actualp->precio, actualp->ex_a, actualp->minP, actualp->maxP);
				actualp=actualp->next;
			}
		}
		
		if(op=='b'){
			ordenar_lista(op);
			actualp=primerop;
			printf("    nombre clave	 familia   U. de medida    Precio  Existencia a.   Stock MIN   Stock MAX\n");
			while (actualp!=NULL){
				printf("%10s %5d %15s %9s %12d	%16d %11d %11d\n", actualp->nom, actualp->clave, actualp->fam, actualp->medida, actualp->precio, actualp->ex_a, actualp->minP, actualp->maxP);
				actualp=actualp->next;
			}
		}
		
		if(op=='d'){
			ordenar_lista(op);
			actualp=primerop;
			printf("Existencia a.  clave     nombre      familia     U. de medida   Precio   Existencia i.   Stock MIN  Stock MAX\n");
			while (actualp!=NULL){
				if(actualp->ex_a<=actualp->minP){
					printf("%13d %6d %10s %12s %11s %13d %15d %11d %10d\n", actualp->ex_a, actualp->clave, actualp->nom, actualp->fam, actualp->medida, actualp->precio, actualp->ex_i, actualp->minP, actualp->maxP);
				}
				actualp=actualp->next;
			}
		}
		
		if(op=='e'){
			ordenar_lista(op);
			actualp=primerop;
			printf("Existencia a.  clave     nombre      familia     U. de medida   Precio   Existencia i.   Stock MIN  Stock MAX\n");
			while (actualp!=NULL){
				if(actualp->ex_a>=actualp->maxP){
					printf("%13d %6d %10s %12s %11s %13d %15d %11d %10d\n", actualp->ex_a, actualp->clave, actualp->nom, actualp->fam, actualp->medida, actualp->precio, actualp->ex_i, actualp->minP, actualp->maxP);
				}
				actualp=actualp->next;
			}
		}
		
		if(op=='f'){
			if(!busca_clave()){
				printf("Error, clave inexistente en la base de datos...\n");
				
			}
			else{
				for(int i=0;i<strlen(actualp->nom);i++) if(actualp->nom[i]=='_') actualp->nom[i]==' ';
				for(int i=0;i<strlen(actualp->fam);i++) if(actualp->fam[i]=='_') actualp->fam[i]==' ';
				for(int i=0;i<strlen(actualp->medida);i++) if(actualp->medida[i]=='_') actualp->medida[i]==' ';
	
				printf("\nClave: %d", actualp->clave);
				printf("\nNombre: %s",actualp->nom);
				printf("\nFamilia del producto: %s",actualp->fam);
				printf("\n-----------------------------------------------------------");
				actualm=primerom;
				printf("\nFecha		Cantidad	Entrada/Salida	Sub Tipo\n");
				while(actualm!=NULL){
					if(actualm->clave_m==clave){
						printf("\n%s	%d		%c		%c", actualm->fecha, actualm->cantidad, actualm->tipo_mov, actualm->sub_mov);
					}
					actualm=actualm->next;
				}
			}	
		}
	}
	pausa();
}


//MENUS
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
   		    elimina_producto();
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
		    lista_reportes(op);
		    break;
        case 'b' :
   		    lista_reportes(op);
           break;
        case 'c' :
   		    consulta_fam();
           break;
        case 'd' :
   		    lista_reportes(op);
           break;
        case 'e' :
   		    lista_reportes(op);
           break;
        case 'f' :
        	lista_reportes(op);
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
