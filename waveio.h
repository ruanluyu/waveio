/**
 * @defgroup   WAVEIO waveio
 *
 * @brief      Save wave file to local disc.
 *
 * @author     ZzStarSound
 * @date       2020.2.11
 */

#ifndef WAVEIO_H
#define WAVEIO_H

namespace waveio{
    /**
     * @brief      Create a new wave file
     *
     * @param[in]  name                The name of the wave file
     * @param[in]  samples_per_second  The samples per second, normally 44100 or 48000
     * @param[in]  bytes_per_sample    The bytes of per sample, normally 1 or 2. 1 means 8 bit of each point, 2 means 16 bit.
     * @param[in]  channels_num        The number of channels, 1 means mono, 2 means stero.
     *
     * @return     error signal, 0 means ok, <0 means something wrong.
     */
    extern int open(
        const char* name,
        const int &samples_per_second,
        const int &bytes_per_sample,
        const int &channels_num
        );
    /**
     * @brief      send one signal to waveio
     *
     * @param[in]  signal_channel_0  Mono channel or L channel of stero mode.
     * @param[in]  signal_channel_1  R channel of stero mode, default is 0.
     * @details    Range of per signal is -1 ~ 1, 0 means the mid point. Clamping will occur if exceeds this range.
     *
     * @return     error signal, 0 means ok, <0 means something wrong.
     */
    extern int send(double signal_channel_0,double signal_channel_1 = .0);
    /**
     * @brief      Save the file to local disc.
     *
     * @return     error signal, 0 means ok, <0 means something wrong.
     */
    extern int close();
}

#endif
