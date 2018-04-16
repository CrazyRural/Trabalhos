
class Node:
	def __init__(self, valor):
		self.valor = valor
		self.esquerda = None
		self.direita = None
		self.color = None

class AVL:

	def __init__(self, *args):
		self.node = None
	
	def redefineSubArvores(self, esquerda, direita):
		self.node.esquerda = esquerda
		self.node.direita = direita

	def inserirRB(self, valor):
		no = Node(valor)
		if not self.node:
			self.node = no
			self.node.esquerda = AVL()
			self.node.direita = AVL()
		elif self.node.valor > valor:
			self.node.esquerda.inserirRB(valor)
		else:
			self.node.direita.inserirRB(valor)	

	def buscaRB(self, busca):
		if not self.node:
			print("Valor não foi encontrado")
			return None	
		elif self.node.valor > busca:
			self.node.esquerda.buscaRB(busca)
		elif self.node.valor < busca :
			self.node.direita.buscaRB(busca)
		else:
			print("Valor foi encontrado")
			return self		

	def encontraNovoValor(self, node):
		if self.node.esquerda.node == None:
			return node
		else:
			node = self.node.esquerda.node
			return node				

	def removeRB(self, valor):
		if self.node is None:
			print("Valor não foi encontrado para remoção")
			return None	
		elif self.node.valor > valor:
			self.node.esquerda.removeRB(valor)
		elif self.node.valor < valor:
			self.node.direita.removeRB(valor)
		else:
			print("Valor foi encontrado... removendo...")
			if self.node.direita.node is None and self.node.esquerda.node is None:
				self.node = None
			elif not self.node.direita.node:
				self.node= self.node.esquerda.node
			elif not self.node.esquerda.node:
				self.node = self.node.direita.node
			else:
				temp = self.encontraNovoValor(self.node)
				print(temp.valor)
				if temp:
					self.node.valor = temp.valor	
				self.node.esquerda.removeRB(temp.valor)

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

	def executaBalanceamento(self):
		bal = self.fator()

		if bal > 1:
			if self.node.esquerda.fator() < 0:
				print("Rotacionando à esquerda\n")
				self.RE()
			else:
				print("Rotacionando duplamente à esquerda\n")
				self.RDE()
		elif bal < -1:
			if self.node.direita.fator() > 0:
				print("Rotacionando à direita\n")
				self.RD()
			else:
				print("Rotacionando duplamente à direita\n")
				self.RDD()
		
		bal = self.fator()
				
		if bal > 1:
			self.executaBalanceamento()
		if bal < -1:
			self.executaBalanceamento()		

	def RE(self):
		anteriorEsq = self.node.esquerda
		self.node.valor, self.node.direita.node.valor = self.node.direita.node.valor, self.node.valor
		self.redefineSubArvores(self.node.direita, self.node.direita.node.direita)
		self.node.esquerda.redefineSubArvores(anteriorEsq, self.node.esquerda.node.esquerda)

	def RD(self):
		anteriorDir = self.node.direita
		self.node.valor, self.node.esquerda.node.valor = self.node.esquerda.node.valor, self.node.valor
		self.redefineSubArvores(self.node.esquerda.node.esquerda, self.node.esquerda)
		self.node.direita.redefineSubArvores(self.node.direita.node.direita, anteriorDir)

	def RDE(self):
		self.node.direita.RD()
		self.RE()

	def RDD(self): 
		self.node.esquerda.RE()
		self.RD()

	def imprimir(self, espaco = 0): # Imprime uma árvore rotacionada 90º no sentido anti-horário
		if self.node:
			self.node.direita.imprimir(espaco + 2)
			print(" " * espaco + str(self.node.valor))
			self.node.esquerda.imprimir(espaco + 2)

	def remocao(self, valor):
		self.removeRB(valor)
		self.executaBalanceamento()

	def colorirArvore(self, raiz):
		if self.node.valor == raiz:
			self.node.color = "N"
		elif self.node.esquerda.node and self.node.esquerda.node.color == "R":
			self.node.color = "N"		
		elif self.node.direita.node and self.node.direita.node.color  == "R":
			self.node.color = "N"
		else :
			self.node.color = "R"	
		
		if self.node.esquerda.node:
			self.node.esquerda.colorirArvore(raiz)
		if self.node.direita.node:
			self.node.direita.colorirArvore(raiz)
	


	def imprimirRB(self, espaco = 0): # Imprime uma árvore pintada rotacionada 90º no sentido anti-horário
		if self.node:
			self.node.direita.imprimirRB(espaco + 2)
			print(" " * espaco + str(self.node.color))
			self.node.esquerda.imprimirRB(espaco + 2)

def main():
	avl = AVL()
	raiz = 5
	avl.inserirRB(raiz)
	avl.inserirRB(3)
	avl.inserirRB(1)
	avl.inserirRB(2)
	avl.inserirRB(-1)
	avl.inserirRB(0)
	avl.inserirRB(7)
	avl.inserirRB(9)
	avl.inserirRB(8)	

	avl.imprimir()
	print("----------------------------------------------")
	avl.colorirArvore(raiz)
	avl.colorirArvore(raiz)
	avl.imprimirRB()
	
	"""print("\n")
				print("--------------------Balanceamento------------------")
				print("\n")
			
				avl.executaBalanceamento()
				avl.imprimir()"""
	
	"""print("\n")
				print("-----------------------Busca-----------------------")
				print("\n")
				
				teclado = int(input("Buscando qual elemento?\n"))
				avl.buscaRB(teclado)
			"""
	"""print("\n")
				print("---------------------Remoção------------------------")
				print("\n")
				
				teclado = int(input("Apagar algum número? \n"))
				avl.remocao(teclado)
				avl.imprimir()"""

main()
