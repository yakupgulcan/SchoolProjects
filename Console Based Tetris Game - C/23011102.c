#include<stdio.h>
#include<stdlib.h> // rand fonskiyonunu kullanabilmek için ekledik.


int M,N,sutun,score[50]={0},oyunSayisi=0,max=0; // diðer fonksiyonlarda da kullanacaðýmýz deðiþkenleri globalde tanýmladýk.

void yeniBlokTemizle(char matrex[][3]); // oyunumuzda yeni gelecek bloðun bilgisinin tutulacaðý matrisi her yeni blok için temizleyeceðimiz fonksiyon.
void yazdir(char matris[][500]); // oyun tablamýzý ekrana yazdirmamiz için oluþturduðumuz fonksiyon.
void yeni_blok_yazdir(char matris[][3]); // yeni bloðun bilgisinin kullanýcýya göstermek için kullanacaðýmýz fonksiyon
void sutunSor(); // kullanýcýya ekrana gelecek yeni bloðun nereye yerleþtirileceði bilgisini aldýðýmýz fonksiyon.

int main(){
	char dondur,yeniBlok[3][3],tabla[500][500];
	int flag=0,i,yer,yes=1,j,h,sayac,d,k,blok,control=0,y,t;
	printf("-----------TETRIS OYUNUNA HOS GELDINIZ-------------\n\n\n");
	printf("Oyunumuzu oynarken goreceginiz blogun en solundaki parcaya uygun sutun koordinatini gireceksiniz.\n\n");
	printf("Oyunu kaybederseniz tekrar oynamak icin 1'e basiniz.\n\n");
	printf("Bir parcayi dondUrmek istediginizde w tuþuna basiniz.\n\n");
	printf("\n-----------IYI OYUNLAR DILERIZ---------------------\n\n");
	printf("\n\n\nOyuna gecmek icin herhangi bir tusa basiniz....\n\n");
	getchar();
	system("cls");
	printf("OYUN TAHTANIZ ICIN BOYUT GIRINIZ (Once Satir Sonra Sutun): \n");
	scanf("%d  %d",&M,&N);
	
	while(yes==1){ // oyunumuzu default olarak baþlatýyoruz, kullanýcýmýz oyunu sonlandýrmak istediðinde yes deðiþkeni deðiþecek.
		oyunSayisi+=1; // oyunumuzu kaç kere oynadýðýmýzý kaydediyoruz.
		for(i=0;i<M;i++){
			for(j=0;j<N;j++){
				tabla[i][j]='.'; // tablamýzý hazýrlýyoruz, her oyuna baþlandýðýndan tablamýz '.' iþareti ile dolacak.
			}
		}
		control=0; // en üst satýrýmýzda herhangi bir parça olup olmadýðýnýn kontrolü. baþlangýçta parça olmadýðý için 0dan baþlatýyoruz.
		yazdir(tabla); // tablamýzý ekrana yazdýrýp oyunumuzu baþlatýyoruz.
		while(control==0){
			blok = rand()%7; // bloðumuzu rastgele alýyoruz, alacaðýmýz deðerleri if ile kontrol ederken uygun bloðu kullanýyoruz.
			printf("\nBLOK NO : %d",blok);
			if(blok==0){ // 111 þekli
				yeniBlokTemizle(yeniBlok); 
				yeniBlok[1][0]='X'; // burada kullanýcýmýza bloðu göstermek için yeniblok adlý matrisimize þeklimizi çiziyoruz.
				yeniBlok[1][1]='X';
				yeniBlok[1][2]='X';
				yeni_blok_yazdir(yeniBlok); // uygun iþlemlerle yeni bloðu çizdikten sonra bloðu ekrana yazdýrýyoruz.
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur == 'w' || dondur == 'W'){ // | 111 dikey hali olacak
					yazdir(tabla); // tablamýzý ekrana yazdýrýyoruz, system("cls") komutu ile üst kýsýmlarý temizleyip döndürülmüþ hali göstereceðiz.
					yeniBlokTemizle(yeniBlok);
					yeniBlok[0][1]='X';
					yeniBlok[1][1]='X';
					yeniBlok[2][1]='X';
					yeni_blok_yazdir(yeniBlok);
					sutunSor(); // kullanýcýmýzdan gösterilen bloðun en soldaki kýsmýnýn hangi sutuna yerleþtirileceðini istiyoruz.
					i=0; // tablamýzda seçilen koordinata uygun satýrý bulmak için tablamýzý kontrol eden kod kýsmýna geçiyoruz.
					flag=0;
					while(flag==0 && i<M-1){
						if(tabla[i][sutun]!='.'){ // tablamýzý i ve flag yapýsý ile, potansiyel yerleri kontrol ediyoruz.
							flag=1;    // eðer herhangi bir yer dolmuþsa döngüden çýkýp bulduðumuz yeri kaydedeceðiz.
						}
						if(tabla[i+1][sutun]!='.'){
							flag=1;
						}
						if(tabla[i+2][sutun]!='.'){
							flag=1;
						}
						i++;
					}
					yer=i-2; // döngüden çýktýktan sonra belirlenen i deðerine göre oluþacak deðeri yer adlý deðiþkenine atayarak iþlem yapýyoruz.
					tabla[yer][sutun]='X'; // kontrolümüzden sonra bulduðumuz uygun satýr ve sütunlara tablamýzda þeklimizi çizdiriyoruz.
					tabla[yer+1][sutun]='X';
					tabla[yer+2][sutun]='X';		
				}
				else{ // kodumuz bundan sonra benzer yapýda devam etmektedir. seçilen blok ve döndürülmüþ haline uygun kontroller yapýlarak uygun yere þeklimiz çizdiriliyor.
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

			else if(blok==1){ // T þekli tersten
				yeniBlokTemizle(yeniBlok);
				yeniBlok[0][1]='X';
				yeniBlok[1][0]='X';
				yeniBlok[1][1]='X';
				yeniBlok[1][2]='X';
				yeni_blok_yazdir(yeniBlok);
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ // ucu sola bakan T þekli
					yazdir(tabla);
					yeniBlokTemizle(yeniBlok);
					yeniBlok[1][1]='X';
					yeniBlok[0][2]='X';
					yeniBlok[1][2]='X';
					yeniBlok[2][2]='X';
					yeni_blok_yazdir(yeniBlok);
					printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
					scanf("%s",&dondur);
					if(dondur=='w' || dondur=='W'){ // düz T þekli
						yazdir(tabla);
						yeniBlokTemizle(yeniBlok);
						yeniBlok[1][0]='X';
						yeniBlok[1][1]='X';
						yeniBlok[1][2]='X';
						yeniBlok[2][1]='X';
						yeni_blok_yazdir(yeniBlok);
						printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
						scanf("%s",&dondur);
						
						if(dondur=='w' || dondur=='W'){ // ucu saða bakan T þekli
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
			else if(blok==2){ // Kare þeklimiz  **  þeklinde
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

			else if(blok==3){  // tek nokta þekli * þeklinde
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


			else if(blok==4){ // L Þekli
				yeniBlokTemizle(yeniBlok);
				yeniBlok[0][1]='X';
				yeniBlok[1][1]='X';
				yeniBlok[2][1]='X';
				yeniBlok[2][2]='X';	
				yeni_blok_yazdir(yeniBlok);
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ //    *  þeklinde olacak bloðumuz
					yazdir(tabla);              //  ***
					yeniBlokTemizle(yeniBlok);
					yeniBlok[1][2]='X';
					yeniBlok[2][0]='X';
					yeniBlok[2][1]='X';
					yeniBlok[2][2]='X';
					yeni_blok_yazdir(yeniBlok);
					printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
					scanf("%s",&dondur);
					if(dondur=='w' || dondur=='W'){ // ** þeklinde olacak parçamýz
						yazdir(tabla);              //  *
						yeniBlokTemizle(yeniBlok);  //  * 
						yeniBlok[0][1]='X';
						yeniBlok[0][2]='X';
						yeniBlok[1][2]='X';
						yeniBlok[2][2]='X';	
						yeni_blok_yazdir(yeniBlok);	
						printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
						scanf("%s",&dondur);
						if(dondur=='w' || dondur=='W'){ // ***  þeklinde olacak parçamýz
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
			else if(blok==5){ // dikey þekil 111
				yeniBlokTemizle(yeniBlok);
				yeniBlok[0][1]='X';
				yeniBlok[1][1]='X';	
				yeniBlok[2][1]='X';
				yeni_blok_yazdir(yeniBlok);
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ // *  þeklinde olacak parçamýz, dönmüþ þekilde.
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
			else if(blok==6){             //   **  þekli için kod
				yeniBlokTemizle(yeniBlok);//  **
				yeniBlok[0][1]='X';
				yeniBlok[0][2]='X';
				yeniBlok[1][0]='X';
				yeniBlok[1][1]='X';
				yeni_blok_yazdir(yeniBlok);	
				printf("\nDondurmek icin 'w' tusuna basiniz, istemiyorsaniz baska bir tusa basiniz : ");
				scanf("%s",&dondur);
				if(dondur=='w' || dondur=='W'){ //  *  þeklindeki parça için kodumuz
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
			score[oyunSayisi]+=1; // her bir parça yerleþtirildikten sonra puanýmýzý 1er arttýrýyoruz.
			h=0;
			while(h<M){ // bir satýrýn tamamen dolup dolmadýðýný kontrol eden döngümüz
				sayac=0;
				d=0;
				while(d<N){
					if(tabla[h][d]=='X'){ // en üst satýrdan alta kadar kontrol ediyoruz ve eðer satýrda blok parçasý varsa her parça için sayacý 1er arttýrýyoruz.
						sayac++; 
					}
					if(sayac==N){ // eðer sayacýmýz sutun sayýsýna eþitlendiyse o satýr tamamen dolduðunu anlamýþ olacaðýz.
						for(y=0;y<N;y++){
							for(t=h;t>0;t--){
								tabla[t][y]=tabla[t-1][y]; // burada da tablamýzda tamamen dolu olan satýrý silmek için bir döngü ile üstteki satýrlarý aþþaðýya kaydýrýyoruz.
							}
						}
						score[oyunSayisi]+=10; // eðer bir satýrý tamamen patlattýysak skorumuz 10 artýyor.
				
					}
					d++;
			
				}
				h++;
			}
	
			for(i=0;i<N;i++){
				if(tabla[0][i]=='X'){ // tablamýzýn en üst satýrýnda herhangi bir blok parçasý olup olmadýðýný kontrol ediyoruz. var ise oyun bitecektir.
					control=1;
				}
			}
			yazdir(tabla);
	
		} // control deðerimiz 1 olduðunda oyunumuz sonlanacaktýr.
		yes=0;
		printf("\n--- GAME OVER ----\n");	
		printf("Tekrar Oynamak icin 1 giriniz : "); // oyuncu oynamaya devam etmek istiyorsa 1 girecektir ve döngü yeniden baþlatýlacaktýr.
		scanf("%d",&yes);
		score[oyunSayisi+1]=0; // burada oyunSayisi+1 kullanarak bir sonraki tur oynanýrsa skorun 0dan baþlatýlmasýný saðlýyoruz.
		if(score[oyunSayisi]>score[max]){
			max=oyunSayisi; // eðer son oynanan oyundaki skor önceki max skordan fazla ise max deðerimiz güncellenecektir.
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
	system("cls"); // tablamýzý yazdýrmadan önce konsolu temizliyoruz
	printf("--OYUN TAHTANIZIN SON DURUMU -- --- MAX SKOR : %d\n\n",score[max]); // en üste rekor skorumuzu yazýyoruz
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("%2c ",oyunAlan[i][j]); // oyun alanýmýzýn son halini ekrana bastýrýyoruz.
		}
		printf("\n");
	}
	
	for(j=0;j<N;j++){
			printf("-- "); 
		}
	printf("\n");
	for(j=0;j<N;j++){ // kullanýcý hangi sutuna yerleþtirebileceðini seçebilmesi için görsellik açýsýndan tablamýzý yazdýktan sonra altýna satýr numaralarýný gösteriyoruz.
		if(j<9){
			printf(" %d ",j+1);
		}
		else{
			printf("%d ",j+1);
		}
		}
	
	printf("\n\nSkorunuz : %d",score[oyunSayisi]); // güncel skorumuzu tablamýzýn altýnda gösteriyoruz.
}

void yeni_blok_yazdir(char blokMatrisi[][3]){
	int i,j;
	printf("\nYeni Blok : \n\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%2c ",blokMatrisi[i][j]); // yeni bloðumuzu ekrana yazdýran komutumuz
			}
		printf("\n");
	}
}

void yeniBlokTemizle(char temizBlok[][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			temizBlok[i][j]=' '; // yeni bloðu kullandýktan sonra sonraki blok için temizlediðimiz komutumuz.
		}
	}
	
}

void sutunSor(){
	int i,j;
	printf("\n");
	printf("Sutun Giriniz : ");
	scanf("%d",&sutun); // kullanýcýdan hangi sutunu isteyeceðimizi belirttiðimiz kodumuz.
	while(sutun>N || sutun<1){ // girilen sutun tablamýzýn sutun sayýsýndan fazla veya 1den küçük ise girilecek sutunu tekrar istiyoruz.
		printf("\nGecersiz Sutun Degeri Girildi -- Tekrar Giriniz\n");
		printf("Sutun Giriniz : ");
		scanf("%d",&sutun);
	}
	sutun=sutun-1;
}
