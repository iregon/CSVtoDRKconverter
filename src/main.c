#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..\include\generator.h"

#define DEVELOP

void get_test_information(struct test_information* info);
void get_files_information(struct files_information* info);

int main(int argc, char** argv) {
	
	#ifndef DEVELOP
	test_information_t test_info;
	files_information_t files_info;
	#endif
	
	#ifdef DEVELOP
	date_t date_debug = {11, 2, 20}; 
	time_td time_debug = {10, 9, 40};
	
	test_information_t test_info = {
		"test",
		"Mugello",
		"SRT20",
		"Matteo Indraccolo",
		"",
		date_debug,
		time_debug,
		"10",
		""
	};
	
	files_information_t files_info = {
		"test/test_input_csv.csv",
		"test/test_input_csv.drk"
	};
	#endif
	
	char** output_content = NULL;
	char output_content_header[DRK_HEADER_SIZE];
	char output_content_test_info[DRK_TEST_INFO_SIZE];
	
	if(argc > 1) {
		printf("ERROR: invalid number of arguments\nThis tool not accept arguments\n");
		return 1;
	}
	
	#ifndef DEVELOP
	/**
	Get initial information
	**/
	get_test_information(&test_info);
	
	get_files_information(&files_info);
	#endif
	
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
	Generate HEADER
	**/
	printf("\nGenerate DRK header...\n");
	generate_header(output_content_header, files_info, test_info);
	
	/**
	Generate TEST INFO
	**/
	printf("Generate DRK test info...\n");
	generate_test_info(output_content_test_info, files_info, test_info);
	
	printf("Writing file...\n");
	// Write HEADER
	for(int i = 0; i < DRK_HEADER_SIZE; i++) {
        fwrite(&output_content_header[i], sizeof(char), 1, drk_file);
    }
    // Write TEST INFO
    for(int i = 0; i < DRK_TEST_INFO_SIZE; i++) {
        fwrite(&output_content_test_info[i], sizeof(char), 1, drk_file);
    }
	
	fclose(csv_file);
	fclose(drk_file);
	
	return 0;
}

void get_test_information(struct test_information* info) {
	printf("######################\n## TEST INFORMATION ##\n######################\n\n");
	printf("Insert test name: ");
	fgets(info->name, 40, stdin);
	
	printf("Insert track: ");
	fgets(info->track, 40, stdin);
	
	printf("Insert vehicle: ");
	fgets(info->vehicle, 40, stdin);
	
	printf("Insert driver: ");
	fgets(info->driver, 40, stdin);
	
	printf("Insert comment: ");
	fgets(info->comment, 200, stdin);
	
	printf("Insert date (dd-mm-yy): ");
	scanf("%d-%d-%d", info->date.day, info->date.month, info->date.year);
	
	printf("Insert time (hh:mm:ss): ");
	scanf("%d:%d:%d", info->time.hour, info->time.minutes, info->time.seconds);
	
	printf("Insert sample rate: ");
	fgets(info->sample_rate, 4, stdin);
		
	printf("Insert segment: ");
	fgets(info->segment, 10, stdin);
}

void get_files_information(struct files_information* info) {
	printf("\n######################\n## FILE INFORMATION ##\n######################\n\n");
	printf("Insert input CSV file name: ");
	scanf("%s", &(info->input_csv_file));
	
	printf("Insert output DRK file name: ");
	scanf("%s", &(info->output_drk_file));
}


