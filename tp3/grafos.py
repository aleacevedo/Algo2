class _Vertice:
    def __init__(self, id = None, valor = None, adyacencias = {}):
        self.id = id
        self.valor = valor

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

    def __len__(self):
        return self.largo

    def keys(self):
        return self.vertices.keys()

    def __getitem__(self, id):
        self.vertices[id].valor

    def __setitem__(self, id, valor):
        if(self.vertices.get(id)==None):
            self.vertices[id] = _Vertice(id, valor,)
        else:
            self.vertices[id].valor = valor

    def __delitem__(self, id):
        if(self.vertices.get(id)==None):
