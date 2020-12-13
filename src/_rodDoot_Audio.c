#include "_rodDoot_DootDoot.h"

void _rodDoot_AudioCallback(void* Userdata, Uint8* Stream, int StreamLength)
{
	_rodDoot_AudioData* Audio = (_rodDoot_AudioData*)Userdata;

	if(!(Audio->Length))
		return;

	Uint32 Length = (Uint32) StreamLength;
	Length = (Length > Audio->Length ? Audio->Length : Length);

	SDL_memcpy(Stream, Audio->Buffer, Length);

	Audio->Buffer += Length;
	Audio->Length -= Length;
}