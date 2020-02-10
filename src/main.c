#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DRK_HEADER_SIZE 1088
#define DRK_TEST_INFO_SIZE 1056

/* TODO (#1#): check max field size */
struct test_information {
	char name[40];
	char track[40];
	char vehicle[40];
	char driver[40];
	//char data_source[40];
	char comment[200];
	char date[8]; // Use american date format mm/dd/yy
	char time[8]; // hh/mm/ss
	char sample_rate[4];
	/* TODO (#1#): check segment size */
	char segment[10];
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
	char output_content_test_info[DRK_TEST_INFO_SIZE];
	
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
	Generate HEADER
	**/
	printf("\nGenerate DRK header...\n");
	memset(output_content_header, 0, DRK_HEADER_SIZE); // clean output_content_header
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
	strncpy (&output_content_header[85], test_info.time, sizeof(test_info.time)); // add time
	output_content_header[1056] = 'P';
	output_content_header[1057] = 'P';
	output_content_header[1058] = 'X';
	output_content_header[1059] = 2;
	
	/**
	Generate TEST INFO
	**/
	printf("Generate DRK test info...\n");
	memset(output_content_test_info, 0, DRK_TEST_INFO_SIZE); // clean output_content_test_info
	strncpy(&output_content_test_info[0], test_info.vehicle, sizeof(test_info.vehicle));
	strncpy(&output_content_test_info[40], test_info.track, sizeof(test_info.track));
	strncpy(&output_content_test_info[80], test_info.driver, sizeof(test_info.driver));
	strncpy(&output_content_test_info[120], test_info.name, sizeof(test_info.name));
	strncpy(&output_content_test_info[160], test_info.comment, sizeof(test_info.comment));
	output_content_test_info[360] = 'N';
	output_content_test_info[361] = 'o';
	output_content_test_info[362] = 'n';
	output_content_test_info[363] = 'e';
	
	printf("Writing file...\n");
	for(int i = 0; i < DRK_HEADER_SIZE; i++) {
        fwrite(&output_content_header[i], sizeof(char), 1, drk_file);
    }
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
	fgets(info->name, sizeof(info->name), stdin);
	
	printf("Insert track: ");
	fgets(info->track, sizeof(info->track), stdin);
	
	printf("Insert vehicle: ");
	fgets(info->vehicle, sizeof(info->vehicle), stdin);
	
	printf("Insert driver: ");
	fgets(info->driver, sizeof(info->driver), stdin);
	
	printf("Insert comment: ");
	fgets(info->comment, sizeof(info->comment), stdin);
	
	printf("Insert date (use american date format mm-dd-yy): ");
	fgets(info->date, sizeof(info->date), stdin);
	
	printf("Insert time (hh:mm:ss): ");
	fgets(info->time, sizeof(info->time), stdin);
	
	printf("Insert sample rate: ");
	fgets(info->sample_rate, sizeof(info->sample_rate), stdin);
		
	printf("Insert segment: ");
	fgets(info->segment, sizeof(info->segment), stdin);
}

void get_files_information(struct files_information* info) {
	printf("\n######################\n## FILE INFORMATION ##\n######################\n\n");
	printf("Insert input CSV file name: ");
	fgets(info->input_csv_file, sizeof(info->input_csv_file), stdin);
	
	printf("Insert output DRK file name: ");
	fgets(info->output_drk_file, sizeof(info->output_drk_file), stdin);
}
