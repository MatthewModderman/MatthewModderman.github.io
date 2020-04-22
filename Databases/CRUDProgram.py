import CreateDocument
import ReadDocument
import UpdateDocument
import DeleteDocument
import json
from bson import json_util 
from pymongo import MongoClient 

connection = MongoClient() 
db = connection['market'] 
collection = db['stocks']

# decide which document manipulation        
def make_decision(): 
    print("Please choose an action to be performed on the databases of stocks:")
    print("1. Create Document")
    print("2. Read Document")
    print("3. Update Document")
    print("4. Delete Document")
    print("Or enter Q to quit")
    answer = input("Choice: ")
    
    if answer == '1' or answer == '2' or answer == '3' or answer == '4':
        return int(answer)
    elif answer == 'Q' or answer == 'q':
        return 5
    else:
        print("The answer you provided was not acceptable:")
        return make_decision()

def continue_program(): # user decides whether to continue entering documents
        answer = input("Enter 1 to continue with the stock program or 2 to end: ")
        if answer == '1':
            main()
        elif answer == '2':
            print("Thank you for examining the program")
        else:
            continue_program()
            
# take manipulation choice and call proper file
def main():
    # all answers lead back to this function
    # all exceptions fall through to here
    try:
        choice = make_decision()
        if choice == 1:
            CreateDocument.create_document()
            continue_program()
        elif choice == 2:
            ReadDocument.read_document()
            continue_program()
        elif choice == 3:
            UpdateDocument.update_document()
            continue_program() 
        elif choice == 4:
            DeleteDocument.delete_document()
            continue_program()            
        elif choice == 5:
            print ("Thank you for examining the program")
    # catch exception if try fails    
    except Exception as ex:
        template = "An exception of type {0} occurred. Arguments:\n{1!r}"
        message = template.format(type(ex).__name__, ex.args)
        print (message)              

main()
