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
void limpiarBuffer(char buf[]){
	for (int i  = 0 ; (buf[i]!='\0') || (i<7); i++ ){
		buf[i]='\0';
	}
}
/*
--------------------------------------------------------------------------------
*/
int TrocearCadena(char  cadena[], char  com[] , char arg[])
{
	int espacios =0;
	int palabras =0;
	int letras =0;
	char trozos[101];

	limpiarBuffer(trozos);

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
	for (int i=0 ; trozos[i]!='\0' ; i++ ) {
		if ((trozos[i]==' ')){
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
void fin(int * x ){
	*x=1;
}
/*
--------------------------------------------------------------------------------
*/
void escollerFuncion(char com[],char arg[],int palabras,int * acabado){
	if (strncmp(com,"autores\0",8)==0){
		printf("autores(com,arg,palabras)\n" );
	}
	else{
		if (strncmp(com,"pid\0",4)==0){
			printf("pid(com,arg,palabras)\n" );
		}
		else{
			if (strncmp(com,"cdir\0",5)==0){
				printf("cdir(com,arg,palabras)\n" );
			}
			else{
				if (strncmp(com,"fecha\0",6)==0){
					printf("fecha(com)\n" );
				}
				else{
					if (strncmp(com,"hora\0",5)==0){
						printf("hora(com)\n" );
					}
					else{
						if (strncmp(com,"hist\0",5)==0){
							printf("hist(com,arg,palabras)\n" );
						}
						else{
							if ((strncmp(com,"fin\0",4)==0) || (strncmp(com,"end\0",4)==0) || (strncmp(com,"exit\0",5)==0)){
								fin(acabado);
							}
							else{
								printf("comando non valido\n" );
							}
						}
					}
				}
			}
		}
	}
}
/*
--------------------------------------------------------------------------------
*/
int main() {
	while (acabado != 1){
		printf("->");
		gets(teclado);
		//Devolbe o comando, o argumento e un número que corresponde a se hai 1, 2 ou mais palabras(3)
		numPalabras=TrocearCadena(teclado , comando, argumento);

		/*mostrar por pantalla comando e argumento, para probas
		puts(teclado );
		puts(comando );
		puts(argumento );
		*/

		escollerFuncion(comando,argumento,numPalabras,&acabado);


		limpiarBuffer(teclado);
		limpiarBuffer(comando);
		limpiarBuffer(argumento);


	}
}
/*
--------------------------------------------------------------------------------
*/
