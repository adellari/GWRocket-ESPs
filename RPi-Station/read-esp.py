import serial

ser = serial.Serial("/dev/cu.usbserial-14110",15200)

print("connected to: " + ser.portstr)
count=1

while True:
	if(ser.in_waiting):
		line = ser.readline().decode('latin-1')
		print(line)
		count = count+1
ser.close()
