#include "../include/generator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generate_header(char out[], files_information_t files_info, test_information_t test_info) {
	memset(out, 0, DRK_HEADER_SIZE); // clean out
	out[0] = 'R';
	out[1] = 'D';
	out[2] = 'X';
	out[3] = 2;
	out[32] = 'R';
	out[33] = 'D';
	out[34] = 'X';
	out[35] = 2;
	strncpy(&out[36], files_info.output_drk_file, sizeof(files_info.output_drk_file)); // add test file name
	
	char date[8];
	format_date_usa(&date[0], test_info.date.day, test_info.date.month, test_info.date.year);
	strncpy(&out[76], date, sizeof(date)); // add date
	
	out[84] = ' ';
	
	char time[8];
	format_time(&time[0], test_info.time.hour, test_info.time.minutes, test_info.time.seconds);
	strncpy (&out[85], time, sizeof(time)); // add time
	
	// Honestly, I have no idea what the following code is used for but it seems to be useful
	out[116] = 38;
	out[117] = 3;
	out[118] = 21;
	out[120] = 32;
	out[121] = 149;
	out[122] = 9;
	out[124] = 12;
	out[125] = 233;
	out[126] = 39;
	out[128] = 23;
	out[130] = 5;
	out[132] = 23;
	out[136] = 45;
	out[137] = 147;
	out[138] = 9;
	out[140] = 44;
	out[141] = 147;
	out[142] = 9;
	out[150] = 16;
	out[152] = 1;
	out[153] = 134;
	out[154] = 244;
	out[155] = 19;
	out[157] = 4;
	out[159] = 21;
	out[160] = 235;
	out[161] = 1;
	out[165] = 35;
	out[166] = 135;
	out[167] = 255;
	out[168] = 101;
	out[169] = 20;
	out[170] = 96;
	out[171] = 17;
	out[172] = 34;
	out[175] = 187;
	out[176] = 146;
	out[177] = 1;
	out[179] = 10;
	out[194] = 55;	//
	out[195] = 1;	//
	out[200] = 10;	//
	out[202] = 6;	//
	out[208] = 4;	//
	out[210] = 10;	// These rows are in each file
	out[212] = 25;	//
	out[213] = 235;	//
	out[214] = 1;	//
	out[220] = 7;	//
	out[222] = 1;	//
	
	// this is useful
	out[1056] = 'P';
	out[1057] = 'P';
	out[1058] = 'X';
	out[1059] = 2;
}

void generate_test_info(char out[], files_information_t files_info, test_information_t test_info) {
	memset(out, 0, DRK_TEST_INFO_SIZE); // clean out
	strncpy(&out[0], test_info.vehicle, sizeof(test_info.vehicle));
	strncpy(&out[40], test_info.track, sizeof(test_info.track));
	strncpy(&out[80], test_info.driver, sizeof(test_info.driver));
	strncpy(&out[120], test_info.name, sizeof(test_info.name));
	strncpy(&out[160], test_info.comment, sizeof(test_info.comment));
	out[360] = 'N';
	out[361] = 'o';
	out[362] = 'n';
	out[363] = 'e';
	out[1040] = 'I';
	out[1041] = 'I';
	out[1042] = 'X';
	out[1043] = 2;
}

void format_date_usa(char date[8], int day, int month, int year) {
	char month_string[2]; 
	itoa(month, month_string, 10);
	if(month_string[1] == 0) {
		month_string[1] = month_string[0];
		month_string[0] = '0';
	}
	strncpy(&date[0], month_string, sizeof(char) * 2); // add date
	
	date[2] = 45;
	
	char day_string[2];
	itoa(day, day_string, 10);
	if(day_string[1] == 0) {
		day_string[1] = day_string[0];
		day_string[0] = '0';
	}
	strncpy(&date[3], day_string, sizeof(char) * 2);
	
	date[5] = 45;
	
	char year_string[2];
	itoa(year, year_string, 10);
	if(year_string[1] == 0) {
		year_string[1] = year_string[0];
		year_string[0] = '0';
	}
	strncpy(&date[6], year_string, sizeof(char) * 2);
}

void format_time(char time[8], int hour, int minutes, int seconds) {
	char hour_string[2]; 
	itoa(hour, hour_string, 10);
	if(hour_string[1] == 0) {
		hour_string[1] = hour_string[0];
		hour_string[0] = '0';
	}
	strncpy(&time[0], hour_string, sizeof(char) * 2); // add date
	
	time[2] = 58;
	
	char minutes_string[2];
	itoa(minutes, minutes_string, 10);
	if(minutes_string[1] == 0) {
		minutes_string[1] = minutes_string[0];
		minutes_string[0] = '0';
	}
	strncpy(&time[3], minutes_string, sizeof(char) * 2);
	
	time[5] = 58;
	
	char seconds_string[2];
	itoa(seconds, seconds_string, 10);
	if(seconds_string[1] == 0) {
		seconds_string[1] = seconds_string[0];
		seconds_string[0] = '0';
	}
	strncpy(&time[6], seconds_string, sizeof(char) * 2);
}

