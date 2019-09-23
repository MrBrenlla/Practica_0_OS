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

int acabado = 0;
char  *teclado[];
char  comando[];
char  argumento[];
/*
--------------------------------------------------------------------------------
*/
int TrocearCadena(char * cadena, char * trozos[])
{ int i=1;
if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
return 0;
while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
i++;
return i;
}
/*
--------------------------------------------------------------------------------
*/
void main() {
	while (acabado != 1){
		printf("->");
		scanf("%c", &teclado);
		TrocearCadena();
	}
}
/*
--------------------------------------------------------------------------------
*/
