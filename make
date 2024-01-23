#/bin/bash


gcc cpass.c -lsodium -o cpassmann
sudo mv cpassmann /usr/local/bin && sudo cp  en.py /usr/local/bin && sudo cp dec.py /usr/local/bin/

