// Programa de teste de dois arquivos
// FATEC - MC - VSGM - 24/05/17 - Vers�o 0.0

#include "Produto.h"

//
// entry point do programa
//
void main(void)
{

	int i,																		// indexador e contador
		nQtde,																	// para receber a quantidade
		nCodigo;																// para receber o codigo do cliente
	char cWork[200],															// para uso do sprintf_s
			cOpcao;																// op��o do operador
	SYSTEMTIME stTime;															// para receber data e hora
	QUANTIDADE stQuantidade;													// struct que conter� a quantidade configurada
	PRODUTO stProduto;															// struct para os dados de um produto
	FILE *fdQtde,																// file descriptor do arquivo com a quantidade
		*fdProduto;																// file descriptor do arquivo de produtos

	PAIS_BRASIL;																// acentua��o brasileira

	// abri o arquivo de quantidade para saber se � a primeira vez do programa
	if(fopen_s(&fdQtde, CAMINHO_QTDE, "rb") != 0) // erro de abertura?
	{ 
		// o arquivo n�o existe - � a primeira vez
		if(fopen_s(&fdQtde, CAMINHO_QTDE, "wb") != 0)							// erro de abertura?
		{
			cout << "Erro de abertura do arquivo: " << CAMINHO_QTDE << endl;
			PAUSA;
			return;																// volta ao S.O.
		}
		
		do
		{
			cout << "Quantidade de produtos entre" << QTDE_MINIMA_PRODUTOS <<
				" e " << QTDE_MAXIMA_PRODUTOS << endl
				<< "Ou zero para cancelar a execu��o do programa: ";
			cin >> stQuantidade.nQuantidade;									// aceita a quantidade de produtos
			if(stQuantidade.nQuantidade == 0)									// cancelar?
				return;															// volta ao sistema operacional

		} while(stQuantidade.nQuantidade < QTDE_MINIMA_PRODUTOS || 
			stQuantidade.nQuantidade > QTDE_MAXIMA_PRODUTOS);

		// temos uma quantidade v�lida gravar e fechar o arquivo
		if(fwrite(&stQuantidade, sizeof(QUANTIDADE), 1, fdQtde) == 0)			// erro de grava��o?
		{
			cout << "Erro de grava��o de quantidade!" << endl;
			fclose(fdQtde);														// fechar o arquivo
			return;																// sair do programa
		}
		fclose(fdQtde);															// fecha o arquivo de quantidade
	}
	// loop de formata��o do arquivo de produtos
	if(fopen_s(&fdProduto, CAMINHO_PRODUTO, "rb") != 0)							// erro de abertura?
	{ 
		// o arquivo n�o existe - � a primeira vez
		if (fopen_s(&fdProduto, CAMINHO_PRODUTO, "wb") != 0)						// erro de abertura?
		{
			cout << "Erro de abertura do arquivo: " << CAMINHO_PRODUTO << endl;
			PAUSA;
			fclose(fdProduto);
			return;																// volta ao S.O.
		}

		for(i = 0; i < stQuantidade.nQuantidade; i++)							// loop de "formata��o" do cadastro
		{
			stProduto.cAtivo = INATIVO;											// produto inativo
			stProduto.nCodigo = i + 1;											// 1, 2, 3,.....QTDE_PRODUTO
			if(fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0)			// erro de grava��o?
			{
				// erro de grava��o
				fclose(fdProduto);												// fechar o arquivo
				cout << "Erro de leitura!" << endl;
				PAUSA;
				fclose(fdProduto);
				return;															// volta ao S.O.

			} // end if

		} // for i

	} // o arquivo de qtde n�o existe
	else																		// o arquivo de quantidade existe
	{
		if(fopen_s(&fdProduto, CAMINHO_PRODUTO, "rb") != 0)						// erro de abertura?
		{
			cout << "Erro de abertura do arquivo: " << CAMINHO_PRODUTO << endl;
			PAUSA;
			fclose(fdProduto);
			return;																// volta ao S.O.
		}

		if (fread(&stQuantidade, sizeof(QUANTIDADE), 1, fdQtde) == 0) {
			cout << "Erro de leitura do arquivo " << CAMINHO_QTDE << endl;
			return;
		}
	}

	nQtde = stQuantidade.nQuantidade;
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);													// data e hora do sistema
		sprintf_s(cWork, sizeof(cWork),
			"\n\tFATEC-MC - Sistema de Cadastramento de Clientes %02d/%02d/%04d %02d:%02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond);
		cout << cWork << endl;
		
		cout << INCLUIR_PRODUTO << " - Incluir novo Produto " << endl;
		cout << EXCLUIR_PRODUTO << " - Excluir um Produto " << endl;
        cout << MOSTRAR_PRODUTO << " - Mostrar um Produto " << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do Programa " << endl;

		cout << "\tSelecione: ";
		cin >> cOpcao;															// op��o do operador
		cOpcao = toupper(cOpcao);												// converte para  mai�scula

		switch(cOpcao)															// avalia a op��o escolhida
		{
			case INCLUIR_PRODUTO:
				if(!PedirCodigoProduto(&nCodigo, nQtde, "Incluir Produto"))	// cancelou a opera��o?
					break;														// volta ao menu

				if(!LerPosional(nCodigo, &stProduto, fdProduto))				// houve erro?
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if(stProduto.cAtivo == ATIVO)									// produto ja ativo?
				{
					cout << "Produto: " << stProduto.nCodigo << " - " <<
						stProduto.cNome;
					cout << "Produto Ativo!";
					PAUSA;
					break;														// volta ao menu
				}
				
				// produto inativo
				cin.ignore(1, EOF);												// ignora a tecla Enter anterior
				cout << "Nome do Produto: ";
				cin.getline(stProduto.cNome, TAMANHO_NOME, '\n');
				cout << "Pre�o do Produto: " ;
				cin >> stProduto.dPrecoUnit;
				stProduto.cAtivo = ATIVO;										// cliente ativo
				cin.ignore(1, EOF);												// ignora a tecla Enter anterior
				cout << "Nome do Produto: ";
				cin.getline(stProduto.cDescricao, TAMANHO_DESCR, '\n');

				if(!GravarPosicional(nCodigo, &stProduto, fdProduto))			// erro?
				{

					cout << "Erro de Grava��o!" << endl;
					PAUSA;
				}

				break;
			
			case EXCLUIR_PRODUTO:
				break;
			
			case MOSTRAR_PRODUTO:
				break;
			
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;

				if (cOpcao == 's' || cOpcao == 'S')
					return;														// volta ao S.O.

				break;															// volta ao menu
			
			default:
				cout << "Digite uma op��o v�lida!!" << endl;
				PAUSA;
				break;

		} // switch

	} // while(true)

} // main