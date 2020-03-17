/* TRABALHO FINAL DE LGP - 2016/2
 Aluna: Gabrielle Souza Favero */
	
	#include <stdio.h> 
	#include <stdlib.h>
	#include <string.h>
	#include <conio.c>
	#include <locale.h>

	void GravaCadastro (int num);
	void LeCadastro (int num);      /* Protótipos de todas as funções usadas*/
	void PesquisaItem ();
	void ApagaTudo ();

	typedef struct Dataltr DATALTR; /* Definição da estrutura e estrutura que guarda as datas das leituras dos livros */
	struct Dataltr
	{
		int dia;
		int mes;
		int ano;
	};
	
	typedef struct livro LIVRO; /* Definição da estrutura e estrutura que guarda os dados dos livros */
	struct livro
	{
		char titulo[300];
		char autor[300];
		char editora[300];
		int ano;
		int edicao;
		DATALTR data;
	};
	struct livro *l; /* Ponteiro para a estrutura */
	
/* PRINCIPAL: */
int main (void)
{
	setlocale(LC_ALL, "Portuguese"); /* Para funcionar acentos e afins... */
	int opcao, quant; /* Variáveis que fazem parte do programa principal: opção do menu escolhida, e quantidade de cadastros para alocar na memória */
	
	/* Início do menu */
	while (opcao!=5) /* while que mostra o menu após o fim das funções, até que o usuário escolha sair, ou digite uma opção inválida */
	{ 
		system ("cls");
		textcolor(11);
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("          x                                                          x\n");
		printf("          x             >>      BIBLIOTECA PESSOAL      <<           x\n");
		printf("          x                                                          x\n");
		printf("          x                       >> MENU <<                         x\n");
		printf("          x                                                          x\n");
		printf("          x              1 - INCLUIR NOVO LIVRO                      x\n");
		printf("          x              2 - VER LIVROS JÁ LIDOS                     x\n");
		printf("          x              3 - PESQUISAR UM LIVRO                      x\n");
		printf("          x              4 - APAGAR TODOS OS LIVROS CADASTRADOS      x\n");
		printf("          x              5 - SAIR                                    x\n");
		printf("          x                                                          x\n");
		printf("          x                                                          x\n");
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
		textcolor(15);
		printf(" Opcao selecionada: ");
		textcolor(3);
		scanf("%d", &opcao);

	/* Início do switch case do menu */
		switch (opcao)
		{
			case 1:	
			{
			/* cadastrar livros */
				system ("cls");	
				textcolor(15);
				
				printf("\n  >>>  Digite o numero livros a serem cadastrados: ");
				scanf("%d", &quant);  /* Leitura do número de itens a serem cadastrados, para alocar na memória */
				l = (struct livro *) malloc (quant * sizeof(struct livro)); /* Alocação da memória */	

				GravaCadastro(quant); /* Chamada da função para inserir os dados dos livros */
				
				textcolor(11);
				printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				printf("          x   >>   PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU   <<  x\n");
				printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				getch(); 
				break;
			};
			
			case 2:	
			{
			/* vizualizar os livros cadastrados */
				system ("cls");
				
				LeCadastro(quant); /* Chamada da função para ver os livros cadastrados */
				
				textcolor(11);
				printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				printf("          x   >>   PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU   <<  x\n");
				printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				getch(); 
				break;
			};
			
			case 3:
			{
			/* Pesquisar um livro pelo nome */
				system ("cls");
				
				PesquisaItem(); /* Chamada da função de pesquisa */
				
				textcolor(11);
				printf("\n\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				printf("          x   >>   PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU   <<  x\n");
				printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				getch(); 
				break;
			};
			
			case 4: 
			{
			/* Apagar todos os livros que foram cadastrados */
				system ("cls");
				
				ApagaTudo(); /* Chamada da função que apaga os cadastros */
				
				textcolor(11);
				printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				printf("          x   >>   PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU   <<  x\n");
				printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
				getch(); 
				break;
			};				
		}; /* Fim do switch case do menu */
	}; /* Fim do while do menu */
		
	if(opcao==5)   /* Opção para sair */
	{
		system ("cls");
		textcolor(11);
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("          x                                                           x\n");
		printf("          x                   >>>   ENCERRANDO   <<<                  x\n");
		printf("          x                                                           x\n");
		printf("          x                                                           x\n");
		printf("          x          > PARA FECHAR PRESSIONE QUALQUER TECLA <         x\n");
		printf("          x                                                           x\n");
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
	};

	if(opcao>5 || opcao<1)   /* Caso a opção digitada seja um número inválido */
	{
		system ("cls");
		textcolor(11);
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("          x                                                           x\n");
		printf("          x                >>>   OPÇÃO INVÁLIDA!   <<<                x\n");
		printf("          x                                                           x\n");
		printf("          x                                                           x\n");
		printf("          x          > PARA VOLTAR PRESSIONE QUALQUER TECLA <         x\n");
		printf("          x                                                           x\n");
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
		getch();
					
	}
	
	system ("pause");
	return 0;
}

/* FUNÇÕES: */

void GravaCadastro (int num) 
	{
	/* Inserir um cadastro */
		int i; /* contador para o for */
		FILE *arq; /* aqruivo */
		LIVRO livro; /* nomeando a struct livro */
		arq = fopen("ArquivoCadastro.txt","ab"); /* abrindo o arquivo, usei "ab" para criar o arquivo se inexistente, e adicionar novos dados ao final dele caso já contenha algum */
	
	/* Caso o arquivo não funcione como desejado */
		if (!arq)
		{
		textcolor(15);
		printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("          x   >>            ERRO NA ABERTURA DO ARQUIVO!          <<  x\n"); 
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		}
		else
		{
			for (i=0; i<num; i++) /* repetição para inserir o numero de cadastros digitado pelo usuário */
			{
				system ("cls");
				/* Pegando os dados */
				textcolor(11);
				fflush(stdin);  /* Limpar o buffer do teclado antes de inserir uma string */ 
				textcolor(15);
				printf("\n------------------------------------- [%.2d] -------------------------------------",i+1);	/* Enumeração dos cadastros  */
				printf("\n >> Título do livro: ");
				textcolor(3);
				gets(livro.titulo);
							
				fflush(stdin);
				textcolor(15);
				printf("\n >> Autor do livro: ");
				textcolor(3);
				gets(livro.autor);
			
				fflush(stdin);
				textcolor(15);
				printf("\n >> Nome da editora: ");
				textcolor(3);
				gets(livro.editora);
				
				textcolor(15);
				printf("\n >> Ano de publicação: ");
				textcolor(3);
				scanf("%d",&livro.ano);
				
				textcolor(15);
				printf("\n >> Edição do livro: ");
				textcolor(3);
				scanf("%d",&livro.edicao);
				
				textcolor(15);
				printf("\n >> Data do término da leitura (dd mm aaaa): ");
				textcolor(3);
				scanf("%d %d %d",&livro.data.dia,&livro.data.mes,&livro.data.ano);
				
				fwrite(&livro, sizeof(livro),1,arq); /* Salvando os dados no arquivo "arq" */
			}
			fclose(arq); /* Fechando o arquivo */
		}
	}
	
	
	void LeCadastro (int tam)
	{
	/* vizualizar todos os cadastros */
		system ("cls");
		int i=0; /* contador para o for */
		FILE *arq; /* arquivo */
		LIVRO livro; /* nomeando a struct livro */
		arq = fopen("ArquivoCadastro.txt","rb"); /* abrindo o arquivo para leitura*/
		
		
		if (arq == NULL) /* Caso o arquivo retorne vazio */
		{
		textcolor(15);
		printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("          x   >>          NÃO HÁ NENHUM LIVRO CADASTRADO!         <<  x\n"); 
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		}
		else
		{	
			textcolor(11);
			printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			printf("          x                                                           x\n");
			printf("          x            >>>   LIVROS QUE VOCÊ JÁ LEU   <<<             x\n");
			printf("          x                                                           x\n");
			printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
			
			while (fread(&livro, sizeof (livro),1,arq)==1) /* while para ler do arquivo e reproduzir os comandos até que chegue ao fim do arquivo */
			{
				textcolor(15);
				printf("------------------------------------- [%.2d] -------------------------------------\n",i+1);
				textcolor(3);
				printf(" >> Título do livro: %s",livro.titulo);	
				printf("\n >> Autor do livro: %s",livro.autor);
				printf("\n >> Nome da editora: %s",livro.editora);
				printf("\n >> Ano de publicação: %d",livro.ano);
				printf("\n >> Edição do livro: %d",livro.edicao);	
				printf("\n >> Data do término da leitura: %d/%d/%d",livro.data.dia,livro.data.mes,livro.data.ano);
				printf("\n\n");
				i++;
			}
		
		
		
		}
		
		fclose(arq); /* Fechando o arquivo */
	}
		
	void PesquisaItem ()
	{
	/* pesquisar um cadastro por nome  */
	
		system ("cls");
		FILE *arq;
		LIVRO livro;
		char pesqlivro[300]; 	/* char para inserir o titulo do livro */
		int op;
		
		arq = fopen("ArquivoCadastro.txt","rb"); /* abrindo o arquivo*/
			
		if (arq == NULL)  /* Caso o arquivo não funcione como desejado */
		{
			textcolor(15);
			printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			printf("          x   >>            ERRO NA ABERTURA DO ARQUIVO!          <<  x\n");
			printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			getch(); 
		}
		else
		{
			textcolor(11);
			printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			printf("          x          >>      PESQUISAR UM LIVRO LIDO      <<         x\n");
			printf("          x                 > DESEJA PESQUISAR POR <                 x\n");
			printf("          x                                                          x\n");
			printf("          x              1 - TÍTULO                                  x\n");
			printf("          x              2 - AUTOR                                   x\n");
			printf("          x              3 - EDITORA                                 x\n");
			printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
			textcolor(15);
			printf(" Opcao selecionada: ");
			textcolor(3);
			scanf("%d", &op);
			
			if (op>=1 && op<=5)
			{
						
				/* Início do switch case do segundo menu */
				switch (op)
				{
					case 1 :
					{
					/* PESQUISA POR TÍTULO */
						fflush(stdin);  /* Limpar o buffer do teclado antes de inserir uma string */
						textcolor(15);
						printf("\n >> Título do livro que deseja encontrar: ");
						textcolor(3);
						gets(pesqlivro);  /* Pega o nome do cadastro que deseja vizualizar */
						
						while (fread(&livro, sizeof (livro),1,arq)==1)  /* Lê o arquivo até o seu final */
						{
							if ( strcmp(pesqlivro, livro.titulo)==0) /* Caso encontre um título igual ao pesquisado */
							{
								textcolor(15);
								printf("\n\n-------------------------------livro encontrado!!-------------------------------");
								textcolor(3);
								/* Mostra os dados do livro pesquisado */
								printf("\n >> Título do livro: %s",livro.titulo);	
								printf("\n >> Autor do livro: %s",livro.autor);
								printf("\n >> Nome da editora: %s",livro.editora);
								printf("\n >> Ano de publicação: %d",livro.ano);	
								printf("\n >> Data do término da leitura %d/%d/%d \n",livro.data.dia,livro.data.mes,livro.data.ano);
							}
						}
						rewind(arq); /* Retorna para o início do arquivo, para a próxima pesquisa ser realizada */
						break;		
					}
					case 2 :
					{
					/* PESQUISA POR AUTOR */
						fflush(stdin);  /* Limpar o buffer do teclado antes de inserir uma string */
						textcolor(15);
						printf("\n >> Autor do livro que deseja encontrar: ");
						textcolor(3);
						gets(pesqlivro);  /* Pega o autor do cadastro que deseja vizualizar */
						
						while (fread(&livro, sizeof (livro),1,arq)==1)  /* Lê o arquivo até o seu final */
						{
							if ( strcmp(pesqlivro, livro.autor)==0) /* Caso encontre um título igual ao pesquisado */
							{
								textcolor(15);
								printf("\n\n-------------------------------livro encontrado!!-------------------------------");
								textcolor(3);
								/* Mostra os dados do livro pesquisado */
								printf("\n >> Título do livro: %s",livro.titulo);	
								printf("\n >> Autor do livro: %s",livro.autor);
								printf("\n >> Nome da editora: %s",livro.editora);
								printf("\n >> Ano de publicação: %d",livro.ano);	
								printf("\n >> Data do término da leitura %d/%d/%d \n",livro.data.dia,livro.data.mes,livro.data.ano);
							}
						}
						rewind(arq); /* Retorna para o início do arquivo, para a próxima pesquisa ser realizada */
						break;	
					}
					case 3 :
					{
					/* PESQUISA POR EDITORA */
						fflush(stdin);  /* Limpar o buffer do teclado antes de inserir uma string */
						textcolor(15);
						printf("\n >> Editora do livro que deseja encontrar: ");
						textcolor(3);
						gets(pesqlivro);  /* Pega a editora do cadastro que deseja vizualizar */
						
						while (fread(&livro, sizeof (livro),1,arq)==1)  /* Lê o arquivo até o seu final */
						{
							if ( strcmp(pesqlivro, livro.editora)==0) /* Caso encontre um título igual ao pesquisado */
							{
								textcolor(15);
								printf("\n\n-------------------------------livro encontrado!!-------------------------------");
								textcolor(3);
								/* Mostra os dados do livro pesquisado */
								printf("\n >> Título do livro: %s",livro.titulo);	
								printf("\n >> Autor do livro: %s",livro.autor);
								printf("\n >> Nome da editora: %s",livro.editora);
								printf("\n >> Ano de publicação: %d",livro.ano);	
								printf("\n >> Data do término da leitura %d/%d/%d \n",livro.data.dia,livro.data.mes,livro.data.ano);
							}
						}
						rewind(arq); /* Retorna para o início do arquivo, para a próxima pesquisa ser realizada */;
						break;		
					}
				}/* Fim do switch case */	
			}		
			else
			{
		system ("cls");
		textcolor(11);
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		printf("          x                                                           x\n");
		printf("          x                >>>   OPÇÃO INVÁLIDA!   <<<                x\n");
		printf("          x                                                           x\n");
		printf("          x                                                           x\n");
		printf("          x          > PARA VOLTAR PRESSIONE QUALQUER TECLA <         x\n");
		printf("          x                                                           x\n");
		printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
		getch();
			}
		}
	}
	
	void ApagaTudo ()
	/* Apagar todos os cadastros feitos */
	{	
		system ("cls");
		remove("ArquivoCadastro.txt"); /* Apaga o arquivo todo */	
					textcolor(11);
					printf("\n          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
					printf("          x   >>        TODOS OS CADASTROS FORAM APAGADOS!        <<  x\n");
					printf("          xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	}
	

