#include "MP3.h"

MP3::MP3(uint8_t rxPin, uint8_t txPin) {
	_serial = new SoftwareSerial(rxPin, txPin);
}

MP3::~MP3() {
	delete _serial;
}

bool MP3::init(void) {
  _serial->begin(9600);
  while (!(*_serial));

#ifdef DEBUG
  Serial.begin(9600);
  while (!Serial);
#endif
  
  delay(100);
  
  selectStorageDevice(SDCard);
  setVolume(0x0e);

  return true;
}

void MP3::selectStorageDevice(MP3StorageDevice device) {
	startTransmission();
	
	_serial->write(0x09);
	_serial->write((uint8_t)0x00);
	_serial->write((uint8_t)0x00);
	_serial->write((uint8_t)device);

#ifdef DEBUG
  Serial.write(0x09);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)device);
#endif
	
	endTransmission();
	delay(200);
}

void MP3::play(uint16_t mp3Index) {
  uint8_t hbyte, lbyte;
  startTransmission();

  hbyte = mp3Index / 256;
  lbyte = mp3Index % 256;

  _serial->write(0x03);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)hbyte);
  _serial->write((uint8_t)lbyte);

#ifdef DEBUG
  Serial.write(0x03);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)hbyte);
  Serial.write((uint8_t)lbyte);
#endif

  endTransmission();
  delay(10);
}

void MP3::play(uint8_t folderIndex, uint8_t mp3Index) {
  startTransmission();
  
  _serial->write(0x0f);
  _serial->write((uint8_t)0x00);
  _serial->write(folderIndex);
  _serial->write(mp3Index);

#ifdef DEBUG
  Serial.write(0x0f);
  Serial.write((uint8_t)0x00);
  Serial.write(folderIndex);
  Serial.write(mp3Index);
#endif
  
  endTransmission();
  delay(10);
}

void MP3::loop(void) {
  startTransmission();

  _serial->write(0x11);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write(0x01);

#ifdef DEBUG
  Serial.write(0x11);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write(0x01);
#endif

  endTransmission();
  delay(10);
}

void MP3::playMP3Folder(uint16_t mp3Index) {
  uint8_t hbyte, lbyte;
  startTransmission();

  hbyte = mp3Index / 256;
  lbyte = mp3Index % 256;
  
  _serial->write(0x12);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)hbyte);
  _serial->write((uint8_t)lbyte);

#ifdef DEBUG
  Serial.write(0x12);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)hbyte);
  Serial.write((uint8_t)lbyte);
#endif

  endTransmission();
  delay(10);
}

void MP3::pause(void) {
  startTransmission();

  _serial->write(0x0e);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);

#ifdef DEBUG
  Serial.write(0x0e);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
#endif

  endTransmission();
  delay(20);
}

void MP3::resume(void) {
  startTransmission();

  _serial->write(0x0d);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);

#ifdef DEBUG
  Serial.write(0x0d);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
#endif

  endTransmission();
  delay(20);
}

void MP3::next(void) {
  startTransmission();

  _serial->write(0x01);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);

#ifdef DEBUG
  Serial.write(0x01);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
#endif

  endTransmission();
  delay(10);
}

void MP3::previous(void) {
  startTransmission();

  _serial->write(0x02);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);

#ifdef DEBUG
  Serial.write(0x02);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
#endif

  endTransmission();
  delay(10);
}

void MP3::setVolume(uint8_t volume) {
	startTransmission();
	
	_serial->write(0x06);
	_serial->write((uint8_t)0x00);
	_serial->write((uint8_t)0x00);
	_serial->write(volume);

#ifdef DEBUG
  Serial.write(0x06);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write(volume);
#endif
	
	endTransmission();
	delay(10);
}

void MP3::increaseVolume(void) {
  startTransmission();

  _serial->write(0x04);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);

#ifdef DEBUG
  Serial.write(0x04);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
#endif

  endTransmission();
  delay(10);
}

void MP3::decreaseVolume(void) {
  startTransmission();

  _serial->write(0x05);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);
  _serial->write((uint8_t)0x00);

#ifdef DEBUG
  Serial.write(0x05);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
  Serial.write((uint8_t)0x00);
#endif

  endTransmission();
  delay(10);
}

void MP3::startTransmission(void) {
	_serial->write(0x7e);
	_serial->write(0xff);
	_serial->write(0x06);

#ifdef DEBUG
  Serial.write(0x7e);
  Serial.write(0xff);
  Serial.write(0x06);
#endif
}

void MP3::endTransmission(void) {
	_serial->write(0xef);

#ifdef DEBUG
  Serial.write(0xef);
#endif
}
