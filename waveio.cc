#include <fstream>
#include <mutex>
#include <cmath>
#include "waveio.h"

namespace waveio{

template <typename Word>
static inline std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
{
for (; size; --size, value >>= 8)
  outs.put( static_cast <char> (value & 0xFF) );
return outs;
}
static std::ofstream *f=nullptr;
static int bps=0;
static int chn=0;
static int sps=0;
static size_t data_chunk_pos=0;

int open(
	const char* name,
	const int &samples_per_second, 
	const int &bytes_per_sample,
	const int &channels_num
	)
{
	if(bytes_per_sample<=0) return -2;
	if(samples_per_second<=0) return -2;
	if(channels_num!=1 && channels_num!=2) return -2;
	f = new std::ofstream( name, std::ios::binary );
	if(!f){
		return -2;
	}
	// Write the file headers
	(*f) << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
	write_word( *f,     16, 4 );  // no extension data
	write_word( *f,      1, 2 );  // PCM - integer samples
	write_word( *f,      channels_num, 2 );  // two channels (stereo file)
	write_word( *f,  samples_per_second, 4 );  // samples per second (Hz)
	write_word( *f, bytes_per_sample*samples_per_second*channels_num, 4 );  // Sample Rate * BytesPerSample * Channels
	write_word( *f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
	write_word( *f,     bytes_per_sample*8, 2 );  // number of bits per sample (use a multiple of 8)
	
	data_chunk_pos = f->tellp();
  	(*f) << "data----";  // (chunk size to be filled in later)

	bps = bytes_per_sample;
	chn = channels_num;
	sps = samples_per_second;
	return 0;
}

static
inline int translate_signal(const double &db){
	if(bps==1) return (int)(((fmin(fmax(db,-1),1)/2)+.5)*255+.5);
	else if(bps==2) return (int)(fmin(fmax(db,-1),1)*32767);
	return 0;
}

int send(double signal_channel_0,double signal_channel_1){
	if(!f) return -2;
	write_word( *f, (unsigned short)translate_signal(signal_channel_0), bps );
    if(chn==2) write_word( *f, (unsigned short)translate_signal(signal_channel_1), bps );
	return 0;
}


int close(){
	// (We'll need the final file size to fix the chunk sizes above)
	size_t file_length = f->tellp();

	// Fix the data chunk header to contain the data size
	f->seekp( data_chunk_pos + 4 );
	write_word( *f, file_length - data_chunk_pos + 8 );

	// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
	f->seekp( 0 + 4 );
	write_word( *f, file_length - 8, 4 ); 

	f->close();
	delete f;
	f=nullptr;

	data_chunk_pos = chn = sps = bps = 0;
	return 0;
}

}
