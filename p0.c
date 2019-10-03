
// Practica 0 se SO
// Data: 4 de Outubro do 2019

// Grupo 1.3
// Brais García Brenlla ; b.brenlla
// Ángel Álvarez Rey ; angel.alvarez.rey






//Inclúense varias librerías necesarias para a realización dos comandos
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//Defínese a constante MAX, que será o tamaño máximo das cadeas
#define MAX  300

int acabado = 0;
int numPalabras;
char  teclado[MAX];
char  comando[MAX];
char argumento[MAX];

 typedef  struct nodo {
 	char dato[MAX];
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
  //Póñense todos os campos da cadea a '\0', o carácter nulo
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
	char trozos[MAX];

	limpiarBuffer(trozos);
  //Elimínanse os espacios innecesarios ou engádese un ao final se non hai,
  //de forma que a nova cadea quede formada por palabras seguidas de espacios
	for (int i=0; (cadena[i]!='\0')&&(cadena[i]!='\n')  ; i++){
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
  //Usando a nova cadea cóllense as dúas primeiras palabras como comando e argumentos respectivamente
  // e úsanse os espazos para devolver 1(se só hai comando), 2(se hai comando e argumento)
  // ou 3(se hai 3 ou mais palabras, pois neste caso habería exceso de argumentos)
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
    //Se só se escribiu comando imprímese toda a información de autores
		if (palabras == 1){
				printf("Brais: b.brenlla\nÁngel: angel.alvarez.rey\n");
		}
    //se se ecribe argumento mírase que parte se debe decir, ou no seu defecto, "Error"
		if (palabras == 2){
				if (strncmp(arg,"-l\0",2)==0){
						printf("b.brenlla\nangel.alvarez.rey\n");
				} else if (strncmp(arg,"-n\0",2)==0){
						 printf("Brais\nÁngel\n");
					}
					else{
						printf("Argumento no válido\n");
					}
		}
}
/*
--------------------------------------------------------------------------------
*/

void fecha(){
	time_t tiempo = time(0);
        //Pídese a fecha ao sistema e móstrase por pantalla
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%c",tlocal);
        printf("%s\n",output);
}

/*
--------------------------------------------------------------------------------
*/
void hora(){
	time_t tiempo = time(0);
        //Pídese a fecha ao sistema e móstrase só a hora por pantalla
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%H:%M:%S",tlocal);
        printf("%s\n",output);

}

/*
--------------------------------------------------------------------------------
*/

void cdir(char arg[], int palabras){
	char dir[MAX];
	limpiarBuffer(dir);
  //Se só se puxo o comando pídese ao sistema a dirección actual e móstrase por pantalla
	if (palabras==1){
		getcwd(dir,MAX);
		puts(dir);
	}
  //Se hai argumento diráselle ao sistema a que dirección cambiar, ou no seu defecto, saltará "Error"
	else{
		if (chdir(arg)!=0){
				printf("Error\n" );
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
    //Se só se escribiu o comando pídese o pid do shell ao sistema e móstrase por pantalla
    if (palabras == 1) {
      printf("Pid del shell: %u\n",pid);
      //Se só se escribiu o argumento "-p" pídese o pid do pai do shell ao sistema e móstrase por pantalla
    } else if (!strcmp("-p",arg)){
      printf("Pid del padre del shell: %u\n",pidp);
      //En outro caso móstrase que o argumento non é válido
    } else {
      printf("Argumento no válido\n");
    }
  }
}
/*
--------------------------------------------------------------------------------
*/


void gardar(char teclado[MAX],tList * h){
  //Se a lista está vacía inicialízase cun novo nodo e cárganse aí os datos
	if (h->inicio==NULL){
		h->inicio=malloc(sizeof(tNodo));
    if (h->inicio!=NULL){ //comprobación do malloc
  		h->final=h->inicio;
  		strcpy(h->inicio->dato,teclado);
  		h->inicio->sig=NULL;
    }
    else printf("Error ao asignar espacio de memoria a un punteiro\n" );
	}
  //Se xa está inicializada créase un novo nodo ao final, gárdase o dato e modifícase final
	else{
		h->final->sig=malloc(sizeof(tNodo));
    if (h->final->sig!=NULL){ //comprobación do malloc
    		h->final=h->final->sig;
    		strcpy(h->final->dato,teclado);
    		h->final->sig=NULL;
      }
      else printf("Error ao asignar espacio de memoria a un punteiro\n" );
	}
}

/*
--------------------------------------------------------------------------------
*/

void verhist(tList h){
	tNodo * aux;
	aux=h.inicio;
  //Recórrese a lista mostrando os elementos por pantalla
	while(aux!=NULL){
		printf("%s",aux->dato );
		aux=aux->sig;
	}
}

/*
--------------------------------------------------------------------------------
*/

void borrarhist(tList * h){
  tNodo * aux;
  aux = h->inicio;
  //Se a lista non está vacía elimínaase o primeiro elemento
  //e vólvese a chamar a borrarhist(h) de forma recursiva ata valeirala
  if (aux != NULL){
    h->inicio=h->inicio->sig;
    free(aux);
    borrarhist(h);
  }
  else h->final=NULL;

  /*
  --------------------------------------------------------------------------------
  */

}

void hist(char arg[], tList * h, int palabras){
  //Se só se escribiu o comando móstrase por pantalla a lista
  if (palabras==1){
    verhist(*h);
  }
  else{
    //Se se reciviu o argumento -c bórrase o historial
    if (strncmp(arg,"-c\0",3)==0){
      borrarhist(h);
    }
    //En outro caso salta o erro "Argumento no válido"
    else{
      printf("Argumento no válido\n" );
    }
  }
}

/*
--------------------------------------------------------------------------------
*/
void escollerFuncion(char com[],char arg[],int palabras,int * acabado,tList * h){
  //Tendo en conta o comando recivido e o número de palabras chámase a función necesaria
  // ou salta o erro por comando non válido ou por exceso de argumentos
	if (palabras==3){
		printf("Solo se admite un argumento\n" );
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
							if (strncmp(com,"hist\0",5)==0){
								hist(arg,h,palabras);
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

  //Mentras non se indica que se acabou leerase por teclado e traballarase coa cadena recivida
	while (acabado != 1){
    printf("->");
    fgets(teclado,MAX,stdin);

    //Gárdase a cadea recivida na lista
		gardar(teclado,&historial);


		//Devolve o comando, o argumento e un número de palabras: 1, 2 ou mais(3)
		numPalabras=TrocearCadena(teclado , comando, argumento);

    //Escóllese a función a facer dependendo do comando
		escollerFuncion(comando,argumento,numPalabras,&acabado,&historial);

    //Límpianse as diversas cadeas que se utilizaron
		limpiarBuffer(teclado);
		limpiarBuffer(comando);
		limpiarBuffer(argumento);


	}
  //vacíase a lista antes de pechar o programa
  borrarhist(&historial);
}
/*
--------------------------------------------------------------------------------
*/
