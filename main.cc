#include <iostream>
#include <cmath>
using namespace std;

#include "waveio.h"


const int freqlst[] = {
	1,1,5,5,6,6,5,0,
	4,4,3,3,2,2,1,0,
	5,5,4,4,3,3,2,0,
	5,5,4,4,3,3,2,0,
	1,1,5,5,6,6,5,0,
	4,4,3,3,2,2,1,0,
	0,0,0,0,0,0,0,0
};
const double freqmap[]={
	0,
	261.63,
	293.67,
	329.63,
	349.23,
	392.00,
	440.00,
};

const double one_key_time = 0.5;
const double one_key_release_time = 0.45;
const double pi = 3.141592653589;

int main()
{
	int sps = 44100;
	int err = waveio::open("Sample.wav",sps,2,2);
	int numofkeys = sizeof(freqlst)/sizeof(int);
	double period = 10.0;
	int onekeyN = (int) (one_key_time * sps);
	double delt = 1.0/sps;
	for(int i = 0;i<numofkeys;i++){
		double t = 0;
		for(int j = 0;j<onekeyN;j++){
			//double freqv = 1+sin(2*pi*t*2)*2;
			double freqv = 1;
			t += delt*freqv;
			if(t<one_key_release_time){
				double amp1 = sin(2*pi* freqmap[freqlst[i]] *t)*(one_key_release_time-t)/one_key_release_time;
				double amp2 = sin(4*pi* freqmap[freqlst[i]] *t)*(one_key_release_time-t)/one_key_release_time;
				double amp3 = sin(pi* freqmap[freqlst[i]] *t)*(one_key_release_time-t)/one_key_release_time;
				double amp = (amp1 + amp2 + amp3) / 3;
				double filter = abs(sin(2*pi*5*t));
				//amp *= filter;
				waveio::send(amp,amp);
			}
			else
			{
				waveio::send(.0);
			}
		}	
	}
	waveio::close();
	return 0;
}