import grafos
import heapq

ARCHIVO = "marvel.pjk"

def walk(grafo, personaje):
    res = {}
    for x in range (20):
        camino = grafo.random_walk(100, personaje)
        camino.remove(personaje)
        res = contar(camino, res)
    return res

def contar(lista, dic = {}):
    for x in lista:
        if (x not in dic.keys()): dic[x] = 0
        dic[x] += 1
    return dic

def ordenar(dic):
    '''Recibe un diccionario y le hace heapify a la lista de su items'''
    lista = []
    res = list(dic.items())
    for x in res:
        x = list(x)
        x.reverse()
        lista.append(x)
    heapq.heapify(lista)
    return lista

def grafo_crear(archivo = ARCHIVO):
    '''Recibe la ruta de un archivo pjk por parametro y crea un grafo a partir del mismo
    si no recibe nada usa la ruta por default'''
    personajes = {}
    grafo = grafos.Grafos()
    archivo = open(archivo)
    for linea in archivo:
        if(linea == "*Arcs\n"): break
        if(not linea == "*Vertices 6411\n"):
            vertice = linea.split(" ")
            personajes[vertice[0]] = vertice[1]
            for i in vertice[2:]:
                personajes[vertice[0]] += " " + i
            personajes[vertice[0]] = personajes[vertice[0]].strip("\n")
            personajes[vertice[0]] = personajes[vertice[0]].strip('"')
            grafo[personajes[vertice[0]]] = 0
    for linea in archivo:
        conexiones = linea.split(" ")
        grafo.agregar_arista(personajes[conexiones[0]],personajes[conexiones[1]],int(conexiones[2]))
    return grafo

def similares(grafo, personaje, cantidad):
    lista = []
    try:
        res = walk(grafo, personaje)
        res = ordenar(res)
        res = heapq.nlargest(cantidad,res)
        for i in range (cantidad):
            lista.append(res[i][1])
        return lista
    except KeyError:
        return []

def recomendar(grafo, personaje, cantidad):
    lista = []
    try:
        res = walk(grafo, personaje)
        res = ordenar(res)
        while(len(lista)<cantidad):
            if(heapq.nlargest(1,res)[0][1] not in grafo.adyacentes(personaje)):
                lista.append(heapq.nlargest(1,res)[0][1])
                res.remove(heapq.nlargest(1,res)[0])
            else:
                res.remove(heapq.nlargest(1,res)[0])
        return lista
    except KeyError:
        pass
'''
def camino(grafo, origen, destino):
    vecinos = []
    vuelta = {}
    costo = {}
    vuelta[origen] = 0
    costo[origen] = 0
    vecinos.push(0,origen)
    while vecinos
'''

def main():
    red = grafo_crear()
    print("similares")
    print(similares(red,"KNIGHT"  , 5))
    print("recomendar")
    print(recomendar(red,"KNIGHT"  , 5))


main()
