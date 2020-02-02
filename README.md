# waveio
A simple cpp11 library to write wav file.Not thread safe currently. 

## Compile:
```cmd
#Create build folder
mkdir build
cd build
#Use CMake & Makefile to compile
cmake ..
make
```

## Run:
```cmd
#Run
./waveio
```

You will see a file named `Sample.wav` in `build` directory.



## Functions:

### open:
```cpp
extern int open(
        const char* name,
        const int &samples_per_second, 
        const int &bytes_per_sample,
        const int &channels_num
        );
```
- name: File name to save
- samples_per_second: samples per second
- bytes_per_sample: bytes per sample. (1 or 2)
- channels_num: 1 for mono, 2 for stereo

### send:
```cpp
extern int send(double signal_channel_0,double signal_channel_1 = .0);    
```
- signal_channel_0: send one signal to mono channel or L channel of stereo. 
- signal_channel_1: send one signal to the R channel of stereo. 
- Signal range: -1.0 ~ 1.0.

### close:
```cpp
extern int close();
```
