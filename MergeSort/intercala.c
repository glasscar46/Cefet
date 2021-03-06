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
void intercala(char *fileA, char *fileB, int i);

int main(int argc, char** argv)
{
    FILE *f;
    Endereco *e;
    long posicao, qtd;
    f = fopen("cep.dat","r");
    if(!f)
        printf("unable to open file");
    else
        printf("file opened");
    fseek(f,0,SEEK_END);
    posicao = ftell(f);
    qtd = (posicao/sizeof(Endereco));
    long fim = round((qtd/16)) + 1;
    rewind(f);
    printf("fim: %ld,qtd: %ld, posicao: %ld",fim,qtd,posicao);


    for(int i = 0; i < 16; i++){
 		char  right[11];
        sprintf(right,"cep_%d.dat",i);
        FILE * aux =  fopen(right,"w");
		if(i != 15){
			e = malloc(fim*sizeof(Endereco));
            fread(e,sizeof(Endereco),fim,f);
			qsort(e,fim,sizeof(Endereco),compara);
            fwrite(e,sizeof(Endereco),fim,aux);
			fclose(aux);
			free(e);
            aux = NULL;
		}
		else{
			e = malloc((fim-5)*sizeof(Endereco));
		long a = fread(e,sizeof(Endereco),fim-5,f);
			qsort(e,fim-5,sizeof(Endereco),compara);
        	fwrite(e,sizeof(Endereco),fim-5,aux);
			fclose(aux);
        	aux = NULL;
			free(e);
		}
    }
   for(int j = 0; j < 16; j++){
        char right [11];
        char output[15];
        sprintf(output,"saida_%d.dat",j);
		sprintf(right,"cep_%d.dat",j);
        intercala(output,right,j+1);
        remove(output);
		remove(right);
    }

}
 void intercala(char  *fileA, char *fileB, int i){
	Endereco ea, eb;
	char saida[15];
	FILE *a;
	sprintf(saida,"saida_%d.dat",i);
	if(i == 1){
		a =fopen("saida_0.dat","w");
		fclose(a);
	}
	a = fopen(fileA,"r+");
	FILE *b = fopen(fileB,"r");
	FILE *output = fopen(saida,"w");
	fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);

	while(!feof(a) && !feof(b))
	{
		if(compara(&ea,&eb)<0)
		{
			fwrite(&ea,sizeof(Endereco),1,output);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else
		{
			fwrite(&eb,sizeof(Endereco),1,output);
			fread(&eb,sizeof(Endereco),1,b);
		}
	}

	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,output);
		fread(&ea,sizeof(Endereco),1,a);
	}
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,output);
		fread(&eb,sizeof(Endereco),1,b);
	}

	fclose(a);
	fclose(b);
	fclose(output);

 }

