#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <map>
#include <utility>

using namespace std;

fstream saida;
vector <string> labels;
vector <int> contAtrib;
int contneg = 0;
int contpos = 0;

vector <int> originais;
map <string, int> indices;


/************************Cria Arvore***********************/
vector< vector<int> > le_entrada(){
	vector< vector<int> > S;
	fstream tabela;
	fstream legenda;
	tabela.open("tabela_processada.csv", ios::in);
	legenda.open("atributos.csv", ios::in);

	if (tabela.is_open()){
		string linha;
		int i = 0;
		getline(tabela, linha);
		while(getline(tabela, linha)){
			vector <int> instancia;
			stringstream token(linha);
			string atributo;
			while(getline(token, atributo, '\t')){
				instancia.push_back(atoi(atributo.c_str()));
			}
			S.push_back(instancia);
			i++;
		}
	} else {
		cout << "Erro: Abrir arquivo da base de dados!\n";
	}
	if (legenda.is_open()){
		string linha;
		getline(legenda, linha);
		stringstream token(linha);
		string atributo;
		while(getline(token, atributo, ',')){
			labels.push_back(atributo);
			contAtrib.push_back(0);
		}
	} else {
		cout << "Erro: Abrir arquivo com legenda dos atributos\n";
	}
	return S;
}

double entropia(vector< vector <int> >S) {
	double pos = 0.0;
	double neg = 0.0;
	for (int i = 0; i<S.size(); i++){
		if (S[i][S[i].size()-1]==1){
			pos++;
		} else {
			neg++;
		}
	}

	if (pos==0 || neg==0){
		return 0;
	}
	pos /= S.size();
	neg /= S.size();

	return - pos*log2(pos) - neg*log2(neg);
}

double somatorio(int a, vector< vector <int> >S){
	vector< vector <int> >Sv;
	double sum = 0.0;
	
	for (int v = 0; v<2; v++){
		for (int j = 0; j<S.size(); j++){
			if (S[j][a]==v){
				Sv.push_back(S[j]);
			}
		}

		sum += ((double)Sv.size()/(double)S.size())*entropia(Sv);
		Sv.clear();
	}

	return sum;
}

double ganho(vector< vector <int> >S, int a){
	return entropia(S) - somatorio(a, S);
}

string criar_no(vector< vector<int> > S, set <int> desconsiderar){ 
	bool pos = false;
	bool neg = false;
	for (int i = 0; i<S.size(); i++){
		if (S[i][S[i].size()-1]==1){
			pos = true;
		} else {
			neg = true;
		}
	}
	if (pos && !neg){ //conjunto so com casos positivos
		//retorna no positivo
		stringstream retorno;
		retorno << "sim" << contpos;
		contpos++;
		return retorno.str();
	} else if (!pos && neg) {
		//retorna no negativo
		stringstream retorno;
		retorno << "nao" << contneg;
		contneg++;
		return retorno.str();
	}

	if (desconsiderar.size()==S[0].size()-1){ //nao tem mais atributos a serem considerados
		int p = 0;
		int n = 0;
		for (int i = 0; i<S.size(); i++){
			if (S[i][S[i].size()-1]==1){
				p++;
			} else {
				n++;
			}
		}
		if (p>=n){
			//retorna no positivo
			stringstream retorno;
			retorno << "sim" << contpos;
			contpos++;
			return retorno.str();
		} else {
			//retorna no negativo
			stringstream retorno;
			retorno << "nao" << contneg;
			contneg++;
			return retorno.str();
		}
	}

	double max_ganho = 0.0;
	int melhor, a;
	for (a = 0; a<S[0].size()-1; a++){
		if (desconsiderar.find(a)==desconsiderar.end()){
			double g = ganho(S, a);
			if (max_ganho<=g){
				max_ganho = g;
				melhor = a;
			}
		}
	}

	desconsiderar.insert(melhor);

	vector < vector<int> > novoS[2];
	for (int i = 0; i<S.size(); i++){
		novoS[S[i][melhor]].push_back(S[i]);
	}
	for (int v = 0; v<2; v++){
		if (novoS[v].size()==0){
			int p = 0;
			int n = 0;
			for (int i = 0; i<S.size(); i++){
				if (S[i][S[i].size()-1]==1){
					p++;
				} else {
					n++;
				}
			}
			if (p>=n){
				//cria positivo em branch v
				saida << labels[melhor] << contAtrib[melhor] << "->sim" << contpos << "[label=" << v << "]" << endl;
				contpos++;
			} else {
				//cria negativo em branch v
				saida << labels[melhor] << contAtrib[melhor] << "->nao" << contneg << "[label=" << v << "]" << endl;
				contneg++;
			}
		} else {
			string ret = criar_no(novoS[v], desconsiderar);
			saida << labels[melhor] << contAtrib[melhor] << "->" <<  ret << "[label=" << v << "]" << endl;
		}
	}
	stringstream retmelhor;
	retmelhor << labels[melhor] << contAtrib[melhor];
	contAtrib[melhor]++;
	return retmelhor.str();
}

bool criar_arvore(vector < vector <int> > S){
	saida.open("arvore_decisao.dot", ios::out);
	if (saida.is_open()){
		saida << "digraph {" << endl;
		set <int> desconsiderar;
		criar_no(S, desconsiderar);
		for (int i = 0; i<contpos; i++){
			saida << "sim" << i << "[fontcolor=white, color=green]" << endl;
		}
		for (int i = 0; i<contneg; i++){
			saida << "nao" << i << "[fontcolor=white, color=red]" << endl;
		}
		saida << "}" << endl;
		saida.close();
		return true;
	} else {
		cout << "Erro: Abrir arquivo de saida!" << endl;
	}
	return false;
}


/**********************Classificacao************************/
vector < vector<int> > le_arvore(){
	fstream legenda;
	legenda.open("atributos.csv", ios::in);
	if (legenda.is_open()){
		string linha;
		getline(legenda, linha);
		stringstream token(linha);
		string atributo;
		while(getline(token, atributo, ',')){
			labels.push_back(atributo);
		}
	} else {
		cout << "Erro: Abrir arquivo com legenda dos atributos\n";
	}

	int cont = 1;
	vector< vector<int> > arvoreGrafo;
	fstream arvore;
	arvore.open("arvore_decisao.dot", ios::in);
	if(arvore.is_open()){
		string linha;
		getline(arvore, linha);
		while(getline(arvore, linha)){
			if (linha[0]=='s' || linha[0]=='n'){
				break;
			}
			stringstream arco(linha);
			string origem = "";
			string destino = "";
			char letra;
			arco.get(letra);
			do{
				origem+=letra;
				arco.get(letra);
			}while(letra!='-');
			arco.get(letra); //>
			arco.get(letra);
			do{
				destino+=letra;
				arco.get(letra);
			} while(letra!='[');

			//cria arco origem -> destino
			if (indices[origem]==0){
				indices[origem] = cont;
				for (int i = 0; i<labels.size(); i++){
					if (origem.find(labels[i])!=string::npos){
						originais.push_back(i);
						break;
					}
				}

				cont++;
				vector <int> vazio;
				arvoreGrafo.push_back(vazio);
			}
			if (indices[destino]==0){
				if(destino.find("sim")!=string::npos){
					indices[destino] = -1;
				} else if (destino.find("nao")!=string::npos){
					indices[destino] = -2;
				} else {
					indices[destino] = cont;
					for (int i = 0; i<labels.size(); i++){
						if (destino.find(labels[i])!=string::npos){
							originais.push_back(i);
							break;
						}
					}

					cont++;
				}
			}
			if (indices[destino]>0){
				arvoreGrafo[indices[origem]-1].push_back(indices[destino]-1);
			} else {
				arvoreGrafo[indices[origem]-1].push_back(indices[destino]);
			}

		}
	} else {
		cout << "Erro: Abrir arquivo da arvore!" << endl;
	}
	return arvoreGrafo;
}

int classifica(vector<int> instancia, vector < vector<int> > arvoreGrafo){
	//quando percorrer, lembrar que -1 eh sim e -2 eh nao
	int atualInst = 17;
	int atual = indices["infertM0"]-1;
	while(arvoreGrafo[atual][instancia[atualInst]]!=-1 && arvoreGrafo[atual][instancia[atualInst]]!=-2){
		atual = arvoreGrafo[atual][instancia[atualInst]];
		atualInst = originais[atual];
	}

	if (arvoreGrafo[atual][instancia[atualInst]]==-1){
		return 1;
	}
	return 0;
}


/**************************Validacao************************/
vector < pair <double, double> > kfold(vector< vector<int> > S, int k){
	vector < vector<int> > arvoreGrafo = le_arvore();
	
	vector < pair<double, double> > pontosRetorno;
	pair <double, double> ponto;

	int confusao[2][2] = {{0, 0}, {0, 0}};
	int cont = 0;
	int tamFold = S.size()/k;
	
	while(S.size()>0){
		if (cont == tamFold && k>1){
			ponto.first = (double)confusao[0][1]/(double)(confusao[0][1]+confusao[0][0]); //TFP
			ponto.second = (double)confusao[1][1]/(double)(confusao[1][1]+confusao[1][0]); //TVP
			pontosRetorno.push_back(ponto);
			for (int i = 0; i<2; i++){
				for (int j = 0; j<2; j++){
					confusao[i][j] = 0;
				}
			}
			cont = 0;
			k--;
		}
		int inst = rand()%S.size();
		int ret = classifica(S[inst], arvoreGrafo);
		confusao[S[inst][S[inst].size()-1]][ret]++;
		S.erase(S.begin()+inst);
		cont++;
	}

	ponto.first = (double)confusao[0][1]/(double)(confusao[0][1]+confusao[0][0]); //TFP
	ponto.second = (double)confusao[1][1]/(double)(confusao[1][1]+confusao[1][0]); //TVP
	pontosRetorno.push_back(ponto);

	return pontosRetorno;
}

int main(int argc, char* argv[]){
	if (argc>1){
		if (atoi(argv[1])==0){
			vector < vector <int> > S = le_entrada();
			if (criar_arvore(S)){
				cout << "Arvore criada com sucesso!" << endl;
			}
		} else if (atoi(argv[1])>1) {
			int k = atoi(argv[1]);
			vector< vector<int> > S = le_entrada();
			vector <pair < double, double> > pontos = kfold(S, k);
			cout << k << "-fold:\n";
			for (int i = 0; i<pontos.size(); i++){
				cout << "(" << pontos[i].first << " ; " << pontos[i].second << ")\t";
			}
			cout << endl;
		} else {	
			vector < vector<int> > arvoreGrafo = le_arvore();

			for (int i = 0; i<labels.size(); i++){
				cout << labels[i] << " ";
			}
			cout << endl;

			int entrada;
			while(cin>>entrada, entrada!=-1){
				int v;
				vector <int> instancia;
				instancia.push_back(entrada);
				for (int i = 1; i<18; i++){
					cin >> v;
					instancia.push_back(v);
				}
				if (classifica(instancia, arvoreGrafo)==1){
					cout << "Engravida" << endl << endl;
				} else {
					cout << "Nao Engravida" << endl << endl;
				}
			}
		}
	}
}