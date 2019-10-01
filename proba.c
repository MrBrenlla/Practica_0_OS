#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define MAX  200

int acabado = 0;
int numPalabras;
char  teclado[101];
char  comando[101];
char argumento[101];

 typedef  struct nodo {
 	char dato[101];
	struct nodo * sig;
 } tNodo;

typedef struct list{
	tNodo * inicio;
	tNodo * final;
} tList;



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
int TrocearCadena(char  cadena[], char com[] , char arg[])
{
	int espacios =0;
	int palabras =0;
	int letras =0;
	char trozos[101];

	limpiarBuffer(trozos);

	for (int i=0; (cadena[i]!='\0')  ; i++){
		if (cadena[i]==' '){
			espacios+=1;
		}
		else{
			trozos[i-espacios]=cadena[i];
			if( (cadena[i+1]==' ') || (cadena[i+1]=='\0') || (cadena[i+1]=='\n' )){
				trozos[(i-espacios)+1]=' ';
				espacios-=1;
			}
		}
	}
	for (int i=0 ; (cadena[i]!='\0') ; i++ ) {
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

// int TrocearCadena(char * cadena, char * trozos[]) {
// 	 int i=1;
// 	 if ((trozos[0]=strtok(cadena," \n\t"))==NULL) {
// 	   return 0;
// 	 }
// 	 while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) {
// 	   i++;
// 	 }
// 	return i;
// }
/*
--------------------------------------------------------------------------------
*/
void fin(int * x ){
	*x=1;
}

/*
--------------------------------------------------------------------------------
*/
void autores( char arg[], int palabras){
		if (palabras == 1){
				printf("Brais: b.brenlla\nÁngel: angel.alvarez.rey\n");
		}
		if (palabras == 2){
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

void fecha(){
	time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
        printf("%s\n",output);
}

/*
--------------------------------------------------------------------------------
*/
void hora(){
	time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%H:%M:%S",tlocal);
        printf("%s\n",output);

}

/*
--------------------------------------------------------------------------------
*/

void cdir(char arg[], int palabras){
	char dir[101];
	limpiarBuffer(dir);
	if (palabras==1){
		getcwd(dir,101);
		puts(dir);
	}
	else{
		if (chdir(arg)!=0){
				printf("error\n" );
		}
	}
}
/*
--------------------------------------------------------------------------------
*/
void pid(char arg[], int palabras) {
  pid_t pid = getpid();
  pid_t pidp = getppid();

  if (pid != 0) {
    if (palabras == 1) {
      printf("Pid del shell: %u\n",pid);
    } else if (!strcmp("-p",arg)){
      printf("Pid del padre del shell: %u\n",pidp);
    } else {
      printf("\n");
    }
  }
}
/*
--------------------------------------------------------------------------------
*/
// void gardar(char teclado[101],tNodo * h){
// 		tNodo * aux = h;
// 		tNodo * new;
// 		while (aux->sig!=NULL){
// 			aux=aux->sig;
// 		}
// 		new = (tNodo *)malloc(sizeof(tNodo));
// 		aux->sig = new;
// 		strcpy(new->dato,teclado);
// 		puts(new->dato);
// 		new->sig=NULL;
// 		printf("6\n" );
// }
//
//
//
// void hist(tNodo * aux) {
// 	printf("chega\n");
// 	while (aux != NULL) {
// 	 		puts(aux->dato);
// 			aux = aux->sig;
// 		}
// 	printf("hist\n");
// }

void gardar(char teclado[101],tList * h){
	if (h->inicio==NULL){
		h->inicio=malloc(sizeof(tNodo));
		h->final=h->inicio;
		strcpy(h->inicio->dato,teclado);
		h->inicio->sig=NULL;

	}
	else{
		h->final->sig=malloc(sizeof(tNodo));
		h->final=h->final->sig;
		strcpy(h->final->dato,teclado);
		h->final->sig=NULL;
	}
}

void hist(tList h){
	tNodo * aux;
	aux=h.inicio;
	while(aux!=NULL){
		printf("%s",aux->dato );
		aux=aux->sig;
	}
}
/*
--------------------------------------------------------------------------------
*/
void escollerFuncion(char com[],char arg[],int palabras,int * acabado,tList h){
	if (palabras==3){
		printf("comando o argumentos no validos\n" );
	}
	else{
		if (strncmp(com,"autores\0",8)==0){
			autores(arg,palabras);
		}
		else{
			if (strncmp(com,"pid\0",4)==0){
				pid(arg,palabras);
			}
			else{
				if (strncmp(com,"cdir\0",5)==0){
					cdir(arg,palabras);
				}
				else{
					if (strncmp(com,"fecha\0",6)==0 && palabras==1){
						fecha();
					}
					else{
						if (strncmp(com,"hora\0",5)==0 && palabras==1){
							hora();
						}
						else{
							if (strncmp(com,"hist\0",5)==0 && palabras==1){
								hist(h);
							}
							else{
								if (((strncmp(com,"fin\0",4)==0) || (strncmp(com,"end\0",4)==0) || (strncmp(com,"exit\0",5)==0)) ){
									fin(acabado);
								}
								else{
									printf("%s no encontrado\n",com );
								}
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
	tList historial;
	historial.inicio=NULL;
	historial.final=NULL;


	while (acabado != 1){
		printf("->");
    fgets(teclado,101,stdin);
		gardar(teclado,&historial);


		//Devolve o comando, o argumento e un número que corresponde a se hai 1, 2 ou mais palabras(3)
		numPalabras=TrocearCadena(teclado , comando, argumento);

		/*mostrar por pantalla comando e argumento, para probas
		// puts(teclado );
		// puts(comando );
		// puts(argumento );
		*/

		escollerFuncion(comando,argumento,numPalabras,&acabado,historial);


		limpiarBuffer(teclado);
		limpiarBuffer(comando);
		limpiarBuffer(argumento);


	}
}
/*
--------------------------------------------------------------------------------
*/
