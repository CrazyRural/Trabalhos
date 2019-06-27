import threading
import time
import socket
import struct
import sys

class Processo:
	# Iniciando Processo
	def __init__(self, identificador, lider, relogio_interno, processos):
		self.identificador = identificador
		self.lider = lider
		self.relogio_interno = relogio_interno
		self.processos = processos
	# Definindo print de Processo como valor do identificador
	def __str__(self):
		return str(self.identificador)
	# Incrementar relógio com valor de delay num intervalo de tempo = delay
	def incrementar_relogio(self, threadName, delay):
		while True:
			time.sleep(delay)
			self.relogio_interno += delay
			#print ("%s: %s" % (threadName, self.relogio_interno))			
	# Se processo verifica que não existe líder, ele convoca eleição
	def algoritmo_bully(self):
		# Respondendo possíveis eleições já existentes. 
		# Se existir eleição convocada por processo de id maior não deve convocar nova eleição, se a eleição existente for de id menor deve convocar nova eleição.
		# Retorna True se processo deve convocar eleição
		resposta = self.receber_mensagem(2)
		# Convoca eleição caso não exista líder ou se é maior que outros processos que convocaram eleição
		if resposta:
			self.convocar_eleicao()

	def sem_lider(self):
		# Respondendo se é lider, caso outro processo tenha perguntado TODO: só processo que é lider deve responder
		self.receber_mensagem(1)
		# Verificando se processo é o líder ou se existe um líder ativo(Processo que responda a mensagem, se identificando como grupo)
		if self.lider or enviar_mensagem(1, 0):
			return False
		else:
			return True

	def convocar_eleicao(self):
		# Enviando mensagem para descobrir se existe algum processo com id maior que o seu para virar líder
		possivel_lider = enviar_mensagem(2, 0)
		# Se nenhum processo respondeu, o processo se torna líder. Só processo com id maior deve responder
		# Se algum processo responder, o processo desiste
		if not possivel_lider:
			self.lider = True
	
	def enviar_mensagem(self,id_mensagem, ajuste):
		respostas = False
		# Enviando mensagem do tipo: "Existe identificador maior que o meu?" mandando seu identificador como parâmetro
		if id_mensagem == 2:
			mensagem = self.identificador
		# Enviando mensagem do tipo: "Ajuste seu relógio com o novo valor informado pelo parâmetro ajuste"
		elif id_mensagem == 4:
			mensagem = ajuste
		# Enviando mensagem do tipo: "Existe líder ativo?", de id_mensagem = 1, ou "Me informe o valor de seu relógio", de id_mensagem = 3, ambos sem parâmetros enviados 
		else:
			mensagem = id_mensagem
		
		# Create the datagram socket
		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

		# Set a timeout so the socket does not block
		# indefinitely when trying to receive data.
		sock.settimeout(5)
		# Set the time-to-live for messages to 1 so they do not
		# go past the local network segment.
		ttl = struct.pack('b', 1)
		sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)
		try:
		    # Send data to the multicast group
			print('sending {!r}'.format(message))
			sent = sock.sendto(message, multicast_group)

		    # Look for responses from all recipients
			for i in range(0,10):
				print('waiting to receive')
				try:
					data, server = sock.recvfrom(16)
					respostas = data
				except socket.timeout:
					print('timed out, no more responses')
					break
				else:
					print('received {!r} from {}'.format(data, server))
		finally:
			print('closing socket')
			sock.close()

		return respostas

	def receber_mensagem(self, id_mensagem):
		#Entender isso e tratar cada tipo de mensagem
		multicast_group = '224.3.29.71'
		server_address = ('', 10000)

		# Create the socket
		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

		# Bind to the server address
		sock.bind(server_address)

		# Tell the operating system to add the socket to
		# the multicast group on all interfaces.
		group = socket.inet_aton(multicast_group)
		mreq = struct.pack('4sL', group, socket.INADDR_ANY)
		sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

		# Recebendo os diferentes tipos de mensagem dos processos conhecidos
		print('\nwaiting to receive message')
		data, address = sock.recvfrom(10)

		print('received {} from {}'.format(data, address))
		print(data)
		# Enviando os diferentes tipos de resposta
		if id_mensagem == 1 and self.lider and int(data) == 1 :
			print('Respondendo que sou líder para', address)
			sock.sendto('Sou líder', address)
		elif id_mensagem == 2:
			if int(data) < self.identificador:
				print('Respondendo que sou candidato a líder para', address)
				sock.sendto('Sou o novo candidato a líder', address)
				return True
			else:
				return False
		elif id_mensagem == 3 and int(data) == 3:
			print('Enviando valor do meu relógio interno para', address)
			sock.sendto(self.relogio_interno, address)
		elif id_mensagem == 4:
			self.relogio_interno = data			
			print('Informando que atualizei meu relógio interno para', address)
			sock.sendto('Atualizei meu relógio', address)

	def algoritmo_berkley(self):		
		# Perguntando aos processos o valor de seus relógios
		respostas = enviar_mensagem(3, 0)
		print ('relógio da outra máquina' + respostas)
		print ('meu relógio' + self.relogio_interno)
		# Calculando novo valor
		total_relogio = 0
		for resposta in respostas:
			total_relogio += resposta.valor_relogio
		relogio_atualizado = total_relogio / (len(respostas)+1)
		print ('novo relógio global' + relogio_atualizado)
		# Enviando ajuste aos relógios
		resposta = enviar_mensagem(4, relogio_atualizado)

#Iniciando Processo
processo = Processo(2, True, time.time(), [2])

#Iniciando Thread que incrementa relógio 
thread = threading.Thread(target=processo.incrementar_relogio, args=("Thread incrementar_relogio", 2))
thread.daemon = True
thread.start()

#Iniciando Funções do Processo
for i in range(0,10):
	print('aa')
	# Caso não exista líder o processo inicia eleição
	if processo.sem_lider():
		print('aaaaaccccc')
		processo.algoritmo_bully()
	# Se processo é o líder ele inicia sincronização de relógios
	if processo.lider:
		print('aabbbbbbbbbbb')
		processo.algoritmo_berkley()
	# Se processo não é lider ele espera para responder líder
	else:
		print('aaxxxxxxxxxxxxxx')
		# Responder valor do seu relógio
		processo.receber_mensagem(3)
		# Confirmar atualização do seu relógio
		print('aaaaacccccasasdasadasdas')
		processo.receber_mensagem(4)

#Finalizando Thread
thread.join()