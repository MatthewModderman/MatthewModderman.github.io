import json 
from bson import json_util 
from pymongo import MongoClient
import pprint

connection = MongoClient() 
db = connection['market'] 
collection = db['stocks']

# Count Moving Average of Stocks with Specified High and Low Values
def count_stocks():
    lowValue = float(input("Enter low value: "))
    highValue = float(input("Enter high value: "))
    if highValue >= lowValue:
            value = db.stocks.count_documents({"50-Day Simple Moving Average":
                                               {"$gte" : lowValue, "$lte" : highValue}})
            print ("The count is " + str(value))           
            print ("The 50 day average count function passed.")         
    else:
        print ("Those values are invalid")
        count_stocks()

# List the Tickers of All Stocks in a Specific Industry
def inudstry_tickers():
    industryName = input("Enter industry: ") 
    for x in db.stocks.find({"Industry": industryName},{"Ticker":1, "_id":0}):
        print (x)
    print ("The industry tickers function passed.")                

# Count the Number of Stocks in an Industry in a Sector 
def sector_shares():
    sectorName = input("Enter sector: ")
    pipeline = [
        {"$match":{"Sector": sectorName}},
        {"$project":{"Sector":1,"Industry":1,"_id":0}},             
        {"$group":{"_id":"$Industry", "count":{"$sum":1}}},
        {"$sort":{"_id":1}}
    ]
    pprint.pprint(list(db.stocks.aggregate(pipeline)))
    print ("The sector shares function passed.")

# menu to choose read function
def read_document():
    print("Please choose from the \"Read Documents\" menu:")
    print("1. Count Moving Average of Stocks with Specified High and Low Values")
    print("2. List the Tickers of All Stocks in a Specific Industry")
    print("3. Count the Number of Stocks in an Industry in a Sector")
    answer = input("Choice: ")
    if answer == '1':
        count_stocks()
    elif answer == '2':
        inudstry_tickers()
    elif answer == '3':
        sector_shares()
    else:
        print("The answer you provided was not acceptable:")
        read_document()
        
    
