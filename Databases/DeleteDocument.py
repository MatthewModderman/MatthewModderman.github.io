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

# verify that the ticker value is correct to delete the document
def verify_delete_document(tickerValue):
    print ("Is this the document you want to delete: Ticker = " + tickerValue+ "?")
    answer = input("Type 1 for yes or 2 for no: ")
    # if the user chooses to delete the document
    if answer == '1':
        return 1
        
    # if the user chooses not to delete the document            
    elif answer == '2':
        return 2
         
    # if the user chooses any input besides those specified           
    else:
        print("Please enter 1 or 2: ")
        verify_delete_document(tickerValue)
        

# delete a document based on inspection key and value
def delete_document(): 
    
    print ("To delete a stock, you will need to enter a key name and the correct value.")
    print ("An example would be \"Ticker\" and \"JEC\".")
    inspectionKey = input("Enter the name of the key: ")
    inspectionValue = input("Enter value: ")
    any_entries = check_existance(inspectionKey, inspectionValue)
    
    # if at least one entry is found, then find and print all entries
    if any_entries == 1:           
        for x in db.stocks.find({inspectionKey: inspectionValue},{"Ticker":1, "_id":0}):
            print (x)
        tickerValue = input("Enter ticker value of entry to delete: ")   
        inspection = db.stocks.find_one({"Ticker": tickerValue})
        
        # if the document with the proper key and value are found
        if inspection != None:
            print (inspection)
            verify = verify_delete_document(tickerValue)
            if verify == 1:
                db.stocks.delete_one({"Ticker": tickerValue})
                print ("The delete function passed.")           
            elif verify == 2:    
                print ("The deletion of this document has been cancelled.") 
            else:
                print ("The delete function failed.") 
            
    # if a document with the key and value are not found 
    else:
        print ("The document with the key: \"" + inspectionKey + "\" and value \"" + inspectionValue + "\" could not be found.")
        print ("Please be aware that the keys and values are case sensitive.")        

          
    
 
           

  

    

    
       
