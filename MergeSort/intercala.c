#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}
void intercala(char *fileA, char *fileB,char * fileC);

int main(int argc, char** argv)
{
    FILE *f,cepA,cepB;
    Endereco *e;
    long posicao, qtd;
    f = fopen("cep.dat","r");
    fseek(f,0,SEEK_END);
    posicao = ftell(f);
    long fim = (long)ceil(qtd/16);
    qtd = ceil(posicao/sizeof(Endereco));
    e = malloc(fim*sizeof(Endereco));
    rewind(f);
    FILE * saidas[16];


    for(int i = 0; i < 16; i++){
            char * dat = ".dat";
            char * right = "cep_" + i ;
            strcat(right,dat);
          FILE * aux =   fopen(right,"w");
            fread(e,sizeof(Endereco),fim,f);
            qsort(e,fim,sizeof(Endereco),compara);
            fwrite(e,sizeof(Endereco),fim,aux);
            saidas[i] = aux;
            fclose(aux);
            aux = NULL;
    }
    FILE *saida = saidas[0];
    for(int i = 1; i < 16; i++){
        

    }

}
 void intercala(char * fileA, char * fileB, char * fileC){
     	FILE *a, *b, *saida;
	Endereco ea, eb;
    a = fopen(fileA,"r");
	b = fopen(fileB,"r");
	saida = fopen(fileC,"w");
    
	fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);

	while(!feof(a) && !feof(b))
	{
		if(compara(&ea,&eb)<0)
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);
		}
	}

	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,saida);
		fread(&ea,sizeof(Endereco),1,a);		
	}
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,saida);
		fread(&eb,sizeof(Endereco),1,b);		
	}

	fclose(a);
	fclose(b);
	fclose(saida);

 }