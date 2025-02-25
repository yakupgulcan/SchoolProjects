#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


typedef enum{ // Operatör tipleri burada bulunacak. Bu operatör türleri operator stackte tuttuðumuzu anlamak ve performoperationu adam gibi yapmamýz için.
	Subtract,
	Addition,
	Multiplication,
	Division,
	Exponent,
	Logarithm,
	Cosinus,
	Sinus,
	Tangent,
	Cotangent,
	Arcsinus,
	Arccosinus,
	Arctangent,
	Arccotangent,
	RightBracket,
	LeftBracket,
	null
}Operator;

typedef struct OperatorStack{
	Operator opert;
	struct OperatorStack* next;
	struct OperatorStack* prev;
	
	
}OperatorStack;

typedef struct OutputStack{
	float value;
	bool checkNull; // Linked list icinde ilk dugumun durumunu kontrol etmemiz gerekecek.
	struct OutputStack* next;
	struct OutputStack* prev;
	
	
}OutputStack;

void printMatrix(float** matrix,int row,int column);
void gaussEleminationMethod();
void gaussSeidelMethod();
float numericalDerivative(char* expression, float valueX, float h, int option);
float** inverseOfMatrix();
void gregoryNewton();
float bisection(char* expression, float a, float b, float tol);
float regulaFalsi(char* expression, float a, float b, float tol);
float newtonRaphson(char* expression, float x0, float tol);
float simpson13(char* expression, float a, float b, int n);
float simpson38(char* expression, float a, float b, int n);
float trapezoid(char* expression, float a, float b, int n);
OutputStack* initializeOutputNode();
OperatorStack* initializeOperatorNode();
void pushOutputNode(OutputStack* headOutput,float val);
void pushOperatorNode(OperatorStack* head,OutputStack* headOutput,Operator op);
Operator popOperatorNode(OperatorStack* head);
float evaluateExpression(char* expression, float valueX);
int findPrecedence(Operator opr);
float performOperation(Operator op, OutputStack* head);
void popOutputNode(OutputStack* head);
void menu();


int main() {
	
    menu();
    return 0;
}

void menu() {
    int choice;
    float a, b, x0;
    float valueX,result,tol;
    char* expression;
    int option,n;
    
    printf("--------------------------------\n\n");
    printf("1. Bisection Method\n");
    printf("2. Regula-Falsi Method\n");
    printf("3. Newton-Raphson Method\n");
    printf("4. Inverse of Matrix\n");
    printf("5. Gauss Elemination Method\n");
    printf("6. Gauss-Seidel Method\n");
    printf("7. Numerical Derivative\n");
    printf("8. Simpson Method\n");
    printf("9. Trapezoidal Method\n");
    printf("10. Gregory-Newton Interpolation\n");
    printf("11. Calculate Function \n");
    printf("\n--------------------------------\n");
    /*printf("Choose Your Method: ");
    scanf("%d", &choice);*/
    while(choice!=0){
    	printf("\nChoose Your Method: ");
    	scanf("%d", &choice);
    	
    	switch(choice){
        case 1:
        	expression = (char*) malloc(sizeof(char)*100);
			printf("Enter your mathematical expression : ");
			scanf("%s",expression);
			printf("Enter the starting range a and b: ");
            scanf("%f %f", &a, &b);
            printf("Enter the tolerence : ");
            scanf("%f", &tol);
            printf("Bisection method result : %f\n", bisection(expression, a, b, tol));
			free(expression);
			break;
        case 2:
        	expression = (char*) malloc(sizeof(char)*100);
			printf("Enter your mathematical expression : ");
			scanf("%s",expression);
			printf("Enter the starting range a and b: ");
			scanf("%f %f", &a, &b);
            printf("Enter the tolerence : ");
            scanf("%f", &tol);
            printf("Regula-Falsi method result: %f\n", regulaFalsi(expression, a, b, tol));
            free(expression);
            break;
        case 3:
        	expression = (char*) malloc(sizeof(char)*100);
			printf("Enter your mathematical expression : ");
			scanf("%s",expression);
            printf("Enter the starting value : ");
            scanf("%f", &x0);
            printf("Enter the tolerence : ");
            scanf("%f", &tol);
            printf("Newton-Raphson method result: %f\n", newtonRaphson(expression, x0, tol));
            free(expression);
            break;
        case 4:
            inverseOfMatrix();
            break;    
        case 5:
            gaussEleminationMethod();
            break;
        case 6:
            gaussSeidelMethod();
            break;
        case 7:
        	printf("\n1. Derivative with forward difference");
        	printf("\n2. Derivative with back difference");
        	printf("\n3. Derivative with central difference");
        	printf("\nChoose one of the options : ");
        	scanf("%d",&option);
        	expression = (char*) malloc(sizeof(char)*100);
			printf("Enter your mathematical expression : ");
			scanf("%s",expression);
			printf("Enter your x value : ");
			scanf("%f",&valueX);
			printf("Enter your tolerence(h) value : ");
			scanf("%f",&tol);
        	result = numericalDerivative(expression, valueX,tol,option);
            printf("\nDerivative at %f is : %f",valueX,result);
            free(expression);
            break;
        case 8:
        	expression = (char*) malloc(sizeof(char)*100);
        	printf("\nFor Simpson 1/3 enter 1 or for Simpson 3/8 enter 2 :");
        	scanf("%d",&option);
        	printf("Enter your mathematical expression : ");
			scanf("%s",expression);
            printf("Enter the starting and ending ranges (a and b) and the number of divisions (n): ");
            scanf("%f %f %d", &a, &b, &n);        	
        	switch(option){
        		case 1:
        			printf("Simpson 1/3 method result: %f\n", simpson13(expression, a, b, n));
        			break;
        		case 2:
        			printf("Simpson 3/8 method result: %f\n", simpson38(expression, a, b, n));
        			break;
        		default:
        			printf("\nThere is no such a option.");
			}
            free(expression);
            break;
        case 9:
        	expression = (char*) malloc(sizeof(char)*100);
			printf("Enter your mathematical expression : ");
			scanf("%s",expression);
            printf("Enter the starting and ending ranges (a and b) ");
            scanf("%f %f", &a, &b);
            printf("Enter the number of divisions (n): ");
            scanf("%d", &n);
            printf("Trapezoidal method result : %f\n", trapezoid(expression, a, b, n));
            free(expression);
            break;
        case 10:
            gregoryNewton();
            break;
        case 11:
            expression = (char*) malloc(sizeof(char)*100);
			printf("Enter your mathematical expression : ");
			scanf("%s",expression);
			printf("Enter your x value : ");
			scanf("%f",&valueX);
			result = evaluateExpression(expression,valueX);
			printf("\nResult for your mathematical expression :  %s for x = %f --- Result is = %.3f",expression,valueX,result);
			free(expression);
            break;
        default:
            printf("Invalid Option!\n");
        
	}
	
    }
}

float bisection(char* expression, float a, float b, float tol) {
    if (evaluateExpression(expression, a) * evaluateExpression(expression, b) >= 0) {
        printf("\nThere is no root for these values of a and b.");
        return 0;
    }

    int i = 0;
    float mid;
    while ((b - a) > tol && i < 100) {
        mid = (a + b) / 2;
        
        printf("\n\nIteration %d:\na = %f\nb = %f\nmid = %f\nf(mid) = %f\n", 
               i+1, a, b, mid, evaluateExpression(expression, mid));
        
        if (evaluateExpression(expression, mid) == 0.0) {
            printf("\nMid Value reached to zero, cannot proceed further...");
            return mid;
        } else if (evaluateExpression(expression, mid) * evaluateExpression(expression, a) < 0) {
            b = mid;
        } else {
            a = mid;
        }

        i++;
    }

    printf("Root found at x = %f after %d iterations\n", mid, i+1);

    return mid;
}

float regulaFalsi(char* expression, float a, float b, float tol) {
    if (evaluateExpression(expression, a) * evaluateExpression(expression, b) >= 0) {
        printf("\nThere is no root for these values of a and b.");
        return 0;
    }

    int i = 0;
    float c;
    
    do {
        c = (a * evaluateExpression(expression, b) - b * evaluateExpression(expression, a)) / (evaluateExpression(expression, b) - evaluateExpression(expression, a));
        
        printf("\n\nIteration %d:\na = %f\nb = %f\nc = %f\nf(c) = %f\n", 
               i+1, a, b, c, evaluateExpression(expression, c));
        
        if (evaluateExpression(expression, c) == 0) {
            printf("\nValue of c has reached to zero, cannot proceed further...");
            return c;
        } else if (evaluateExpression(expression, c) * evaluateExpression(expression, a) < 0) {
            b = c;
        } else {
            a = c;
        }
        
        i++;
    } while (fabs(evaluateExpression(expression, c)) > tol && i < 100);
    
    printf("Root found at x = %f after %d iterations\n", c, i);

    return c;
}

float newtonRaphson(char* expression, float x0, float tol) {
    float h;
    int i = 0;

    do {
        float fx = evaluateExpression(expression, x0);
        float dfx = numericalDerivative(expression, x0, 0.00001, 3);
        h = fx / dfx;

        printf("\n\nIteration %d:\nx0 = %f\nf(x0) = %f\nf'(x0) = %f\n", 
               i+1, x0, fx, dfx);

        x0 = x0 - h;
        i++;
    } while (fabs(h) >= tol && i < 100);


    printf("Root found at x = %f after %d iterations\n", x0, i);

    return x0;
}


float simpson13(char* expression, float a, float b, int n) {
    float h = (b - a) / n;
    float sum = evaluateExpression(expression,a) + evaluateExpression(expression,b);
    int i;
    for (i = 1; i < n; i += 2)
        sum += 4 * evaluateExpression(expression,a + i * h);
    for (i = 2; i < n-1; i += 2)
        sum += 2 * evaluateExpression(expression,a + i * h);

    return (h / 3) * sum;
}


float simpson38(char* expression, float a, float b, int n) {
	int i;
	float x;
    if (n % 3 != 0) {
        printf("\nn must be a multiple of 3 for Simpson's 3/8 rule.\n");
        return 0;
    }

    float h = (b - a) / n;
    float sum = evaluateExpression(expression, a) + evaluateExpression(expression, b);

    for (i = 1; i < n; i++) {
        x = a + i * h;
        if (i % 3 == 0) {
            sum += 2 * evaluateExpression(expression, x);
        } else {
            sum += 3 * evaluateExpression(expression, x);
        }
    }

    return (3 * h / 8) * sum;
}


float trapezoid(char* expression, float a, float b, int n) {
	int i;
    float h = (b - a) / n;
    float sum = (evaluateExpression(expression,a) + evaluateExpression(expression,b)) / 2;
    
    for (i = 1; i < n; i++){
    	sum += evaluateExpression(expression,a + i * h);
	}
	float result = h*sum;
        
    return result;
}


OutputStack* initializeOutputNode(){
	OutputStack* head = (OutputStack*) malloc(sizeof(OutputStack));
	if(!head){
		printf("Memory Allocation Failed.");
		return NULL;
	}
	head->prev = NULL;
	head->next = NULL;
	head->checkNull = true;
	return head;
}


OperatorStack* initializeOperatorNode(){
	OperatorStack* head = (OperatorStack*) malloc(sizeof(OperatorStack));
	if(!head){
		printf("Memory Allocation Failed.");
		return NULL;
	}
	head->prev = NULL;
	head->next = NULL;
	head->opert = null;
	return head;
}

float evaluateExpression(char* expression, float valueX){
	OperatorStack* operatorHead = initializeOperatorNode();
	OutputStack* outputHead = initializeOutputNode();
	int i = 0;
	float holdVal = 1;
	Operator tempOp;
    float returnValue;
	
	while (expression[i] != '\0') {
        if((expression[i] >= '0' && expression[i] <= '9') || expression[i] == 'x' || expression[i] == 'e'){
        	if((expression[i] >= '0' && expression[i] <= '9')){
        		sscanf(&expression[i], "%f", &holdVal);
        		i++;
			}
        	
        	while ((expression[i] >= '0' && expression[i] <= '9') || (expression[i] == '.')){
        		i++;
			}
            
            if(expression[i] != 'x' && expression[i] != 'e'){
            	pushOutputNode(outputHead,holdVal);
            	i--;
			}
			
			else if(expression[i] == 'x'){
                pushOutputNode(outputHead,holdVal);
				pushOperatorNode(operatorHead,outputHead,Multiplication);
           		pushOutputNode(outputHead,valueX);
			}
			
			else if(expression[i] == 'e'){
				pushOutputNode(outputHead,holdVal);
				pushOperatorNode(operatorHead,outputHead,Multiplication);
           		pushOutputNode(outputHead,M_E);
			}
			
            holdVal = 1;
		}
		
		else if (expression[i] == 'l' && expression[i + 1] == 'o' && expression[i + 2] == 'g') {
            pushOperatorNode(operatorHead,outputHead,Logarithm);
            i += 3;
        }
		
		else if (expression[i] == 's' && expression[i + 1] == 'i' && expression[i + 2] == 'n') {
            pushOperatorNode(operatorHead,outputHead,Sinus);
            i += 2;
        } 
		
		else if (expression[i] == 'c' && expression[i + 1] == 'o' && expression[i + 2] == 's') {
            pushOperatorNode(operatorHead,outputHead,Cosinus);
            i += 2;
        } 
		
		else if (expression[i] == 't' && expression[i + 1] == 'a' && expression[i + 2] == 'n') {
			pushOperatorNode(operatorHead,outputHead,Tangent);
			i += 2;
        }
        
		else if (expression[i] == 'c' && expression[i + 1] == 'o' && expression[i + 2] == 't') {
			pushOperatorNode(operatorHead,outputHead,Cotangent);
			i += 2;
        }
        
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' &&
                   expression[i + 3] == 's' && expression[i + 4] == 'i' && expression[i + 5] == 'n') {
                   	
            pushOperatorNode(operatorHead,outputHead,Arcsinus);
            i += 5;
        } 
		
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' &&
                   expression[i + 3] == 'c' && expression[i + 4] == 'o' && expression[i + 5] == 's') {
            pushOperatorNode(operatorHead,outputHead,Arccosinus);
            i += 5;
        } 
		
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' &&
                   expression[i + 3] == 't' && expression[i + 4] == 'a' && expression[i + 5] == 'n') {
            pushOperatorNode(operatorHead,outputHead,Arctangent);
            i += 5;
        } 
		
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' &&
                   expression[i + 3] == 'c' && expression[i + 4] == 'o' && expression[i + 5] == 't') {
            pushOperatorNode(operatorHead,outputHead,Arccotangent);
            i += 5;
    	}
    	else if(expression[i] == '-'){
    		pushOperatorNode(operatorHead,outputHead,Subtract);
        	
		}
		else if(expression[i] == '+'){
			pushOperatorNode(operatorHead,outputHead,Addition);
        	
		}
		else if(expression[i] == '/'){
			pushOperatorNode(operatorHead,outputHead,Division);
        	
		}
		else if(expression[i] == '*'){
			pushOperatorNode(operatorHead,outputHead,Multiplication);
        	
		}
        else if(expression[i] == '^'){
        	pushOperatorNode(operatorHead,outputHead,Exponent);
		}
        
        else if(expression[i] == '('){
        	pushOperatorNode(operatorHead,outputHead,LeftBracket);
        	
		}
		
		else if(expression[i] == ')'){
			pushOperatorNode(operatorHead,outputHead,RightBracket);
        	
		}
        i++;
        
    }
    while(operatorHead->opert != null){
    	tempOp = popOperatorNode(operatorHead);
		returnValue = performOperation(tempOp,outputHead);
		pushOutputNode(outputHead,returnValue);
	}
    
    return outputHead->value;
}

int findPrecedence(Operator opr) {
    switch (opr) {
        case Addition:
        case Subtract:
        case LeftBracket:
            return 1;
        case Multiplication:
        case Division:
            return 2;
        case Exponent:
            return 3;
        case Logarithm:
        case Cosinus:
        case Sinus:
        case Tangent:
        case Cotangent:
        case Arcsinus:
        case Arccosinus:
        case Arctangent:
        case Arccotangent:
            return 4;
        default:
            return -1;
    }
}

float performOperation(Operator op, OutputStack* head) {
	OutputStack* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    float tempVal1 = current->value;
    float tempVal2 = current->prev ? current->prev->value : 0;
    popOutputNode(head);
	
    switch (op) {
        case Addition:
        	popOutputNode(head);
            return tempVal1 + tempVal2;
        case Subtract:        	
        	popOutputNode(head);
            return tempVal2 - tempVal1;
        case Multiplication:
        	popOutputNode(head);
            return tempVal1 * tempVal2;
        case Division:
        	popOutputNode(head);
            return tempVal2 / tempVal1;
        case Exponent:
        	popOutputNode(head);
            return pow(tempVal2, tempVal1);
        case Logarithm:
        	popOutputNode(head);
            return log(tempVal1)/log(tempVal2);  
        case Sinus:
            return sin(tempVal1);  
        case Cosinus:
            return cos(tempVal1);  
        case Tangent:
            return tan(tempVal1);  
        case Cotangent:
            return 1 / tan(tempVal1);  
        case Arcsinus:
            return asin(tempVal1);
        case Arccosinus:
            return acos(tempVal1);  
        case Arctangent:
            return atan(tempVal1);  
        case Arccotangent:
            return atan(1 / tempVal1); 
        default:
            printf("Invalid operation\n");
            return 0.0;
    }
}

void pushOutputNode(OutputStack* headOutput, float val) {
	if(headOutput->checkNull == true){
		headOutput->value = val;
		headOutput->checkNull = false;
		headOutput->next = NULL;
		return;
	}
	else{
		OutputStack* current;
		current = headOutput;
		
		while (current->next != NULL) {
			current = current->next;
		}
		
		OutputStack* additionNode = (OutputStack*)malloc(sizeof(OutputStack));
		if (!additionNode) {
	    	printf("Memory allocation failed.");
	    	return;
		}
		
		additionNode->value = val;
		additionNode->prev = current;
		additionNode->next = NULL;
		current->next = additionNode;
		current = additionNode;
		current->next = NULL;
		return ;
	}
}


void pushOperatorNode(OperatorStack* head,OutputStack* headOutput,Operator op){
	OperatorStack* current = head;
	Operator tempOp;
	float returnValue;
	
	while(current->next != NULL){
		current = current->next;
	}
	
	if(head->opert == null){
		head->opert = op;
		return ;
	}
	
	if(op == LeftBracket){ // eðer gelecek operrtör ( ise
		OperatorStack* additionNode = (OperatorStack*) malloc(sizeof(OperatorStack));
		if(!additionNode){
			printf("Memory Allocation failed..");
			return ;
		}
		additionNode->opert = op;
		additionNode->next = NULL;
		additionNode->prev = current;
		current->next = additionNode;
		return;
	}
	else if(op == RightBracket)	{
		while(current->opert != LeftBracket ){
			if(head->next != NULL){
				current = current->prev;
			}
			
			tempOp = popOperatorNode(head);
			returnValue = performOperation(tempOp,headOutput);
			pushOutputNode(headOutput,returnValue);
		}
		popOperatorNode(head);
	}
	else{
		if(findPrecedence(op)<=findPrecedence(current->opert)){
			while(findPrecedence(current->opert)>findPrecedence(op)){
				if(head->next != NULL){
				current = current->prev;
				}
				tempOp = popOperatorNode(head);
				returnValue = performOperation(tempOp,headOutput);
				pushOutputNode(headOutput,returnValue);
			}			
			
			if(head->opert == null){
				head->opert = op;
			}
			else{
				OperatorStack* additionNode = (OperatorStack*) malloc(sizeof(OperatorStack));
				if(!additionNode){
				printf("Memory Allocation Failed..");
				return ;
				}
				additionNode->opert = op;
				additionNode->next = NULL;
				additionNode->prev = current;
				current->next = additionNode;
			}
			
			
		}
		else{
			OperatorStack* additionNode = (OperatorStack*) malloc(sizeof(OperatorStack));
			if(!additionNode){
				printf("Memory Allocation Failed..");
				return ;
			}
			additionNode->opert = op;
			additionNode->next = NULL;
			additionNode->prev = current;
			current->next = additionNode;
		}
		
	}
	
}



Operator popOperatorNode(OperatorStack* head){
	OperatorStack* current = head;
	OperatorStack* tempNode = NULL;
	Operator temp;
	
	if(head->opert == null){
		printf("Error :  Operator Stack is empty. ");
		return;
	}
	else if(head->next == NULL){
		temp = head->opert;
		head->opert = null;
		return temp;
	}
	else{
		while(current->next != NULL){
			current = current->next;
		}
		
		temp = current->opert;
		tempNode = current;
		current = current->prev;
		current->next = NULL;
		free(tempNode);
		return temp;
	}
}


void popOutputNode(OutputStack* head){
	OutputStack* current = head;
	OutputStack* temp = NULL;
	
	if(head->checkNull == true){
		printf("\n***Output node is already empty***\n");
		return;
	}
	else if(head->next == NULL){
		head->checkNull = true;
	}
	else{
		while(current->next != NULL){
		current = current->next;
		}
		current->prev->next = NULL;
		free(current);
	}
}


void gaussEleminationMethod(){
	int N;
	printf("\nHow many equations/variables will be in your matrix : ");
	scanf("%d",&N);
	float** augmentedMatrix = (float**) malloc(sizeof(float*)*N);
	if(!augmentedMatrix){
		printf("\nMemory allocation failed...");
		return;
	}
	int i;
	int j;
	for(i=0;i<N;i++){
		augmentedMatrix[i] = (float *) malloc(sizeof(float)*(N+1));
		
		if(!augmentedMatrix[i]){
		printf("\nMemory allocation failed...");
		return;
		}
		
		for(j=0;j<N+1;j++){
			printf("Enter AugmentedMatrix[%d][%d] : ",i+1,j+1);
			scanf("%f",&augmentedMatrix[i][j]);
		}
	}
	printf("\n\nOriginal Augmented Matrix : \n");
	printMatrix(augmentedMatrix,N,N+1);
	
	int k;
	float* tempRow;
	float holdDiagonal;
	float holdMultiple;
	
	for(i=0;i<N;i++){
		if(augmentedMatrix[i][i] == 0){
			k=i+1;
			while(augmentedMatrix[k][i] == 0 && k<N){
				k++;
			}
			
			if(k==N && augmentedMatrix[k][i] == 0){
				printf("\nFailed matrix is cannot be inverted");
				return;
			}
			
			tempRow = augmentedMatrix[i];
			augmentedMatrix[i] = augmentedMatrix[k];
			augmentedMatrix[k] = tempRow;
		}
		
		holdDiagonal = augmentedMatrix[i][i]; 
		for(j=0;j<N+1;j++){     // Burada matrisimizdeki satýrlarý matrisin köþegenlerine gelen satýrlara bölüyoruz ki köþegenler hep 1 olsun.
			augmentedMatrix[i][j] = (float)augmentedMatrix[i][j]/holdDiagonal;
		}
		
		for(k=i+1;k<N;k++){
			holdMultiple = augmentedMatrix[k][i]/augmentedMatrix[i][i]; // köþegenin altýndaki deðerleri 0 lamak için köeþegen ile ayný sütünua denk gelen elemanýn katsayýsýný alýyoruz. sonradan çarpýp çýkaracaðýz.
			
			for(j=0;j<N+1;j++){
			augmentedMatrix[k][j] = augmentedMatrix[k][j] - (augmentedMatrix[i][j]*holdMultiple); // burada da köþegenin altýndaki satýrlardan köþegenin olduðu satýr * katsayýyý çýkarýyoruz.
			}
		}
		
	}
	
	float* solutionArray = (float*) malloc(sizeof(float)*N);
	if(!solutionArray){
		printf("failed");
		return ;
	}
	
	float solution;
	float sum;
	
	for(i=N-1;i>=0;i--){
		sum = augmentedMatrix[i][N];
		
		for(j=N-1;j>i;j--){
			sum -= augmentedMatrix[i][j]*solutionArray[j];
		}
		
		
		
		solution = sum/augmentedMatrix[i][i];
		
		//printf("\nnow %d and solution is %f\n",i,solution);
		
		solutionArray[i] = solution;
		
	}
	
	printf("\n\nInverted Matrix : \n");
	printMatrix(augmentedMatrix,N,N+1);
	
	for(i=0;i<N;i++){
		printf("\nSolution for x%d : %f",i+1,solutionArray[i]);
	}
	
	
	
	
}

void gaussSeidelMethod(){
	int N;
	printf("\nHow many equations/variables will be in your matrix : ");
	scanf("%d",&N);
	float** augmentedMatrix = (float**) malloc(sizeof(float*)*N);
	if(!augmentedMatrix){
		printf("\nMemory allocation failed...");
		return;
	}
	int i;
	int j;
	for(i=0;i<N;i++){
		augmentedMatrix[i] = (float *) malloc(sizeof(float)*(N+1));
		
		if(!augmentedMatrix[i]){
		printf("\nMemory allocation failed...");
		return;
		}
		
		for(j=0;j<N+1;j++){
			printf("Enter Matrix[%d][%d] : ",i+1,j+1);
			scanf("%f",&augmentedMatrix[i][j]);
		}
	}
	
	
	float* tempRow;
	int maxRow = 0;
	
	for(i=0;i<N;i++){ // Matriste çaprazýn çarpýmýný en büyük olacak þekilde ayarlýyoruz.
		maxRow = 0;
		for(j=0;j<N;j++){
			if(fabsf(augmentedMatrix[j][i]) >= fabsf(augmentedMatrix[maxRow][i])){
				maxRow = j;
			}
		}
		tempRow = augmentedMatrix[i];
		augmentedMatrix[i] = augmentedMatrix[maxRow];
		augmentedMatrix[maxRow] = tempRow;
	}
	
	float** solutionMatrix = (float**) calloc(1,sizeof(float*));
	*solutionMatrix = (float*) calloc(N,sizeof(float));
	
	printf("\nEnter starting values for iterations : ");
	
	for(i=0;i<N;i++){
		printf("x%d : ",i+1);
		scanf("%f",&solutionMatrix[0][i]);
	}
	
	printf("\nEnter epsilon : ");
	float epsilon;
	scanf("%f",&epsilon);
	
	int flag = 0;
	float solution;
	int k=1; 
	float sum;
	int h;
	int flag2;
	
	while(!flag && k<100){
		solutionMatrix = (float**) realloc(solutionMatrix,sizeof(float*)*(k+1));
		solutionMatrix[k] = (float*) malloc(sizeof(float)*N);		
	
		for(i=0;i<N;i++){
			sum = augmentedMatrix[i][N];
			
			for(j=0;j<i;j++){
			
				sum -= augmentedMatrix[i][j]*solutionMatrix[k][j];
			}
			
			for(h=j+1;h<N;h++){
				sum -= augmentedMatrix[i][h]*solutionMatrix[k-1][h];
			}
			
			solution = sum/augmentedMatrix[i][i];
			solutionMatrix[k][i] = solution;
		}
		flag2 = 0;
		for(i=0;i<N;i++){
			if(fabsf(solutionMatrix[k][i]-solutionMatrix[k-1][i])>epsilon){
				flag2 = 1;
			}
		}
		
		if(!flag2){
			flag = 1;
		}
		k++;	
	}
	
	printf("\nYour Entry Matrix : \n");
	printMatrix(augmentedMatrix,N,N+1);
	printf("\n\nYour Solution Matrix : \n");
	printMatrix(solutionMatrix,k,N);
}


void gregoryNewton() {
    int N, i, j;
    float valueX;

    printf("\nHow many values will you enter: ");
    scanf("%d", &N);

    float* xArray = (float*) malloc(N * sizeof(float));
    float* yArray = (float*) malloc(N * sizeof(float));
    
    printf("\nEnter your values:\n");
    for (i = 0; i < N; i++) {
        printf("x%d: ", i);
        scanf("%f", &xArray[i]);
        printf("y%d: ", i);
        scanf("%f", &yArray[i]);
    }

    float** differenceTable = (float**) malloc(N * sizeof(float*));
    
    for (i = 0; i < N; i++) {
        differenceTable[i] = (float*) malloc((N - i) * sizeof(float));
        differenceTable[i][0] = yArray[i];
    }

    for (j = 1; j < N; j++) {
        for (i = 0; i < N - j; i++) {
            differenceTable[i][j] = differenceTable[i + 1][j - 1] - differenceTable[i][j - 1];
        }
    }

    // Print the difference table
    printf("\nDifference Table:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N - i; j++) {
            printf(" |%5.2f| ", differenceTable[i][j]);
        }
        printf("\n");
    }
        float x0;

    printf("\nEnter the Value of X : ");
    scanf("%f",&valueX);
    /*printf("\nEnter the Value of x0 : ");
    scanf("%f",&x0);*/
    
    float summation;
    summation = yArray[0];
    float lValue;
    float hValue = xArray[1]-xArray[0];
    float multiplicaton = 1;
    lValue = (valueX-xArray[0])/hValue;
    
    for(i=1;i<N;i++){
    	for(j=0;j<i;j++){
    		multiplicaton *= (lValue-j);
		}
		
		multiplicaton = multiplicaton/tgamma(i+1);
		multiplicaton *= differenceTable[0][i];
		summation += multiplicaton;
		multiplicaton = 1;
	}
	
	printf("\n\nYour function result for x = %f is : %f ",valueX,summation);
	





    for (i = 0; i < N; i++) {
        free(differenceTable[i]);
    }
    
    free(differenceTable);
    free(xArray);
    free(yArray);
}






float** inverseOfMatrix(){
	printf("Enter rows and columns number for the matrix : ");
	int N;
	scanf("%d",&N);
	float** myMatrix;
	myMatrix = (float**) malloc(sizeof(float*)*N);
	float** identityMatrix;
	identityMatrix = (float**) malloc(sizeof(float*)*N);
	int i;
	int j;
	
	if(!identityMatrix || !myMatrix){
			printf("\nMemory failed..");
			return;
		}
	
	for(i=0;i<N;i++){
		myMatrix[i] = (float*) malloc(sizeof(float)*N);
		if(!myMatrix[i]){
			printf("\nMemory failed..");
			return;
		}
		for(j=0;j<N;j++){
			printf("\nEnter Matrix[%d][%d] : ",i+1,j+1);
			scanf("%f",&myMatrix[i][j]);
		}
	}
	printf("\nOriginal matrix : \n");
	printMatrix(myMatrix,N,N);
	
	for(i=0;i<N;i++){
		identityMatrix[i] = (float*) malloc(sizeof(float)*N);
		if(!identityMatrix[i]){
			printf("\nMemory failed..");
			return;
		}
		for(j=0;j<N;j++){
			identityMatrix[i][j] = 0.0f;
			}
		identityMatrix[i][i] = 1.0f;
	}
	
	int k=0;
	float *tempRow;
	float holdDiagonal;
	float holdMultiple;
	
	
	for(i=0;i<N;i++){
		
		if(myMatrix[i][i] == 0){ // matrisin ilk satýrýnýn sütünu 0 diye kontrol et. varsa hata düzelt.
			k = i+1;
			while(myMatrix[k][i] == 0 && k<N){ // burada myMatrix[i][k] idi ama þansa çalýþýyormuþ meðer
				k++;
			}
			
			if(k==N && myMatrix[i][k] == 0){
				printf("\nFailed matrix is cannot be inverted");
				return;
			}
			
			tempRow = myMatrix[i];
			myMatrix[i] = myMatrix[k];
			myMatrix[k] = tempRow;
			tempRow = identityMatrix[i];
			identityMatrix[i] = identityMatrix[k];
			identityMatrix[k] = tempRow;
		}
		
		holdDiagonal = myMatrix[i][i];
		for(j=0;j<N;j++){
			myMatrix[i][j] = (float)myMatrix[i][j]/holdDiagonal;
			identityMatrix[i][j] = (float) identityMatrix[i][j]/holdDiagonal;
		}
		
		for(k=1;k<N-i;k++){
			holdMultiple = myMatrix[i+k][i]/myMatrix[i][i];
			
			for(j=0;j<N;j++){
			myMatrix[i+k][j] = myMatrix[i+k][j] - (myMatrix[i][j]*holdMultiple);
			identityMatrix[i+k][j] -= (identityMatrix[i][j]*holdMultiple);
			}
		}
	}
	
		for(i=N-1;i>=0;i--){
			for(k=1;k<i+1;k++){
				holdMultiple = (float) myMatrix[i-k][i]/myMatrix[i][i];
				for(j=0;j<N;j++){
					myMatrix[i-k][j] = myMatrix[i-k][j]-(myMatrix[i][j]*holdMultiple);
					identityMatrix[i-k][j] -= (identityMatrix[i][j]*holdMultiple);
				}
			}
		}
	
	printf("\nInverted Matrix : \n");
	printMatrix(identityMatrix,N,N);
	
	
	for(i=0;i<N;i++){
		free(identityMatrix[i]);
		free(myMatrix[i]);
	}
	free(identityMatrix);
	free(myMatrix);
	return identityMatrix;
	
}



float numericalDerivative(char* expression, float valueX, float h, int option){
	float derivative;
	switch(option){
		case 1:
			derivative = (evaluateExpression(expression,(valueX+h))-evaluateExpression(expression,valueX))/h;
			break;
		case 2:
			derivative = (evaluateExpression(expression,valueX)-evaluateExpression(expression,(valueX-h)))/h ;
			break;
		case 3:
			derivative = (evaluateExpression(expression,(valueX+h))-evaluateExpression(expression,(valueX-h)))/(2*h);
			break;
		default:
			printf("!!!! Failed Derivative !!!!");
			return 0;
	}
	
	return derivative;
	
}

void printMatrix(float** matrix,int row,int column){
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf(" |%.3f| ",matrix[i][j]);
		}
		printf("\n");
		
	}
	return;
	
}
