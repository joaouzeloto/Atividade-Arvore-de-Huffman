struct arvore
{
	char simb;
	int qtde;
	struct arvore *dir, *esq;
};
typedef struct arvore Tree;

struct caixas
{
	Tree *arv;
	struct caixas	*prox;
};
typedef struct caixas Box;

char criaSimbAl() {
    srand(time(NULL));
    int numeroAleatorio = rand() % 26 + 65;
    char letraSorteada = (char)numeroAleatorio;
    return letraSorteada;
}

struct auxiliarString
{
	char palavra[30], simbo, codHuff[15];
	int qtde;
	struct auxiliarString *prox;
};
typedef struct auxiliarString auxStr;

char existe(Box *B, char a)
{
	while(B!=NULL)
	{
		if(B->arv->simb!=a)
			B = B->prox;
		else
			return 1;
	}
	return 0;
}

void ordenaBox(Box **B,Box **novo)
{
	Box *ant=NULL,*prox=*B;
	while(prox!=NULL&&(*novo)->arv->qtde>prox->arv->qtde)
	{
		ant = prox;
		prox = prox->prox;
	}
	if(ant==NULL)
	{
		(*novo)->prox = *B;
		*B = *novo;
	}
	else
		if(prox==NULL)
			ant->prox = *novo;
		else
			{
				ant->prox = *novo;
				(*novo)->prox = prox;
			}
}
	

void criaCaixas(Box **boxI,auxStr **auxS)
{
	Box *novoB = (Box*) malloc(sizeof(Box));
	Tree *novo = (Tree*) malloc(sizeof(Tree));
	novo->qtde = (*auxS)->qtde;
	novo->simb = criaSimbAl();
	while(existe(*boxI,novo->simb))
		novo->simb = criaSimbAl();
	novoB->arv = novo;
	novoB->prox = NULL;
	(*auxS)->simbo = novo->simb;
	if(*boxI==NULL)
		*boxI = novoB;
	else
	{
		ordenaBox(*&boxI,&novoB);
	}
}



