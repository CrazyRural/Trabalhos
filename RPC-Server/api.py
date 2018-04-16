# -*- coding: utf-8 -*-

from SimpleXMLRPCServer import SimpleXMLRPCServer
from SimpleXMLRPCServer import SimpleXMLRPCRequestHandler
from config import config
import psycopg2
import sys

class API():
	
	def connect(self):
		conn = None
		try:
			params = config()
			print('Conectando ao banco de dados...')

			conn = psycopg2.connect(**params)
			cur = conn.cursor()
			cur.execute('SELECT version()')
			db_version = cur.fetchone()
			print(db_version)
			cur.close()

		except (Exception, psycopg2.DatabaseError) as error:
			print(error)

		finally:
			if conn is not None:
				print('Conexão estabelecida!')
				return conn, cur
	
	def adicionarNotaAlunoMateria(self, mat, cod, nota):
		self.cur = self.conn.cursor()
		cod = cod.upper()
		try:
			self.cur.execute('INSERT INTO tabelao VALUES ((%s), (%s), (%s))',(mat, cod, nota,))
			self.conn.commit()
			self.cur.close()
			return "Nota registrada com sucesso!"
		except Exception as e:
			params = config()
			self.conn = psycopg2.connect(**params)
			self.cur = self.conn.cursor()
			try:
				self.cur.execute('UPDATE tabelao SET nota = (%s) WHERE matricula ILIKE (%s) AND  materia ILIKE (%s)',(nota, mat, cod,))
				self.conn.commit()
				self.cur.close()
				return "Nota registrada com sucesso!"
			except Exception as e:
				pass

	def listarNotaAlunoMateria(self, cod, mat):
		self.cur = self.conn.cursor()
		cod = cod.upper()
		self.cur.execute('SELECT t.nota FROM public.tabelao t WHERE t.matricula ILIKE (%s) AND t.materia ILIKE (%s)',(mat, cod,))
		row = self.cur.fetchone()
		self.cur.close()
		if not row[0]:
			return "Aluno não possui nota nessa matéria."
		else:
			return "Aluno "+mat+ " tirou : "+ str(row[0])

	def consultarNotasAluno(self, mat):
		self.cur = self.conn.cursor()
		self.cur.execute('SELECT 1 FROM public.tabelao t WHERE t.matricula ILIKE (%s)',(mat,))
		row = self.cur.fetchone()
		a =[]
		if row > 0:
			a.append("Notas do Aluno: " + str(mat) + " -->")
			self.cur.execute('SELECT t.nota, t.materia FROM public.tabelao t WHERE t.matricula ILIKE (%s)',(mat,))
			rows = self.cur.fetchall()
			for row in rows:
				a.append("  " + str(row[1]) + ": " + (str(row[0]) if row[0] else "Nenhuma nota cadastrada"))
			self.cur.close()
		else:
			a.append("Aluno não encontrado")
		return a

	def consultarCR(self, mat):
		self.cur = self.conn.cursor()
		self.cur.execute('SELECT 1 FROM public.tabelao t WHERE t.matricula ILIKE (%s)',(mat,))
		row = self.cur.fetchone()
		if row > 0:
			self.cur.execute('SELECT (SUM(t.nota)/COUNT(t.matricula))::float AS media, t.matricula FROM public.tabelao t WHERE t.matricula ILIKE (%s) GROUP BY(t.matricula)',(mat,))
			rows = self.cur.fetchone()
			a = "CR do aluno "+mat+" é : "+ str(rows[0])			
		else:
			a = "Aluno não encontrado"
		return a

	def __init__(self):
		self.conn, self.cur = self.connect()

class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

class APIServer():

	global api
	api = API()	

	def cadastrarNota(self, mat, cod_disc, nota):
		return api.adicionarNotaAlunoMateria(mat, cod_disc, nota)
	

	def consultarNota(self, cod_disc, mat):
	    return api.listarNotaAlunoMateria(cod_disc, mat)
	

	def consultarNotas(self, mat):
	    return api.consultarNotasAluno(mat)
	

	def consultarCR(self, mat):
	    return api.consultarCR(mat)
	
	def start(self):		
		print("API rodando na porta 8000...")
		self.servidor.register_introspection_functions()
		self.servidor.register_function(self.cadastrarNota)
		self.servidor.register_function(self.consultarNota)
		self.servidor.register_function(self.consultarNotas)
		self.servidor.register_function(self.consultarCR)
		try:
			self.servidor.serve_forever()
		except (KeyboardInterrupt, SystemExit):
			print("Desligando API da porta 8000...")
			for i in range(0,15000000):
				x = i + 1
			print("\nBye!")
			sys.exit(0)

	def __init__(self):
		self.servidor = SimpleXMLRPCServer(("localhost", 8000), requestHandler=RequestHandler, allow_none=True)
		self.start()

s = APIServer()
