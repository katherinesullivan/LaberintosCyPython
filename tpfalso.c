#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Van a venir dados en det orden?
//tiempo que tarda en correr con 300000 (deja de correr a los 6 seg aprox pero en cargar el archivo tarda bastante)
//verificacion si hay forma mas facil
//siempre va ser posible resolverlo?
//Ver de usar un arreglo unidimensional

int cuentolineas (FILE *entrada) {
	int count = 0;
	char c;
	for (c = getc(entrada); c != EOF; c = getc(entrada)) //tomará un caracter hasta llegar al final del archivo, si encuentra que este caracter es un \n, aumenta el count que funciona como contador de líneas
        if (c == '\n'){
        count = count + 1;
	}
	//printf ("%d\n", count);
	return count;
}

void tomadatos (FILE *entrada, int cantfijos, char* dimension, char** fijos, char* aleatorios, char* inicial, char* objetivo){
	char basura [200];
	int i = 0;
	while (i<5) {
		fscanf (entrada, "%[^\n]\n", basura);
		if (strcmp(basura, "dimension") == 0){
			fscanf (entrada, "%[^\n]\n", dimension);
			i++;
		}else {
			if (strcmp(basura, "obstaculos fijos") == 0){
				for (int n=0;n<cantfijos;n++){
					fscanf(entrada, "%[^\n]\n", fijos[n]);
				}
				i++;
				}else {
					if (strcmp(basura, "obstaculos aleatorios") == 0){
						fscanf (entrada, "%[^\n]\n", aleatorios);
						i++;
						}else {
							if (strcmp(basura, "posicion inicial") == 0){
							fscanf (entrada, "%[^\n]\n", inicial);
							i++;
							}else {
								if (strcmp(basura, "objetivo") == 0){
									fscanf (entrada, "%[^\n]\n", objetivo);
									i++;
								}}}}}}
							}

int verificador(int x, int y, char** laberinto, int tamanio){
	int bandera = 1;
	if (x<1 || x>tamanio || y<1 || y>tamanio){
		bandera = 0;
		}
	if (bandera){
		if (laberinto[y-1][x-1]!='0'){
			bandera = 0;
			}
		}
	return bandera;
	}
	
	
void escribe (char** laberinto, int tamanio, char caracter, int cant){
	int n=0;
	while(n<cant){
		int x = (rand()%tamanio)+1;
		int y = (rand()%tamanio)+1;
		if (laberinto[y-1][x-1]=='0'){
			laberinto[y-1][x-1] = caracter;
			n++;
			}
		}
	}

void transforma (char** laberinto, int tamanio){
	for (int i=0; i<tamanio; i++){
		for(int j=0; j<tamanio; j++){
			if (laberinto[i][j] == '0'){ //ver de transformar los 0 en paredes y dsp los otros en * 2 it LOS VOY A HABER PASADO
				laberinto[i][j] = '1';
				}else {
					if (laberinto[i][j] == '*'){
						laberinto[i][j] = '0';
						}
					}
			}
		}
	}

int generacion (int tamanio, int seed, FILE* salida, char** laberinto, int cantfijos, char** fijos, int aleat, int xi, int yi, int xo, int yo){
	int bandera = 0;
	if (verificador (xi, yi, laberinto, tamanio)){
		laberinto[yi-1][xi-1]='I';
	}else {
		bandera = 1;
		}
	if ((!bandera) && verificador(xo, yo, laberinto, tamanio)){ //VERIFICADO Q HAGA LOS DOS 
		laberinto[yo-1][xo-1]='X';
		}else {
			bandera = 1; //BANDERASSSSS
			}
	srand(seed);
	int i = 0;
	while((!bandera) && i<cantfijos){
		int x;
		int y;
		sscanf(fijos[i], "(%d,%d)", &x, &y);
		if (verificador(x, y, laberinto, tamanio)){ //VERIFICA COMO FC APARTE
			laberinto[y-1][x-1]='1';
			}else {
				bandera = 1;
				}
		i++;
	}
	if (!bandera){
		int espaciolibre = (tamanio*tamanio) - cantfijos - aleat;
		if (aleat < espaciolibre || aleat == espaciolibre){
			escribe(laberinto, tamanio, '1', aleat);
			} else {
				escribe(laberinto, tamanio, '*', espaciolibre);
				transforma (laberinto, tamanio);
				}
			}
	return bandera;
	}


int main (int argc, char * *argv) {
	int retorno = 0;
	FILE *entrada = fopen(argv[1], "r+"); //archivo de 
	FILE *salida = fopen(argv[3], "w+"); 
	if (entrada == NULL){
		 printf ("No se pudo abrir el archivo en el directorio actual.\n");
		 printf("%d", retorno);
	 }else {
		 if (salida == NULL){
			 printf ("No se pudo abrir el archivo en el directorio actual.\n");
			 //printf("%d", retorno);
		 }else {
			 int seed = atoi(argv[2]);
			 int cantfijos = cuentolineas (entrada)-9;
			 rewind (entrada);
			 char *dimension = malloc(sizeof(char)*10000);
			 char **fijos = malloc(sizeof(char*)*(cantfijos+1));
			 for (int i=0;i<cantfijos;i++){
				 fijos[i]=malloc(sizeof(char)*1000);
			 }
			 char *aleatorios = malloc(sizeof(char)*10000);
			 char *inicial = malloc(sizeof(char)*100000);
			 char *objetivo = malloc(sizeof(char)*100000);
			 tomadatos(entrada, cantfijos, dimension, fijos, aleatorios, inicial, objetivo);
			 int tamanio = atoi(dimension);
			 free(dimension);
			 int aleat = atoi(aleatorios);
			 free(aleatorios);
			 int xi, yi, xo, yo;
			 sscanf(inicial, "(%d,%d)", &xi, &yi);
			 sscanf(objetivo, "(%d,%d)", &xo, &yo);
			 free(inicial);
			 free(objetivo);
			 char ** laberinto = malloc(sizeof(char*)*tamanio); //armo un arreglo de arreglos que representarán las lineas (coordenada y)
			 for (int i=0;i<tamanio;i++){
				 laberinto[i]=malloc(sizeof(char)*tamanio+1);
				 laberinto[i][tamanio] = '\0'; //cada linea contiene dimension de chars (el numero de char representará la coordenda x)
				 for (int n=0;n<tamanio;n++){
					 laberinto[i][n]='0'; //inicializo todas las posiciones en 0 
					 } //laberinto[y-1][x-1] será el elemento de coordenadas (x, y)
			 }
			 int resultado = generacion(tamanio, seed, salida, laberinto, cantfijos, fijos, aleat, xi, yi, xo, yo); // ACA VER SI ME DEVUELVE 0 O 1
			 if (resultado == 0){
				 for (int i=0;i<tamanio;i++){
					 //printf("%d", retorno);
					 fprintf(salida, "%s\n", laberinto[i]);
				 }
				 } else {
					 printf("superposición de datos");
					 retorno = 1;
					 }
			free(laberinto);
			free(fijos);
		 }}
		 printf("%d", retorno);
		 return retorno;
	 }
