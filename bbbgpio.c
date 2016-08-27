#include "bbbgpio.h"

FILE* _GPIO_file(unsigned int _pin , const char *_file) {
	char file[40];

	snprintf(file, sizeof(file), "/sys/class/gpio/gpio%d/", _pin);

	strcat(file,_file);

	FILE *pFile = fopen(file, "r+");

	return pFile;
}

int GPIO_setStatus(unsigned int _pin, unsigned int _status) {
	char status;

	if(_status == UP) {
		status = '1';
	} else {
		status = '0';
	}

	FILE *pFile = _GPIO_file(_pin, "value");

	if(pFile != NULL) {
		fwrite(&status, sizeof(char), 1, pFile);
		fclose(pFile);

		return 1;
	}

	perror("Error Status file");
	return -1;
}

int GPIO_setMode(unsigned int _pin, unsigned int _mode) {

	char mode[4];

	if(_mode == INPUT) {
		strcpy(mode,"in");
	} else if(_mode == OUTPUT) {
		strcpy(mode,"out");
	} else {
		printf("Mode invalid, GPIO_%d", _pin);
		return -1;
	}

	FILE *pFile = _GPIO_file(_pin, "direction");

	if(pFile != NULL) {
		fwrite(mode, sizeof(char), strlen(mode), pFile);
		fclose(pFile);

		return 1;
	}

	perror("Error Mode file");
	return -1;
}

int GPIO_status(unsigned int _pin) {
	FILE *pFile = _GPIO_file(_pin, "value");
	char buffer;

	if(pFile != NULL) {
		fread(&	buffer, sizeof(char), 1, pFile);
		fclose(pFile);

		if(buffer == '1') return UP;
		else return DOWN;
	}

	perror("Error Read status file");
	return -1;
}
