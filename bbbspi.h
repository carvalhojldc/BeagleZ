/*
 * bbbspi.h
 *
 *  Created on: Aug 27, 2016
 *      Author: carvalho
 */

#ifndef BBBSPI_H_
#define BBBSPI_H_

#include <fcntl.h>
#include <linux/spi/spidev.h>

#define SPI_1_CS0 28
#define SPI_1_D0 29
#define SPI_1_SCLK 30

#define SPI_N_BITS 8
#define SPI_SPEED 500000

typedef struct {

	/* fileids
	 * bus
	 * device
	 * speed
	 * nbits
	 */

} SPI;

/*
 * @brief abre /sys/class/spidev/spidev[b].[d]
 *
 * @param b SPI bus
 * @param d device
 * @return Retorna o arquivo descritor para spidev
 */
int SPI_open(unsigned int b, unsigned int d) {
	char file[30];

	snprintf(file, sizeof(file), "/sys/class/spidev/spidev%d.%d", b, d);

	int SPI_file = open(file, O_RDWR);

	if(SPI_file < 0) {
		perror("Error! Open SPI failed");
	}

	return SPI_file;
}

/*
 * @brief Close file of SPI
 *
 * @param SPI_file
 * */
void SPI_close(unsigned int SPI_file) {
	close(SPI_file);
}

int SPI_config(unsigned int SPI_file, uint8_t mode, uint8_t nBits, uint32_t speed) {
	int flag = 0;

	flag = ioctl(SPI_file, SPI_IOC_WR_MODE, &mode);
	if (flag == -1) {
		pabort("can't set spi mode");
		return flag;
	}

	flag = ioctl(SPI_file, SPI_IOC_WR_BITS_PER_WORD, &nBits);
	if (flag == -1) {
		pabort("can't set bits per word");
		return flag;
	}

	flag = ioctl(SPI_file, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (flag == -1) {
		pabort("can't set max speed hz");
		return flag;
	}

	return 1;
}

uint8_t SPI_transfer(unsigned int SPI_FILE, uint8_t data) {

	return NULL;
}

#endif /* BBBSPI_H_ */
