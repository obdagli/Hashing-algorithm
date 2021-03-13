#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TABLE_SIZE 997

typedef struct hashTable{
	int key;
	char value[50];
	char fileName[50];
}hash;
hash hTable[TABLE_SIZE];
//hashTablosunun her elemaninin key degerini -1 yaparak daha sonrasinda karsilastirma icin hazir hale getirir.
void hashReset(){
	int i=0;
	for(i=0;i<TABLE_SIZE;i++){
		hTable[i].key=-1;
	}
}
void writeHash(int finalhash){
	FILE* fproc = fopen("hashTable.txt","a+");
	fprintf(fproc,"%d %s %s\n",hTable[finalhash].key,hTable[finalhash].value,hTable[finalhash].fileName);
	fclose(fproc);
}
//Verilen kelimeyi hornerMethod yontemiyle key'e cevirdikten sonra
//Elde edilen bu key kullanilarak double-hashing yapilir.
//Ve i degeri bir iterasyon aracisi gibi gorulerek(step-size)
//Istenen adim sayisini ekrana yazdirir.
void searchHashKey(int searchkey){
	int firstHash = searchkey % TABLE_SIZE;
	int secondHash = 1 + (searchkey % TABLE_SIZE - 1);	
	int i = 0;
	int finalHash = (firstHash + i * secondHash) % TABLE_SIZE;
	while(hTable[finalHash].key == -1){
		i++;
		int finalHash = (firstHash + i * secondHash) % TABLE_SIZE;
	}
	printf("\nWord '%s' Found - Step Size --> %d",hTable[finalHash].value,i+1);
}
//Daha once olusturulmus olan hashTable.txt dosyamizda deger olabileceginden ya da �st�ne ekleme islemi yapilabileceginden
//Ayni hashinge sahip alana birden fazla kelime eklenmesinin onune gecilmesi icin
//Program calistirilirken getHashTable kullanilarak bir onceki dosyadan veriler cekilir ve programin kendi hashTable'ina yazdirilir.
int getHashTable(char fileName[50]){
	hash node;
	int ncounter=0;
	FILE* fproc = fopen(fileName,"r");
	while(!feof(fproc)){
		fscanf(fproc,"%d %s %s",&(node.key),node.value,node.fileName);
		int firstHash = node.key % TABLE_SIZE;
		int secondHash = 1 + (node.key % TABLE_SIZE - 1);	
		int i = 0;
		int finalHash = (firstHash + i * secondHash) % TABLE_SIZE;	
		hTable[finalHash].key = node.key;
		strcpy(hTable[finalHash].value,node.value);
		strcpy(hTable[finalHash].fileName,node.fileName);
		ncounter++;
	}
	fclose(fproc);
	return ncounter-1;
}
//n = # of keys -- M = Table_size
void loadfactor(int* n){
	double loadfactor = (double)(*n) / TABLE_SIZE;
	printf("\nLoadfactor --> %.2f",loadfactor);
	if(loadfactor >= 0.8){
		printf("\n Warning! If loadfactor reach 1.0 program will abondoned");
	}else if(loadfactor == 1){
		printf("Loadfactor is 1, program will be abondoned soon!");
		exit(0);
	}
}
//hornerMethod'dan gelen struct icin hashTable'a ekleme yapilacagindan
//double-hashing yapildiktan sonra elde edilen finalHash degeri, hTable �zerinde kontrol edilir
//Eger daha once herhangi bir deger yoksa (-1) bu struct'i oraya ekler ve dosyaya yazmak �zere writeHash fonksiyonuna gonderir.
//Eger o finalHash adresine daha onceden deger girilmisse yani ayni hashing adresinde baska bir kelime varsa, tabloda bos olan yere ekleneceginden
//while icerisinde i birer birer arttirilarak tablo �zerinde dolasilir ve bos bir yer bulunur.
void insert(hash newcoms,int* ncounter){
	int firstHash = newcoms.key % TABLE_SIZE;
	int secondHash = 1 + (newcoms.key % TABLE_SIZE - 1);
	int i = 0;
	int finalHash = (firstHash + i * secondHash) % TABLE_SIZE;		
	if(hTable[finalHash].key == -1){
		hTable[finalHash] = newcoms;
		writeHash(finalHash);
		(*ncounter)++;
	}else{
		while(i<TABLE_SIZE && hTable[finalHash].key != -1 && hTable[finalHash].key != newcoms.key){			
			i++;
			finalHash = (firstHash + i * secondHash) % TABLE_SIZE;
		}
		if(hTable[finalHash].key == -1){
			hTable[finalHash] = newcoms;
			writeHash(finalHash);
			(*ncounter)++;
		}else if(hTable[finalHash].key == newcoms.key){
			strcpy(hTable[finalHash].fileName,newcoms.fileName);
		}
		else{
			printf("\n-!- hashTable's size exceeded -!-\n");
			printf("%s couldn't written in the hashTable",newcoms.value);
		}
	}
	loadfactor(ncounter);
}
//hornerMethod isleminin sadece bir kelime i�in yapilmasi. Elde edilen key degeri searchHashKey fonksiyonuna gonderilir.
void hornerForWord(char word[50]){
	int j=0,key=0;
	char temp2;
	int length = strlen(word);
	int us = length - 1;
	for(j=0;j<length;j++){
		temp2 = word[j];
		if(temp2 >= 'a'){
			temp2 = 'A' - 'a' + temp2;
		}
			key += abs((pow(2,us)*(temp2-'A'+1)));
			us--;
	}
	
	searchHashKey(key);
}
//Temp dizisine tek tek char seklinde karakterleri cekerek aralarinda bosluk bulana dek ilerler.
//Bulunan bosluk bulunan bir kelime demek oldugundan bu kelime icin hornerMethod islemi yapilir.
//Elde edilen key, value, fileName degerleri ve loadfactor icin kullanilacak olan n degeri insert fonksiyonuna gonderilir.
//struct newnode seklinde**
void hornerMethod(char fileName[50],int* n){	
	FILE* fproc = fopen(fileName,"r");
	int i,j,key = 0;
	hash newnode;
	char temp[50];
	char temp2;
	while(!feof(fproc)){
		temp[i] = fgetc(fproc);
		if(temp[i] == ' ' || temp[i] == '\n'){
			temp[i] = '\0';
			int length = strlen(temp);
			int us = length - 1;
			for(j=0;j<length;j++){
				temp2 = temp[j];
				if(temp2 >= 'a'){
					temp2 = 'A' - 'a' + temp2;
				}
				key += abs((pow(2,us)*(temp2-'A'+1)));
				us--;
			}
			newnode.key = key;
			strcpy(newnode.value,temp);
			strcpy(newnode.fileName,fileName);
			insert(newnode,n);
			for(i=0;i<length-1;i++){
				temp[i] = '\0';
			}
			key = 0; //Key degerini her adimda key += seklinde kullandigimiz icin sifirladik ki diger adimda sorun olmasin.
			i=-1; //While icerisinde i++ seklinde diziye atama islemi oldugundan, ilk key bulundugunda diziyi sifirlayip i = -1 yazdim asagida da i++ yaptigim icin i=0 olmus oldu.
		}
		i++;
	}
	fclose(fproc);
}
//Program baslangicinda hashReset ve getHashTable
//Calistirilarak once hash tablosu resetlenir daha sonrasinda
//Onceki hashtable degerlerini tabloya koyar ve istenilene gore arama ya da dokumandan kaynak ekleme yapar.
int main(int argc, char *argv[]) {
	hashReset();	
	char fileName[50];
	int choice;	
	int n = getHashTable("hash.txt");
	printf("We've found a hashTable already. Do u want to search a word or enter a new file?\n1: Search - 2: New File --> ");
	scanf("%d",&choice);
	if(choice == 1){
		char word[50];
		printf("\nWord : ");
		scanf("%s",word);
		hornerForWord(word);		
	}else if(choice == 2){
		printf("Please enter your file name (Ex. ""file1.txt""): ");
		scanf("%s",fileName);
		hornerMethod(fileName,&n);
	}
	
	
	return 0;
}
