
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Helper retourne true si égale à la chaine en parametre, false sinon 
int isNextToken(FILE *fp, const char *token){
		char str[10];
		// recupération de la position dans le texte :
		long pos = ftell(fp);
		// copie de la chaine à suivre
		fscanf(fp, "%s", str);
		// comparaison :
		if (!strcmp(str, token)){ 
			
			return true;
		}
	// retour à la position dans le texte avent l'appelle de fonction
	fseek(fp,pos,SEEK_SET);
	return false;
}

//**************************************************************************************

void screenInfo(FILE *fp, const char *token) {

	char str[60];
	//int lenght = strlen(token);
	bool flag = 1;
	char tk1[10];
	char tk2[10]={0};
	
	
	sscanf(token,"%s %s" ,tk1 ,tk2);
	

   	// Controle de l'existance du fichier :
	if(fp == NULL) perror("no file open");
	     
	// Déplacment au début du fichier : 
	rewind(fp);
	  
	// Boucle de lecture du fichier:
  	while (fscanf(fp, "%s", str)!=EOF){
	  	
	  	// condition pour récupérer le n° de processeur
	  	if (!strcmp(str, "processor")) {
		   	fscanf(fp, "%s", str);
			fseek(fp,1,SEEK_CUR);			   	
		   	if( fgets (str, 2, fp)!=NULL ) printf("pour le processeur: %s =>", str);
		}
			// est ce que j'ai trouver le premier mot ?
		if (!strcmp(str, tk1) ) {
			
			// est ce que j'ai le second ?
			if (isNextToken(fp, tk2)||(strlen(tk2)==0)){
		   		

				if (isNextToken(fp,":")){
					
					fseek(fp,1,SEEK_CUR);
				}
			   	
			   	if( fgets (str, 60, fp)!=NULL ) {
					printf("%s",token);
					printf(" => %s\n", str);
				}
		   	}
		} 
   	}
}


//*******************************************************************************************
int main (int argc, char const *argv[])
{

	FILE * myFile;
	char str[20];
	char tk1[20];
	char tk2[20];
	int myPID;
	int major;
	int minor;
	int blocks;
	char name[5];


	myFile = fopen ("/proc/cpuinfo", "r");

	if(myFile == NULL) {
		perror("Error opening file");
		return 1;     
	}

	screenInfo(myFile, "model name") ;
	screenInfo(myFile, "cpu MHz");
	screenInfo(myFile, "cache size");
	screenInfo(myFile, "address sizes");
	fclose(myFile);

	myFile = fopen ("/proc/meminfo", "r");

	if(myFile == NULL) {
		perror("Error opening file");
		return 1;     
	}
	screenInfo(myFile, "MemTotal:") ;
	screenInfo(myFile, "MemFree:") ;
	fclose(myFile);


	// Ouverture du fichier version
	myFile = fopen ("/proc/version", "r");
	while (fscanf(myFile, "%s %s", tk1, tk2)!=EOF){
		  	
		  
		  	if (!strcmp(tk1, "Linux") && !strcmp(tk2, "version")) {	
		  		fscanf(myFile, "%s", str);	   	
			   	printf("Linux version: %s\n", str);
			} 
	}
	// fermeture du fichier version
	fclose(myFile);


//************************************************************************************************************************


	// demande du numero de pid en parametre :

	scanf("%d%*[^\n]", &myPID);
	// recupération du numero de PID
	sprintf(str, "%s%d%s", "/proc/", myPID,"/status");

	myFile = fopen (str, "r");

	// test pour s'assurer de l'ouverture d'un fichier
	if(myFile == NULL) {
		perror("Error opening file");
		return 1;  
	}

	screenInfo(myFile, "Pid:") ;
	screenInfo(myFile, "Name:") ;
	screenInfo(myFile, "Tgid:") ;
	screenInfo(myFile, "PPid:") ;
	screenInfo(myFile, "Threads:") ;
	screenInfo(myFile, "Uid:") ;
	screenInfo(myFile, "Gid:") ;

	fclose(myFile);


  return 0;

}

