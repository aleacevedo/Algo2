import grafos
grafo = grafos.Grafos()
grafo["Alejo"] = 0
grafo["Juan"] = 0
grafo["Tomas"] = 0
grafo["Federico"] = 0
grafo["Ramon"] = 0
grafo["Leo"] = 0
grafo["Gaston"] = 0
grafo.agregar_arista("Alejo", "Juan", 1)
grafo.agregar_arista("Alejo", "Tomas", 1)
grafo.agregar_arista("Alejo", "Federico", 8)
grafo.agregar_arista("Juan", "Ramon")
grafo.agregar_arista("Federico", "Leo")
grafo.agregar_arista("Tomas", "Gaston", 3)
grafo.agregar_arista("Juan", "Gaston", 20)
grafo.agregar_arista("Federico", "Gaston", 10)
grafo["Juancho"] = 0
print("Alejo")
print (grafo.camino("Alejo","Gaston"))
