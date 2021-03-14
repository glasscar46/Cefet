#include <stdio.h>
#include <string.h>

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


int busca(char* file,char * cep, long primeiro, long ultimo){
  if(primeiro > ultimo){
      return -1;
  }
  long meio = (ultimo + primeiro)/2;
  FILE *f = fopen(file,"r");
  Endereco e;
  int a = fseek(f,meio * sizeof(Endereco) ,SEEK_SET);
  int qtd =fread(&e,sizeof(Endereco),1,f);
  fclose(f);
  if(strncmp(cep,e.cep,8)==0){
      printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
	
        return 0;
  }
  else if(strncmp(cep,e.cep,8) > 0){
	  primeiro = meio + 1;
      return busca(file,cep,primeiro,ultimo);
  }
  else{
	  ultimo = meio - 1;
    return busca(file,cep,primeiro,ultimo);
  }
}

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	long tamanhoArquivo, posicao, primeiro, ultimo, meio;
	if(argc != 2)
	{
		fprintf(stderr, "\nUSO: %s [CEP\n]", argv[0]);
		return 1;
	}
	f = fopen("cep_ordenado.dat","r");
	if(f == NULL){
		fprintf(stderr,"Unable to open file (%s)\n",argv[1]);
		return -1;
	}
	fseek(f,0,SEEK_END);
	tamanhoArquivo = ftell(f);
	rewind(f); // fseek(f,0,SEEK_SET);
	primeiro = 0;
	ultimo = (tamanhoArquivo/sizeof(Endereco))-1;
	fclose(f);
  int resultado = busca("cep_ordenado.dat",argv[1],primeiro,ultimo);

 if(resultado == -1){
   printf("CEP not found");
 }
	return 0;
}