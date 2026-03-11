import socket
import threading

IP = "26.18.49.149"
PORT = 25565

def connect():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((IP, PORT))
        print("Connesso")
    except:
        print("Connessione fallita")

threads = []

for _ in range(200):
    t = threading.Thread(target=connect)
    t.start()
    threads.append(t)

for t in threads:
    t.join()