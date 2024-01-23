from cryptography.fernet import Fernet
import sys 
import os


def decrypt_file(encryptedfile , keyfile):
    try :

        with open(keyfile , 'rb') as keyfile:
            seckey = keyfile.read()
            keyfile.close()


        with open(encryptedfile, 'rb') as encfile:
            data = encfile.read()
            decrypted = Fernet(seckey).decrypt(data)
            encfile.close()


        with open(encryptedfile, 'wb') as encfile :
            encfile.write(decrypted)
            encfile.close()
            return 0;
    except :
        return -1
    

decrypt_file(sys.argv[1],sys.argv[2]) 
