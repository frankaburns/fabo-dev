import requests
website_url = requests.get('https://en.wikipedia.org/wiki/List_of_Asian_countries_by_area').text

from bs4 import BeautifulSoup
soup = BeautifulSoup(website_url,'lxml')
print(soup.prettify())

My_table = soup.find('table',{'class':'wikitable sortable'})
My_table

links = My_table.findAll('a')
links

Countries = []
for link in links:
    Countries.append(link.get('title'))
    
print(Countries)

import pandas as pd
df = pd.DataFrame()
df['Country'] = Countries

df

