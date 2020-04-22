import json 
from bson import json_util 
from pymongo import MongoClient

connection = MongoClient() 
db = connection['market'] 
collection = db['stocks']

#check that there is at least one entry with the key and value
def check_existance(inspectionKey, inspectionValue):
     foundOne = db.stocks.find_one({inspectionKey: inspectionValue})
     if foundOne != None:
          return 1;
     else:
          return 0;
     

# Update Any Value of a Stock Based On the Key
def update_any_value():
     inspectionKey = input("Enter key of stock to update: ")
     inspectionValue = input("Enter current value of the stock to update: ")
     any_entries = check_existance(inspectionKey, inspectionValue)
     
     # if at least one entry is found, then find and print all entries
     if any_entries == 1:
          for x in db.stocks.find({inspectionKey: inspectionValue},{inspectionKey: 1, "Ticker":1, "_id":0}):
               print (x)
          tickerValue = input("Enter ticker value of entry to delete: ")
          inspection = db.stocks.find_one({"Ticker": tickerValue})
          
          # if the document with the proper key and value are found
          if inspection != None:
               updateKey = input("Enter updated key: ")
               updateValue = input("Enter updated value: ")
               db.stocks.update({inspectionKey: inspectionValue},
                                    {'$set': {updateKey: updateValue}})
               print ("The update function of this document passed.")
          else:
               print ("The document does not exist.")
               
     else:
          print ("The document with the key: \"" + inspectionKey + "\" and value \"" + inspectionValue + "\" could not be found.")
          print ("Please be aware that the keys and values are case sensitive.")        


# Update the Volume of a Stock        
def update_volume():
     tickerValue = input("Enter ticker value: ")
     volumeValue = eval(input("Enter volume value: "))
    
     # the volume value has to be greater than or equal to 0  
     if volumeValue >= 0:
          inspection = db.stocks.find_one({"Ticker": tickerValue})
          
          # if the ticker value exists, the volume can be updated
          if inspection != None:
               db.stocks.update({"Ticker": tickerValue},
                              {'$set': {"Volume": volumeValue}})
               print ("The update function of this document passed.")
          # if the ticker value does not exist    
          else:
               print ("The document does not exist.")               
     else:
          print ("The volume value must be greater than 0")
          print ("The update function of this document failed.")


# menu to choose update function
def update_document():
    print("Please choose from the \"Update Documents\" menu:")
    print("1. Update Any Value of a Stock Based On the Key")
    print("2. Update the Volume of a Stock")
    answer = input("Choice: ")
    if answer == '1':
        update_any_value()
    elif answer == '2':
        update_volume()
    else:
        print("The answer you provided was not acceptable:")
        update_document()  
