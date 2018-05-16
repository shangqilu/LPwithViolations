#include "headers.h"
#include "fileIO.h"
#include "geometry.h"

using namespace std;

static char *line = NULL;
static int max_line_len;

static char* readline(FILE *input)
{
	if (fgets(line, max_line_len, input) == NULL)
		return NULL;

	while (strrchr(line, '\n') == NULL)
	{
		max_line_len *= 2;
		line = (char *)realloc(line, max_line_len);
		int len = (int)strlen(line);
		if (fgets(line + len, max_line_len - len, input) == NULL)
			break;
	}
	return line;
}

void exit_input_error(int line_num)
{
	printf("Wrong input format at line %d\n", line_num);
	exit(1);
}
void LoadDataLibSVMFormat(int n, int dimension, char* filename, PointSet &points)
{
	if (strstr(filename, "csv") != NULL) {
		printf("csv file\n");
		LoadDataCSVFormat(n, dimension, filename, points);
		return;
	}
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "can't open input file %s\n", filename);
		exit(1);
	}
	max_line_len = 1024;
	line = (char *)malloc(max_line_len * sizeof(char));
	int n_instance = 0;
	int n_features = 0;
	char *c_label, *endptr;
	char *idx, *val;
	bool positive_label = false;
	bool negative_label = false;
	clock_t startreadtime = clock();

	while (readline(fp) != NULL){
		n_instance++;
		if (n_instance % 100000 == 0) {
			printf("%d\n", n_instance);
			fflush(stdin);
		}
		int inst_max_index = 0;
		c_label = strtok(line, " \t\n");
		if (c_label == NULL)
		{
			puts("wrong label");
			exit_input_error(n_instance);
		}

		errno = 0;
		int cur_label = (int)strtol(c_label, &endptr, 0);
		if (endptr == c_label || errno != 0 || *endptr != '\0'){
			puts("wrong label2");
			exit_input_error(n_instance);
		}

		/*if (cur_label != -1 && cur_label != 1) {
			printf("label should be -1 or 1 !\n");
			exit_input_error(n_instance);
		}*/
		//cout << cur_label << endl;
		double *x = new double[dimension];
		Point *curPt = new Point(dimension, x);

		if (Label_type == 0) {
			if (cur_label == 1) {
				positive_label = true;
				curPt->y = 1;
			}
			else {
				negative_label = true;
				curPt->y = -1;
			}
		}
		else if (Label_type == 1){
			if (cur_label <= 4) {
				positive_label = true;
				curPt->y = 1;
			}
			else {
				negative_label = true;
				curPt->y = -1;
			}
		}else if (Label_type == 2) {
			if (cur_label <= 499) {
				curPt->y = 1;
			}else{
				curPt->y = -1;
			}
		}

		

		while (1)
		{
			idx = strtok(NULL, ":");
			val = strtok(NULL, " \t");

			if (val == NULL)
			{
				break;
			}


			errno = 0;
			int cur_index = (int)strtol(idx, &endptr, 10);
			if (endptr == idx || errno != 0 || *endptr != '\0' || cur_index <= inst_max_index
				|| cur_index > dimension)
			{
				printf("index must start from 1 to d in ascending order\n");
				exit_input_error(n_instance);
			}
			else
			{
				inst_max_index = cur_index;
			}

			errno = 0;
			double cur_val = strtod(val, &endptr);
			if (endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
			{
				puts("wrong value");
				exit_input_error(n_instance);
			}
			curPt->x[cur_index - 1] = cur_val;
			//cout << cur_index << " " << cur_val << " " << n_instance << endl;
		}
		points.push_back(curPt);
		//delete []x;
		//delete []curPt;
		if (n_features < inst_max_index) {
			n_features = inst_max_index;
		}
	}

	if (n_instance != n) {
		printf("%d instances != %d\n", n_instance, n);
		PrintError("The number of instances in the file is not equal to n");
	}
	if (positive_label == false || negative_label == false) {
		PrintError("There is only one class of label.");
	}

	clock_t endreadtime = clock();
	double duration = (endreadtime - startreadtime) / (double)CLOCKS_PER_SEC;
	printf("read data time: %f\n", duration);

	free(line);
	fclose(fp);
}




void LoadDataCSVFormat(int n, int dimension, char* filename, PointSet &points)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "can't open input file %s\n", filename);
		exit(1);
	}
	max_line_len = 1024;
	line = (char *)malloc(max_line_len * sizeof(char));
	int n_instance = 0;
	int n_features = 0;
	char *c_label, *endptr;
	char *idx, *val;
	bool positive_label = false;
	bool negative_label = false;
	clock_t startreadtime = clock();
	readline(fp);
	while (readline(fp) != NULL){
		n_instance++;
		if (n_instance % 100000 == 0) {
			printf("%d\n", n_instance);
			fflush(stdin);
			//return;
		}
		int inst_max_index = 0;
		c_label = strtok(line, ",\n");
		if (c_label == NULL)
		{
			puts("wrong label");
			exit_input_error(n_instance);
		}

		errno = 0;
		int cur_label = (int)strtod(c_label, &endptr);
		//printf("curlabel %d\n", cur_label);
		//puts(c_label);
		if (endptr == c_label || errno != 0 || *endptr != '\0'){
			puts("wrong label2");
			exit_input_error(n_instance);
		}

		/*if (cur_label != -1 && cur_label != 1) {
			printf("label should be -1 or 1 !\n");
			exit_input_error(n_instance);
		}*/
		//cout << cur_label << endl;
		double *x = new double[dimension];
		Point *curPt = new Point(dimension, x);

		if (Label_type == 0) {
			if (cur_label == 1) {
				positive_label = true;
				curPt->y = 1;
			}
			else {
				negative_label = true;
				curPt->y = -1;
			}
		}
		else if (Label_type == 1){
			if (cur_label <= 4) {
				positive_label = true;
				curPt->y = 1;
			}
			else {
				negative_label = true;
				curPt->y = -1;
			}
		}else if (Label_type == 2) {
			if (cur_label <= 499) {
				curPt->y = 1;
			}else{
				curPt->y = -1;
			}
		}

		
		int cur_index = 0;
		while (1)
		{
			val = strtok(NULL, ",");

			if (val == NULL)
			{
				break;
			}

			errno = 0;
			double cur_val = strtod(val, &endptr);
			if (endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
			{
				puts("wrong value");
				exit_input_error(n_instance);
			}
			curPt->x[cur_index] = cur_val;
			cur_index++;
			//cout << cur_index << " " << cur_val << " " << n_instance << endl;
		}
		points.push_back(curPt);
		//delete []x;
		//delete []curPt;
		if (n_features < inst_max_index) {
			n_features = inst_max_index;
		}
	}

	if (n_instance != n) {
		printf("%d instances != %d\n", n_instance, n);
		PrintError("The number of instances in the file is not equal to n");
	}
	if (positive_label == false || negative_label == false) {
		PrintError("There is only one class of label.");
	}

	clock_t endreadtime = clock();
	double duration = (endreadtime - startreadtime) / (double)CLOCKS_PER_SEC;
	printf("read data time: %f\n", duration);

	free(line);
	fclose(fp);
}



