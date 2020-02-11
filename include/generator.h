#ifndef GENERATOR_H
#define GENERATOR_H

#define DRK_HEADER_SIZE 1088
#define DRK_TEST_INFO_SIZE 1056

struct date {
	int day;
	int month;
	int year;
};

typedef struct date date_t;

struct time {
	int hour;
	int minutes;
	int seconds;
};

typedef struct time time_td;

/* TODO (#1#): check max field size */
struct test_information {
	char name[40];
	char track[40];
	char vehicle[40];
	char driver[40];
	//char data_source[40];
	char comment[200];
	date_t date;
	time_td time; 
	char sample_rate[4];
	/* TODO (#1#): check segment field size */
	char segment[10];
};

typedef struct test_information test_information_t;

struct files_information {
	char input_csv_file[50];
	char output_drk_file[40];
};

typedef struct files_information files_information_t;

void generate_header(char out[], files_information_t files_info, test_information_t test_info);
void generate_test_info(char out[], files_information_t files_info, test_information_t test_info);
void format_date_usa(char date[8], int day, int month, int year);
void format_time(char time[8], int hour, int minutes, int seconds);

#endif
