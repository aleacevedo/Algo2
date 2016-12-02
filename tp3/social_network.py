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
    '''Recibe una lista y devuelve un diccionario que tiene como clave cada
    elemento de esta lista y como valor la cantidad de veces que aparece,
    en caso de que tambien se le pase un diccionario se le suman a los ya preexistentes'''
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

def camino(grafo, origen, destino):
    vecinos = []
    camino = []
    vuelta = {}
    costo = {}
    vuelta[origen] = []
    costo[origen] = 0
    heapq.heappush(vecinos,(0,origen))
    while (len(vecinos)!=0):
        actual = heapq.heappop(vecinos)[1]
        if actual == destino:
            break
        for vecino_actual in grafo.adyacentes(actual):
            if(costo[actual]!=0): nuevo_costo = (1/costo[actual] + 1/grafo.obtener_peso_arista(actual, vecino_actual))
            else:   nuevo_costo = (costo[actual] + 1/grafo.obtener_peso_arista(actual, vecino_actual))
            if (vecino_actual not in costo or nuevo_costo < costo[vecino_actual]):
                costo[vecino_actual] = nuevo_costo
                heapq.heappush(vecinos,(nuevo_costo,vecino_actual))
                vuelta[vecino_actual] = actual
    if(destino in vuelta):
        while (actual!=origen):
            camino.insert(0, actual)
            actual = vuelta[actual]
        camino.insert(0,actual)
        return  camino
    return camino


def centralidad_b(grafo, cantidad):
    apariciones = {}
    res = []
    for origen in grafo.keys():
        cola = []
        visto = {}
        heapq.heappush(cola, (0, origen))
        while len(cola)!=0:
            vertice = heapq.heappop(cola)[1]
            visto[vertice] = True
            for vecino in grafo.adyacentes(vertice):
                if(vecino not in apariciones): apariciones[vecino] = 0
                if(not vecino == origen and not vertice == origen): apariciones[vecino] += 1
                if(not vecino in visto):
                    visto[vecino] = True
                    heapq.heappush(cola,(0, vecino))
    ordenados = ordenar(apariciones)
    print(apariciones)
    for x in heapq.nlargest(cantidad, ordenados):
        res.append(x[1])
    return res


def main():
    red = grafo_crear()
    print("Centralidad")
#    print(centralidad(red,5))
    print("centralidad_b")
    print(centralidad_b(red,5))

main()
