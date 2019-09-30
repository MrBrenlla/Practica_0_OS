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
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
	puts(trozos);
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
void autores( char com[],char arg[], int palabras){
		if (palabras == 0){
				printf("Brais: b.brenlla\nÁngel: angel.alvarez.rey\n");
		}
		if (palabras == 1){
				if (strncmp(arg,"-l\0",2)==0){
						printf("b.brenlla\nangel.alvarez.rey\n");
				} else if (strncmp(arg,"-n\0",2)==0){
						 printf("Brais\nÁngel\n");
					}
					else{
						printf("Error\n");
					}
		}
}
/*
--------------------------------------------------------------------------------
*/

void fecha( char *com[], int palabras){
	time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
        printf("%s\n",output);

        return 0;
}

/*
--------------------------------------------------------------------------------
*/
void hora( char *com[], int palabras){
	time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%H:%M:%S",tlocal);
        printf("%s\n",output);

        return 0;
}

/*
--------------------------------------------------------------------------------
*/

void cdir(char com[], char arg[], int palabras){
	char *directorioActual[100];

  if (palabras == 0) {
    printf("%s\n", getcwd(directorioActual, 100));
  } else if (chdir(arg[0]) != 0) {
    printf("Non se puido cambiar o directorio\n");
	}
}
/*
--------------------------------------------------------------------------------
*/
void pid(char *arg[], int palabras) {
  pid_t pid = getpid();
  pid_t pidp = getppid();

  if (pid != 0) {
    if (palabras == 0) {
      printf("Pid del shell: %lu\n",pid);
    } else if (!strcmp("-p",arg)){
      printf("Pid del padre del shell: %lu\n",pidp);
    } else {
      printf("\n");
    }
  }
}
/*
--------------------------------------------------------------------------------
*/
void escollerFuncion(char com[], char arg[],int palabras,int * acabado){
	if (strncmp(com,"autores\0",8)==0){
		autores(com, arg, palabras);
	}
	else{
		if (strncmp(com,"pid\0",4)==0){
			pid( arg, palabras);
		}
		else{
			if (strncmp(com,"cdir\0",5)==0){
				(com, arg, palabras);
			}
			else{
				if (strncmp(com,"fecha\0",6)==0){
					fecha(&com, palabras);
				}
				else{
					if (strncmp(com,"hora\0",5)==0){
						hora(com, palabras);
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
		//Devolve o comando, o argumento e un número que corresponde a se hai 1, 2 ou mais palabras(3)
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
