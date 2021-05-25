import requests
import json
import random
from threading import Thread
from randomtimestamp import randomtimestamp
import time

url1 = "http://localhost:9080/soil/conditions"
url2 = "http://localhost:9080/meteo/conditions"

headers = {
  'Content-Type': 'application/json'
}


def generateSoilRequest():
    while True:
        payload = json.dumps({
          "minerals": {
            "Ca": round(random.uniform(0, 4), 2),
            "K": round(random.uniform(0, 5), 2),
            "Mg": round(random.uniform(0, 2.5), 2),
            "N": round(random.uniform(0, 6.5), 2),
            "P": round(random.uniform(0, 1.5), 2),
            "S": round(random.uniform(0, 1.5), 2)
          },
          "soil_humidity": random.randint(10, 70),
          "pH": round(random.uniform(6, 8), 1)
        })

        response = requests.request("PUT", url1, headers=headers, data=payload)
        print(response.text)
        time.sleep(round(random.uniform(0.1, 0.5), 1))


def generateMeteoRequest():
    while True:
        payload = json.dumps({
            "air_temperature": round(random.uniform(15, 35), 1),
            "air_humidity": random.randint(40, 90),
            "time_of_day": str(randomtimestamp(pattern='%H:%M:%S'))
        })

        response = requests.request("PUT", url2, headers=headers, data=payload)
        print(response.text)
        time.sleep(round(random.uniform(0.1, 0.5), 1))


if __name__ == '__main__':
    Thread(target=generateSoilRequest).start()
    Thread(target=generateMeteoRequest).start()
