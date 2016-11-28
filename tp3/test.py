archivo = open("pepo.txt")
for linea in archivo:
    if(linea == "tomas\n"):
        break
    print(linea)

for linea in archivo:
    print(linea)
