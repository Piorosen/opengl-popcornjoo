#include<iostream>
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

using namespace std;
using namespace FMOD;

System* pSystem;
Sound* pSound[2];
Channel* pChannel[1];

void SoundSystem() {
	System_Create(&pSystem);

	pSystem->init(4, FMOD_INIT_NORMAL, NULL);

	pSystem->createSound("test.mp3", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);
	//pSystem->createSound("Festival_of_Ghost.wav", FMOD_DEFAULT, NULL, &pSound[1]);
}

void Play(int Sound_num) {

	pSystem->playSound(pSound[0], NULL, 0, pChannel);
}


int main(void) {
	SoundSystem();
	while (1) {

		Play(0);
	}


	return 0;
}