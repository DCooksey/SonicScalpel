#include "maximilian.h"
#include "maxiFFT.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <sndfile.hh>

//To hold initially loaded in recording
maxiSample initialSample, initialSampleTwo, resultingSample;

double out;

/*
 * (Spectrogram Data - V = n * m)
 *
 * (V = W * H)
 *
 * (W = n * r)
 * (H = r * m)
 */
const int r = 10;
const int n = 512;
const int m = 128;


//Swapped n - m
//Now using analyseSample 2

//Obsolete values???
//float v[2][512];
//float w[2][r];
//float h[r][512];

float v[n][m] = {0};

//Before the attempt to create matrices from CSVs - This was the theory
//float w[n][r];
//float h[r][m];

//Sizes due to result of NMF (?????????)
float w[128][129] = {0};
float h[512][128] = {0};

float phase[n][m] = {0};

maxiFFT mfft;
maxiIFFT ifft;

double sampleOut;

int initialBufferSize;
int sampleRate;
int signalLength;
int bStop;
int vIndex;
unsigned int readIndex, chunkPosition;

double wave, sample, outputs[2], ifftVal;

float freqMag[n*m] = {0};
int64_t freqMagIndex = 0;

int nAverages;
//float *ifftOutput;

int windowSize, fftSize, ifftSize, hopSize;
int bins, dataSize;

float *audioData;
float *deconstructedAudioData;
int64_t ifftDataSize = 0;

float ifftData[n*m];
/////PHASE DEBUG
float phaseData[n*m];
int64_t phaseIndex = 0;

float currentPhase[n*m];
//TESTING - Changed from float to short
short audioStream[n*m] = {0};

int64_t audioStreamIndex = 0;

int IFFTValsOver1 = 0;

int64_t samplesWrote = 0;
int64_t freqMagAtZero = 0;
int64_t phaseAtZero = 0;

//ATTEMPT: Writing a RAW bin file
void mickRAW(){

        char buffer[ifftDataSize *2]; // if it's a float

        //memcpy(buffer, ifftData, ifftDataSize * 2);

        for(int i = 0; i < ifftDataSize; i+=2){
           buffer[i] = (char)ifftData[i];
        }

        ofstream myFile ("rawBinaryData.bin", ios::out | ios::binary);
        myFile.write (buffer, sizeof(ifftData) *2);

       // out.write((char *)&f1,sizeof(float));


        myFile.close();

}

extern "C" {
//ATTEMPT: SNDFILE LIB

static void
process_data (float *data, int count, int channels)
{	double channel_gain [6] = { 0.5, 0.8, 0.1, 0.4, 0.4, 0.9 } ;
    int k, chan ;

    /* Process the data here.
    ** If the soundfile contains more then 1 channel you need to take care of
    ** the data interleaving youself.
    ** Current we just apply a channel dependant gain.
    */

    for (chan = 0 ; chan < channels ; chan ++)
        for (k = chan ; k < count ; k+= channels)
            data [k] *= channel_gain [chan] ;

    return ;
} /* process_data */

int create_file (const char * fname, int format)
{
    SNDFILE *file2;
    SF_INFO x;
    //SndfileHandle file ;

    memset(&x, 0, sizeof(x));

    x.samplerate = sampleRate;
    x.frames = ifftDataSize;
    x.format = format;
    x.channels = 1;

    file2 = sf_open(fname,SFM_WRITE,&x);
    if (file2 == NULL)
        printf ("sf_open failed : %s\n", sf_strerror (file2));

//    int channels = 1;
//    int srate = 44100 ;

    //file = SndfileHandle(fname, SFM_WRITE, format, channels, srate) ;

    //const float *p = ifftData;

   // memset(ifftData, 0, sizeof(ifftData));

    //sf_write_float(file2,p,ifftDataSize+1*4);
//    if(!sf_write_float(file2, ifftData, ifftDataSize)){
//        std::cout << "ERROR WRITING TO WAVE" << std::endl;
//    }else if(sf_write_float(file2, ifftData, ifftDataSize)){
//        std::cout << "WROTE AUDIOSTREAM TO WAVE" << std::endl;
//    }

   // for(int64_t i = 0; i < 65536; i++){
        //process_data(ifftData, ifftDataSize, x.channels);
        sf_write_float(file2, ifftData, ifftDataSize);
   // }

//    for(int64_t i = 0; i < 65536; i++){
//        sf_write_float(file2, ifftData, i);
//    }


    //samplesWrote = sf_write_float(file2, ifftData, ifftDataSize);
    //std::cout << "SAMPLES WROTE : " << samplesWrote << std::endl;

  //  sf_write_float(file2,ifftData,ifftDataSize);
    sf_close(file2);

    return 0;

//    SF_INFO y;

//    y.channels=1;
//    y.format= format;
//    y.samplerate=44100;
   // y.sections=65356 * 1 * 16 / 8;
    //y.seekable=1;


   // SNDFILE *x = sf_open("AAAA.wav",0,&y);
   // memset (audioStream, 0, sizeof (audioStream)) ;

    //SNDFILE *x;
    //x = sf_open("AAAA.wav",0,y);

    //file.write(audioStream, 65536) ;
   // sf_write_float(sf_open("AAAA.wav",0,y), ifftData,ifftDataSize);

   // sf_close();
    std::cout << "FILE WRITING DONE" << std::endl;

}

void create_file2 (const char * fname, int format)
{
    SndfileHandle file ;
    int channels = 1 ;
    int srate = 44100 ;

    printf ("Creating file named '%s'\n", fname) ;

    file = SndfileHandle(fname, SFM_WRITE, format, channels, srate) ;

    memset (ifftData, 0, sizeof (ifftData)) ;

    file.writeRaw(ifftData, sizeof(ifftData));

    std::cout << "FILE WRITING DONE" << std::endl;
    }
}

//ATTEMPT: Standard Libraries
template <typename T>
void write(std::ofstream& stream, const T& t) {
    stream.write((const char*)&t, sizeof(T));
}

template <typename SampleType>
void writeWAVData(const char* outFile, SampleType* buf, size_t bufSize,
                  int sampleRate, short channels)
{
    std::ofstream stream(outFile, std::ios::binary);
    stream.write("RIFF", 4);
    write<int>(stream, 36 + bufSize);
    stream.write("WAVE", 4);
    stream.write("fmt ", 4);
    write<int>(stream, 16);
    write<short>(stream, 1);                                        // Format (1 = PCM)
    write<short>(stream, channels);                                 // Channels //mono/sterio
    write<int>(stream, sampleRate);

    write<int>(stream, sampleRate * channels * sizeof(SampleType)); // Byterate
    write<short>(stream, channels * sizeof(SampleType));            // Frame size
    write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample
    stream.write("data", 4);
    uint32_t sz = bufSize;
    stream.write((const char*)&sz, 4);
    stream.write((const char*)buf, bufSize);
}

void vToCSV(){

    //MATRIX V
    std::ostringstream ss;
    std::ofstream fileHandler;

    fileHandler.open("v.csv");

    for(int i = 0; i < n; i++){

        for(int j = 0; j < m; j++){

            fileHandler << v[i][j] << ',';

        }

        fileHandler << '\n';

    }

    fileHandler.close();

    std::cout << std::endl;

    std::cout << "Successfully turned V into a CSV file!" << std::endl;
}

void wToMatrix(){

    std::ifstream fileHandler;

    std::cout << "Beginning to create MATRIX W from CSV file." << std::endl;

    fileHandler.open("w.csv");


    for(int row = 0; row < 128; ++row)
    {
        std::string line;
        std::getline(fileHandler, line);
        if ( !fileHandler.good() )
            break;

        std::stringstream iss(line);

        for (int col = 0; col < 129; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;

            float f = boost::lexical_cast<float>(val);

            w[row][col] = f;
        }
    }

    fileHandler.close();

    std::cout << "SUCCESSFULLY created MATRIX W!!! " << std::endl;

    //COMMENT OUT AND DISPLAY CONTENTS OF MATRIX

//    for(int row = 0; row < 128; ++row)
//      {
//          std::cout << "ROW : " << row << std::endl;

//          for (int col = 0; col < 129; ++col)
//          {
//              std::cout << "COL: " << col << std::endl;
//              std::cout << w[row][col] << std::endl;
//          }
//      }


}

void hToMatrix(){

    std::ifstream fileHandler;

    std::cout << "Beginning to create MATRIX H from CSV file." << std::endl;

    fileHandler.open("h.csv");


    for(int row = 0; row < 512; ++row)
    {
        std::string line;
        std::getline(fileHandler, line);
        if ( !fileHandler.good() )
            break;

        std::stringstream iss(line);

        for (int col = 0; col < 128; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;

            float f = boost::lexical_cast<float>(val);

            h[row][col] = f;
        }
    }

    fileHandler.close();

    std::cout << "SUCCESSFULLY created MATRIX H!!! " << std::endl;

    //COMMENT OUT AND DISPLAY CONTENTS OF MATRIX

//    for(int row = 0; row < 512; ++row)
//      {
//          std::cout << "ROW : " << row << std::endl;

//          for (int col = 0; col < 128; ++col)
//          {
//              std::cout << "COL: " << col << std::endl;
//              std::cout << h[row][col] << std::endl;
//          }
//      }
}

void nmf(){

    std::cout << "Calling script to Factorise V into W and H" << std::endl;
    system("./nmf.sh");
    std::cout << "* NMF COMPLETE! *" << std::endl;
}

void analyseSample(maxiSample sample){
    signalLength = sample.length;

    vIndex = -1;

    for (int miniBuffer = 0; miniBuffer < 512; miniBuffer++) {
        audioData[miniBuffer] = (float)sample.play();
    }

    for (int i = 0; i < initialBufferSize; i++) {
        wave = audioData[i];

        if (mfft.process(wave)) {

            vIndex++;

            std::cout << "Reached buffer point " << i << std::endl;

            mfft.magsToDB();

            for (int j = 0; j < fftSize / 2; j++) {

                v[vIndex][j] = mfft.magnitudes[j];
                std::cout << "Analysis Frame: " << vIndex << " FFT Bin: "<< j << " ******* -> " << mfft.magnitudes[j] << std::endl;

            }

        }

    }

    std::cout << "ANALYSIS COMPLETE. PROCEEDING INTO SECOND PHASE - NMF!" << std::endl;

}

void analyseSample2(maxiSample sample){

    vIndex = -1;

    for (int miniBuffer = 0; miniBuffer < 512; miniBuffer++) {
        audioData[miniBuffer] = (float)sample.play();
    }

    for (int i = 0; i < initialBufferSize; i++) {
        wave = audioData[i];

        if (mfft.process(wave)) {

            vIndex++;

            std::cout << "Reached buffer point " << i << std::endl;

            mfft.magsToDB();


            for (int j = 0; j < fftSize / 2; j++) {

                v[j][vIndex] = mfft.magnitudes[j];

                phase[j][vIndex] = mfft.phases[j];

                std::cout << "Analysis Frame: " << vIndex << " FFT Bin: "<< j << " ******* -> " << mfft.magnitudes[j] << std::endl;
                std::cout << "PHASE: " << mfft.magnitudes[j] << std::endl;
            }

        }

    }

    std::cout << "* STFT ANALYSIS COMPLETE *" << std::endl;

}

void analyseSample3(){

    vIndex = -1;

    for (int miniBuffer = 0; miniBuffer < 512; miniBuffer++) {
        audioData[miniBuffer] = (float)initialSampleTwo.play();
    }

    for (int i = 0; i < initialBufferSize; i++) {
        wave = audioData[i];

        if (mfft.process(wave)) {

            vIndex++;

            std::cout << "Reached buffer point " << i << std::endl;

            mfft.magsToDB();


            for (int j = 0; j < fftSize / 2; j++) {

                v[j][vIndex] = mfft.magnitudes[j];

                phase[j][vIndex] = mfft.phases[j];

                std::cout << "Analysis Frame: " << vIndex << " FFT Bin: "<< j << " ******* -> " << mfft.magnitudes[j] << std::endl;
                std::cout << "PHASE: " << mfft.magnitudes[j] << std::endl;
            }

        }

    }

    std::cout << "* STFT ANALYSIS COMPLETE *" << std::endl;

}

void buildWAV(){

    std::cout << "Writing IFFT data to Audio Data stream!" << std::endl;

    for(int j = 0; j < 128; j++){

        for(int i = 0; i < 512; i++){
            freqMag[freqMagIndex] = v[i][j];
            freqMagIndex++;
        }
    }

    freqMagIndex = 0;

    std::cout << "Done!" << std::endl;

    initWAV();

    //int greaterThanZero = 0;

    for(int i = 0; i < (n* m); i++){
        std::cout << "Freq Mag test. Val " << i << " = " << freqMag[i] << std::endl;

//        if(freqMag[i] > 0) {
//            greaterThanZero++;
//        }
    }

    //std::cout << "Number of items over zero: " << greaterThanZero << std::endl;

    float sample;

    for(int j = 0; j < 128; j++){
        for(int i = 0; i < initialBufferSize; i++){

            //audioStream[audioStreamIndex] = ifft.process(&deconstructedAudioData[i], &phase[i][j]);
            //audioStream[audioStreamIndex] = ifft.process(&freqMag[freqMagIndex], &phase[i][j]);
            sample = ifft.process(&freqMag[freqMagIndex], &phase[i][j]);
            ifftData[audioStreamIndex] = ifft.process(&freqMag[freqMagIndex], &phase[i][j]);
            outSample(sample);

            std::cout << "IFFT DATA point " << audioStreamIndex << " = " << ifft.process(&freqMag[freqMagIndex], &phase[i][j]) << std::endl;

            audioStreamIndex++;
            freqMagIndex++;

            ifftDataSize++;

//            if((ifft.process(&freqMag[freqMagIndex], &phase[i][j]) > 0 )|| (ifft.process(&freqMag[freqMagIndex], &phase[i][j]) < 0)){
//                greaterThanZero++;
//            }
        }
    }

  //  std::cout << "Number of items that were not zero: " << greaterThanZero << std::endl;

    //greaterThanZero = 0;
    freqMagIndex = 0;
    audioStreamIndex = 0;
}

void buildWAV2(){

    std::cout << "Writing IFFT data to Audio Data stream!" << std::endl;

    for(int j = 0; j < 128; j++){

        for(int i = 0; i < 512; i++){
            freqMag[freqMagIndex] = v[i][j];
            freqMagIndex++;
        }
    }


    for(int j = 0; j < 128; j++){

        for(int i = 0; i < 512; i++){
            phaseData[phaseIndex] = phase[i][j];
            phaseIndex++;
        }
    }

    freqMagIndex = 0;
    phaseIndex = 0;

    std::cout << "Done!" << std::endl;

    initWAV();

    //int greaterThanZero = 0;

    for(int64_t i = 0; i < (n* m); i++){
        std::cout << "Freq Mag test. Val " << i << " = " << freqMag[i] << std::endl;

        if(freqMag[i] == 0) {
           freqMagAtZero++;
       }
    }

    for(int64_t i = 0; i < (n* m); i++){
        //std::cout << "Freq Mag test. Val " << i << " = " << freqMag[i] << std::endl;

        if(phaseData[i] == 0) {
           phaseAtZero++;
       }
    }

    //std::cout << "Number of items over zero: " << greaterThanZero << std::endl;

    for(int j = 0; j < 128; j++){
        for(int i = 0; i < initialBufferSize; i++){

            //!!!!!!!!!!!!!SOMETHING IS GOING WRONG HERE

            ifftData[audioStreamIndex] = ifft.process(&freqMag[freqMagIndex], &phaseData[phaseIndex]);
            std::cout << "IFFT Process Value: " << ifftData[audioStreamIndex] << std::endl;
            //std::cout << "IFFT Process Value: " << audioStream[audioStreamIndex] << std::endl;

            audioStreamIndex++;
            ifftDataSize++;
            phaseIndex++;
            freqMagIndex++;

//            if((ifft.process(&freqMag[freqMagIndex], &phase[i][j]) > 0 )|| (ifft.process(&freqMag[freqMagIndex], &phase[i][j]) < 0)){
//                greaterThanZero++;
//            }
        }
    }

  //  std::cout << "Number of items that were not zero: " << greaterThanZero << std::endl;

    //greaterThanZero = 0;
    freqMagIndex = 0;
    audioStreamIndex = 0;

    //CONVERT FLOAT TO SHORT

//    for(int i = 0; i < ifftDataSize; i++){

//        audioStream[i] = ifftData[i] * 32767;
//    }

}

void countPhase(){

    float counter, counter2 = 0;

    for(int i = 0; i < n; i++){
        counter += phase[i][0];
        counter2 += phase[i][1];
    }

    std::cout << "FIRST CHUNK PHASES ADD UP TO = " << counter << std::endl;
    std::cout << "SECOND CHUNK PHASES ADD UP TO = " << counter << std::endl;
    std::cout << "TOTAL = " << counter + counter2 << std::endl;
}

void setup() {
    initialSample.load("/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/snare.wav");//load in your samples. Provide the full path to a wav file.
    initialSampleTwo.load("/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/machinedrum_rhodes-chroma-riff-45_synths_one_shot_.wav");
    sampleRate = 44100;
    initialBufferSize = 512;

    fftSize = 1024;
    windowSize = 512;
    hopSize = 256;

    audioData = new float[initialBufferSize];

    memset(audioData, 0, initialBufferSize * sizeof(float));

    mfft.setup(fftSize, windowSize, hopSize);
    ifft.setup(fftSize, windowSize, hopSize);


    //analyseSample2(initialSample);
    analyseSample3();

    vToCSV();

    nmf();

    wToMatrix();

    hToMatrix();

    buildWAV2();

    const char * fname = "AAAAA.wav" ;

    //SNDFILE CREATE WAV
    create_file (fname, SF_FORMAT_WAV | SF_FORMAT_PCM_16) ;

    mickRAW();

    std::cout << "All processes are done! size =  " << ifftDataSize << std::endl;

    std::cout << "Freq Mags at zero = " << freqMagAtZero << std::endl;

    std::cout << "Phases at zero = " << phaseAtZero << std::endl;

}

void play(double *output) {
    
    
    out=initialSampleTwo.play();
    
    output[0]=out;
    output[1]=output[0];
    
}



