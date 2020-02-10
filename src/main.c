#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DRK_HEADER_SIZE 1088

/* TODO (#1#): check max field size */
struct test_information {
	char name[256];
	char track[40];
	char vehicle[40];
	char driver[40];
	//char data_source[40];
	char** comment;
	char date[8]; // Use american date format mm/dd/yy
	char time[8]; // hh/mm/ss
	int sample_rate;
	char** segment;
};

struct files_information {
	char input_csv_file[50];
	char output_drk_file[40];
};

void get_test_information(struct test_information* info);
void get_files_information(struct files_information* info);

int main(int argc, char** argv) {
	
	struct test_information test_info;
	struct files_information files_info;
	
	char** output_content = NULL;
	char output_content_header[DRK_HEADER_SIZE];
	
	if(argc > 1) {
		printf("ERROR: invalid number of arguments\nThis tool not accept arguments\n");
		return 1;
	}
	
	/**
	Get initial information
	**/
	get_test_information(&test_info);
	
	get_files_information(&files_info);
	
	/**
	Open files
	**/
	FILE *csv_file = fopen(files_info.input_csv_file, "r");
	if(csv_file == NULL) {
		printf("ERROR: CSV file not found\n");
		return 1;
	}
	
	FILE *drk_file = fopen(files_info.output_drk_file, "wb");
	if(drk_file == NULL) {
		printf("ERROR: DRK file not found\n");
		return 1;
	}
	
	/**
	Generate output content (HEADER)
	**/
	printf("\nGenerate DRK header...\n");
	memset(output_content_header, 0, sizeof(output_content_header)); // clean output_content_header
	output_content_header[0] = 'R';
	output_content_header[1] = 'D';
	output_content_header[2] = 'X';
	output_content_header[3] = 2;
	output_content_header[32] = 'R';
	output_content_header[33] = 'D';
	output_content_header[34] = 'X';
	output_content_header[35] = 2;
	strncpy(&output_content_header[36], files_info.output_drk_file, sizeof(files_info.output_drk_file)); // add test file name
	strncpy(&output_content_header[76], test_info.date, sizeof(test_info.date)); // add date
	output_content_header[84] = ' ';
	strncpy(&output_content_header[85], test_info.time, sizeof(test_info.time)); // add time
	output_content_header[1056] = 'P';
	output_content_header[1057] = 'P';
	output_content_header[1058] = 'X';
	output_content_header[1059] = 2;
	
	printf("Writing file...\n");
	for(int i = 0; i < DRK_HEADER_SIZE; i++) {
        fwrite(&output_content_header[i], sizeof(char), 1, drk_file);
    }
	
	fclose(csv_file);
	fclose(drk_file);
	
	return 0;
}

void get_test_information(struct test_information* info) {
	printf("######################\n## TEST INFORMATION ##\n######################\n\n");
	printf("Insert test name: ");
	scanf("%s", &(info->name));
	
	printf("Insert track: ");
	scanf("%s", &(info->track));
	
	printf("Insert vehicle: ");
	scanf("%s", &(info->vehicle));
	
	printf("Insert driver: ");
	scanf("%s", &(info->driver));
	
	printf("Insert comment: ");
	scanf("%s", &(info->comment));
	
	printf("Insert date (use american date format mm-dd-yy): ");
	scanf("%s", &(info->date));
	
	printf("Insert time (hh:mm:ss): ");
	scanf("%s", &(info->time));
	
	printf("Insert sample rate: ");
	scanf("%d", &(info->sample_rate));
		
	printf("Insert segment: ");
	scanf("%s", &(info->segment));
}

void get_files_information(struct files_information* info) {
	printf("\n######################\n## FILE INFORMATION ##\n######################\n\n");
	printf("Insert input CSV file name: ");
	scanf("%s", &(info->input_csv_file));
	
	printf("Insert output DRK file name: ");
	scanf("%s", &(info->output_drk_file));
}
