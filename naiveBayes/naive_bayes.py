from numpy import prod

f = open('tabela_processada.txt')
f2 = open('resultado.txt','w+')

dados = f.read()
dados = dados.replace('\t','')

#criando matriz de dados
matriz_dados = []
for i in range(19):
	coluna = []
	matriz_dados.append(coluna)

#preenchendo matriz de dados
linha = 0
for i in range(len(dados)):
	if(dados[i] != '\n'):
		matriz_dados[linha].append(dados[i])
		linha = linha+1
	else:
		linha = 0

while(1):
	query = []
	resp = raw_input('Entre com a idade do homem:')
	query.append(resp)
	resp = raw_input('O homem pratica exercicio fisico? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem fuma? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem bebe? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem usa alguma droga? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem tem algum problema reprodutivo? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem fez vasetomia? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem foi diagnosticado com alguma DST? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('O homem tem historico de infertilidade? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('Entre com a idade da mulher:')
	query.append(resp)
	resp = raw_input('A mulher pratica exercicio fisico? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher fuma? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher bebe? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher usa alguma droga? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher tem algum problema reprodutivo? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher teve as tubas ligadas? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher foi diagnosticado com alguma DST? (1 para sim, 0 para nao):')
	query.append(resp)
	resp = raw_input('A mulher tem historico de infertilidade? (1 para sim, 0 para nao):')
	query.append(resp)

	#executando o naive bayes

	qnt_pos = 0
	qnt_neg = 0

	#calcula a quantidade de instancias positivas e negativas
	for i in range(len(matriz_dados[0])):
		if(matriz_dados[18][i] == '0'):
			qnt_neg = qnt_neg+1
		else:
			qnt_pos = qnt_pos+1

	p_fertil = 1
	p_infertil = 1

	for i in range(len(query)):
		nominador_pos = 0 #parte de cima de fracao de cada P(An|POS)
		nominador_neg = 0 #parte de cima de fracao de cada P(An|NEG)

		for j in range(len(matriz_dados[0])):

			if(matriz_dados[i][j] == query[i] and matriz_dados[18][j] == '1'):
				nominador_pos = nominador_pos + 1

			elif(matriz_dados[i][j] == query[i] and matriz_dados[18][j] == '0'): #P(Ai|0)
				nominador_neg = nominador_neg + 1

		p_fertil = p_fertil*(nominador_pos/(qnt_pos/1.0))
		p_infertil = p_infertil*(nominador_neg/(qnt_neg/1.0))	

			
	p_fertil = p_fertil*((qnt_pos)/(565/1.0))
	p_infertil = p_infertil*((qnt_neg)/(565/1.0))

	print('\n')

	if(p_fertil>p_infertil):
		f2.write('1' + '\n')
	else:
		f2.write('0' + '\n')
		
		


			
	
	
	



	
	
	
	


