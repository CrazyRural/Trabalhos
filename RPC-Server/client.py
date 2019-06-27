# -*- coding: utf-8 -*-
import xmlrpc.client

global s
s = xmlrpc.client.ServerProxy('http://localhost:8000', allow_none=True)

s.system.listMethods()
def main():
	print("Aperte somente o ENTER a qualquer momento para sair de qualquer escolha e/ou do próprio menu principal.\n")
	while True:
		escrita = (input("\n1- Dar Nota ao Aluno em Curso\n2- Consultar Nota do Aluno\n3- Listar Notas do Aluno\n"+
							"4- CR do Aluno\nSua opção: "))
		if escrita == "":
			print("Bye!")
			break
		print(escrita)
		try:
			seleciona(escrita)()
		except Exception as e:
			print("Aperta direito imbecil")

def darNotaAoAluno():
	while True:
		try:
			matricula, materia, nota = map(str, input("Dar nota ao aluno(matricula, materia, nota): ").split(', '))
			try:
				a = s.cadastrarNota(matricula, materia, float(nota))
				print(a)
			except xmlrpc.client.Fault as err:
				print("A fault occurred")
				print("Fault code: %d"%err.faultCode)
				print("Fault string: %s"%err.faultString)
		except Exception as e:
			break

def notaDoAlunoMateria():
	while True:
		try:
			materia, matricula = map(str, input("Nota do aluno(materia, matricula): ").split(', '))
			try:
				a = s.consultarNota(materia, matricula)
				print(a)
			except xmlrpc.client.Fault as err:
				print("A fault occurred")
				print("Fault code: %d"%err.faultCode)
				print("Fault string: %s"%err.faultString)
		except Exception as e:
			break

def notasDoAluno():
	while  True:
		escrita = str(input("Digite uma matricula para ver as notas(matricula): "))
		if escrita != "":
			try:
				notas = s.consultarNotas(escrita)
				print(''.join(notas))
			except xmlrpc.client.Fault as err:
				print("A fault occurred")
				print("Fault code: %d" % err.faultCode)
				print("Fault string: %s" % err.faultString)
		else:
			break

def consultarCR():
	while  True:
		escrita = str(input("Consultar CR(matricula): "))
		if escrita != "":
			try:
				print(s.consultarCR(escrita))
			except xmlrpc.client.Fault as err:
				print("A fault occurred")
				print("Fault code: %d" % err.faultCode)
				print("Fault string: %s" % err.faultString)
		else:
			break

def seleciona(escrita):
	return {
	 		'1': darNotaAoAluno, 
	 		'2': notaDoAlunoMateria, 
	 		'3': notasDoAluno,
	 		'4': consultarCR
	 		}.get(escrita, "")

try:
	main()
except (KeyboardInterrupt, SystemExit):
	print("\nBye!")