1. a secret_key python file will generate a hash and will also save a code to a secret_key.txt 
file that will only be able to be obtain via a USB stick

2. In order to run both files we need to input the code. If the worong file was not inserted then the programm
will stop

3. Once both programms run they will start to connect together

4. send.py will then be able start a timer and then it will state if both files are connected

5. once reciever.py says that file has being connected. Send.py will then send the file

6. once all data has been send send.py will get a verification that the data was sent

7. the receiver.py wil recieved the data in 1024 bytes and after will print a message saying 
that they have gather all the data
 
8. after getting all the data it will then print the data

9. After printing the data it will then print out the data hash and verified if it the same hash as the 
one in the secret_key.txt file 

10. after veryfing that the data is correct it will then send the data back 
to the sender and delete the data 

11. Once the sender recived the file the sender will then hash the file to ensure that the 
file is the correct one and it was not tampered with

12. If tampered then it will send a message saying it that it was tampered

13. Once the program ends then the program will stop and print the endtime as well as the 
total time the programm ran