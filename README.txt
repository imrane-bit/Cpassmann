cpassmann 1.0 by Qubit                cpassmann Reference Guide                 

NAME
       cpassmannn - c passwords manager

SYNOPSIS

       cpassmann -{option} -{option}...etc

DESCRIPTION
  Cpassmann is a simple but usefull terminal password manager by Qubit, it not meant to compete with the already available passwords managers but i hope the users find it helpfull ,it basically gives you the ability to protect your password with encryption while having easy access to them , the program needs a usb in order to store the very variable encryption key .

  cpassmann is a enchanted version made with c of a  previous version i made with python , the encryption and decryption process still rely on python because of some complication hat encoutered me while emplementing symetric encryption in c , the encryption and decryption scripts rely on the python cryptography library. otherwise the program is totally in c .

  the program have not much of dependencies , you aonly need :
  *a linux operating sysytem
  *libsodium cryptography lib in C .
  *python 3
  *gcc or any compiler
   
   +you can install all of them by running the following commands :

   ++if on Fedora run  : 
     sudo dnf makecache --refresh
     sudo dnf -y install libsodium
     sudo dnf -y install gcc
     sudo dnf -y install python3
   ++if on Arch or Arch based sysytems:
     sudo pacman -Syu 
     sudo pacman -S libsodium
     sudo pacman -S gcc
     sudo pacman -S python3
   ++if on ubuntu or ubuntu based systems :
     sudo apt-get update 
     sudo apt-get install libsodium-dev
     sudo apt-get install python3
     sudo apt-get install gcc

-the packages should be available in most package managers whatever distro you're using  

INSTALATION
you need first to specify to edit the path to the usb in the source code to the path of yours and also the path of your home directory , they are in the head of  the ccode like the following :
    

    #include <string.h> 
    #include <stdio.h>
    #include <sodium.h>
    #include <stdlib.h>
 
    char *usbpath = "" ;/*the full path to your usb between inside "" 
    example :char *usbpath = "/run/media/qubit/myusb" */;
    char *home = "";/* the full path to your home directory here
    example : /home/qbit/*/

    write the coresponding info between the "" .
    then cd to the folder of passmann and run the following commands:
           chmod +x make
           ./make

and now you're good to go 


USAGE :
    cpassmann is a command line program that take its arguments that specify the a  ction trought the cmmand line ,the command are as follows:

    SYNOPSIS

       cpassmann -{option} -{option}...etc

  OPTIONS
      -A : show all the accounts
      -a : add an account
      -m : modify account , you should provide a second option regarding what you want to change :
        -m -u(username) 
        -m -e(email) 
        -m -P(password 
        -m -p(platform)

      -s : search for a account by a keyword 
          SYNOPSIS : cpassmann -s KEYWORD
      -d : to delete a account using its number (numbers are shown when printing the accounts ) 
          SYNOPSIS : cpassmann -d NUMBER

thats all i gess , if you encounter any problem please email me ,or just edit the code yourself if you want and can do it .

SEE YOU , SPACE COWBOY.
