from heapq import heappush, heappop
from copy import deepcopy

matriz = []
posicaoVazio = [0,0]

def lerMatriz(): 
	arq = open('quebraCabeca.txt', 'r')    
	texto = arq.readlines()
	for i in texto:
		vetor = []
		for j in i.split():
			vetor.append(j)
		matriz.append(vetor)
		vetor = []
	arq.close()
	for ind_i in range(3):
		for ind_j in range(3):
			if matriz[ind_i][ind_j] == '-1':
				posicaoVazio[0] = ind_i
				posicaoVazio[1] = ind_j


def alterarPosicao(matriz, posicaoVazio, pos):
	if pos == 'subir': #cima
		if(posicaoVazio[0] > 0):
			matriz[posicaoVazio[0] - 1][posicaoVazio[1]], matriz[posicaoVazio[0]][posicaoVazio[1]] = matriz[posicaoVazio[0]][posicaoVazio[1]], matriz[posicaoVazio[0] - 1][posicaoVazio[1]]
			posicaoVazio[0] = posicaoVazio[0] - 1
           # else:
            #    print("Impossivel realizar operacao")
	elif pos == 'descer': #baixo
		if(posicaoVazio[0] < 2):
			matriz[posicaoVazio[0] + 1][posicaoVazio[1]], matriz[posicaoVazio[0]][posicaoVazio[1]] = matriz[posicaoVazio[0]][posicaoVazio[1]], matriz[posicaoVazio[0] + 1][posicaoVazio[1]]
			posicaoVazio[0] = posicaoVazio[0] + 1
            #else:
             #   print("Impossivel realizar operacao")
	elif pos == 'direita': #direita
		if(posicaoVazio[1] < 2):
			matriz[posicaoVazio[0]][posicaoVazio[1] + 1], matriz[posicaoVazio[0]][posicaoVazio[1]] = matriz[posicaoVazio[0]][posicaoVazio[1]], matriz[posicaoVazio[0]][posicaoVazio[1] + 1]
			posicaoVazio[1] = posicaoVazio[1] + 1
            #else:
             #   print("Impossivel realizar operacao")
	elif pos == 'esquerda': #esquerda
		if(posicaoVazio[1] > 0):
			matriz[posicaoVazio[0]][posicaoVazio[1] - 1], matriz[posicaoVazio[0]][posicaoVazio[1]] = matriz[posicaoVazio[0]][posicaoVazio[1]], matriz[posicaoVazio[0]][posicaoVazio[1] - 1]
			posicaoVazio[1] = posicaoVazio[1] - 1
            #else:
             #   print("Impossivel realizar operacao")
	else:
		print("Comando Invalido")
        #print (matriz)

def euristicaManhattan(matriz, gabarito):
	resultado = 0	
	for i_m in range(3):
		for j_m in range(3):
			ind = matriz[i_m][j_m]
			for i in range(3):
				for j in range(3):
					if ind == gabarito[i][j]:
						i_g = i
						j_g = j
			resultado = resultado + (abs(i_m - i_g) + abs(j_m - j_g))
	return resultado


def comparaMatriz(matriz, gabarito):
	contador = 0
	for i in range(3):
		for j in range(3):
			if matriz[i][j] == gabarito[i][j]:
				contador = contador + 1
	if contador == 9:
		return True
	else:
		return False


def geraTuplaAEstrela(gX, posicaoVazio, comando, matriz, gabarito):
	tupla = (gX,matriz,posicaoVazio)
	matrizTemporaria = deepcopy(matriz)
	posicaoTemporaria = deepcopy(posicaoVazio)
	alterarPosicao(matrizTemporaria, posicaoTemporaria, comando)
	if(not(comparaMatriz(matrizTemporaria,matriz))):
		fX = gX + euristicaManhattan(matriz, gabarito) #f(X) = g(X) + h(X)
		tupla = (fX,matrizTemporaria,posicaoTemporaria)
	return tupla
    
def buscaAEstrela(matriz, posicaoVazio, Gabarito, limite):
	it = 0
	heap = []
	Matriz = matriz
	tupla = (0, matriz, posicaoVazio)
	heappush(heap, tupla)   
	while not(comparaMatriz(Matriz, Gabarito)) and it < limite:              
		gX,Matriz,posicaoVazio = heappop(heap)
		for indiceTupla in range(4):
			if(indiceTupla == 0):
				comando = 'subir'
			if(indiceTupla == 1):
				comando = 'descer'
			if(indiceTupla == 2):
				comando = 'direita'
			if(indiceTupla == 3):
				comando = 'esquerda'
			tupla = geraTuplaAEstrela(gX, posicaoVazio, comando, Matriz, Gabarito)
			if(not(tupla[0] == gX) and not(tupla[1] == Matriz) and not(tupla[2] == posicaoVazio)):
				heappush(heap, tupla) 
		it += 1
		print("iteracao: " + str(it) + "\nCusto: "+ str(gX) +"\nResultado: ")
		print(Matriz)

def geraTuplaGulosa(posicaoVazio, comando, Matriz, Gabarito):
	tupla = (0,Matriz,posicaoVazio)
	matrizTemporaria = deepcopy(Matriz)
	posicaoTemporaria = deepcopy(posicaoVazio)
	alterarPosicao(matrizTemporaria, posicaoTemporaria, comando)
	if(not(comparaMatriz(matrizTemporaria,Matriz))):
		fX = euristicaManhattan(Matriz, Gabarito) #f(X) = h(X)
		tupla = (fX,matrizTemporaria,posicaoTemporaria)
	return tupla
    
def buscaGulosa(matriz, posicaoVazio, Gabarito, limite):
	it = 0
	heap = []
	Matriz = matriz
	tupla = (0, matriz, posicaoVazio)
	heappush(heap, tupla)       
	while not(comparaMatriz(Matriz,Gabarito)) and it < limite: 
		gX,Matriz,posicaoVazio = heappop(heap)
		for indiceTupla in range(4):
			if(indiceTupla == 0):
				comando = 'subir'
			if(indiceTupla == 1):
				comando = 'descer'
			if(indiceTupla == 2):
				comando = 'direita'
			if(indiceTupla == 3):
				comando = 'esquerda'
			tupla = geraTuplaGulosa(posicaoVazio, comando, Matriz, Gabarito)
			if(not(tupla[0] == gX) and not(tupla[1] == Matriz) and not(tupla[2] == posicaoVazio)):
				heappush(heap, tupla) 
		it += 1
		print("iteracao: " + str(it) + "\nCusto: "+ str(gX) +"\nResultado: ")
		print(Matriz)


def geraTuplaLargura(gX, posicaoVazio, comando, Matriz, Gabarito):
	tupla = (0,Matriz,posicaoVazio)
	matrizTemporaria = deepcopy(Matriz)
	posicaoTemporaria = deepcopy(posicaoVazio)
	alterarPosicao(matrizTemporaria, posicaoTemporaria, comando)
	if(not(comparaMatriz(matrizTemporaria,Matriz))):
		fX = gX + 1 #f(X) = g(X) + 1
		tupla = (fX,matrizTemporaria,posicaoTemporaria)
	return tupla
    
def buscaLargura(matriz, posicaoVazio, Gabarito, limite):
	it = 0
	vetor = []
	Matriz = matriz
	tupla = (0, matriz, posicaoVazio)
	vetor.append(tupla) 
	while not(comparaMatriz(Matriz,Gabarito)) and it < limite:              
		gX,Matriz,posicaoVazio = vetor[0]
		del vetor[0]   
		for indiceTupla in range(4):
			if(indiceTupla == 0):
				comando = 'subir'
			if(indiceTupla == 1):
				comando = 'descer'
			if(indiceTupla == 2):
				comando = 'direita'
			if(indiceTupla == 3):
				comando = 'esquerda'
			tupla = geraTuplaLargura(gX, posicaoVazio, comando, Matriz, Gabarito)
			if(not(tupla[0] == gX) and not(tupla[1] == Matriz) and not(tupla[2] == posicaoVazio)):
				vetor.append(tupla) 
		it += 1
		print("iteracao: " + str(it) + "\nCusto: "+ str(gX) +"\nResultado: ")
		print(Matriz)

def geraTuplaCustoUniforme(gX, posicaoVazio, comando, Matriz, Gabarito):
	tupla = (0,Matriz,posicaoVazio)
	matrizTemporaria = deepcopy(Matriz)
	posicaoTemporaria = deepcopy(posicaoVazio)
	alterarPosicao(matrizTemporaria, posicaoTemporaria, comando)
	if(not(comparaMatriz(matrizTemporaria.matriz,Matriz))):
		fX = gX + 1 #f(X) = g(X) + 1
		tupla = (fX,matrizTemporaria,posicaoTemporaria)
	return tupla
    
def buscaCustoUniforme(matriz, posicaoVazio, Gabarito, limite):
	it = 0
	heap = []
	Matriz = matriz
	tupla = (0, matriz, posicaoVazio)
	heappush(heap, tupla)      
	while not(comparaMatriz(Matriz,Gabarito)) and it < limite:              
		gX,Matriz,posicaoVazio = heappop(heap)
		for indiceTupla in range(4):
			if(indiceTupla == 0):
				comando = 'subir'
			if(indiceTupla == 1):
				comando = 'descer'
			if(indiceTupla == 2):
				comando = 'direita'
			if(indiceTupla == 3):
				comando = 'esquerda'
			tupla = geraTuplaAEstrela(gX, posicaoVazio, comando, Matriz, Gabarito)
			if(not(tupla[0] == gX) and not(tupla[1] == Matriz) and not(tupla[2] == posicaoVazio)):
				heappush(heap, tupla) 
		it += 1
		print("iteracao: " + str(it) + "\nCusto: "+ str(gX) +"\nResultado: ")
		print(Matriz)

def main():
	gabarito = [['-1','1','2'],['3','4','5'],['6','7','8']]
	print("Gabarito: " + str(gabarito))
	lerMatriz()
	#print(matriz)
	#print(posicaoVazio)
	print("Puzzle: " + str(matriz))
	print("\n--------------Busca A*--------------\n")
	buscaAEstrela(matriz, posicaoVazio, gabarito, 50)
	print("\n-----------Busca Gulosa--------------\n")
	buscaGulosa(matriz, posicaoVazio, gabarito, 50)
	print("\n-----------Busca Largura--------------\n")
	buscaLargura(matriz, posicaoVazio, gabarito, 50)
	print("\n-----------Busca Custo Uniforme--------------\n")
	buscaLargura(matriz, posicaoVazio, gabarito, 50)

main()

"""

#gabarito = [[-1, 1, 2],[3, 4, 5],[6, 7, 8]]def diferenca(u, v):
    x, y = u
    w, z = v
    return abs(w - x) + abs(z - y)

def pesoManhattan(atual, gabarito):
	total = 0;
	for i in atual:
		if i != 0:
			total += diferenca(coordenadas(gabarito[i]), coordenadas(atual.index(i)))
			manhattan = total
	return total

def movimentosPossiveis(atual):
	index = atual.index(0)
	if index in [3, 4, 5, 6, 7, 8]:
		novoEstado = atual[:]
		novoEstado[index], novoEstado[index - 3] = novoEstado[index - 3], novoEstado[index]
		return novoEstado
	if index in [1, 2, 4, 5, 7, 8]:
		novoEstado = atual[:]
		novoEstado[index], novoEstado[index - 1] = novoEstado[index - 1], novoEstado[index]
		return novoEstado
	if index in [0, 1, 3, 4, 6, 7]:
		novoEstado = atual[:]
		novoEstado[index], novoEstado[index + 1] = novoEstado[index + 1], novoEstado[index]
		return novoEstado
	if index in [0, 1, 2, 3, 4, 5]:
		novoEstado = atual[:]
		novoEstado[index], novoEstado[index + 3] = novoEstado[index + 3], novoEstado[index]
		return novoEstado"""   
