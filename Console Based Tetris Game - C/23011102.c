#include<stdio.h>
#include<stdlib.h> // rand fonskiyonunu kullanabilmek i�in ekledik.


int M,N,sutun,score[50]={0},oyunSayisi=0,max=0; // di�er fonksiyonlarda da kullanaca��m�z de�i�kenleri globalde tan�mlad�k.

void yeniBlokTemizle(char matrex[][3]); // oyunumuzda yeni gelecek blo�un bilgisinin tutulaca�� matrisi her yeni blok i�in temizleyece�imiz fonksiyon.
void yazdir(char matris[][500]); // oyun tablam�z� ekrana yazdirmamiz i�in olu�turdu�umuz fonksiyon.
void yeni_blok_yazdir(char matris[][3]); // yeni blo�un bilgisinin kullan�c�ya g�stermek i�in kullanaca��m�z fonksiyon
void sutunSor(); // kullan�c�ya ekrana gelecek yeni blo�un nereye yerle�tirilece�i bilgisini ald���m�z fonksiyon.

int main(){
	char dondur,yeniBlok[3][3],tabla[500][500];
	int flag=0,i,yer,yes=1,j,h,sayac,d,k,blok,control=0,y,t;
	printf("-----------TETRIS OYUNUNA HOS GELDINIZ-------------\n\n\n");
	printf("Oyunumuzu oynarken goreceginiz blogun en solundaki parcaya uygun sutun koordinatini gireceksiniz.\n\n");
	printf("Oyunu kaybederseniz tekrar oynamak icin 1'e basiniz.\n\n");
	printf("Bir parcayi dondUrmek istediginizde w tu�una basiniz.\n\n");
	printf("\n-----------IYI OYUNLAR DILERIZ---------------------\n\n");
	printf("\n\n\nOyuna gecmek icin herhangi bir tusa basiniz....\n\n");
	getchar();
	system("cls");
	printf("OYUN TAHTANIZ ICIN BOYUT GIRINIZ (Once Satir Sonra Sutun): \n");
	scanf("%d  %d",&M,&N);
	
	while(yes==1){ // oyunumuzu default olarak ba�lat�yoruz, kullan�c�m�z oyunu sonland�rmak istedi�inde yes de�i�keni de�i�ecek.
		oyunSayisi+=1; // oyunumuzu ka� kere oynad���m�z� kaydediyoruz.
		for(i=0;i<M;i++){
			for(j=0;j<N;j++){
				tabla[i][j]='.'; // tablam�z� haz�rl�yoruz, her oyuna ba�land���ndan tablam�z '.' i�areti ile dolacak.
			}
		}
		control=0; // en �st sat�r�m�zda herhangi bir par�a olup olmad���n�n kontrol�. ba�lang��ta par�a olmad��� i�in 0dan ba�lat�yoruz.
		yazdir(tabla); // tablam�z� ekrana yazd�r�p oyunumuzu ba�lat�yoruz.
		while(control==0){
			blok = rand()%7; // blo�umuzu rastgele al�yoruz, alaca��m�z de�erleri if ile kontrol ederken uygun blo�u kullan�yoruz.
			printf("\nBLOK NO : %d",blok);
			if(blok==0){ // 111 �ekli
				yeniBlokTemizle(yeniBlok); 
				yeniBlok[1][0]='X'; // burada kullan�c�m�za blo�u g�stermek i�in yeniblok adl� matrisimize �eklimizi �iziyoruz.
				yeniBlok[1][1]='X';
				yeniBlok[1][2]='X';
				yeni_blok_yazdir(yeniBlok); // uygun i�lemlerle yeni blo�u �izdikten sonra blo�u ekrana yazd�r�yoruz.
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur == 'w' || dondur == 'W'){ // | 111 dikey hali olacak
					yazdir(tabla); // tablam�z� ekrana yazd�r�yoruz, system("cls") komutu ile �st k�s�mlar� temizleyip d�nd�r�lm�� hali g�sterece�iz.
					yeniBlokTemizle(yeniBlok);
					yeniBlok[0][1]='X';
					yeniBlok[1][1]='X';
					yeniBlok[2][1]='X';
					yeni_blok_yazdir(yeniBlok);
					sutunSor(); // kullan�c�m�zdan g�sterilen blo�un en soldaki k�sm�n�n hangi sutuna yerle�tirilece�ini istiyoruz.
					i=0; // tablam�zda se�ilen koordinata uygun sat�r� bulmak i�in tablam�z� kontrol eden kod k�sm�na ge�iyoruz.
					flag=0;
					while(flag==0 && i<M-1){
						if(tabla[i][sutun]!='.'){ // tablam�z� i ve flag yap�s� ile, potansiyel yerleri kontrol ediyoruz.
							flag=1;    // e�er herhangi bir yer dolmu�sa d�ng�den ��k�p buldu�umuz yeri kaydedece�iz.
						}
						if(tabla[i+1][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+2][sutun]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2; // d�ng�den ��kt�ktan sonra belirlenen i de�erine g�re olu�acak de�eri yer adl� de�i�kenine atayarak i�lem yap�yoruz.
					tabla[yer][sutun]='X'; // kontrol�m�zden sonra buldu�umuz uygun sat�r ve s�tunlara tablam�zda �eklimizi �izdiriyoruz.
					tabla[yer+1][sutun]='X';
					tabla[yer+2][sutun]='X';		
				}
				else{ // kodumuz bundan sonra benzer yap�da devam etmektedir. se�ilen blok ve d�nd�r�lm�� haline uygun kontroller yap�larak uygun yere �eklimiz �izdiriliyor.
					sutunSor();
					i=0;
					flag=0;
					while(flag==0 && i<=M){
						if(tabla[i][sutun]!='.'){
							flag=1;
						}
						if(tabla[i][sutun+1]!='.'){
							flag=1;
						}
						if(tabla[i][sutun+2]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2;
					tabla[yer][sutun]='X';
					tabla[yer][sutun+1]='X';
					tabla[yer][sutun+2]='X';
				}
			}

			else if(blok==1){ // T �ekli tersten
				yeniBlokTemizle(yeniBlok);
				yeniBlok[0][1]='X';
				yeniBlok[1][0]='X';
				yeniBlok[1][1]='X';
				yeniBlok[1][2]='X';
				yeni_blok_yazdir(yeniBlok);
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ // ucu sola bakan T �ekli
					yazdir(tabla);
					yeniBlokTemizle(yeniBlok);
					yeniBlok[1][1]='X';
					yeniBlok[0][2]='X';
					yeniBlok[1][2]='X';
					yeniBlok[2][2]='X';
					yeni_blok_yazdir(yeniBlok);
					printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
					scanf("%s",&dondur);
					if(dondur=='w' || dondur=='W'){ // d�z T �ekli
						yazdir(tabla);
						yeniBlokTemizle(yeniBlok);
						yeniBlok[1][0]='X';
						yeniBlok[1][1]='X';
						yeniBlok[1][2]='X';
						yeniBlok[2][1]='X';
						yeni_blok_yazdir(yeniBlok);
						printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
						scanf("%s",&dondur);
						
						if(dondur=='w' || dondur=='W'){ // ucu sa�a bakan T �ekli
							yazdir(tabla);
							yeniBlokTemizle(yeniBlok);
							yeniBlok[0][1]='X';
							yeniBlok[1][1]='X';
							yeniBlok[2][1]='X';
							yeniBlok[1][2]='X';
							yeni_blok_yazdir(yeniBlok);
							sutunSor();
							i=0;
							flag=0;
							while(flag==0 && i<M-1){
								if(tabla[i][sutun]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun]!='.'){
									flag=1;
								}
								if(tabla[i+2][sutun]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun+1]!='.'){
									flag=1;
								}
								i++;
							}
							yer=i-2;
		
							tabla[yer][sutun]='X';
							tabla[yer+1][sutun]='X';
							tabla[yer+2][sutun]='X';
							tabla[yer+1][sutun+1]='X';	
				
				
						}
						else{
							sutunSor();
							i=0;
							flag=0;
							while(flag==0 && i<M){
								if(tabla[i][sutun]!='.'){
									flag=1;
								}
								if(tabla[i][sutun+1]!='.'){
									flag=1;
								}
								if(tabla[i][sutun+2]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun+1]!='.'){
									flag=1;
								}
								i++;
							}
							yer=i-2;
							tabla[yer][sutun]='X';
							tabla[yer][sutun+1]='X';
							tabla[yer][sutun+2]='X';
							tabla[yer+1][sutun+1]='X';
				
						}
				
						}
						else{
							sutunSor();
							i=0;
							flag=0;
							while(flag==0 && i<M-1){
								if(tabla[i][sutun+1]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun+1]!='.'){
									flag=1;
								}
								if(tabla[i+2][sutun+1]!='.'){
									flag=1;
								}
								i++;
							}
							yer=i-2;
	
							tabla[yer][sutun+1]='X';
							tabla[yer+1][sutun]='X';
							tabla[yer+1][sutun+1]='X';
							tabla[yer+2][sutun+1]='X';
			
						}
				
				}
				else{
					sutunSor();
					i=0;
					flag=0;
					while(flag==0 && i<M){
						if(tabla[i][sutun+1]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun]!='.'){
							flag=1;
						}	
						if(tabla[i+1][sutun+1]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun+2]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2;
					tabla[yer][sutun+1]='X';
					tabla[yer+1][sutun]='X';
					tabla[yer+1][sutun+1]='X';
					tabla[yer+1][sutun+2]='X';
		
				}
		
			}
			else if(blok==2){ // Kare �eklimiz  **  �eklinde
				yeniBlokTemizle(yeniBlok);  //  **
				yeniBlok[0][1]='X';
				yeniBlok[0][2]='X';
				yeniBlok[1][1]='X';
				yeniBlok[1][2]='X';
				yeni_blok_yazdir(yeniBlok);
				sutunSor();
				i=0;
				flag=0;	
				while(flag==0 && i<M){
					if(tabla[i][sutun]!='.'){
						flag=1;
					}
					if(tabla[i+1][sutun]!='.'){
						flag=1;
					}
					if(tabla[i+1][sutun+1]!='.'){
						flag=1;
					}
					if(tabla[i][sutun+1]!='.'){
						flag=1;
					}
					i++;
				}
				yer=i-2;
	
				tabla[yer][sutun]='X';
				tabla[yer][sutun+1]='X';
				tabla[yer+1][sutun+1]='X';
				tabla[yer+1][sutun]='X';
			}

			else if(blok==3){  // tek nokta �ekli * �eklinde
				yeniBlokTemizle(yeniBlok);
				yeniBlok[1][1]='X';
				yeni_blok_yazdir(yeniBlok);
				sutunSor();
				i=0;
				flag=0;
				while(flag==0 && i<=M){
					if(tabla[i][sutun]!='.'){
						flag=1;
					}
					i++;
				}
				yer=i-2;
	
				tabla[yer][sutun]='X';
			}


			else if(blok==4){ // L �ekli
				yeniBlokTemizle(yeniBlok);
				yeniBlok[0][1]='X';
				yeniBlok[1][1]='X';
				yeniBlok[2][1]='X';
				yeniBlok[2][2]='X';	
				yeni_blok_yazdir(yeniBlok);
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ //    *  �eklinde olacak blo�umuz
					yazdir(tabla);              //  ***
					yeniBlokTemizle(yeniBlok);
					yeniBlok[1][2]='X';
					yeniBlok[2][0]='X';
					yeniBlok[2][1]='X';
					yeniBlok[2][2]='X';
					yeni_blok_yazdir(yeniBlok);
					printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
					scanf("%s",&dondur);
					if(dondur=='w' || dondur=='W'){ // ** �eklinde olacak par�am�z
						yazdir(tabla);              //  *
						yeniBlokTemizle(yeniBlok);  //  * 
						yeniBlok[0][1]='X';
						yeniBlok[0][2]='X';
						yeniBlok[1][2]='X';
						yeniBlok[2][2]='X';	
						yeni_blok_yazdir(yeniBlok);	
						printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
						scanf("%s",&dondur);
						if(dondur=='w' || dondur=='W'){ // ***  �eklinde olacak par�am�z
							yazdir(tabla);				// *
							yeniBlokTemizle(yeniBlok);
							yeniBlok[1][0]='X';
							yeniBlok[1][1]='X';
							yeniBlok[1][2]='X';
							yeniBlok[2][0]='X';
							yeni_blok_yazdir(yeniBlok);
							sutunSor();
							i=0;
							flag=0;
							while(flag==0 && i<M){
								if(tabla[i][sutun]!='.'){
									flag=1;
								}
								if(tabla[i][sutun+1]!='.'){
									flag=1;
								}
								if(tabla[i][sutun+2]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun]!='.'){
									flag=1;
								}
								i++;
							}
							yer=i-2;
	
							tabla[yer][sutun]='X';
							tabla[yer][sutun+1]='X';
							tabla[yer][sutun+2]='X';
							tabla[yer+1][sutun]='X';
						}
						else{
							sutunSor();
							i=0;
							flag=0;
							while(flag==0 && i<M-1){
								if(tabla[i][sutun]!='.'){
									flag=1;
								}
								if(tabla[i][sutun+1]!='.'){
									flag=1;
								}
								if(tabla[i+1][sutun+1]!='.'){
									flag=1;
								}
								if(tabla[i+2][sutun+1]!='.'){
									flag=1;
								}
								i++;
							}
							yer=i-2;
	
							tabla[yer][sutun]='X';
							tabla[yer][sutun+1]='X';
							tabla[yer+1][sutun+1]='X';
							tabla[yer+2][sutun+1]='X';
						}
				
					}
					else{
						sutunSor();
						i=0;
						flag=0;
						while(flag==0 && i<M){
							if(tabla[i+1][sutun]!='.'){
								flag=1;
							}
							if(tabla[i+1][sutun+1]!='.'){
								flag=1;
							}
							if(tabla[i+1][sutun+2]!='.'){
								flag=1;	
							}
							if(tabla[i][sutun+2]!='.'){
								flag=1;
							}
							i++;
						}
						yer=i-2;
		
						tabla[yer+1][sutun]='X';
						tabla[yer+1][sutun+1]='X';
						tabla[yer+1][sutun+2]='X';
						tabla[yer][sutun+2]='X';
					}
		
				}
				else{
				sutunSor();	
				i=0;
				flag=0;
				while(flag==0 && i<M-1){	
					if(tabla[i][sutun]!='.'){	
						flag=1;	
					}
					if(tabla[i+1][sutun]!='.'){
						flag=1;
					}
					if(tabla[i+2][sutun]!='.'){
						flag=1;
					}
					if(tabla[i+1][sutun+1]!='.'){
						flag=1;
					}
					i++;
				}
				yer=i-2;
	
				tabla[yer][sutun]='X';
				tabla[yer+2][sutun+1]='X';
				tabla[yer+1][sutun]='X';		
				tabla[yer+2][sutun]='X';
		
				}
		
			}
			else if(blok==5){ // dikey �ekil 111
				yeniBlokTemizle(yeniBlok);
				yeniBlok[0][1]='X';
				yeniBlok[1][1]='X';	
				yeniBlok[2][1]='X';
				yeni_blok_yazdir(yeniBlok);
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ // *  �eklinde olacak par�am�z, d�nm�� �ekilde.
					yazdir(tabla);				// *
					yeniBlokTemizle(yeniBlok);	// *
					yeniBlok[1][0]='X';	
					yeniBlok[1][1]='X';
					yeniBlok[1][2]='X';
					yeni_blok_yazdir(yeniBlok);	
					sutunSor();
					i=0;
					flag=0;
					while(flag==0 && i<=M){
						if(tabla[i][sutun]!='.'){
							flag=1;
						}
						if(tabla[i][sutun+1]!='.'){
							flag=1;
						}
						if(tabla[i][sutun+2]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2;
	
					tabla[yer][sutun]='X';
					tabla[yer][sutun+2]='X';
					tabla[yer][sutun+1]='X';
				}
				else{
					sutunSor();
					i=0;
					flag=0;
					while(flag==0 && i<M-1){
						if(tabla[i][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+2][sutun]!='.'){
							flag=1;
						}
						i++;	
					}		
					yer=i-2;
	
					tabla[yer][sutun]='X';	
					tabla[yer+1][sutun]='X';
					tabla[yer+2][sutun]='X';
		
				}
	
			}
			else if(blok==6){             //   **  �ekli i�in kod
				yeniBlokTemizle(yeniBlok);//  **
				yeniBlok[0][1]='X';
				yeniBlok[0][2]='X';
				yeniBlok[1][0]='X';
				yeniBlok[1][1]='X';
				yeni_blok_yazdir(yeniBlok);	
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ //  *  �eklindeki par�a i�in kodumuz
					yazdir(tabla);				//  **
					yeniBlokTemizle(yeniBlok);	//   *
					yeniBlok[0][1]='X';
					yeniBlok[1][1]='X';
					yeniBlok[1][2]='X';
					yeniBlok[2][2]='X';	
					yeni_blok_yazdir(yeniBlok);
					sutunSor();		
					i=0;	
					flag=0;
					while(flag==0 && i<M-1){
						if(tabla[i][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun+1]!='.'){
							flag=1;
						}
						if(tabla[i+2][sutun+1]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2;
		
					tabla[yer][sutun]='X';
					tabla[yer+1][sutun]='X';
					tabla[yer+1][sutun+1]='X';
					tabla[yer+2][sutun+1]='X';
				}
				else{
					sutunSor();
					i=0;
					flag=0;
					while(flag==0 && i<M){
						if(tabla[i][sutun+1]!='.'){
							flag=1;
						}
						if(tabla[i][sutun+2]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+1][sutun+1]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2;
	
					tabla[yer][sutun+1]='X';
					tabla[yer][sutun+2]='X';
					tabla[yer+1][sutun]='X';
					tabla[yer+1][sutun+1]='X';
				}
	
			}
			score[oyunSayisi]+=1; // her bir par�a yerle�tirildikten sonra puan�m�z� 1er artt�r�yoruz.
			h=0;
			while(h<M){ // bir sat�r�n tamamen dolup dolmad���n� kontrol eden d�ng�m�z
				sayac=0;
				d=0;
				while(d<N){
					if(tabla[h][d]=='X'){ // en �st sat�rdan alta kadar kontrol ediyoruz ve e�er sat�rda blok par�as� varsa her par�a i�in sayac� 1er artt�r�yoruz.
						sayac++; 
					}
					if(sayac==N){ // e�er sayac�m�z sutun say�s�na e�itlendiyse o sat�r tamamen doldu�unu anlam�� olaca��z.
						for(y=0;y<N;y++){
							for(t=h;t>0;t--){
								tabla[t][y]=tabla[t-1][y]; // burada da tablam�zda tamamen dolu olan sat�r� silmek i�in bir d�ng� ile �stteki sat�rlar� a��a��ya kayd�r�yoruz.
							}
						}
						score[oyunSayisi]+=10; // e�er bir sat�r� tamamen patlatt�ysak skorumuz 10 art�yor.
				
					}
					d++;
			
				}
				h++;
			}
	
			for(i=0;i<N;i++){
				if(tabla[0][i]=='X'){ // tablam�z�n en �st sat�r�nda herhangi bir blok par�as� olup olmad���n� kontrol ediyoruz. var ise oyun bitecektir.
					control=1;
				}
			}
			yazdir(tabla);
	
		} // control de�erimiz 1 oldu�unda oyunumuz sonlanacakt�r.
		yes=0;
		printf("\n--- GAME OVER ----\n");	
		printf("Tekrar Oynamak icin 1 giriniz : "); // oyuncu oynamaya devam etmek istiyorsa 1 girecektir ve d�ng� yeniden ba�lat�lacakt�r.
		scanf("%d",&yes);
		score[oyunSayisi+1]=0; // burada oyunSayisi+1 kullanarak bir sonraki tur oynan�rsa skorun 0dan ba�lat�lmas�n� sa�l�yoruz.
		if(score[oyunSayisi]>score[max]){
			max=oyunSayisi; // e�er son oynanan oyundaki skor �nceki max skordan fazla ise max de�erimiz g�ncellenecektir.
		}
	
		if(yes==1){
			printf("OYUN TAHTANIZ ICIN BOYUT GIRINIZ (Once Satir Sonra Sutun): ");
			scanf("%d  %d",&M,&N);
			printf("\n");
		
		}
	}
	printf("Oyun Bitti --  %d kere Oynadiniz.",oyunSayisi);
	return 0;
}


void yazdir(char oyunAlan[][500]){
	int i,j;
	system("cls"); // tablam�z� yazd�rmadan �nce konsolu temizliyoruz
	printf("--OYUN TAHTANIZIN SON DURUMU -- --- MAX SKOR : %d\n\n",score[max]); // en �ste rekor skorumuzu yaz�yoruz
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("%2c ",oyunAlan[i][j]); // oyun alan�m�z�n son halini ekrana bast�r�yoruz.
		}
		printf("\n");
	}
	
	for(j=0;j<N;j++){
			printf("-- "); 
		}
	printf("\n");
	for(j=0;j<N;j++){ // kullan�c� hangi sutuna yerle�tirebilece�ini se�ebilmesi i�in g�rsellik a��s�ndan tablam�z� yazd�ktan sonra alt�na sat�r numaralar�n� g�steriyoruz.
		if(j<9){
			printf(" %d ",j+1);
		}
		else{
			printf("%d ",j+1);
		}
		}
	
	printf("\n\nSkorunuz : %d",score[oyunSayisi]); // g�ncel skorumuzu tablam�z�n alt�nda g�steriyoruz.
}

void yeni_blok_yazdir(char blokMatrisi[][3]){
	int i,j;
	printf("\nYeni Blok : \n\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%2c ",blokMatrisi[i][j]); // yeni blo�umuzu ekrana yazd�ran komutumuz
			}
		printf("\n");
	}
}

void yeniBlokTemizle(char temizBlok[][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			temizBlok[i][j]=' '; // yeni blo�u kulland�ktan sonra sonraki blok i�in temizledi�imiz komutumuz.
		}
	}
	
}

void sutunSor(){
	int i,j;
	printf("\n");
	printf("Sutun Giriniz : ");
	scanf("%d",&sutun); // kullan�c�dan hangi sutunu isteyece�imizi belirtti�imiz kodumuz.
	while(sutun>N || sutun<1){ // girilen sutun tablam�z�n sutun say�s�ndan fazla veya 1den k���k ise girilecek sutunu tekrar istiyoruz.
		printf("\nGecersiz Sutun Degeri Girildi -- Tekrar Giriniz\n");
		printf("Sutun Giriniz : ");
		scanf("%d",&sutun);
	}
	sutun=sutun-1;
}
