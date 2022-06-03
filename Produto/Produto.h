// Declara��es do programa de teste de arquivos
#include <iostream>
#include <Windows.h>
using namespace std;

// defini��es do programa
#define PAUSA																		system("pause")
#define LIMPAR_TELA																	system("cls")
#define QTDE_MAXIMA_PRODUTOS														10000
#define QTDE_MINIMA_PRODUTOS														1000
#define PAIS_BRASIL																	setlocale(LC_ALL, "portuguese_brazil")
#define CAMINHO_QTDE																"..\\Quantidade.qtd"
#define CAMINHO_PRODUTO																"..\\Produto.cad"
#define ATIVO																		'A'
#define INATIVO																		'I'
#define TAMANHO_DESCR																40
#define TAMANHO_NOME																40

// op��es do menu
#define INCLUIR_PRODUTO																'I'
#define EXCLUIR_PRODUTO																'E'
#define MOSTRAR_PRODUTO																'M'
#define	SAIR_DO_PROGRAMA															'S'

//
// struct do produto
//
typedef struct tagPRODUTO
{
	int nCodigo;																	// c�digo de 1, 2, 3, .... at� a qtd dimensionada
	char cAtivo,																	// Produto ativo = 'A' e inativo = 'I'
		cNome[TAMANHO_NOME + 1],													// Para receber o nome do produto
		cDescricao[TAMANHO_DESCR + 1];												// descri��o do produto
	double dPrecoUnit;																// Pre�o unitario
} PRODUTO;

//
// struct da quantidade
//
typedef struct tagQUANTIDADE
{
	int nQuantidade;																	// quantidade dimensionada de produtos
} QUANTIDADE;

// Prototipos das fun��es
bool LerPosional(int nCodigo, PRODUTO *ptrBuffer, FILE *fdProduto);
bool GravarPosicional(int nCodigo, PRODUTO *ptrBuffer, FILE *fdProduto);
bool PedirCodigoProduto(int *ptrCodigo, int ptrQuantidade, char *ptrTransacao);