import random

class _Vertice:
    def __init__(self, id = None, valor = None, adyacencias = {}):
        self.id = id
        self.valor = valor
        self.adyacencias = adyacencias

class _IteradorGrafo:
    def __init__(self, vertices, ids):
        self.ids = ids
        self.actual = 0
        self.vertices = vertices;

    def __next__(self):
        try id = ids[actual]:
            actual++
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
            self.largo++
            self.vertices[id] = _Vertice(id, valor,)
        else:
            self.vertices[id].valor = valor

    def __delitem__(self, id):
        if(self.vertices.get(id)!=None):
            self.largo--
            del self.vertices[id]
            del self.adyacencias[id]
            key = self.keys()
            for i in key:
                del self.adyacencias[i][id]

    def __contains__(self, id):
        return self.vertices.get(id)!=None

    def agregar_arista(self, desde, hasta, peso = 1):
        if (!self.__contains__(hasta)): raise KeyError
        self.vertices[desde].adyacencias[hasta] = peso
        if(!self.diri):
            self.vertices[hasta].adyacencias[desde] = peso

    def borrar_arista(self, desde, hasta):
        if (!self.__contains__(desde)): raise KeyError
        if (!self.__contains__(hasta)): raise KeyError
        try:
            del self.vertices[desde].adyacencias[hasta]
            if(!self.diri): del self.vertices[hasta].adyacencias[desde]
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
        camino = []
        while x in largo:
            if(origen == None): origen = random.choice(self.vertices.keys())
            for x in self.vertices[origen].adyacencias:
                adyacentes = []
                for i in range self.vertices[origen].adyacencias[x]:
                    adyacentes.append(x)
            camino.append(random.choice(adyacentes))
            x++
        return camino
