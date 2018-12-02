# necessita ter o modulo openpyxl instalado para funcionar
from openpyxl import load_workbook

wb = load_workbook('tabela.XLSX') # tabela

target = wb.active # tabela ativa

tabela = []

#guarda valores da tabela em uma matriz
for row in target.values:
	linha = []
	for values in row:
		linha.append(values)
	tabela.append(linha)

tabela_processada = []
rotulo = 0

for i in range(len(tabela[0])):

	linha_processada = []
	
	if(tabela[0][i] == 'MaleAge'): #idade do homem
		linha_processada.append('A')
		for j in range(1,566):
			if(tabela[j][i] <= 60):
				linha_processada.append('IF')
			else:
				linha_processada.append('II')
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'exercism'): #homem pratica esporte
		linha_processada.append('B')
		for j in range(1,566):
			linha_processada.append(tabela[j][i])
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'smoknowm'): #fuma
		linha_processada.append('C')
		for j in range(1,566):
			linha_processada.append(tabela[j][i])
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'alcohlm'): #bebe
		linha_processada.append('D')
		for j in range(1,566):
			if(tabela[j][i] >= 3):
				linha_processada.append(1)
			else:
				linha_processada.append(0)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'grassm'): #usa alguma droga
		linha_processada.append('E')
		for j in range(1,566):
			if(tabela[j][i] >= 2 or tabela[j][i+1] >= 1 or tabela[j][i+2] >= 1 or tabela[j][i+3] >= 1 or tabela[j][i+4] >= 1 or tabela[j][i+5] >= 1 or tabela[j][i+6] >= 1 or tabela[j][i+7] >= 1):
				linha_processada.append(1)
			else:
				linha_processada.append(0)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'reprodum'): #tem problema reprodutivo
		linha_processada.append('F')
		for j in range(1,566):
			linha_processada.append(tabela[j][i])
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'vasectom'): #fez vasectomia
		linha_processada.append('G')
		for j in range(1,566):
			linha_processada.append(tabela[j][i])
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'stdm'): #foi diagnosticado com alguma std
		linha_processada.append('H')
		for j in range(1,566):
			linha_processada.append(tabela[j][i])
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'infertm'): #foi dito ao homem que ele era infertil
		linha_processada.append('I')
		for j in range(1,566):
			linha_processada.append(tabela[j][i])
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'Femaleage'): #idade da mulher
		linha_processada.append('J')
		for j in range(1,566):
			if(tabela[j][i] >= 35):
				linha_processada.append('II')
			else:
				linha_processada.append('IF')
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'sporty1f'): #mulher pratica esporte
		linha_processada.append('K')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020"):
				linha_processada.append(0)
			elif(tabela[j][i]>=1):
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'smnownuf'): #mulher fuma
		linha_processada.append('L')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020"):
				linha_processada.append(0)
			elif(tabela[j][i]>=1):
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'alcoholf'): #mulher bebe
		linha_processada.append('M')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020" or tabela[j][i] < 3):
				linha_processada.append(0)
			elif(tabela[j][i]>=3):
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'grassf'): #mulher usa alguma droga
		linha_processada.append('N')
		for j in range(1,566):
			if(tabela[j][i] >= 2 or tabela[j][i+1] != u"\u0020" or tabela[j][i+2] != u"\u0020" or tabela[j][i+3] != u"\u0020" or tabela[j][i+4] != u"\u0020" or tabela[j][i+5] != u"\u0020" or tabela[j][i+6] != u"\u0020" or tabela[j][i+7] != u"\u0020"):
				linha_processada.append(1)
			else:
				linha_processada.append(0)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'reprtypf'): #mulher tem problemas reprodutivos
		linha_processada.append('O')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020"):
				linha_processada.append(0)
			else:
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'tuballig'): #mulher teve tubas ligadas
		linha_processada.append('P')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020"):
				linha_processada.append(0)
			else:
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'stdf'): #mulher tem historico de dst
		linha_processada.append('Q')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020"):
				linha_processada.append(0)
			else:
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'infertf'): #historico de infertilidade
		linha_processada.append('R')
		for j in range(1,566):
			if(tabela[j][i] == u"\u0020"):
				linha_processada.append(0)
			else:
				linha_processada.append(1)
		tabela_processada.append(linha_processada)

	if(tabela[0][i] == 'POSNEG'):
		rotulo = i

linha_processada = []

linha_processada.append('engravidou')

for i in range(1,566): #teste do rotulo

	if(tabela[i][rotulo] == 'P' or tabela[i][rotulo] == 'PBD' or tabela[i][rotulo] == 'PS'):
		linha_processada.append(1)

	elif(tabela[i][rotulo+1] == 'P' or tabela[i][rotulo+1] == 'PBD' or tabela[i][rotulo+1] == 'PS'):
		linha_processada.append(1)

	elif(tabela[i][rotulo+2] == 'P' or tabela[i][rotulo+2] == 'PBD' or tabela[i][rotulo+2] == 'PS'):
		linha_processada.append(1)

	else:
		linha_processada.append(0)

tabela_processada.append(linha_processada)

f = open('tabela_processada.txt', 'w+')

f.write('\n'.join(['\t'.join([str(x[i]) if len(x) > i else '' for x in tabela_processada]) for i in range(len(max(tabela_processada)))]))




		

		

		
			



 



