'''
	Feito por João Victor Araújo, Julia Rodrigues e Victor Diniz
'''
class Heap:
	
	def __init__ (self, size):
		self.heap = [None] * (size + 1)
		self.Nos = 0

	def insereHeap(self, x):
		self.heap[self.Nos+1] = x		
		self.Nos += 1			 		 
		self.subirElementos(self.Nos)   

	def buscarHeap(self, chave):	
		for i in range(0, len(self.heap)):
			if chave == self.heap[i]:
				return i
			else:
				continue

	def removerHeap(self, chave):
		
		r = self.heap[chave]			
		self.heap[chave] = self.heap[self.Nos]	
		self.Nos -= 1	
		pai = int(chave/2)
			
		if chave == 1 or self.heap[pai] > self.heap[chave] :  #chave is root 
			self.descerElementos(chave)  # Move the nodeself.heap[chave] DOWN the tree
		else:
			self.subirElementos(chave)	# Move the nodeself.heap[chave] UP the tree
		return r
	
	def subirElementos(self, chave):

		print("\nAntes de subir maiore(s) elemento(s)")
		self.imprimirHeap()

		while (chave != 1):

			pai = int(chave/2)

			if self.heap[chave] > self.heap[pai]:		  
				aux = self.heap[pai]
				self.heap[pai] = self.heap[chave]
				self.heap[chave] = aux
				chave = pai
			else:
				break

	def descerElementos(self, chave):

		print("\nAntes de descer menore(s) elemento(s): ")
		self.imprimirHeap()
		while 2*chave <= self.Nos:
			temp = 2*chave				
			temp2 = 2*chave+1			
			if temp2 <= self.Nos:
				
				if self.heap[chave] > self.heap[temp] and self.heap[chave] > self.heap[temp2]:
					break
				
				else: 
				
					if self.heap[temp] > self.heap[temp2]:
			
						aux = self.heap[chave]
						self.heap[chave] = self.heap[temp]
						self.heap[temp] = aux
										
						chave = temp		

					else:
					
						aux = self.heap[chave]
						self.heap[chave] = self.heap[temp2]
						self.heap[temp2] = aux
						chave = temp2		
		
			else:
			
				if self.heap[chave] > self.heap[temp]:
			
					break

				else: 
				 
					aux = self.heap[chave]
					self.heap[chave] =self.heap[temp]
					self.heap[temp] = aux
					chave = temp		

	def imprimirNo(self, n, altura):
		for i in range(0, altura):
			print("		", end = "")

		print(str(self.heap[n]))

	def imprimirHeap(self):
		if ( self.Nos == 0 ):
			print("Heap vazia")
			print("-------------------------------------------------------")
			return

		self.calculaEspaco(1, 0)
		print("---------------------------------------------------")

	def calculaEspaco(self, n, altura):
		if n > self.Nos:
			return
		base, aux = 2, 1 	
		self.calculaEspaco(base * n + 1, altura + aux)
		self.imprimirNo(n, altura)
		self.calculaEspaco(base * n, altura + aux)

def main():

	v = [2, 7, 5, 9, 13, 1, 4, 24, 12, 17, 15, 8, 3, 6, 22]		
	x = Heap(100)
	for i in range(0, len(v)):
		print("Inserindo: " + str(v[i]))
		x.insereHeap(v[i])
		x.imprimirHeap()
	x.removerHeap(3)	
	index = int(input(""))
	print("Removendo ...")
	index = x.buscarHeap(index)
	try:
		x.removerHeap(index)
	except:
		print("Valor não encontrado para remoção")	
	x.imprimirHeap()	
main()
