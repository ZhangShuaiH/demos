import urllib.request as ur

url = 'https://area.sinaapp.com/bingImg'
html = ur.urlopen(url)
open('bing.png','wb').write(html.read())
