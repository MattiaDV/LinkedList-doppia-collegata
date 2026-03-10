import requests
import threading

def req():
    res = requests.get("http://localhost:3000")
    print(res.status_code)

threads = []
    
for _ in range(1000):
    t = threading.Thread(target=req)
    t.start()
    threads.append(t)

for t in threads:
    t.join()