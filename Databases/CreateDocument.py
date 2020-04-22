import json 
from bson import json_util 
from pymongo import MongoClient 

connection = MongoClient() 
db = connection['market'] 
collection = db['stocks']

#check that there is not another ticker with that value
def check_existance(tickerValue):
     foundOne = db.stocks.find_one({"Ticker": tickerValue})
     if foundOne == None:
         return 1;
     else:
         return 0;

# verify that the values are correct to create the document
def verify_create_document(tickerValue): 

    print("Please verify the creation of a new stock with Ticker value: " + tickerValue)
    answer = input("Enter 1 for yes or 2 for no: ")

    if answer == '1':
        return 1;
    elif answer == '2':
        return 2;
    else:
        verify_create_document(tickerValue)

# add mode key-value pairs into a new document
def fill_in_new_document(tickerValue):
    print("Would you like to add any more information to the new stock?")
    answer = input("Enter 1 for yes or 2 for no: ")
    
    if answer == '1':
        inspectionKey = input("Enter new key of stock: ")
        inspectionValue = input("Enter new value for the " + inspectionKey + " key: ")
        db.stocks.update({"Ticker": tickerValue}, {"$set": {inspectionKey: inspectionValue}})
        inspection = db.stocks.find_one({"Ticker": tickerValue})
        print(inspection)
        fill_in_new_document(tickerValue)
    elif answer == '2':
        inspection = db.stocks.find_one({"Ticker": tickerValue})
        print(inspection)
        print("The new stock has been added to the collection.")
    else:    
        fill_in_new_document(tickerValue)

# create a document for stocks db
def create_document(): 
    
    print ("To create a new stock, you will need to enter a string at least 3 characters long for the ticker value.")
    print ("An example would be \"AAA\".") 

    tickerValue = input("Enter a ticker value: ")
    doesNotExist = check_existance(tickerValue)

    # ensure there is not a stock with the ticker value already
    if doesNotExist:
        verify = verify_create_document(tickerValue)
        if verify == 1:
            db.stocks.insert_one({"Ticker" : tickerValue})
            print ("The creation of this document passed.")   
            fill_in_new_document(tickerValue)
        else:
            print ("The creation of this document has been cancelled.") 
    else:
        print("A stock already exists with the ticker value " + tickerValue + ".")
            
  

    
