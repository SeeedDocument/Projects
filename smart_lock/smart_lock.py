import face_recognition
import numpy
import os
import picamera
import time
import matplotlib.pyplot as plt
import RPi.GPIO as GPIO
from PIL import Image
from ublox_lara_r2 import *

class SmartLock:
	def __init__(self, relay_pin = 5, known_faces_path='known_faces/'):
		self.__init_hardware(relay_pin)
		self.__init_recognise(known_faces_path)
		
		self.__init_ublox()
	
	def load_known_faces(self):
		known_faces = os.listdir(self.__known_faces_path)
		
		for known_face in known_faces:
			self.__known_faces_name.append(known_face[0 : len(known_face) - len('.jpg')])
			
			known_face_image = face_recognition.load_image_file(self.__known_faces_path + known_face)
			self.__known_faces_encoding.append(face_recognition.face_encodings(known_face_image)[0])
		
		return len(self.__known_faces_encoding)
	
	def capture_and_recognise(self):
		self.__camera.capture(self.__capture, format='rgb')
		
		face_locations = face_recognition.face_locations(self.__capture)
		face_encodings = face_recognition.face_encodings(self.__capture, face_locations)
		for face_encoding in face_encodings:
			self.__matched = face_recognition.compare_faces(self.__known_faces_encoding, face_encoding)
		
		return self.__recognise_face_names()
	
	def unlock(self):
		if self.__matched.count(True) > 0:
			img = Image.open('{}/{}.jpg'.format(self.__known_faces_path, self.__known_faces_name[0]))
			plt.imshow(img)
			self.__send_sms()
			
			plt.ion()
			GPIO.output(self.__relay_pin, GPIO.HIGH)
			print('Door opened')
			
			plt.pause(3)
			
			plt.close()
			GPIO.output(self.__relay_pin, GPIO.LOW)
			self.__reset_recognise_params()
			
			return True
		
		self.__retry_count += 1
		print('Please try again...{}'.format(self.__retry_count))
		
		return False
	
	@property
	def phonenum(self):
		return self.__phonenum
	
	@phonenum.setter
	def phonenum(self, phonenum):
		self.__phonenum = phonenum
	
	def __init_hardware(self, relay_pin):
		# init pin of relay
		GPIO.setmode(GPIO.BOARD)
		GPIO.setwarnings(False)
		self.__relay_pin = relay_pin
		GPIO.setup(self.__relay_pin, GPIO.OUT)
		
		# init raspberry pi camera
		self.__camera = picamera.PiCamera()
		self.__camera.resolution = (320, 240)
		self.__capture = numpy.empty((240, 320, 3), dtype=numpy.uint8)
	
	def __init_recognise(self, known_faces_path):
		# initialize known face parameters
		self.__known_faces_name = []
		self.__known_faces_encoding = []
		self.__known_faces_path = known_faces_path
		
		self.__reset_recognise_params()
	
	def __init_ublox(self):
		self.__ublox = Ublox_lara_r2()
		self.__ublox.initialize()
		self.__ublox.reset_power()
		
		self.__phonenum = None
		self.__ublox.debug = False
	
	def __reset_recognise_params(self):
		self.__matched = []
		self.__retry_count = 0
	
	def __recognise_face_names(self):
		match_names = []
		
		for i in range(0, len(self.__matched)):
			if self.__matched[i]:
				match_names.append(self.__known_faces_name[i])
		
		return match_names
	
	def __send_sms(self):
		if self.__phonenum == None:
			return False
		
		for unlocker in self.__recognise_face_names():
			if self.__ublox.sendAT('AT+CMGF=1\r\n'):
				print(self.__ublox.response)
			
			if self.__ublox.sendAT('AT+CMGS="{}"\r\n'.format(self.__phonenum)):
				print(self.__ublox.response)
			
			if self.__ublox.sendAT('{} enter the room.\x1a'.format(unlocker)):
				print(self.__ublox.response)

if __name__ == '__main__':
	lock = SmartLock()
	
	print('Loading known faces...')
	print('{} known face(s) loaded.'.format(lock.load_known_faces()))
	
	lock.phonenum = '<your_phone_number>'
	
	while True:
		for name in lock.capture_and_recognise():
			print('Hello, {}.'.format(name))
		
		lock.unlock()
		
