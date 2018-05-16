#include "globalVar.h"
#include "headers.h"
#include "geometry.h"
#include "fileIO.h"
#include "dataGenerator.h"
#include "kViolation.h"
#include "simplex.h"


using namespace std;


void Usage()
{
    printf(
        "LP with violations Algorithm\n"
        "Options:\n"
        "-n {integer}	the number of points\n"
        "-d {integer}	the dimensionality of points\n"
        "-f {string}	the full path of input file name\n"
        "-k {integer}   k violations\n"
        "-m {integer}   choosing method"
        "   0:  Exact LP with k violations\n"
        "   1:  Approx LP with k violations\n"
        "-z {integer}   sampling size in sample method\n"
        "-e {double}    epsilon: the approximation for error rate (default 0.1)\n"
        "-r {integer}   repeating times\n"
        "-L {integer}   label of input data\n"
        "   0:  1 and others\n"
        "   1:  <= 4 and >= 5\n"
        "   2:  <= 499 and >= 500\n"

        "-g {integer}   generating dataset with R and y\n"
        "   1:  Origin Dataset\n"
        "   2:  Random Dataset\n"
        "   3:  Grid Dataset\n"
        "-p {double}    the percent of noise points of the dataset\n"
        "-R {double }	the radius of the dataset\n"
        "-y {double }	the margin of the dataset\n"
        "               or the margin of our margin algorithm(parameter r in Ballseptron)\n"
        "-x {double }   the percent of generated positive dataset\n"
    );

}


void InitializeGlobalVariables(int n, int d, double p, int method, int k, 
                               double R, double y, int label_type, int sample_size, double epsilon)
{
    N = n;
    Dim = d;
    Percent = p;
    Method = method;
    K = k;
    Radius = R;
    Margin = y;
    Label_type = label_type;
    Sample_size = sample_size;
    Epsilon = epsilon;
}


int main(int argc, char ** argv)
{
    //TestSimplex2();
    //return 0;

    srand(time(NULL));


#ifndef DEBUG__

    bool legal = true;


    int n = -1;
    int d = -1;
    double p = 1;
    double epsilon = 0.1;
    int k = 0;
    char file_name[200];
	char model_file_name[200];
    char result_file_name[200];

    double R = 1;
    double y = 0;

    int generate_data = 0;

	int method = 0;
    int repeating = 1;
    int label_type = 0;

    double positive_per = 0.5;


    int sample_size = 1;
    //parse command line
    int i;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            legal = false;
            break;
        }
        if (++i > argc)
        {
            legal = false;
            break;
        }
        switch(argv[i-1][1])
        {
        case 'n' :
        {
            n = atoi(argv[i]);
            if (n <= 0){
                legal = false;
                printf("error in input -n\n");
            }
            printf("n: %d\n", n);
            break;
        }
        case 'd' :
        {
            d = atoi(argv[i]);
            if (d <= 0){
                legal = false;
                printf("error in input -d\n");
            }
            printf("d: %d\n", d);
            break;
        }
        case 'p' :
        {
            p = atof(argv[i]);
            if (p < 0 || p > 1){
                legal = false;
                printf("error in input -p\n");
            }
            printf("p: %f\n", p);
            break;
        }
        case 'f' :
        {
            strcpy(file_name, argv[i]);
            
            char *model = strrchr(argv[i], '/');
            if (model == NULL) {
            	model = argv[i];
            }else {
            	++ model;
            }
            sprintf(model_file_name, "%s.model", model);
            sprintf(result_file_name, "%s.result", model);
            break;
        }
        case 'g':
        {
			generate_data = atoi(argv[i]);
			if (generate_data < 0 || generate_data > 3){
				legal = false;
                printf("error in input -g\n");
            }
			printf("g: %d\n", generate_data);
            break;
        }
        case 'e' :{
            epsilon = atof(argv[i]);
            if (epsilon < 0) {
                legal = false;
                printf("error in input -e\n");
            }
            printf("epsilon: %f\n", epsilon);
            break;
        }
        case 'k':
        {
            k = atoi(argv[i]);
            if (k < 0)
            {
                legal = false;
                printf("error in input -k\n");
            }
			printf("k: %d\n", k);
            break;
        }
        case 'R':
        {
            R = atof(argv[i]);
            if (R < 0){
                legal = false;
                printf("error in input -R\n");
            }
            printf("R: %f\n", R);
            break;
        }
        case 'y':
        {
            y = atof(argv[i]);
            if (y < 0){
                legal = false;
                printf("error in input -y\n");
            }
            printf("y: %f\n", y);
            break;
        }
		case 'm':
		{
			method = atoi(argv[i]);
			if (method < 0 || method > 1){
				legal = false;
                printf("error in input -m\n");
            }
			printf("method: %d\n", method);
			break;
		}
        case 'r':
        {
            repeating = atoi(argv[i]);
            if (repeating < 1){
                legal = false;
                printf("error in input -r\n");
            }
            printf("repeating: %d\n", repeating);
            break;
        }
        
        case 'L':
        {
            label_type = atoi(argv[i]);
            if (label_type < 0 || label_type > 2) {
                legal = false;
                printf("error in input -L\n");
            }
            printf("label_type: %d\n", label_type);
            break;
        }
        case 'x':
        {
            positive_per = atof(argv[i]);
            if (positive_per < 0 || positive_per > 1) {
                legal = false;
                printf("error in input -x\n");
            }
            printf("positive_percent: %f\n", positive_per);
            break;
        }
        case 'z':
        {
            sample_size = atof(argv[i]);
            if (sample_size < 0) {
                legal = false;
                printf("error in input -z\n");
            }
            printf("sample_size: %d\n", sample_size);
            break;
        }
        default:
        {
            legal = false;
            break;
        }

        }

    }

    if (n <= 0 || d <= 0 || p < 0)
    {
        legal = false;
        printf("=========================================\n");
        printf("You should indicate legal -n, -d, -p, -f at least.\n");
    }
    if (!legal)
    {
        printf("=========================================\n");
        printf("Please check your input.\n");
        printf("=========================================\n");
        Usage();
        exit(1);
    }
    //given n, d, k, train_datafilename, epsilon, rho
    
    //initialize global variables
    InitializeGlobalVariables(n, d, p, method, k, R, 
        y, label_type, sample_size, epsilon);


    if (generate_data == 1)
    {
        printf("Generating origin points\n");
		GenOriginDataSet(file_name, Margin, Radius, n, k);
		return 0;
	}
	else if (generate_data == 2) {
		printf("Generating random points\n");
		GenRandomDataSet(file_name, Margin, n, k, positive_per);
		return 0;
	}
	else if (generate_data == 3) {
		printf("Generating grid points\n");
		//GenRandomDataSet(file_name, Margin, n, k, 0.5);
		GenTwoDimensinoGridDataSet(file_name, n);
		return 0;
	}

    //start time
    clock_t start = clock();

	PointSet points;
	points.reserve(n);
	LoadDataLibSVMFormat(n, d, file_name, points);

	//PrintPoints(points, d);
	//preprocess Points in a radius sqrt(Dim) centering at origin
	
    //PreprocessPoints(points);

    //permuting points
    HyperPlane plane(Dim);
	if (method == 0) {
		
        int len = strlen(model_file_name);
        model_file_name[len] = '0';
        model_file_name[len+1] = '\0';
		KViolation(points, plane);

	}else if(method == 1){
        int len = strlen(model_file_name);
        model_file_name[len] = '1';
        model_file_name[len+1] = '\0';
        ApproximateKViolation(points, plane);
    }else {
        PrintError("error in chosen method");
    }

	
	

	puts("Deleting points...");
	//release PointSet
	for (int i = 0; i < N; i++) {
		//if (i > 0 && i % 10000 == 0) printf("%d\n", i);
		delete[] points[i]->x;
		delete (points[i]);
		points[i] = NULL;
	}
	points.clear();
    //end time
    clock_t endtime = clock();


    //write result into a file/the console
    double duration = (endtime - start) / (double) CLOCKS_PER_SEC;
    printf("\nprogram ended...\n");
    printf("overall time: %fs\n", duration);


#endif // DEBUG__

}
