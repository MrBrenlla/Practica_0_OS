/*
Struct nodo
{
Int dato;
Struct nodo *enlace;
};
Struct nodo *cabecera;
cabecera=NULL;

-----------------------------------

typedef struct Elemento
{
int dato;
struct Elemento *enlace;
Cabecera=NULL;
} Nodo;
Nodo*cabecera;
*/

#include <stdio.h>
#include <string.h>

int acabado = 0;
char  teclado[101];
char  comando[101];
/*
--------------------------------------------------------------------------------
*/
void TrocearCadena(char  cadena[], char  trozos[])
{
	int espacios =0;
	for (int i=0; i<100  ; i++){
		if (cadena[i]==' '){
			espacios+=1;
		}
		else{
			trozos[i-espacios]=cadena[i];
			if( cadena[i+1]==' '){
				trozos[(i-espacios)+1]=' ';
				espacios-=1;
			}
		}
	}
}

/*
--------------------------------------------------------------------------------
*/
void limpiarBuffer(char buf[]){
	for (int i  = 0 ; buf[i]!='\0'; i++ ){
		buf[i]='\0';
	}
}

/*
--------------------------------------------------------------------------------
*/
void main() {
	while (acabado != 1){
		printf("->");
		gets(teclado);
		TrocearCadena(teclado , comando);
		for (int i=0 ; i<101 ; i++){
		printf("%c",  comando[i] );
	}
		limpiarBuffer(teclado);
		limpiarBuffer(comando);


	}
}
/*
--------------------------------------------------------------------------------
*/
