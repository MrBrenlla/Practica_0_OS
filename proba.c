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
int numPalabras;
char  teclado[101];
char  comando[101];
char argumento[101];
/*
--------------------------------------------------------------------------------
*/
int TrocearCadena(char  cadena[], char  com[] , char arg[])
{
	int espacios =0;
	int palabras =0;
	int letras =0;
	char trozos[101];
	for (int i=0; cadena[i]!='\0'  ; i++){
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
	for (int i=0 ; i<101 ; i++ ) {
		if (trozos[i]==' '){
			palabras+=1;
		}
		else{
			switch (palabras) {
				case 0:com[i]=trozos[i]; letras+=1; break;
				case 1:arg[i-(letras+1)]=trozos[i]; break;
				default: return palabras; break;
			}
		}
	}
return palabras;
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
		//Devolbe o comando, o argumento e un número que corresponde a se hai 1, 2 ou mais palabras(3)
		numPalabras=TrocearCadena(teclado , comando, argumento);

		//mostrar por pantalla comando e argumento, para probas
		for (int i=0 ; comando[i]!='\0' ; i++){
			printf("%c",  comando[i] );
		}
		printf("\n" );
		for (int i=0 ; argumento[i]!='\0' ; i++){
			printf("%c",  argumento[i] );
		}
		printf("\n" );




		limpiarBuffer(teclado);
		limpiarBuffer(comando);
		limpiarBuffer(argumento);


	}
}
/*
--------------------------------------------------------------------------------
*/
