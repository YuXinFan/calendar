from base import *

year = 646373
i = 1
days = 0
while ( i < year):
    days += daysYear(i)
    i +=1
print(days)
print("leap" if leap(year) else "non leap")
month = 7 - 1
for i in range(month):
    print(daysMonth(year, i + 1))
    days += daysMonth(year, i + 1)
print(days)
days += 9
print(days)
