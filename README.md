# TPfinalProg2

Programa desarrollado para la asignatura de Programación 2 del primer año de la carrera Licenciatura en Ciencias de la Computación de la Universidad Nacional de Rosario.

El objetivo de programa es resolver con Python un archivo de laberinto generado en C, siempre que se pueda crear un laberinto con solución dada la entrada.
Si con determinado laberinto no se puede se genera un print que dice que por ahora no es posible encontrar una solucion y se van creando otros hasta poder. Una vez que termino de correr el programa si no aparece un print que diga "Datos de entrada incompatibles para la generación del laberinto" significa que se encomtró una solución que se eplicita en uno de los archivos de salida.

El programa toma como entrada un archivo con el siguiente formato:

obstaculos fijos
(x1,y1)
(x2,y2)
...
(xn,yn)
obstaculos aleatorios
k
posicion inicial
(xi,yi)
objetivo
(xf,yf)
dimension
C

donde las (x,y) representan coordenadas del laberinto y k y C son números.

 
 PARA CORRER EL PROGRAMA:

Primero generar un archivo ejecutable a.out del archivo de C corriendo la siguiente línea en caso de tener el compilador gcc:

gcc tpfalso.c

o

gcc -o a.out tpfalso.c

Luego correr el archivo de python con el siguiente formato:

python tp5.py entrada.txt laberinto.txt solucion.txt

Por default el nombre de esos archivos es entrada2.txt, archivosalida.txt, soluciontp.txt