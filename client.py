import socket
import sys

PORT = 4210;

family_addr = socket.AF_INET
# host = "192.168.1.102"
host = "127.0.0.1"

try:
	sock = socket.socket(family_addr, socket.SOCK_STREAM)
except socket.error as msg:
	print("Could not create socket: " + str(msg[0]) + ": " + msg[1])
	sys.exit(1);

try:
	sock.connect((host, PORT))
except socket.error as msg:
	print("Could not open socket: ", msg)
	sock.close()
	sys.exit(1);

while True:
	# msg = input("Enter message to send: ")
	# assert isinstance(msg, str)
	# msg = msg.encode()
	# sock.sendall(msg)

	sock.sendall(b"\x01\xFF\xFF\xFF\x00\x64\x00\x64\x01")
	print("Send all of them")


	#// data = sock.recv(1024)
	#// if not data: break; 
	#// print("GOT SOME")
	# print("Reply: " + data.decode())

sock.close()
