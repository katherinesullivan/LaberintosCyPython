import subprocess
import random
from collections import deque


def obtenerinicio(laberinto, dimension):
	xi = -1
	yi = -1
	bandera = 1
	i=0
	j=0
	while (i<dimension and bandera):
		while (j<dimension):
			if laberinto [i][j] == "I":
				xi = j
				yi = i
				bandera = 0
			j = j+1
		i = i+1
	return xi+1, yi+1
	
				
def generavecinos(node, dimension, laberinto):
	vecinos = []
	if node[0]+1 <= dimension and laberinto [node[1]-1][node[0]+1-1] != '1':
		vecinos.append((node[0]+1, node[1]))
	if node[0]-1 > 0 and laberinto [node[1]-1][node[0]-1-1] != '1':
		vecinos.append((node[0]-1, node[1]))
	if node[1]+1 <= dimension and laberinto [node[1]+1-1][node[0]-1] != '1':
		vecinos.append((node[0], node[1]+1))
	if node[1]-1 > 0 and laberinto [node[1]-1-1][node[0]-1] != '1':
		vecinos.append((node[0], node[1]-1))
	return vecinos
	
	
def bfs (inicio, laberinto, dimension, camino):
	estado = 0
	visitados = set()#ahora vemos
	queue = deque([[inicio]]) #va a contener los distintos caminitos formados
	while queue != [] and not estado:
		try:
			path = queue.popleft() #saco el primer caminito de la queue
		except (IndexError):
			print("Por ahora no es posible encontrar solución")
			return
		#print(path)
		#print(queue)
		node = path [-1] #agarro el ultimo paso para seguir completando el caminito a partir de él
		#print(node)
		if node not in visitados: #ver de no hacer la lista de visitados asi no la tengo que ir llevando -> ponerle -1 en lab -> str
			neighbours = generavecinos(node, dimension, laberinto) #DEL LARGO
			#print(neighbours)
			for neighbour in neighbours:
				#if laberinto [neighbour[1]-1][neighbour[0]-1] != "1":
				nuevopath = list(path)
				nuevopath.append(neighbour) #agrego el nuevo paso al caminito
				queue.append(nuevopath) #agg el nuevo caminito a la queue
				if laberinto[neighbour[1]-1][neighbour[0]-1] == "X": #vale la pena definir algo aparte para lab[][] ya que lo uso 2 vc
					camino.append(nuevopath)
					estado = 1
			visitados.add(node)
	return estado
	
def resuelve (archivoentrada, archivosalidac, soluciontp):
	nosolucion = 1
	while nosolucion:
		solucion = open(soluciontp, "w+")
		seed = str(random.randrange(10000))
		response = subprocess.run(["./a.out", archivoentrada, seed, archivosalidac])
		if response.returncode: 
			nosolucion = 0
			solucion.writelines(["Datos de entrada incompatibles para la generación del laberinto"])
		else:
			camino= []
			#solucion = open(soluciontp, "w+")
			salida = open(archivosalidac, "r+")
			laberinto = salida.readlines() #lista de dimension strings con dimension+1 caracteres (\n al cual no vale la pena eliminar dado que nunca lo vamos a acceder)
			salida.close()
			dimension = len(laberinto)
			inicio = tuple(obtenerinicio(laberinto, dimension))
			resultado = bfs(inicio, laberinto, dimension, camino)
			if resultado:
				nosolucion=0
				solucion.writelines(str(camino)) #ver como queda la impresion de esto
		solucion.close()

resuelve("entrada2.txt", "archivosalida.txt", "soluciontp.txt")
