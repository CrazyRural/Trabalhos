 # -*- coding: utf-8 -*-
class Vertice(object):
	def __init__(self):
		self.antecessorVertice = {}
		self.profundidade = {}

	def iniciaVertices(self, v):
		self.antecessorVertice[v] = v
		self.profundidade[v] = 0

	def encontraVerticeAntecessor(self, v):
		if self.antecessorVertice[v] == v:
			return self.antecessorVertice[v]
		else:
			return self.encontraVerticeAntecessor(self.antecessorVertice[v])

	def equilibraVerticeAntecessor(self, v1, v2):
		if self.profundidade[v1] > self.profundidade[v2]:
			self.antecessorVertice[v2]= self.antecessorVertice[v1]
			self.profundidade[v2] = self.profundidade[v1] + 1
		elif self.profundidade[v1] == self.profundidade[v2]:
			self.antecessorVertice[v2] = self.antecessorVertice[v1]
			self.profundidade[v2]= self.profundidade[v2] + 1

class Aresta(object):
	def __init__(self, v1, v2, peso):
		self.v1 = v1
		self.v2 = v2
		self.peso = peso

class Grafo(object):
	def __init__(self):
		self.vertices = []
		self.arestas = []
		self.arvoreGeradora = []
		self.distancias = {}
	
	def adicionaArestas(self, Aresta):
		self.arestas.append(Aresta)

	def Kruscal(self):
		v = Vertice()

		for i in self.vertices:
			v.iniciaVertices(i)

		self.arestas.sort(key=lambda x: x.peso)
		
		for i in self.arestas:
			v1 = v.encontraVerticeAntecessor(i.v1)
			v2 = v.encontraVerticeAntecessor(i.v2)
			if v1 != v2:
				self.arvoreGeradora.append(i)
				v.equilibraVerticeAntecessor(v1, v2)

	
	def iniciaDistancias(self, v):
		self.distancias[v] = 999999999

	def BellmanFord(self, v):
		for i in self.vertices:
			self.iniciaDistancias(i)
		self.distancias[v] = 0
		print 'BellmanFord executando'
		
		for i in range(1, len(self.vertices) - 1):
			for j in self.arestas:
				if self.distancias[j.v1] + j.peso < self.distancias[j.v2]:
					self.distancias[j.v2] =  self.distancias[j.v1] + j.peso
			'''for i in self.arestas:
				if self.distancias[i.v1] + j.peso < self.distancias[i.v2]:
					print 'Ciclo negativo!'''
					
			

	def imprimeGrafo(self):
		x = 1
		for i in self.arestas:
			print '{}º Aresta: {}-{}\nPeso: {}'.format(x, i.v1, i.v2, i.peso)
			print
			x = x + 1
		return x - 1

	def imprimeArvoreGeradora(self):
		x = 1
		pesoTotal = 0
		for i in self.arvoreGeradora:
			print '{}º Aresta: {}-{}\nPeso: {}'.format(x ,i.v1, i.v2, i.peso)
			print
			pesoTotal = pesoTotal + i.peso	
			x = x + 1
		return x - 1, pesoTotal

	def imprimeTabelaDistancias(self, v):
		self.distanciasAux = sorted(self.distancias)
		for i in self.distanciasAux:
			print 'Distância de {} para {} é {}'.format(v , i, 'Infinito' if self.distancias[i] == 10000000  else self.distancias[i]) 

def main():

	grafo = Grafo()
	grafo.vertices = ['A','D','E','C','B']

	
	arestaAB = Aresta('A','B', 12)
	grafo.adicionaArestas(arestaAB)
	arestaAD = Aresta('A','D', 10)
	grafo.adicionaArestas(arestaAD)
	arestaAC = Aresta('A','C', 13)
	grafo.adicionaArestas(arestaAC)
	arestaBD = Aresta('B','D', 5)
	grafo.adicionaArestas(arestaBD)
	arestaCE = Aresta('C','E', 23)
	grafo.adicionaArestas(arestaCE)
	arestaCD = Aresta('C','D', 50)
	grafo.adicionaArestas(arestaCD)
	arestaDE = Aresta('D','E', 17)
	grafo.adicionaArestas(arestaDE)
	
	print '/------------------------------------GRAFO ORIGINAL'
	x = grafo.imprimeGrafo()
	print x, 'Arestas do Grafo Original'
	grafo.Kruscal()
	print '/----------------------------------KRUSKAL RESULTADO'
	x, peso = grafo.imprimeArvoreGeradora()
	print x, 'Arestas na Árvore Geradora\nC(MST) = {}\n'.format( peso)
	
	'''
	grafo.vertices.append('F')
	arestaDC = Aresta('D','C', 25)
	grafo.adicionaArestas(arestaDC)
	arestaDF = Aresta('D','F', 31)
	grafo.adicionaArestas(arestaDF)
	arestaEC = Aresta('E','C', 12)
	grafo.adicionaArestas(arestaEC)
	arestaED = Aresta('E','D', 31)
	grafo.adicionaArestas(arestaED)
	grafo.adicionaArestas(arestaEC)
	arestaEF = Aresta('E','F', 14)
	grafo.adicionaArestas(arestaEF)
	arestaFE = Aresta('F','E', 6)
	grafo.adicionaArestas(arestaFE)
	arestaFA = Aresta('F','A', 40)
	grafo.adicionaArestas(arestaFA)
	
	grafo.arestas.sort(key=lambda x: x.peso)
	
	print '/------------------------------------GRAFO ORIGINAL'
	x = grafo.imprimeGrafo()
	'''

	v = raw_input("Qual ponto inicial?\n")
	if str.upper(v) not in grafo.vertices: 
		exit()
	#v = 'A'
	grafo.BellmanFord(str.upper(v))
	print '/--------------------------------- BELLMAN RESULTADO'
	grafo.imprimeTabelaDistancias(str.upper(v))


main()	