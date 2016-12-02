import random
import heapq
class _Vertice:
    def __init__(self, id = None, valor = None):
        self.id = id
        self.valor = valor
        self.adyacencias = {}

class _IteradorGrafo:
    def __init__(self, vertices, ids):
        self.ids = ids
        self.actual = 0
        self.vertices = vertices;

    def __next__(self):
        try:
            id = ids[actual]
            actual += 1
            return self.vertices[id].valor
        except IndexError:
            raise StopIteration()


class Grafos:
    def __init__(self, es_dirigido = False):
        self.vertices = {}
        self.adyacencias = {}
        self.largo = 0
        self.diri = es_dirigido

    def __len__(self):
        return self.largo

    def keys(self):
        return self.vertices.keys()

    def __getitem__(self, id):
        return self.vertices[id].valor

    def __setitem__(self, id, valor):
        if(self.vertices.get(id)==None):
            self.largo += 1
            self.vertices[id] = _Vertice(id, valor,)
        else:
            self.vertices[id].valor = valor

    def __delitem__(self, id):
        if(self.vertices.get(id)!=None):
            self.largo -= 1
            del self.vertices[id]
            for i in self.vertices:
                try:
                    del self.vertices[i].adyacencias[id]
                except KeyError:
                    pass
    def __contains__(self, id):
        return self.vertices.get(id)!=None


    def agregar_arista(self, desde, hasta, peso = 1):
        if (not self.__contains__(hasta)): raise KeyError
        self.vertices[desde].adyacencias[hasta] = peso
        if(not self.diri):
            self.vertices[hasta].adyacencias[desde] = peso

    def borrar_arista(self, desde, hasta):
        if (not self.__contains__(desde)): raise KeyError
        if (not self.__contains__(hasta)): raise KeyError
        try:
            del self.vertices[desde].adyacencias[hasta]
            if(not self.diri): del self.vertices[hasta].adyacencias[desde]
        except KeyError:
            raise ValueError

    def obtener_peso_arista(self, desde, hasta):
        try:
            return self.vertices[desde].adyacencias[hasta]
        except KeyError:
            return None

    def adyacentes(self, id):
        return self.vertices[id].adyacencias.keys()

    def random_walk(self, largo, origen = None):
        if(largo==0): return []
        camino = []
        adyacentes = []
        if(origen == None): origen = random.choice(list(self.vertices.keys()))
        camino.append(origen)
        for x in (self.vertices[origen].adyacencias):
            for i in range (self.vertices[origen].adyacencias[x]):
                adyacentes.append(x)
        return camino + self.random_walk(largo-1, random.choice(adyacentes))

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

    def dijkstra(grafo, origen):
        cola = []
        distancia = {}
        padre = {}
        visto = {}
        for vertice in grafo.keys():
            distancia[vertice] = 99999999
            padre[vertice] = None
            visto[vertice] = False
        distancia[origen] = 0
        heapq.heappush(cola, (distancia[origen], origen))
        while len(cola)!=0:
            vertice = heapq.heappop(cola)[1]
            visto[vertice] = True
            for vecino in grafo.adyacentes(vertice):
                if(not vecino in visto or distancia[vecino] > distancia[vertice] + grafo.obtener_peso_arista(vecino, vertice)):
                    distancia[vecino] = distancia[vertice] + grafo.obtener_peso_arista(vecino, vertice)
                    padre[vecino] = vertice
                    heapq.heappush(cola,(distancia[vecino], vecino))
        return padre

    def contar(grafo, lista, dic = {}):
        '''Recibe una lista y devuelve un diccionario que tiene como clave cada
        elemento de esta lista y como valor la cantidad de veces que aparece,
        en caso de que tambien se le pase un diccionario se le suman a los ya preexistentes'''
        for x in lista:
            if (x not in dic.keys()): dic[x] = 0
            dic[x] += 1
        return dic

    def ordenar(grafo, dic):
        '''Recibe un diccionario y le hace heapify a la lista de su items'''
        lista = []
        res = list(dic.items())
        for x in res:
            x = list(x)
            x.reverse()
            lista.append(x)
        heapq.heapify(lista)
        return lista

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
        ordenados = grafo.ordenar(apariciones)
        print(apariciones)
        for x in heapq.nlargest(cantidad, ordenados):
            res.append(x[1])
        return res


    def centralidad(grafo, cantidad):
        contados = {}
        res = []
        for x in grafo.keys():
            print(x)
            dic = grafo.dijkstra(x)
            lista = list(dic.keys())
            lista.remove(x)
            contados = grafo.contar(lista, contados)
            lista = list(dic.values())
            contados = grafo.contar(lista, contados)
        print(contados)
        ordenados = grafo.ordenar(contados)
        for x in heapq.nlargest(cantidad, ordenados):
            res.append(x[1])
        return res
