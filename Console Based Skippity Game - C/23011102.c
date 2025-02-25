
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/*
	******************************************************************************************************************

	Videolu anlat�m drive linki : https://drive.google.com/file/d/1YmdQWp4FNg31aI8jCoyAJRPHyH12QD8p/view?usp=sharing

	******************************************************************************************************************

*/




typedef enum { // Oyundaki ta�lar�m�z i�in yeni bir veri t�r� tan�mlad�k.
    empty,
    A,
    B,
    C,
    D,
    E
} Skipper;

typedef struct { // Kazan�lan ta�larla ilgili puanland�rma hesab� i�in gereken struct.
    int sumOfTheSkippers;
    int leastSet;
    int leastSkipper;
}SkipperPoint;

typedef struct { // Undo, Redo ve di�er i�lemlerimizde belirli bir hamleyi bellekte tutmak i�in Move structu olu�turuyoruz.
    int moveRow, moveColumn;
    int newRow, newColumn;
    int capturedPiece;
} Move;

typedef struct Player { // Oyuncunun ismi ve kazand��� ta�lar� i�erecek bir struct.
    char* name;
    int gainedSkippers[6];
} Player;

typedef struct { // Oyunumuzun g�ncel durumunu tutmak i�in gerekli olan Struct. Bu struct ile oyun tahtas�, oyuncular�n kaznd�klar� ta�lar, Oyun modu, oyunun s�ras� ve yap�lan son hamlenin ne oldu�unu tutmu� olaca��z.
    int** board;
    int boardSize;
    Player player1, player2;
    int whichsTurn;
    Move lastMove;
    int gameMode;
}GameState;

int checkIsInBoard(int boardSize, int i, int j) { // Girdi�imiz koordinat�n oyun alan� s�n�rlar� i�erisinde kal�p kalmad���n� kontrol eden fonksyion.
    return i >= 0 && i < boardSize && j >= 0 && j < boardSize;
}

int takeBoardSize() { // Oyun tahtas�n�n ka�a ka�l�k �ekilde olu�turulaca��n� kullan�c�dan al�p istenmeyen durumlar�n da �nlenmesi i�in gereken fonksiyonumuz.
    int boardSize;
    while (1) {
        printf("\nEnter board size for your game (even number between 6 and 20): ");
        scanf("%d", &boardSize);

        if (boardSize >= 6 && boardSize <= 20 && boardSize % 2 == 0) {
            return boardSize;
        }
        else {
            printf("\nInvalid input. Please enter again.");
        }
    }
}



/*
	initializeBoard() fonksiyonu ile oyun tahtam�z i�in ald���m�z boyuta g�re bir oyun tahtas� olu�turuyoruz. Bunu malloc ile hallediyoruz.
	Daha sonras�nda oyun tahtam�za rastgele ta�lar�n dizilimini ger�ekle�tiriyoruz.



*/
int** initializeBoard(int boardSize) { 
    int maxPieceNum = (boardSize * boardSize) / 5 + 1;
    int i,j,piece;
    int numberOfSkippers[5] = {maxPieceNum, maxPieceNum, maxPieceNum, maxPieceNum, maxPieceNum};
    int** board = (int**) malloc(sizeof(int*) * boardSize);
    srand(time(NULL));
    if (!board) {
        printf("Memory Allocation Failed.");
        exit(1);
    }

    for (i = 0; i < boardSize; i++) {
        board[i] = (int*)malloc(sizeof(int) * boardSize);
        if (!board[i]) {
            printf("Memory Allocation Failed.");
            exit(1);
        }

        for (j = 0; j < boardSize; j++) {
            do {
                piece = rand() % 5;
            } while (numberOfSkippers[piece] == 0);

            board[i][j] = piece + 1;
            numberOfSkippers[piece]--;
        }
    }

    int index = boardSize / 2 - 1;
    board[index][index] = empty;
    board[index][index + 1] = empty;
    board[index + 1][index] = empty;
    board[index + 1][index + 1] = empty;

    return board;
}


void printBoard(int** board, int boardSize,Player* player1, Player* player2) { // Oyun tahtam�z� ve son puan durumlar�n� ekrana yazd�ran fonksiyon.
    int i, j;
	system("cls");    

    for (i = 0; i < boardSize; i++) {
        printf("%2d: |", i + 1);
        for (j = 0; j < boardSize; j++) {
            switch (board[i][j]) {
                case A: printf(" A "); break;
                case B: printf(" B "); break;
                case C: printf(" C "); break;
                case D: printf(" D "); break;
                case E: printf(" E "); break;
                default: printf(" . ");
            }
        }
        printf("|\n");
    }

    printf("     ");
    for (i = 0; i < boardSize; i++) {
        printf("-- ");
    }
    
    printf("\n     ");
    for (i = 0; i < boardSize; i++) {
        printf("%2d ", i + 1);
    }
    
    printf("\n");
    
    printf("\n%10s -> A : %d | B : %d | C : %d | D : %d | E : %d|",player1->name,player1->gainedSkippers[A],player1->gainedSkippers[B],player1->gainedSkippers[C],player1->gainedSkippers[D],player1->gainedSkippers[E]);
	printf("\n%10s -> A : %d | B : %d | C : %d | D : %d | E : %d|",player2->name,player2->gainedSkippers[A],player2->gainedSkippers[B],player2->gainedSkippers[C],player2->gainedSkippers[D],player2->gainedSkippers[E]);
	printf("\n\n");
	printf("-------------------------------------------------------------------");
	printf("\n");
}


void getMove(int* row, int* col, int boardSize) { // Oyuncu hamle yapmak istedi�inde hareket ettirmek istedi�i ta�� girdi olarak ald���m�z fonksiyon.
    do{
		printf("\nEnter the row of the skipper you want to move: ");
		scanf("%d", row);
		printf("\nEnter the column of the skipper you want to move: ");
		scanf("%d", col);
		(*row)--;
		(*col)--;
		if(!checkIsInBoard(boardSize,*row,*col)){
    		printf("\nInvalid input... Try Again");
		}
    	
	}while(!checkIsInBoard(boardSize,*row,*col));
}

void getNewPosition(int* newRow, int* newCol,int boardSize){ // Oyuncu yapt��� hamlede ta��n yeni konumunu istedi�imiz fonksiyon.
	do{
		printf("\nEnter the row of where you want to move your skipper : ");
    	scanf("%d", newRow);
    	printf("\nEnter the column of where you want to move your skipper : ");
    	scanf("%d", newCol);
    	(*newRow)--;
   		(*newCol)--;
    	
    	if(!checkIsInBoard(boardSize,*newRow,*newCol)){
    		printf("\nInvalid input...");
		}
	}while(!checkIsInBoard(boardSize,*newRow,*newCol));
	
    
}

/*
	makeMove() fonksiyonu, oyuncudan yapaca�� hamleleri ister ve yap�lacak hamlenin uygun olup olmad���n� kontrol eder.
	Hamle uygun de�ilse kullan�c�dan tekrar girdi ister, verilen hamle uygun olana kadar s�rd�r�r.
	Uygun hamle yakaland���nda da gereken hamle ger�ekle�tirilip oyuncuya kazand��� ta� puan olarak eklenir.
	Ayr�ca e�er oyuncu hamlesinden sonra farkl� bir hamle f�rsat� varsa bunu da belirtip yeni koordinat ister.
	
	*/

void makeMove(int** board, Player* player, int boardSize, Player* player2, GameState* gameState) {
    int answer =0;
    int moveRow, moveColumn, newRow, newColumn;
    printf("\n%s's turn\n", player->name);

    getMove(&moveRow, &moveColumn,boardSize);

    do {
    	answer = 0;
        getNewPosition(&newRow, &newColumn,boardSize);
		       
	    if (checkIsValidMove(board,  boardSize,  moveRow,  moveColumn,  newRow,  newColumn)){
	
	        if (newRow == moveRow){
	            if (newColumn > moveColumn && board[moveRow][moveColumn + 1] != empty) {
	                player->gainedSkippers[board[moveRow][moveColumn + 1]]++;
	                gameState->lastMove.capturedPiece = board[moveRow][moveColumn + 1];
	                board[moveRow][moveColumn + 1] = empty;
	            } else if (newColumn < moveColumn && board[moveRow][moveColumn - 1] != empty) {
	                player->gainedSkippers[board[moveRow][moveColumn - 1]]++;
	                gameState->lastMove.capturedPiece = board[moveRow][moveColumn - 1];
	                board[moveRow][moveColumn - 1] = empty;
	            }
	            board[newRow][newColumn] = board[moveRow][moveColumn];
	        	board[moveRow][moveColumn] = empty;
	        }else if (newColumn == moveColumn) {
	            if (newRow > moveRow && board[moveRow + 1][moveColumn] != empty) {
	                player->gainedSkippers[board[moveRow + 1][moveColumn]]++;
	                gameState->lastMove.capturedPiece = board[moveRow + 1][moveColumn];
	                board[moveRow + 1][moveColumn] = empty;
	            } else if (newRow < moveRow && board[moveRow - 1][moveColumn] != empty) {
	                player->gainedSkippers[board[moveRow - 1][moveColumn]]++;
	                gameState->lastMove.capturedPiece = board[moveRow - 1][moveColumn];
	                board[moveRow - 1][moveColumn] = empty;
	            }
	            board[newRow][newColumn] = board[moveRow][moveColumn];
	        	board[moveRow][moveColumn] = empty;
	        }
	        else{
	        	printf("\nInvalid Move 2 Gorelim Diye.\n");
	        	printf("\nInvalid move. Please Try again. ");
	       		getMove(&moveRow, &moveColumn,boardSize);
	       		getNewPosition(&newRow, &newColumn,boardSize);
	        	answer = 1;
			}
	        
	    }else {
	        printf("\nInvalid move 1. Please Try again. ");
	        getMove(&moveRow, &moveColumn,boardSize);
	        answer = 1;	        
	    }
	    
	    if(checkIsAnotherMove(board,boardSize,newRow,newColumn)){
	    	printf("\nThere is a possibility of another move, will you continue? (1 or 0) : ");
	    	scanf("%d",&answer);
	    	moveRow = newRow;
	    	moveColumn = newColumn;
		}
        
    }while (answer);
    
    gameState->lastMove.moveRow = moveRow;
    gameState->lastMove.moveColumn = moveColumn;
    gameState->lastMove.newRow = newRow;
    gameState->lastMove.newColumn = newColumn;
}



void undoMove(GameState* gameState) { // Hamleyi geri almam�za yarayan fonksiyonumuz.
    if (gameState->lastMove.capturedPiece == 0) {
        printf("No moves to undo!\n");
        return;
    }

    Move lastMove = gameState->lastMove;
    gameState->board[lastMove.moveRow][lastMove.moveColumn] = gameState->board[lastMove.newRow][lastMove.newColumn];
    gameState->board[lastMove.newRow][lastMove.newColumn] = empty;

    printf("\n Captured Piece : %d",gameState->lastMove.capturedPiece);
    gameState->board[(lastMove.moveRow + lastMove.newRow) / 2][(lastMove.moveColumn + lastMove.newColumn) / 2] = lastMove.capturedPiece;
    
    if(gameState->gameMode == 1){
    	gameState->player1.gainedSkippers[gameState->lastMove.capturedPiece]--;
    	return;
	}
    if(gameState->whichsTurn == 0){
        gameState->player1.gainedSkippers[lastMove.capturedPiece]--;
	}
	else{
		gameState->player2.gainedSkippers[lastMove.capturedPiece]--;
	}
        
    
    gameState->lastMove.capturedPiece = 0;

}

void redoMove(GameState* gameState) { // Geri ald���m�z hamleyi tekrar yapmak i�in gereken fonksiyonumuz.
    if (gameState->lastMove.capturedPiece != 0 && gameState->lastMove.moveRow == -1) {
        printf("No moves to redo!\n");
        return;
    }

    Move lastMove = gameState->lastMove;
    gameState->board[lastMove.newRow][lastMove.newColumn] = gameState->board[lastMove.moveRow][lastMove.moveColumn];
    lastMove.capturedPiece = gameState->board[(lastMove.moveRow + lastMove.newRow) / 2][(lastMove.moveColumn + lastMove.newColumn) / 2];
    gameState->board[lastMove.moveRow][lastMove.moveColumn] = empty;

    gameState->board[(lastMove.moveRow + lastMove.newRow) / 2][(lastMove.moveColumn + lastMove.newColumn) / 2] = empty;
    
    if(gameState->gameMode == 1){
    	gameState->player1.gainedSkippers[lastMove.capturedPiece]++;
    	return;
	}
    if(gameState->whichsTurn == 0){
        gameState->player1.gainedSkippers[lastMove.capturedPiece]++;
	}
	else{
		gameState->player2.gainedSkippers[lastMove.capturedPiece]++;
	}
	
}


void saveGame(GameState* gameState) { // Oyunu binary format�nda kaydeden fonksiyonumuz.
	int i;
    FILE* file = fopen("saved_game.bin", "wb");
    if (!file) {
        printf("Error saving the game!\n");
        return;
    }

    fwrite(&gameState->boardSize, sizeof(int), 1, file);
    for (i = 0; i < gameState->boardSize; i++) {
        fwrite(gameState->board[i], sizeof(int), gameState->boardSize, file);
    }

    fwrite(&gameState->whichsTurn, sizeof(int), 1, file);
    fwrite(&gameState->gameMode, sizeof(int), 1, file);
    fwrite(gameState->player1.gainedSkippers, sizeof(int), 6, file);
    fwrite(gameState->player2.gainedSkippers, sizeof(int), 6, file);
    fclose(file);
    printf("Game saved successfully.\n");
    sleep(2);
}

void loadGame(GameState* gameState) { // Binary dosyas�ndan verileri okuyarak kaydedilmi� versiyonu y�klememizi sa�layan fonksiyon.
	int i;
    FILE* file = fopen("saved_game.bin", "rb");
    if (!file) {
        printf("Error loading the game!\n");
        return;
    }

    fread(&gameState->boardSize, sizeof(int), 1, file);
    gameState->board = (int**)malloc(sizeof(int*) * gameState->boardSize);
    for (i = 0; i < gameState->boardSize; i++) {
        gameState->board[i] = (int*)malloc(sizeof(int) * gameState->boardSize);
        fread(gameState->board[i], sizeof(int), gameState->boardSize, file);
    }

    fread(&gameState->whichsTurn, sizeof(int), 1, file);
    fread(&gameState->gameMode, sizeof(int), 1, file);
    fread(gameState->player1.gainedSkippers, sizeof(int), 6, file);
    fread(gameState->player2.gainedSkippers, sizeof(int), 6, file);
    fclose(file);
    printf("Game loaded successfully.\n");
}


int checkIsAnotherMove(int** board,int boardSize,int i,int j){ // Yap�lan bir hamleden sonra yeni pozisyonda ba�ka bir hamle f�rsat� olup olmad���n� kontrol eden fonksiyon.
	int flag = 1;
	int (*fpCheck)(int,int,int);
	fpCheck = checkIsInBoard;
	
	if(fpCheck(boardSize,i+2,j) && board[i][j] != empty && board[i+1][j] != empty && board[i+2][j] == empty){
		return 1;
	}
	else if(fpCheck(boardSize,i-2,j) && board[i][j] != empty && board[i-1][j] != empty && board[i-2][j] == empty){
		return 1;
	}
	else if(fpCheck(boardSize,i,j+2) && board[i][j] != empty && board[i][j+1] != empty && board[i][j+2] == empty){
		return 1;
	}
	else if(fpCheck(boardSize,i,j-2) && board[i][j] != empty && board[i][j-1] != empty && board[i][j-2] == empty){
		return 1;
	}
	else{
		return 0;
	}
}


int checkIsValidMove(int** board, int boardSize, int moveRow, int moveColumn, int newRow, int newColumn) { // Girilen koordinatlardaki hamle se�ene�inin ge�erli bir hamle olup olmad���n� kontrol eden fonksiyon. 
    if (board[moveRow][moveColumn] == empty || board[newRow][newColumn] != empty) {
        return 0;
    }
    if (abs(newRow - moveRow) > 2 || abs(newColumn - moveColumn) > 2) {
        return 0;
    }
    if ((newRow == moveRow && abs(newColumn - moveColumn) == 2) || (newColumn == moveColumn && abs(newRow - moveRow) == 2)) {
        return 1;
    }
    return 0;
}


int checkIsGameEnd(int** board,int boardSize){ // Oyunda yap�lacak hamle kal�p kalmad���n� kontrol eden fonksiyon. Oyun Sonunda 0 d�nd�r�r ve oyunumuzun bitti�ini anlam�� oluruz.
	int i=0,j=0;
	while(i<boardSize){
		j=0;
		while(j<boardSize){
			if(checkIsAnotherMove(board, boardSize, i, j)){
				return 0;
			}
			j++;
		}
		i++;
	}
	return 1;
}

/*
	doAnotherMove() fonksiyonu bilgisayar modunda �st �ste 2 hamle se�ene�i tespit edildikten sonra 2. hamleyi ger�ekle�tiren fonksiyondur.


*/

void doAnotherMove(GameState* gameState, int i, int j){ 
	int (*fpCheck)(int,int,int);
	int boardSize = gameState->boardSize;
	fpCheck = checkIsInBoard;
	int k =0,l=0;
	int temp =0;
	int gainedSkipper = 0;
	
	if(fpCheck(boardSize,i+2,j) && gameState->board[i][j] != empty && gameState->board[i+1][j] != empty && gameState->board[i+2][j] == empty){
		k = i+2;
		l = j;
		gainedSkipper = gameState->board[i+1][j];
		gameState->board[i+1][j] = empty;
	}
	else if(fpCheck(boardSize,i-2,j) && gameState->board[i][j] != empty && gameState->board[i-1][j] != empty && gameState->board[i-2][j] == empty){
		k = i-2;
		l = j;
		gainedSkipper = gameState->board[i-1][j];
		gameState->board[i-1][j] = empty;
	}
	else if(fpCheck(boardSize,i,j+2) && gameState->board[i][j] != empty && gameState->board[i][j+1] != empty && gameState->board[i][j+2] == empty){
		k = i;
		l = j+2;
		gainedSkipper = gameState->board[i][j+1];
		gameState->board[i][j+1] = empty;
	}
	else if(fpCheck(boardSize,i,j-2) && gameState->board[i][j] != empty && gameState->board[i][j-1] != empty && gameState->board[i][j-2] == empty){
		k = i;
		l = j-2;
		gainedSkipper = gameState->board[i][j-1];
		gameState->board[i][j-1] = 0;
	}
	
	else{
		return;
	}
	printBoard(gameState->board, gameState->boardSize, &gameState->player1, &gameState->player2);
	
	
	gameState->board[k][l] = gameState->board[i][j];
	gameState->board[i][j] = empty;
	gameState->player2.gainedSkippers[gainedSkipper]++;
	return;
	
}

void evaluateSkipperPoint(Player* player,SkipperPoint* playerSkipperPoint){ // Skipperlardan elde edilen puan� hesaplayan ve oyun sonunda kimin kazand���n� kar��la�t�rmam�z� sa�layan fonksiyon
	int i,j,leastSet = 1000 ,leastSkipper = 1;								// Ayr�ca bu fonksiyonu bilgisayar modunda elimizde hangi ta�tan en az say�da var belirlemek i�in de kullan�yoruz.
	
	for(i=1;i<6;i++){
		if(leastSet>player->gainedSkippers[i]){
			leastSet = player->gainedSkippers[i];
			leastSkipper = i;
		}
	}
    int sumOfTheSkippers = player->gainedSkippers[A] + player->gainedSkippers[B] + player->gainedSkippers[C] + player->gainedSkippers[D] + player->gainedSkippers[E];
    
    playerSkipperPoint->leastSet =leastSet;
    playerSkipperPoint->leastSkipper = leastSkipper;
    playerSkipperPoint->sumOfTheSkippers = sumOfTheSkippers;
    
    return;
}

int** simulateMove(GameState* gameState, int** tempBoard, int i,int j,int k,int l){ // Bilgisayar modunda yap�lacak olas� bir hamleden sonra ba�ka bir hamle se�ene�i do�u do�mad���n� kontrol etmemize yarayan fonksiyon.
	int h,m;
	for(h=0;h<gameState->boardSize;h++){											// Oyun tahtas�n� olas� her hamle i�in de�i�tirmek yerine ge�i�i bir tahta yap�p yapt���m�z hamlenin etkisini o tahtadan g�r�yoruz.
		for(m=0;m<gameState->boardSize;m++){
			tempBoard[h][m] = gameState->board[h][m];
		}
	}
	tempBoard[k][l] = tempBoard[i][j];
	tempBoard[i][j] = empty;
	tempBoard[(k+i)/2][(j+l)/2] = empty;
	return tempBoard;
}


/*
	Bilgisayar�n hamle yapmas�n�n 2 temel opsiyonu vard�r.
	�lki �st �ste 2 hamle yapma se�ene�inin varl���d�r. B�yle bir hamle var ise bu hamle �nceliklendirilir.
	E�er �st �ste 2 hamle yapma �ans�m�z yok ise alaca��m�z ta��n seti en az say�da tutan ta� olmas� �nceliklendirilir.
	E�er bu 2 �art da sa�lanm�yorsa uygun hamlelerden ilki yap�lm�� olur.



*/

void makeComputerMove(GameState* gameState) { // Bilgisayara s�ra geldi�inde bilgisyar�n hamle yapmas�n� sa�layan fonksiyon.
	SkipperPoint skipperPoint;
	int boardSize = gameState->boardSize;
    int bestMoveValue = -1000;
    int moveValue = 0;
    Move bestMove;
    int i, j, k, l;
    
    int** tempBoard = (int**) malloc(sizeof(int*) * boardSize);
    if (!tempBoard) {
        printf("Memory Allocation Failed.");
        exit(1);
    }

    for (i = 0; i < boardSize; i++) {
        tempBoard[i] = (int*)malloc(sizeof(int) * boardSize);
        if (!tempBoard[i]) {
            printf("Memory Allocation Failed.");
            exit(1);
        }

        for (j = 0; j < boardSize; j++) {
        	tempBoard[i][j] = gameState->board[i][j];
        }
    }

    for (i = 0; i < gameState->boardSize; i++){
        for (j = 0; j < gameState->boardSize; j++) {
            if (gameState->board[i][j] != empty) {
                for (k = 0; k < gameState->boardSize; k++) {
                    for (l = 0; l <gameState->boardSize; l++) {
                    	moveValue = 0;
                        if (checkIsValidMove(gameState->board, gameState->boardSize, i, j, k, l)){
                        	moveValue += evaluateMove(gameState, i, j, k, l);
                        	tempBoard = simulateMove(gameState,tempBoard,  i, j, k, l);
                        	if(checkIsAnotherMove(tempBoard, boardSize,k,l)){
                        		moveValue += 10;
							}
                            if (moveValue > bestMoveValue) {
                                bestMoveValue = moveValue;
                                bestMove.moveRow = i;
                                bestMove.moveColumn = j;
                                bestMove.newRow = k;
                                bestMove.newColumn = l;
                            }
                        }
                    }
                }
            }
        }
    }
    
    evaluateSkipperPoint(&gameState->player2,&skipperPoint);
    gameState->board[bestMove.newRow][bestMove.newColumn] = gameState->board[bestMove.moveRow][bestMove.moveColumn];
    gameState->board[bestMove.moveRow][bestMove.moveColumn] = empty;
    
    if (bestMove.newRow == bestMove.moveRow) {
        if (bestMove.newColumn > bestMove.moveColumn) {
        	gameState->player2.gainedSkippers[gameState->board[bestMove.moveRow][bestMove.moveColumn + 1]]++;
            gameState->board[bestMove.moveRow][bestMove.moveColumn + 1] = empty;
        } else {
        	gameState->player2.gainedSkippers[gameState->board[bestMove.moveRow][bestMove.moveColumn - 1]]++;
            gameState->board[bestMove.moveRow][bestMove.moveColumn - 1] = empty;
        }
    } else {
        if (bestMove.newRow > bestMove.moveRow) {
            gameState->player2.gainedSkippers[gameState->board[bestMove.moveRow + 1][bestMove.moveColumn]]++;
            gameState->board[bestMove.moveRow + 1][bestMove.moveColumn] = empty;
        } else {
            gameState->player2.gainedSkippers[gameState->board[bestMove.moveRow - 1][bestMove.moveColumn]]++;
            gameState->board[bestMove.moveRow - 1][bestMove.moveColumn] = empty;
        }
    }
    
    if(checkIsAnotherMove(gameState->board, boardSize,bestMove.newRow,bestMove.newColumn)){
        doAnotherMove(gameState,bestMove.newRow,bestMove.newColumn);
	}
}



int evaluateMove(GameState* gameState, int moveRow, int moveColumn, int newRow, int newColumn){ // Yap�lacak olas� hamleden elde edilecek puan� hesaplayan fonksiyonumuz.
    int score = 0;
    SkipperPoint computerSkipperPoint;
    int gainedSkipper;
    evaluateSkipperPoint(&gameState->player2,&computerSkipperPoint);
    
    gainedSkipper = gameState->board[(moveRow + newRow) / 2][(moveColumn +newColumn) / 2];
    
    if(computerSkipperPoint.leastSkipper == gainedSkipper){
    	score += 10;
	}
	else{
		score += 5;
	}

    return score;
}

void play2Mode(GameState* gameState){ // 2 ki�ilik oyun modunun oynanmas�n� sa�layan fonksiyonumuz. Ayr�ca men� ve hamle s�ras� i�lemlerini ger�ekle�tiren fonksiyon.
    int i;
    
    
    char option = '1';
    while (!checkIsGameEnd(gameState->board, gameState->boardSize)){
        printBoard(gameState->board, gameState->boardSize, &gameState->player1, &gameState->player2);

        printf("Options:\n");
        printf("1. Make a move\n");
        printf("2. Undo the last move\n");
        printf("3. Redo the last undone move\n");
        printf("4. Save the game\n");
        printf("5. Exit\n");

        scanf("%c", &option);

        switch (option){
            case '1':
                if (gameState->whichsTurn == 0) {
                    makeMove(gameState->board, &gameState->player1, gameState->boardSize, &gameState->player2, gameState);
                    gameState->whichsTurn = 1;
                } else{
                    makeMove(gameState->board, &gameState->player2, gameState->boardSize, &gameState->player1, gameState);
                    gameState->whichsTurn = 0;
                }
                break;
            case '2':
            	if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                undoMove(gameState);
                
                if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                break;
            case '3':
            	if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                redoMove(gameState);
                if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                break;
            case '4':
                saveGame(gameState);
                break;
            case '5':
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}


void playWithComputer(GameState* gameState){ // Bilgisayar modunda oynamam�z� sa�layan, men� ve hamle s�ras� i�lemlerini ger�ekle�tiren fonksiyon.
    int i;
    char option = '1';
    while (!checkIsGameEnd(gameState->board, gameState->boardSize)){
        printBoard(gameState->board, gameState->boardSize, &gameState->player1, &gameState->player2);
        
        printf("Options:\n");
		printf("1. Contiune the game\n");
	    printf("2. Undo the last move\n");
	    printf("3. Redo the last undone move\n");
	    printf("4. Save the game\n");
	    printf("5. Exit\n");
	    printf("Choose your option : ");
	    scanf("%c", &option);
		
        

        switch (option){
            case '1':
                if (gameState->whichsTurn == 0) {
                    makeMove(gameState->board, &gameState->player1, gameState->boardSize, &gameState->player2, gameState);
                    gameState->whichsTurn = 1;
                }else{
                	printf("\nComputer Is Making a move...\n");
                	sleep(1);
                	makeComputerMove(gameState);
                    gameState->whichsTurn = 0;
                }
                break;
            case '2':
            	if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                undoMove(gameState);
                
                if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                break;
            case '3':
            	if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                redoMove(gameState);
                if (gameState->whichsTurn == 0){
            		gameState->whichsTurn = 1;
				}
				else{
					gameState->whichsTurn = 0;
				}
                break;
            case '4':
                saveGame(gameState);
                break;
            case '5':
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int determineTheWinner(SkipperPoint player1Skipper,SkipperPoint player2Skipper){ // Oyun Sonunda kazanan oyuncunun tespit edilmesini sa�layan fonksiyon.
	if(player1Skipper.leastSet > player2Skipper.leastSet){
		return 0;
	}
	else if(player2Skipper.leastSet > player1Skipper.leastSet){
		return 1;
	}
	else{
		if(player1Skipper.sumOfTheSkippers>player2Skipper.sumOfTheSkippers){
			return 0;
		}
		else if(player2Skipper.sumOfTheSkippers>player1Skipper.sumOfTheSkippers){
			return 1;
		}
		else{
			return 2;
		}
	}
	
}

void printPlayer(Player* player) { // Oyun sonunda oyuncu ve kazand��� ta�lar�n ekrana bast�r�lmas�n� ger�ekle�tiren fonksiyon.
    printf("\n%s : \n", player->name);
    printf("Gained Skippers:\n");
    printf("A: %d\n", player->gainedSkippers[A]);
    printf("B: %d\n", player->gainedSkippers[B]);
    printf("C: %d\n", player->gainedSkippers[C]);
    printf("D: %d\n", player->gainedSkippers[D]);
    printf("E: %d\n", player->gainedSkippers[E]);
}




int main() { // Oyunumuzun modunu mainde istiyoruz. Ve tercihe g�re istenilen mod �al��t�r�l�r. Oyun sonunda kazan�lan�n da tespit edilmesini sa�lar.
	int option,i;
	printf("******* Welcome to Skippity Game *******\n");
	printf("\n1 - Load a saved game ");
	printf("\n2 - Play 2 players mode");
	printf("\n3 - Play Against Computer ");
	printf("\n\nChoose one of the options Above : ");
	scanf("%d",&option);
	GameState gameState;
	if(option == 1){
		loadGame(&gameState);
		if(gameState.gameMode == 0){
			gameState.player1.name = "Player 1";
			gameState.player2.name = "Player 2";
		}
		else{
			gameState.player1.name = "Player 1";
			gameState.player2.name = "Computer";
		}
	}
	else{
		gameState.boardSize = takeBoardSize();
		gameState.board = initializeBoard(gameState.boardSize);
		gameState.player1.name = "Player 1";
		gameState.gameMode = option-2;
		if(gameState.gameMode == 0){
			gameState.player2.name = "Player 2";
		}
		else{
			gameState.player2.name = "Computer";
		}
		for (i = 0; i < 6; i++) {
        gameState.player1.gainedSkippers[i] = 0;
        gameState.player2.gainedSkippers[i] = 0;
    	}
		gameState.whichsTurn = 0;
	}
	
	if(gameState.gameMode == 0){
		play2Mode(&gameState);
	}
	else{
		playWithComputer(&gameState);
	}
	
	printBoard(gameState.board, gameState.boardSize, &gameState.player1, &gameState.player2);
	sleep(2);
	printf("\n*****Game over!*******\n\n");
	SkipperPoint player1Skipper;
	SkipperPoint player2Skipper;
	evaluateSkipperPoint(&gameState.player1,&player1Skipper);
	evaluateSkipperPoint(&gameState.player2,&player2Skipper);
	int winner = determineTheWinner(player1Skipper,player2Skipper);
	
	printPlayer(&gameState.player1);
	printf("\n-------------------\n");
	printPlayer(&gameState.player2);
	
	

	
	if(winner == 0){
		printf("\nPlayer 1 is the winner. There were at least %d sets of each tile.",player1Skipper.leastSet);
	}
	else if(winner == 1){
		if(gameState.gameMode == 1){
			printf("\nComputer is the winner. There were at least %d sets of each tile.",player2Skipper.leastSet);
		}
		else{
			printf("\nPlayer 2 is the winner. There were at least %d sets of each tile.",player2Skipper.leastSet);
		}
	}
	else{
		printf("\nFriendship won. The match ended in a draw.");
	}
	
		
	for (i = 0; i < gameState.boardSize; i++) {
		free(gameState.board[i]);
	}
	free(gameState.board);

    return 0;
}
