#include <stdio.h>    // Gerekli kütüphanelerin yüklenmesi.
#include <stdlib.h>	 //
#include <math.h>
#include <time.h> 
//!!!#include <string.h>

#define TRAIN_ROWS 8000 		// Eðitim kümesindeki örnek sayýsý
#define INPUT_SIZE 785  		// Modelin giriþ büyüklüðü /28*28+1
#define EPSILON 1e-8 			// log(0) ve 0a bölmeden kaçýnmak için eps deðeri
#define NUM_CLASSES 4			// Verideki sýnýf sayýsý
#define LEARNING_RATE 0.1		// GD ve SGD için learning rate
#define ADAM_LEARNING_RATE 0.01 // Adam için learning rate
#define EPOCHS 50				// Epochs sayýsý, 1 epoch = veri kümesindeki tüm örneklerin kullanýlmasý
#define EPOCH_PERIOD 10			// epoch bilgisinin hangi aralýklarla bastýrýlacaðýný belirlemek için deðiþken
#define TEST_COUNT 2000			// Test kümesindeki örnek sayýsý
#define ADAM_BETA1 0.9			// Adam için hyperparameterlar
#define ADAM_BETA2 0.999		


// Kaydedilecek dosyalarýn isimleri
#define ADAM_LOG "adam_logs_d.csv"
#define ADAM_WEIGHTS "adam_weights_d.csv"
#define GD_LOG "gd_logs_d.csv"
#define GD_WEIGHTS "gd_weights_d.csv"
#define SGD_LOG "sgd_logs_d.csv"
#define SGD_WEIGHTS "sgd_weights_d.csv"
#define SAVED_WEIGHTS "saved_weights_d.txt"





/*
Oluþturacaðýmýz model ile ilgili verileri struct yapýsýnda tutarak kod karmaþýklýðýnýn önüne geçiyoruz.
Model ile ilgili ve fonksiyonlarda sýkça beraber kullanýlan deðerleri Model structumuzda tutuyoruz.
*/

typedef struct {
    double **train_data;
    int *train_labels;
    double **weights;
    double *logits; 				// softmax öncesi z deðerlerini tutan pointer
    double *probabilities;			// z çýktýlarýnýn softmaxe verilerek her sýnýf için tahminin belirlenmesi
    double **gradients;
    double **initial_weights;		// modelleri çalýþtýrmadan önce elde ettiðimiz random weightsleri kaydediyoruz.
    double **test_data;
    int *test_labels;
    double **logs;					// modellerin her epochtaki loss, accuracy ve zaman metriklerini tutmak için pointer
    /*
	Allocate Memory For Logs
    
    train_loss
    train_accuracy
    test_loss
    test_accuracy
    time_elapsed
    */
    
    // Adam parametreleri
    double **adam_m;  // First moment estimate
    double **adam_v;  // Second moment estimate
    int adam_t;        // Adam Timestep 
} Model;


void softmax(Model *model);
double compute_loss(double *predictions, int true_label);
void free_model(Model *model);
void read_train_data(const char *data_file, const char *label_file, Model *model); 
void free_adam_params(Model *model); 
int predict(Model *model, double *input);
void compute_gradients(Model *model);
void gradient_descent(Model *model);
void train_model_gd(Model *model);
void train_model_sgd(Model *model);
void initialize_adam_params(Model *model);
//void save_weights(Model *model, char *file_name);
void reset_weights(Model *model);
double calculate_accuracy_train(Model *model);
double calculate_accuracy_test(Model *model);
double compute_test_loss(Model *model);
double compute_train_loss(Model *model);
void save_txt(double* data, int size, char* label);
void save_logs(Model *model, char *label);
void save_weights_log(Model *model, const char *filename, int epoch);
void train_model_adam(Model *model);


void save_weights(Model *model){
	FILE *fp_weight = fopen(SAVED_WEIGHTS,"w");
	int i,j;
	
    for(i=0;i<NUM_CLASSES;i++){
    	for(j=0;j<INPUT_SIZE;j++)
    		fprintf(fp_weight,"%lf ",model->weights[i][j]);
	}
    
    
    fclose(fp_weight);
}
void load_weights(Model *model){
	// Read weights
	int i,j;
    FILE *weight_file = fopen(SAVED_WEIGHTS, "r");
    if(weight_file == NULL) {
        fprintf(stderr, "Error opening weight file\n");
    }
    
    for(i = 0; i < NUM_CLASSES; i++) {
        for(j = 0; j < INPUT_SIZE; j++) {
            if(fscanf(weight_file, "%lf", &model->weights[i][j]) != 1) {
                fprintf(stderr, "Error reading weights\n");
                fclose(weight_file);
            }
        }
    }
    fclose(weight_file);
}

void print_weights(Model *model) {
    int i, j;
    for(i = 0; i < NUM_CLASSES; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            printf("%lf\n", model->weights[i][j]);
        }
    }
}

int main() {
	
	/*
	
	Model veri tipinden yapýmýzý oluþturuyoruz.
	train_data ve labelleri vererek modelimize gerekli bilgilieri yüklüyoruz.
	Sýrasýyla gd, sgd ve adam algoritmalarýný çalýþtýrýyoruz.
	algoritma geçiþleri öncesinde model parametrelerini initial deðerlere getiriyoruz.
	
	*/
    Model model;
    read_train_data("4class_train_data.txt", "4class_train_label.txt", &model);
    //load_weights(&model);
    //save_weights(&model);
    
    int a = 3;
    
    
    
    switch (a) {
		case 1:
			load_weights(&model);
			printf("\n---- ADAM --- \n");
		    train_model_adam(&model);
		    printf("\nADAM test loss : %lf\n",compute_test_loss(&model));
		    reset_weights(&model);
		// code block
			break;
		case 2:
			load_weights(&model);
			printf("---- Gradient Descent ---\n");
		    train_model_gd(&model);
		    printf("\nGD test loss : %lf\n",compute_test_loss(&model));
		    reset_weights(&model);
		// code block
			break;
		case 3:
			load_weights(&model);
			printf("\n---- Stochastic Gradient Descent --- \n");
		    train_model_sgd(&model);
		    printf("SGD test loss : %lf\n",compute_test_loss(&model));
		    reset_weights(&model);
		// code block
			break;
		default:
			printf("default");
	}
    
    
    
    
    /*printf("\n---- ADAM --- \n");
    train_model_adam(&model);
    printf("\nADAM test loss : %lf\n",compute_test_loss(&model));
    reset_weights(&model); */
    
    //print_weights(&model);
    /*printf("---- Gradient Descent ---\n");
    train_model_gd(&model);
    printf("\nGD test loss : %lf\n",compute_test_loss(&model));
    reset_weights(&model);
    
    printf("\n---- Stochastic Gradient Descent --- \n");
    train_model_sgd(&model);
    printf("SGD test loss : %lf\n",compute_test_loss(&model));
    reset_weights(&model);*/
    
    
    
    
    free_model(&model);
    
    return 0;
}




void read_train_data(const char *data_file, const char *label_file, Model *model) {
    FILE *data_fp, *label_fp,*test_label_file,*test_data_file; // dosyalardan okuma yapmamýz için gereken file pointerlar
    int i, j, row;

    // modelimizdeki tüm pointerleri NULL olarak baþlatýyoruz
    model->train_data = NULL;
    model->train_labels = NULL;
    model->weights = NULL;
    model->logits = NULL;
    model->probabilities = NULL;
    model->gradients = NULL;
    model->adam_m = NULL;
    model->adam_v = NULL;
    model->initial_weights = NULL;
    model->test_data = NULL;
    model->test_labels = NULL;
    model->logs = NULL;

    // Memory allocation
    model->train_data = (double **)malloc(TRAIN_ROWS * sizeof(double *));
    model->train_labels = (int *)malloc(TRAIN_ROWS * sizeof(int));
    model->weights = (double **)malloc(NUM_CLASSES * sizeof(double *));
    model->logits = (double *)malloc(NUM_CLASSES * sizeof(double));
    model->probabilities = (double *)malloc(NUM_CLASSES * sizeof(double));
    model->gradients = (double **)malloc(NUM_CLASSES * sizeof(double *));
    model->initial_weights = (double **)malloc(NUM_CLASSES * sizeof(double *));
    model->test_labels = (int *) malloc(TEST_COUNT * sizeof(int));
    model->logs = (double **) malloc(5 * sizeof(double *));
    
    // logs
    for(i=0;i<5;i++){
    	model->logs[i] = (double *)malloc(EPOCHS * sizeof(double));
	}
	
    // test_data
    model->test_data = (double **)malloc(TEST_COUNT * sizeof(double *));
    for (i = 0; i < TEST_COUNT; i++) {
        model->test_data[i] = (double *)malloc(INPUT_SIZE * sizeof(double));
    }
    
    // Dosyadan okuma 
    test_label_file = fopen("4class_test_label.txt", "r");
    if(test_label_file == NULL) {
        fprintf(stderr, "Error opening label file\n");
        exit(1);
    }
    
    for (i = 0; i < TEST_COUNT; i++) {
        if (fscanf(test_label_file, "%d", &model->test_labels[i]) != 1) {
            fprintf(stderr, "Error reading label at line: %d\n", i);
            fclose(test_label_file);
            exit(1);
        }
    }
    fclose(test_label_file);
    
    
    test_data_file = fopen("4class_test_data.txt", "r");
    if(test_data_file == NULL) {
        fprintf(stderr, "Error opening data file\n");
        exit(1);
    }

    for (i = 0; i < TEST_COUNT; i++) {
        for (j = 0; j < INPUT_SIZE-1; j++) {
            if (fscanf(test_data_file, "%lf", &model->test_data[i][j]) != 1) {
                fprintf(stderr, "Error reading data at line: %d, column: %d\n", i, j);
                fclose(test_data_file);
                exit(1);
            }
        }
        model->test_data[i][INPUT_SIZE-1] = 1.0;  // Bias term
    }
    fclose(test_data_file);
    
    
    // Weights, gradients memory allocation. rastgele deðerler yerine 0dan baþlamalarý için calloc kullandýk.
    for (i = 0; i < NUM_CLASSES; i++) {
        model->weights[i] = (double *)calloc(INPUT_SIZE, sizeof(double));
        model->gradients[i] = (double *)calloc(INPUT_SIZE, sizeof(double));
        model->initial_weights[i] = (double *)calloc(INPUT_SIZE, sizeof(double));
    }

    // parametrelerin rastgele olarak baþlatýlmasý
    srand(time(NULL));
    for (i = 0; i < NUM_CLASSES; i++) {
        for (j = 0; j < INPUT_SIZE; j++) {
            model->weights[i][j] = (double) rand()/RAND_MAX*0.1 - 0.05 ;
            model->initial_weights[i][j] = model->weights[i][j];
        }
    }

    // Train verisinin okunmasý
    label_fp = fopen(label_file, "r");
    if (!label_fp) {
        perror("Label file could not be opened");
        exit(1);
    }
    for (i = 0; i < TRAIN_ROWS; i++) {
        if (fscanf(label_fp, "%d", &model->train_labels[i]) != 1) {
            fprintf(stderr, "Error reading label\n");
            fclose(label_fp);
            exit(1);
        }
    }
    fclose(label_fp);

    // Open and read data file
    data_fp = fopen(data_file, "r");
    if (!data_fp) {
        perror("Data file could not be opened");
        exit(1);
    }
    for (i = 0; i < TRAIN_ROWS; i++) {
        model->train_data[i] = (double *)malloc(INPUT_SIZE * sizeof(double));
        for (j = 0; j < INPUT_SIZE - 1; j++) {
            if (fscanf(data_fp, "%lf", &model->train_data[i][j]) != 1) {
                fprintf(stderr, "Error reading data\n");
                fclose(data_fp);
                exit(1);
            }
        }
        model->train_data[i][INPUT_SIZE - 1] = 1.0; // bias terimi için son hücreyi 1den baþlatýyoruz.
    }
    fclose(data_fp);
    
    // Veri özellikle SGD'de belli bir sýrada olmamasý için veriyi karýþtýrma iþlemi yapýyoruz.
    for (row = 0; row < TRAIN_ROWS; row++) {
        srand(time(NULL));
        int swap_index = rand() % TRAIN_ROWS;
            
        // Swap 
        double *temp_data = model->train_data[row];
        int temp_label = model->train_labels[row];
            
        model->train_data[row] = model->train_data[swap_index];
        model->train_labels[row] = model->train_labels[swap_index];
            
        model->train_data[swap_index] = temp_data;
        model->train_labels[swap_index] = temp_label;
    }
        
        
}

// adam algoritmasý çalýþtýðýnda parametrelerinin baþlatýlmasý için fonksiyon
void initialize_adam_params(Model *model) {
    int i, j;
    
    
    model->adam_m = (double **)malloc(NUM_CLASSES * sizeof(double*));
    model->adam_v = (double **)malloc(NUM_CLASSES * sizeof(double*));
    
    
    for (i = 0; i < NUM_CLASSES; i++) {
    	model->adam_m[i] = (double *)calloc(INPUT_SIZE, sizeof(double));
        model->adam_v[i] = (double *)calloc(INPUT_SIZE, sizeof(double));
    }
    
    model->adam_t = 0; // timestep
}

// programýmýzý çalýþtýrdýktan bellek tahsisini geri veriyoruz
void free_adam_params(Model *model) {
	int i,j;
    if (model->adam_m) {
        for (i = 0; i < NUM_CLASSES; i++) {
            free(model->adam_m[i]);
        }
        
        free(model->adam_m);
        model->adam_m = NULL;
    }
        

    if (model->adam_v) {
        for ( i = 0; i < NUM_CLASSES; i++) {
                free(model->adam_v[i]);
        }
    
        free(model->adam_v);
        model->adam_v = NULL;
    }
}

// programýmýzý çalýþtýrdýktan bellek tahsisini geri veriyoruz
void free_model(Model *model) {
	int i;
    // Free training data
    if (model->train_data) {
        for ( i = 0; i < TRAIN_ROWS; i++) {
            free(model->train_data[i]);
        }
        free(model->train_data);
        model->train_data = NULL;
    }

    // Free labels
    free(model->train_labels);
    model->train_labels = NULL;

    // Free weights
    if (model->weights) {
        for ( i = 0; i < NUM_CLASSES; i++) {
            free(model->weights[i]);
            free(model->initial_weights[i]);
        }
        free(model->weights);
        free(model->initial_weights);
        model->weights = NULL;
        model->initial_weights = NULL;
    }

    // Free other allocations
    free(model->logits);
    free(model->probabilities);

    // Free gradients
    if (model->gradients) {
        for ( i = 0; i < NUM_CLASSES; i++) {
            free(model->gradients[i]);
        }
        free(model->gradients);
        model->gradients = NULL;
    }
    
    for (i = 0; i < TEST_COUNT; i++) {
        free(model->test_data[i]);
    }
    free(model->test_data);
    free(model->test_labels);

    // Free Adam parameters if they exist
    free_adam_params(model);
}

// weightslerin initial deðerlerine döndürmemiz için fonksiyon
void reset_weights(Model *model){
	int cls, feature;
	
	for(cls=0; cls < NUM_CLASSES; cls++){
		for(feature = 0; feature < INPUT_SIZE; feature++){
			model->weights[cls][feature] = model->initial_weights[cls][feature];
		}
	}
}

// forward passte elde ettiðimiz z deðerlerini olasýlýk deðerlerine dönüþtürmek için softmax fonksiyonu
void softmax(Model *model) {
    int i;
    double max_z = model->logits[0];

    // Overflow'u önlemek için max deðer bulma
    for (i = 1; i < NUM_CLASSES; i++) {
        if (model->logits[i] > max_z) {
            max_z = model->logits[i];
        }
    }

    double logits_expsum = 0.0;
    for (i = 0; i < NUM_CLASSES; i++) {
        model->probabilities[i] = exp(model->logits[i] - max_z);
        logits_expsum += model->probabilities[i];
    }

    // Normalize etme
    for (i = 0; i < NUM_CLASSES; i++) {
        model->probabilities[i] /= logits_expsum;
    }
}


// Categorical cross entropy kullanarak tek bir veri örneði için hata hesaplamasý
double compute_loss(double *predictions, int true_label) {
    return -log(predictions[true_label] + EPSILON);
}

// adam ve gradient descent algoritmasýnda her epochta gradyanlarý hesaplayan fonksiyon
void compute_gradients(Model *model) {
    int cls, row, feature;

    // gradyanlarý önce 0 ile dolduruyoruz.
    for (cls = 0; cls < NUM_CLASSES; cls++) {
        for (feature = 0; feature < INPUT_SIZE; feature++) {
            model->gradients[cls][feature] = 0.0;
        }
    }

    // Eðitim setindeki her veri örneði için gradyanlarý hesaplýyoruz
    for (row = 0; row < TRAIN_ROWS; row++) {
    	
        // predict fonksiyonu kullanarak bulunduðumuz satýra ait olasýlýklarý elde ediyoruz
        predict(model, model->train_data[row]);

        // gradyanlarý hesaplayýp topluyoruz NUM_CLASSES*INPUT_SIZE kadar parametre
        // burada hem modelimizin gerçek etiketten farkýný hem de yanlýþ etiket için verdiði olasýlýklarý kullanýyoruz.
        // Bu sayede daha kararlý bir öðrenme süreci elde ediyoruz.
        for (cls = 0; cls < NUM_CLASSES; cls++) {
            // gradyan hesabýnda kullanýlan y-y_hat deðerini kullanýyoruz.
            double error = model->probabilities[cls] - (cls == model->train_labels[row] ? 1.0 : 0.0);
            
            // g(w[cls][feature]) = (y[row]-y_hat[row])*x[row][feature] yaparak hesaplama yapýyoruz.
            for (feature = 0; feature < INPUT_SIZE; feature++) {
                model->gradients[cls][feature] += error * model->train_data[row][feature];
            }
        }
    }

    // Gradyanlarý normalize ediyoruz
    for (cls = 0; cls < NUM_CLASSES; cls++) {
        for (feature = 0; feature < INPUT_SIZE; feature++) {
            model->gradients[cls][feature] /= TRAIN_ROWS;
        }
    }
}

// veri örnekleri için tahmin edilen deðeri hesaplayan fonksiyon.
int predict(Model *model, double *input) {
    int cls, feature;
    int predicted_class = 0;
    
    // logits yani z deðerlerini hesaplýyoruz
    for(cls = 0; cls < NUM_CLASSES; cls++) {
        model->logits[cls] = 0.0;
        for(feature = 0; feature < INPUT_SIZE; feature++) {
            model->logits[cls] += input[feature] * model->weights[cls][feature];
        }
    }
    
    // Softmax
    softmax(model);
    
    // en yüksek olasýlýða sahip sýnýf etiketini buluyoruz
    for(cls = 1; cls < NUM_CLASSES; cls++) {
        if(model->probabilities[cls] > model->probabilities[predicted_class]) {
            predicted_class = cls;
        }
    }
    
    return predicted_class;
}

// gradyanlarý kullanarak weightleri güncelleyecek gradient descent algoritmasý wt+1 = wt - e*dL/dw
void gradient_descent(Model *model) {
    int cls, feature;
    // Iterate through all classes
    for (cls = 0; cls < NUM_CLASSES; cls++) {
        // Iterate through all features (including bias)
        for (feature = 0; feature < INPUT_SIZE; feature++) {
            // Update weights using the precomputed gradients
            model->weights[cls][feature] -= LEARNING_RATE * model->gradients[cls][feature];
        }
    }
}


// modeli gradient descent ile eðitmemiz için fonksiyon
void train_model_gd(Model *model) {
    int epoch, row, cls, feature;
    clock_t start, end; // algoritmanýn çalýþma süresini kaydetmek için deðiþkenler
    double elapsed_time;
	start = clock(); // döngü baþlamadan önceki zamaný ölçüyoruz
	
    for (epoch = 0; epoch < EPOCHS; epoch++) {
    	
    	save_weights_log(model, GD_WEIGHTS, epoch); 		// T-sne ile görselleþtirme için her epochta mevcut weightleri kaydediyoruz
    	
    	
    	/*
    	Modelimizin performansý için her epochta model metriklerini kaydediyoruz.
    	train ve test kümesi için loss ve doðruluk hesaplýyoruz.
    	*/
        model->logs[0][epoch] = compute_train_loss(model);			
        model->logs[1][epoch] = calculate_accuracy_train(model);
        model->logs[2][epoch] = compute_test_loss(model);
        model->logs[3][epoch] = calculate_accuracy_test(model);
		
		// modelimizin eðitim sürecini ekrana bastýrma        
        if (epoch % EPOCH_PERIOD == 0 || epoch == 0) {
            printf("Epoch %d, Loss: %f\n", epoch, model->logs[0][epoch]);
        }

        //Gradyanlarý hesapla ve güncelle
        compute_gradients(model);
        gradient_descent(model);
        
        // her epochta geçen sürenin kaydýný tutuyoruz.
    	end = clock();
    	elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    	model->logs[4][epoch] = elapsed_time;

    }
    // modelimiz çalýþmasýný bitirdikten sonra elde ettiðimiz verileri csv formatýnda kaydediyoruz
    save_logs(model,GD_LOG);
}


// modelin sgd ile eðitilmesi için fonksiyon
void train_model_sgd(Model *model) {
    int epoch, cls, feature, row, iteration;
    clock_t start, end;
    double elapsed_time;
	start = clock();
    int rand_index;
    
    // random fonksiyonunun düzgün çalýþmasý için srand kullanýyoruz
    srand(time(NULL));
    
    for (epoch = 0; epoch < EPOCHS; epoch++) {
    	save_weights_log(model, SGD_WEIGHTS, epoch); // T-Sne için weight kaydý
    	
    	// modele ait metriklerin her epochta tutulmasý
    	model->logs[0][epoch] = compute_train_loss(model);
        model->logs[1][epoch] = calculate_accuracy_train(model);
        model->logs[2][epoch] = compute_test_loss(model);
        model->logs[3][epoch] = calculate_accuracy_test(model);
        
        // modelimize ait anlýk loss verilerini ekrana bastýrma
        if (epoch % EPOCH_PERIOD == 0 || epoch == 0) {
            printf("Rand_index: %d, Epoch: %d, Loss: %f \n", rand_index, epoch, model->logs[0][epoch]);
        }
        
        
        // her epochta tüm veri kümesi üzerinden geçebilmek için iterasyon kullanýyoruz
        for(iteration=0; iteration < TRAIN_ROWS; iteration++){
        	
	        // veri kümesinden rastgele örnek seçiyoruz
	        rand_index = rand() % TRAIN_ROWS;
	        
	        // forward pass ile modele ait olasýlýklarý buluyoruz
	        predict(model,model->train_data[rand_index]);
	        
	        // her örnek için weightleri güncelliyoruz
	        for (cls = 0; cls < NUM_CLASSES; cls++) {
	            double error = model->probabilities[cls] - (cls == model->train_labels[rand_index] ? 1.0 : 0.0);
	                
	            for (feature = 0; feature < INPUT_SIZE; feature++) {
	                model->weights[cls][feature] -= LEARNING_RATE * error * model->train_data[rand_index][feature];
	            }
	        }
		}
		end = clock();
    	elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    	model->logs[4][epoch] = elapsed_time;
	        
        
        
    }
    // modele ait metriklerin kaydedilmesi
	save_logs(model,SGD_LOG);
}


// modelin adam algoritmasý ile eðitilmesi
void train_model_adam(Model *model) {
    int epoch, row, cls, feature;
    clock_t start, end;
    double elapsed_time;
	start = clock();
    
    // Adam parametrelerini baþlatýyoruz
    if (model->adam_m == NULL) {
        initialize_adam_params(model);
    }
    
    for (epoch = 0; epoch < EPOCHS; epoch++) {
        model->adam_t++;
        
        save_weights_log(model, ADAM_WEIGHTS, epoch); //T-sne için weightlerin kaydedilmesi
        
        // metriklerin tutulmasý
        model->logs[0][epoch] = compute_train_loss(model);
        model->logs[1][epoch] = calculate_accuracy_train(model);
        model->logs[2][epoch] = compute_test_loss(model);
        model->logs[3][epoch] = calculate_accuracy_test(model);
        
        // belli periyotla verileri ekrana bastýrma
        if (epoch % EPOCH_PERIOD == 0 || epoch == 0) {
            printf("Epoch %d, Loss: %f\n", epoch, model->logs[0][epoch]);
		}
        
        
        // mevcut gradyanlarý hesapla
        compute_gradients(model);

    	// ADAM güncellemelerini uygulama
        for (cls = 0; cls < NUM_CLASSES; cls++) {
            for (feature = 0; feature < INPUT_SIZE; feature++) {
                
                // first moment estimate
                model->adam_m[cls][feature] = ADAM_BETA1 * model->adam_m[cls][feature] + 
                                            (1 - ADAM_BETA1) * model->gradients[cls][feature];
                
                // second moment estimate
                model->adam_v[cls][feature] = ADAM_BETA2 * model->adam_v[cls][feature] + 
                                            (1 - ADAM_BETA2) * (model->gradients[cls][feature] * model->gradients[cls][feature]);
                
                // Bias correction
                double m_hat = model->adam_m[cls][feature] / (1 - pow(ADAM_BETA1, model->adam_t));
                double v_hat = model->adam_v[cls][feature] / (1 - pow(ADAM_BETA2, model->adam_t));
                
                // Update weights
                model->weights[cls][feature] -= ADAM_LEARNING_RATE * m_hat / (sqrt(v_hat) + EPSILON);
            }
        }
        
        // epochta geçen süreyi kaydetme
        end = clock();
    	elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    	model->logs[4][epoch] = elapsed_time;
        
    }
    // modele ait metriklerin csv olarak kaydedilmesi
    save_logs(model,ADAM_LOG);
}

// modelin test kümesi üzerindeki doðruluðunu hesaplayan fonksiyon
double calculate_accuracy_test(Model *model){
	int i;
	int num_correct = 0;
    for(i = 0; i < TEST_COUNT; i++) {
        int prediction = predict(model, model->test_data[i]);
        if(prediction == model->test_labels[i]) {
            num_correct++;
        }
    }
    float accuracy = (double) num_correct / TEST_COUNT * 100.0;
    return accuracy;
}

// modelin eðitim kümesi üzerindeki doðruluðunu hesaplayan fonksiyon
double calculate_accuracy_train(Model *model){
	int num_correct = 0,i;
    for(i = 0; i < TRAIN_ROWS; i++) {
        int prediction = predict(model, model->train_data[i]);
        if(prediction == model->train_labels[i]) {
            num_correct++;
        }
    }
    double accuracy = (double) num_correct / TRAIN_ROWS * 100.0;
    return accuracy;
	
}

// modelin eðitim kümesi lossunu hesaplayan fonksiyon
double compute_train_loss(Model *model){
	int row;
	double actual_total_loss = 0.0;
	for (row = 0; row < TRAIN_ROWS; row++) {
        predict(model,model->train_data[row]);
        actual_total_loss += compute_loss(model->probabilities, model->train_labels[row]);
    }
    
    actual_total_loss = (double) actual_total_loss / TRAIN_ROWS;
    
    return actual_total_loss ;
}

// modelin test kümesi lossunu hesaplayan fonksiyon
double compute_test_loss(Model *model){
	int row;
	double actual_total_loss = 0.0;
	for (row = 0; row < TEST_COUNT; row++) {
        predict(model,model->test_data[row]);
        actual_total_loss += compute_loss(model->probabilities, model->test_labels[row]);
    }
    
    actual_total_loss = (double) actual_total_loss / TEST_COUNT;
    
    return actual_total_loss;
}

// modele ait metrikleri csv olarak kaydeden fonksyion
void save_logs(Model *model, char *label){
	FILE *loss_file = fopen(label, "w");
	int i;
	fprintf(loss_file, "Train_Loss,Train_Accuracy,Test_Loss,Test_Accuracy,Time_Elapsed\n");

	
	
	for(i=0; i<EPOCHS; i++){
		
		fprintf(loss_file, "%lf,%lf,%lf,%lf,%lf\n", 
            	model->logs[0][i], model->logs[1][i], model->logs[2][i], model->logs[3][i], model->logs[4][i]);

	}
	
	fclose(loss_file);
}

// modelin her epochtaki weightlerini csv olarak kaydeden fonksiyon
void save_weights_log(Model *model, const char *filename, int epoch) {
    FILE* fp_weight = fopen(filename,"a");
    int i, j;
    if(epoch==0){
    	fprintf(fp_weight,"epoch,", epoch);
    	for(i=0; i < NUM_CLASSES; i++){
    		for(j=0; j<INPUT_SIZE;j++){
    			fprintf(fp_weight,"w%d%d,",i,j);
			}
		}
		fprintf(fp_weight, "\n"); 
	}
	
    fprintf(fp_weight,"%d,", epoch);
    for(i = 0; i < NUM_CLASSES; i++){
        for(j = 0; j < INPUT_SIZE; j++){
            fprintf(fp_weight,"%lf,", model->weights[i][j]);
        }
    }
    if(epoch != EPOCHS-1)
    	fprintf(fp_weight, "\n");  // Her sýnýf için yeni satýr
    fclose(fp_weight);
}
