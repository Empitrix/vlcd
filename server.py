import socket
import sys

PORT = 4210;
family_addr = socket.AF_INET

try:
	sock = socket.socket(family_addr, socket.SOCK_STREAM)
except socket.error as msg:
	print('Error: ' + str(msg[0]) + ': ' + msg[1])
	sys.exit(1)

print('Socket created')
	
try:
	sock.bind(('', PORT))
	print('Socket binded')
	sock.listen(1)
	print('Socket listening')
	conn, addr = sock.accept()
	print('Connected by', addr)
except socket.error as msg:
	print('Error: ' + str(msg[0]) + ': ' + msg[1])
	sock.close()
	sys.exit(1)

while True:
	data = conn.recv(128)
	if not data: break
	data = data.decode()
	print('Received data: ' + data)

	# reply = 'OK: ' + data
	# conn.send(b"\x01\xFF\xFF\xFF\x00\x64\x00\x64\x01")
conn.close()

