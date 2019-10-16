#include <alc.h>
#include <al.h>
#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"OpenAL32.lib")

static ALuint sid;
static int waveform;
ALuint buffers[AUDIO_WAVEFORM_PULSE_MAX];

int audioInit() {
	ALCdevice* device = alcOpenDevice(NULL);// const ALCchar* devicename );
	if (device == NULL)
		return 1;
	ALCcontext* context = alcCreateContext(
		device,//ALCdevice *device,
		NULL); //const ALCint* attrlist );
	if (context == NULL)
		return 1;

	alcMakeContextCurrent(context); //ALCcontext *context


	alGenBuffers(
		AUDIO_WAVEFORM_PULSE_MAX,//ALsizei n,
		buffers);//ALuint* buffers );

	unsigned char pulse[][8] = {
		{0xff,0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0xff,0xff,0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0xff,0xff,0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
		{0xff,0xff,0xff, 0xff, 0xff0, 0xff, 0x00, 0x00} };

	for (int i = AUDIO_WAVEFORM_PULSE_12_5; i <= AUDIO_WAVEFORM_PULSE_MAX; i++){
		ALsizei size = sizeof pulse[0];
	alBufferData(
		buffers[i], AL_FORMAT_MONO8,	//ALuint bid, ALenum format, 
		pulse[i],//const ALvoid* data,
		size, size * 440);//ALsizei size, ALsizei freq );
}

	
	alGenSources(
		1,//ALsizei n, 
		&sid);//ALuint * sources
	

	
	
	alSourcei(
		sid,//ALuint sid, 
		AL_LOOPING,//ALenum param, 
		AL_TRUE);//ALint value
	alSourcef(
		sid,//ALuint sid,
		AL_GAIN,//ALenum param, 
		0.1f);	//ALfloat value 

	return 0;
	
}
void audioWaveform(int _waveform) {
	waveform = _waveform;
}
void audioPlay() {
	alSourcei(
		sid,//ALuint sid, 
		AL_BUFFER,//ALenum param, 
		buffers[waveform]);//ALint value
	alSourcePlay( sid);
}
void audioStop() {
	alSourceStop(sid);
}