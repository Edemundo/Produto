// Funções do programa que cadastro um produto em um comercio
#include "Produto.h"

bool PedirCodigoProduto(int *ptrCodigo, int nQuantidade, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;
	do
	{
		cout << "Código Produto (1 a " << nQuantidade << "): ";
		cin >> *ptrCodigo;														// recebe o código

		if(*ptrCodigo == 0)														// cancelou?
			return false;														// indica que cancelou

	} while( *ptrCodigo < 1 || *ptrCodigo > nQuantidade);
	return true;		
}

bool LerPosional(int nCodigo, PRODUTO *ptrStBuffer, FILE *fdProduto)
{
	if(fseek(fdProduto, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0)			// erro?
		return false;

	if(fread_s(ptrStBuffer, sizeof(PRODUTO), sizeof(PRODUTO), 1, fdProduto) == 0)	// erro?
		return false;
	
	return true;																	// indica tudo OK													

}

bool GravarPosicional(int nCodigo, PRODUTO *ptrBuffer, FILE *fdProduto)
{
	if(fseek(fdProduto, (nCodigo - 1), SEEK_SET) != 0)							// erro de seek?
		return false;
	if(fwrite(ptrBuffer, sizeof(PRODUTO), 1, fdProduto) == 0)					// erro de gravação
		return false;

	if(nCodigo != ptrBuffer->nCodigo)											// não é o produto buscado
		return false;
	return true;
}