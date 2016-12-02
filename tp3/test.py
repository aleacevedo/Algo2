import grafos
grafo = grafos.Grafos()
grafo["Alejo"] = 0
grafo["Juan"] = 0
grafo["Tomas"] = 0
grafo["Federico"] = 0
grafo["Ramon"] = 0
grafo["Leo"] = 0
grafo["Gaston"] = 0
grafo["Toto"] = 0
grafo.agregar_arista("Alejo", "Juan", 1)
grafo.agregar_arista("Alejo", "Tomas", 4)
grafo.agregar_arista("Alejo", "Federico", 8)
grafo.agregar_arista("Alejo", "Ramon")
grafo.agregar_arista("Alejo", "Leo")
grafo.agregar_arista("Alejo", "Gaston", 40)
print(grafo.centralidad(1))
print(grafo.centralidad_b(1))
