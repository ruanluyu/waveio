#ifndef WAVEIO_H
#define WAVEIO_H 

namespace waveio{
	extern int open(
		const char* name,
		const int &samples_per_second, 
		const int &bytes_per_sample,
		const int &channels_num
		);
	extern int send(double signal_channel_0,double signal_channel_1 = .0);
	extern int close();
}

#endif