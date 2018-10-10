#ifndef __MP3_H__
#define __MP3_H__

#include <Arduino.h>
#include <SoftwareSerial.h>

// #define DEBUG

typedef enum {
	USBDisk	= 1, 
	SDCard	= 2
} MP3StorageDevice;

class MP3 {
	public:
		MP3(uint8_t rxPin, uint8_t txPin);
		~MP3();
   
		bool init(void);
		void selectStorageDevice(MP3StorageDevice device);
		
    void play(uint16_t mp3Index);
		void play(uint8_t folderIndex, uint8_t mp3Index);

    void loop(void);
    void playMP3Folder(uint16_t mp3Index);
		
		void pause(void);
		void resume(void);
		
		void next(void);
		void previous(void);
		
		void setVolume(uint8_t volume);
		void increaseVolume(void);
		void decreaseVolume(void);
		
	private:
		SoftwareSerial * _serial;
		
		void startTransmission(void);
		void endTransmission(void);
};

#endif // __MP3_H__
