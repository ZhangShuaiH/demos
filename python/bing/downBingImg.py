import urllib.request as ur
import datetime

url = 'https://area.sinaapp.com/bingImg'
html = ur.urlopen(url)
open('bing/'+datetime.date.today().strftime('%Y-%m-%d')+'.png','wb').write(html.read())
