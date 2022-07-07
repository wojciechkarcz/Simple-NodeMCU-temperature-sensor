import requests
import datetime
from time import strftime, time

#Replace with your sensor IP address
ip = '192.168.X.X'
url = 'http://' + ip + '/temp'

response = requests.get(url)

temp = response.text.split('&')[0]
hum = response.text.split('&')[1]

timestamp = datetime.datetime.now()
timestamp_date = str(timestamp.strftime("%d-%m-%Y"))
timestamp_time = str(timestamp.strftime("%H:%M"))

entry = timestamp_date + "," + timestamp_time + "," + temp + "," + hum + "\n"

#Opening and writing data to a CSV file
csv = open('/home/pi/Documents/temperature_log.csv', 'a')
try:
  csv.write(entry)
finally:
  csv.close()
