#include <stdio.h>

// TODO check max field size
struct test_information {
	char** venue;
	char** vehicle;
	char** user;
	char** data_source;
	char** comment;
	char** date; // Use american date format mm/dd/yyyy
	char** time; // hh/mm/ss
	int sample_rate;
	char** segment;
};

struct files_information {
	char** input_csv_file;
	char** output_drk_file;
};

void get_initial_information(struct test_information* info);
void get_files_information(struct files_information* info);

int main(int argc, char** argv) {
	
	struct test_information initial_info;
	struct files_information files_info;
	
	if(argc > 1) {
		printf("ERROR: invalid number of arguments\nThis tool not accept arguments\n");
		return 1;
	}
	
	get_initial_information(&initial_info);
	
	get_files_information(&files_info);
	
	// printf("%s", &(initial_information.venue));
	
	
	
	return 0;
}

void get_initial_information(struct test_information* info) {
	printf("Insert venue: ");
	scanf("%s", &(info->venue));
	
	printf("Insert vehicle: ");
	scanf("%s", &(info->vehicle));
	
	printf("Insert user: ");
	scanf("%s", &(info->user));
	
	info->data_source = "AIM Data Logger";
	
	printf("Insert comment: ");
	scanf("%s", &(info->comment));
	
	printf("Insert date (Use american date format mm/dd/yyyy): ");
	scanf("%s", &(info->date));
	
	printf("Insert time (hh:mm:ss): ");
	scanf("%s", &(info->time));
	
	printf("Insert sample rate: ");
	scanf("%d", &(info->sample_rate));
		
	printf("Insert segment: ");
	scanf("%s", &(info->segment));
}

void get_files_information(struct files_information* info) {
	printf("Insert input CSV file: ");
	scanf("%s", &(info->input_csv_file));
	
	printf("Insert output DRK file: ");
	scanf("%s", &(info->output_drk_file));
}
