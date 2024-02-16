#include <stdio.h>
#include <portaudio.h>

int main(int argc, char *argv[])
{

    WAVEReader *reader = new WAVEReader();
    if (!reader->Open(argv[1]))
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    AudioStreamBasicDescription stream_desc;
    memset(&stream_desc, 0, sizeof(AudioStreamBasicDescription));
    stream_desc.Format = 32768;     // 44100 Hz, 16 bit, stereo
    stream_desc.SampleRate = 44100; // Samples per second
    stream_desc.Channels = 2;
    stream_desc.FramesPerFrame = 16;
    stream_desc.SamplesPerFrame = 16;
    stream_desc.BytesPerFrame = 16;
    reader->SetPointers(0, NULL, 0, 0); // Setup pointers to default output buffer
    AudioInputStream *input_stream = reader->Open(argv[1], &stream_desc, nullptr);
    if (!input_stream)
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    int sample_rate_hertz = 44100; // Samples per second
    int num_channels = 2;
    float sample_resolution = 16; // bits per sample
    int buffer_size = static_cast<int>(num_channels * sample_resolution);
    AudioSampleType *samples = new AudioSampleType[buffer_size];
    float *audio_data = new float[buffer_size];
    int bytes_per_sample = 16;
    for (int i = 0; i < buffer_size; i++)
    {
        samples[i] = static_cast<float>(i) / num_channels;
        audio_data[i] = samples[i];
    }
    input_stream->SetPointers(num_channels * sample_resolution, audio_data, 0, 0); // Setup pointers to output buffer
    input_stream->PutFloat(samples, buffer_size);                                  // Write samples to output buffer
    input_stream->Close();
    delete[] audio_data;
    reader->Release();
    System::Runtime::InteropServices::GetUnmanagedAuth();
    return 0;
}