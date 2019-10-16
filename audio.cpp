#include <alc.h>
#include <al.h>
#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"OpenAL32.lib")

static ALuint sid;

int audioInit() {
	ALCdevice*  device = alcOpenDevice(NULL);// const ALCchar* devicename );
	if (device == NULL)
		return 1;
	ALCcontext* context = alcCreateContext(
		device,//ALCdevice *device,
		NULL); //const ALCint* attrlist );
	if (context == NULL)
		return 1;

	alcMakeContextCurrent(context); //ALCcontext *context
	
	ALuint bid;
	alGenBuffers(
		1,//ALsizei n,
		&bid);//ALuint* buffers );

	unsigned char data[] = {0xff,0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	alBufferData(
		bid,AL_FORMAT_MONO8,	//ALuint bid, ALenum format, 
		data,//const ALvoid* data,
		sizeof data,sizeof(data)*440);//ALsizei size, ALsizei freq );
	

	
	alGenSources(
		1,//ALsizei n, 
		&sid);//ALuint * sources
	

	alSourcei(
		sid,//ALuint sid, 
		AL_BUFFER,//ALenum param, 
		bid);//ALint value
	
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
void audioPlay() {
	alSourcePlay( sid);
}
void audioStop() {
	alSourceStop(sid);
}