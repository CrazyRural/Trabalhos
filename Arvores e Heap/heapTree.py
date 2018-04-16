
class Node:
	def __init__(self, chave):
		self.chave = chave
		self.pai = None
		self.direita = None
		self.esquerda = None

class Heap:
	def __init__(self, *args):
		self.node = None

	def redefineFilhosPai(pai, esquerda, direita):
		self.heap.pai = pai
		self.heap.esquerda = esquerda
		self.heap.direita = direita

	def fator(self):
		pEsq = 0
		pDir = 0
		if self.node:
			pEsq = self.node.esquerda.calculaProfundidade()
			pDir = self.node.direita.calculaProfundidade()
		return pDir - pEsq

	def calculaProfundidade(self):
		pEsq = 0
		pDir = 0
		if self.node:
			pEsq = self.node.esquerda.calculaProfundidade()
			pDir = self.node.direita.calculaProfundidade()
		resultado = max(pEsq, pDir) + 1
		return resultado
	

	def inserirHeap(self, chave, noPai = None):
		no = Node(chave) 
		if not self.node:
			self.node = no
			self.node.esquerda = Heap()
			self.node.direita = Heap()
			self.node.pai = noPai
		else:
			pai = self.node
			fator = self.fator()
			fatorSAE = self.node.esquerda.fator()
			fatorSAD = self.node.direita.fator()

			if fator == 0:
				if fatorSAE == 0 and fatorSAD == 0:
					self.node.esquerda.inserirHeap(chave,pai)
				elif fatorSAE == 0 and fatorSAD < -1:	
					self.node.direita.node.direita.inserirHeap(chave, pai)
				elif fatorSAE == 0 and fatorSAD > 1:	
					self.node.direita.node.esquerda.inserirHeap(chave, pai)	
			elif fator < -1:
				self.node.direita.inserirHeap(chave,pai)
			elif fator > 1:	
				self.node.esquerda.inserirHeap(chave, pai)		
	def imprimirHeap(self, espaco = 0): # Imprime uma árvore rotacionada 90º no sentido anti-horário
		if self.node:
			self.node.direita.imprimirHeap(espaco + 2)
			print(" " * espaco + str(self.node.chave))
			self.node.esquerda.imprimirHeap(espaco + 2)				

def main():
	heap = Heap()

	heap.inserirHeap(7)
	heap.inserirHeap(8)
	heap.inserirHeap(5)
	heap.inserirHeap(6)
	heap.inserirHeap(3)
	heap.inserirHeap(4)
	heap.inserirHeap(9)
	heap.inserirHeap(2)
	heap.inserirHeap(1)
	heap.inserirHeap(0)
	heap.inserirHeap(-1)
	heap.imprimirHeap()	

main()					