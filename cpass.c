#include <string.h> 
#include <stdio.h>
#include <sodium.h>
#include <stdlib.h>
#include <sys/stat.h>

char *usbpath = "/run/media/qbit/whitehouse/" ;/*the full path to your usb between inside "" 
    example :char *usbpath = "/run/media/qubit/myusb" */;

char *home = "/home/qbit/";/* the full path to your home directory here
    example : char *home = "/home/qbit/" */


char *remend(char *lineh){
  char *c = malloc(sizeof(char));
  char *output = malloc(1000*sizeof(char));
  while(*(c=lineh++) != '\0'){
    if (*c == '\n'){
      continue;
    }
    else {
      strncat(output,c,1);
    }
  }
  return output;
}
//backup file path 
char *bkfile; 

//file path 
char *filepath;

//backup key path 
char *bkkey;
//keypath 
char *keypath;

char *cpasfolder;

char *bk;

char *bk1;

char *bk2;

int defpaths(void){
  cpasfolder = malloc(1000*sizeof(char));
  bk= malloc(1000*sizeof(char));
  bk1= malloc(1000*sizeof(char));
  bk2= malloc(1000*sizeof(char));
  sprintf(cpasfolder,"%s.cpassmann/",remend(home));
  sprintf(bk,"%s.backup",remend(cpasfolder));
  sprintf(bk1,"%s.cpassmannkey",remend(usbpath));
  sprintf(bk2,"%s.cpassmannkey/.backup",remend(usbpath));
    struct stat sb; 
  struct stat ab; 
  struct stat kb; 
  struct stat lb; 
  if (stat(cpasfolder, &sb) == 0) {
    ;
  }
  else {
    if(mkdir(cpasfolder,S_IRWXU) != -1)
     ; 
   else {
     printf("eror mkdir2\n");
     return -1;
   }
  }  
  if (stat(bk, &ab) == 0) {
    ;
  }
  else {
    if(mkdir(bk,S_IRWXU) != -1)
     ; 
   else {
     printf("eror mkdir2\n");
     return -1;
   }
  }  
  if (stat(bk1, &kb) == 0) {
    ;
  }
  else {
    if(mkdir(bk1,S_IRWXU) != -1)
     ; 
   else {
     printf("eror mkdir2\n");
     return -1;
   }
  } 
  if (stat(bk2, &lb) == 0) {
    ;
  }
  else {
    if(mkdir(bk2,S_IRWXU) != -1)
     ; 
   else {
     printf("eror mkdir2\n");
     return -1;
   }
  }  
 


  bkfile = malloc(1000*sizeof(char));
  sprintf(bkfile,"%s.cpassmann/.backup/accounts",home);
  filepath= malloc(1000*sizeof(char));
  sprintf(filepath,"%s.cpassmann/accounts",home);
  if (fopen(filepath,"r") != NULL)
    ;
  else {
    fopen(filepath,"a");
  }

  bkkey= malloc(1000*sizeof(int));
  sprintf(bkkey,"%s.cpassmannkey/.backup/key.key",usbpath);
  keypath = malloc(1000*sizeof(int));
  sprintf(keypath,"%s.cpassmannkey/key.key",usbpath);
}
char *accountline;
char *c;
char *randpass(int i){
  char *password = calloc(i,sizeof(char));
  c = malloc(sizeof(char)) ;
  for (;i > 0 ; i--){
    *c = (char ) (randombytes_uniform(96)+32);
    strncat(password,c,1);
  }
  return password ;
}

int encrypt(char *filename){
  char *command = malloc(100*sizeof(char));
  sprintf(command,"python3 /usr/local/bin/en.py %s ",filename);
  system(command);
  free(command);
  return 0;
}
int decrypt(char *filename ,char *key){
  char *command = malloc(300*sizeof(char));
  sprintf(command,"python3 /usr/local/bin/dec.py %s %s",filename,key);
  system(command);
  free(command);
   return 0;
}
char *stcomma(char *text,int num){
  char *output;
  extern char *c;
  c = malloc(2*sizeof(char));
  switch (num) {
    case 0:
      output = malloc(100*sizeof(char));
      break ;
    case 1:
      output = malloc(100*sizeof(char));
      break;
    case 2:
      output = malloc(400*sizeof(char));
      break;
    case 3:
      output = malloc(400*sizeof(char));
      break;

  }
  while((*c=*text++) != '\0'){
    if (*c == ((char) 192)){
      char *n;
      *n = ',';
      strncat(output,n,1);
    }
    else {
      strncat(output,c,1);
    }
  }
  return output;

}
char *commast(char *text,int num){
  char *output;
  extern char *c;
  c = malloc(2*sizeof(char));
  switch (num) {
    case 0:
      output = malloc(100*sizeof(char));
      break ;
    case 1:
      output = malloc(100*sizeof(char));
      break;
    case 2:
      output = malloc(400*sizeof(char));
      break;
    case 3:
      output = malloc(100*sizeof(char));
      break;

  }
  while((*c=*text++) != '\0'){
    if (*c == ','){
      char *n = malloc(2*sizeof(char));
      *n= (char) 192;
      strncat(output,n,1);
    }
    else {
      strncat(output,c,1);
    }
  }
  return output;

}

char *getcolumn(char *line){
  char *output = malloc(strlen(line)*sizeof(char));
  while (*line == ',' ){
    ++line;
  }
  while (*line != ',' &&  *line != '\0'){
    strncat(output,line,1);
    ++line;
  }
  accountline = line;
  return output;
}

void printaccount(int i){
  printf("%2d:\n",i);
  printf("   name : %s\n",stcomma(getcolumn(accountline),0));
  printf("   email : %s\n",stcomma(getcolumn(accountline),1));
  printf("   password : %s\n",stcomma(getcolumn(accountline),2));
  printf("   platform : %s\n\n",stcomma(getcolumn(accountline),3));
}

char *apndclmns(char *name , char *email ,char *password,char *other ){
  char *o = ",";
  char *line = malloc((strlen(name)+strlen(email)+strlen(password)+strlen(other)+4)*sizeof(char));
  strcat(line,name);
  strcat(line,o);
  strcat(line,email);
  strcat(line,o);
  strcat(line,password);
  strcat(line,o);
  strcat(line,other);
  return line;
}

void putline(char *line , FILE *file){
  fputs(line, file);
  return ;
}



void showallaccs(char *filename){
  int i = 0;
  extern char *accountline;
  accountline= malloc(1000*sizeof(char));
  FILE *file = fopen(filename,"r");
  while (fgets(accountline ,1000,file) != NULL ){
    if (i == 0){
      ++i;
      continue;
    }

    printaccount(i++);
    accountline= calloc(1000,sizeof(char));
    continue ;
  }
  return ;
}

void getaccount(char *thefile){
  char *name = malloc (100*sizeof(char));
  char *email=malloc(100*sizeof(char));
  char *password = malloc(400*sizeof(char));
  char *other = malloc(100*sizeof(char));
  char *commandd = malloc(300*sizeof(char));
  char *command = malloc(300*sizeof(char));
  printf("enter the name :");
  fgets(name,100,stdin);
  printf("enter the email :");
  fgets(email,100,stdin);
  printf("enter the password :");
  fgets(password,400,stdin);
  printf("enter the other :");
  fgets(other,100,stdin);
  char *acc = malloc(1000*sizeof(char));
  acc = apndclmns(remend(commast(name,0)),remend(commast(email,2)),remend(commast(password,2)),commast(other,3));
  sprintf(commandd,"cp %s temp",thefile);
  system(commandd);
  FILE *accounts = fopen("temp","a");
  FILE *accountss = fopen("temp","r");
  char* test = malloc(2000*sizeof(int));
  int U =3;
  int B =0;
  while (fgets(test,3000,accountss) != NULL && U-- >=0){
    printf("%s\n",test);
    ++B;
  }
if (B==0){
  putline("\n",accounts);
  putline(acc,accounts);
}
else {
  putline(acc,accounts);
}
  free(name);
  free(email);
  free(password);
  free(other);
  free(acc);
  sprintf(command,"mv temp %s",thefile);
  system(command);
  fclose(accounts);
  free(commandd);
  free(command);
}

void keywordsearch(char *filename,char *keyword){
  extern char *accountline;
  accountline= malloc(700*sizeof(char));
  int i = 0;
  FILE *file = fopen(filename,"r");
  while (fgets(accountline ,700,file) != NULL ){
    if (strstr(accountline,keyword)){
      printaccount(i++);
      continue ;
    }
    else {
      ++i;
      continue;
    }
  }
  fclose(file);
  return ;
}

void delaccount(int j ,char *thefile){
  extern char *accountline;
  int i = 0;
  accountline= malloc(700*sizeof(char));
  char *command= malloc(300*sizeof(char));
  FILE *tmp = fopen("temp","a");
  FILE *accs = fopen(thefile,"r");
  while (fgets(accountline ,700,accs) != NULL ){
    if (i != j ){
      fputs(accountline, tmp);
      ++i;
      continue ;
    }
    else {
      ++i;
      continue;
    }
  }
  fclose(accs);
  fclose(tmp);
  sprintf(command, "rm %s",thefile);
  system(command);
  sprintf(command, "mv temp %s",thefile);
  system(command);
  free(command);
  return ;
}

int modifyaccount (int accnum , char *option ,char *thefile){
  extern char *accountline;
  accountline= malloc(700*sizeof(char));
  char *command= malloc(300*sizeof(char));
  char *opt;
  char *new ;
  int i = 0;
  FILE *tmp = fopen("temp","a");
  FILE *accs = fopen(thefile,"r");
  if (*option == 'P' ){
    opt = "password";
    new = malloc(400*sizeof(char));
  }
  else if (*option == 'e'){
    opt = "email";
    new = malloc(100*sizeof(char));}
  else if (*option == 'u'){
    opt = "user";new = malloc(100*sizeof(char));}
  else if (*option == 'p'){
    opt = "ptaform";new = malloc(100*sizeof(char));}
  else {
    printf("no valid option\n");
    return -1;
  }
  while (fgets(accountline ,700,accs) != NULL ){
    if (i != accnum ){
      fputs(accountline, tmp);
      ++i;
      continue ;
    }
    else {
      char *name = malloc(100*sizeof(char));
      char *email=malloc(100*sizeof(char));
      char *password = malloc(400*sizeof(char));
      char *platform = malloc(100*sizeof(char));

      printf("enter the new %s : ",opt);
      fgets(new,400,stdin);
      if (*option == 'u'){
        getcolumn(accountline);
        email = getcolumn(accountline);
        password = getcolumn(accountline);
        platform = getcolumn(accountline);
        accountline = apndclmns(remend(commast(new,0)),commast(email,2),commast(password,2),commast(platform,3));
      }
      else if (*option == 'e'){
        name = getcolumn(accountline);
        getcolumn(accountline);
        password = getcolumn(accountline);
        platform = getcolumn(accountline);
        accountline = apndclmns(commast(name,0),remend(commast(new,2)),commast(password,2),commast(platform,3));
      }
      else if (*option == 'P'){
        name = getcolumn(accountline);
        email = getcolumn(accountline);
        getcolumn(accountline);
        platform = getcolumn(accountline);
        accountline = apndclmns(commast(name,0),commast(email,2),remend(commast(new,2)),commast(platform,3));
      }
      else if (*option == 'p'){
        name = getcolumn(accountline);
        email = getcolumn(accountline);
        password = getcolumn(accountline);
        getcolumn(accountline);
        strcat(new,"\n");
        accountline = apndclmns(commast(name,0),commast(email,2),commast(password,2),remend(commast(new,3)));
      }
      fputs(accountline, tmp);
      ++i;
      free(name);
      free(email);
      free(password);
      free(platform);

      continue;
    }
  }
  fclose(accs);
  fclose(tmp);
  sprintf(command, "rm %s",thefile);
  system(command);
  sprintf(command, "mv temp %s",thefile);
  system(command);
  free(command);
  return 0 ;
}
int genfile(char *filename){
  FILE *accos = fopen(filename,"r");
  FILE *accounts = fopen("account","a");
  char *wtf= malloc(400*sizeof(char));
  while (fgets(wtf,400,accos)!= NULL){
    fputs(commast(wtf,2),accounts);
  }
  return 0;
  free(wtf);
  fclose(accos);
  fclose(accounts);
}
void order(char *filename){
  FILE *smthng = fopen(filename,"r");
  FILE *gigity = fopen(filepath,"a");
  int i = 0;
  char *wtf= malloc(800*sizeof(char));
  char *name = malloc(100*sizeof(char));
  char *email=malloc(100*sizeof(char));
  char *password = malloc(400*sizeof(char));
  char *platform = malloc(100*sizeof(char));


  while(fgets(name,100,smthng)!= NULL){
  fgets(email,100,smthng);
  fgets(password,400,smthng);
  fgets(platform,100,smthng);
  wtf = apndclmns(remend(name),remend(email),remend(password),platform);
  fputs(wtf, gigity);
    }



  free(name);
  free(email);
  free(password);
  free(platform);
  fclose(gigity);
  fclose(smthng);
}
int makebackup(char *bkkey,char *key,char *bkfile ,char *file){
  FILE *pkey = fopen(key,"r");
  FILE *pbkkey = fopen(bkkey,"w");
  char *buff = malloc(80*sizeof(char));
  while (fgets(buff,80,pkey) != NULL){
    fputs(buff, pbkkey);
  }
  fclose(pkey);
  fclose(pbkkey);
  free(buff);
  FILE *pfile = fopen(file,"r");
  FILE *pbkfile = fopen(bkfile,"w");
  char *buffer = malloc(100000000*sizeof(char));
  while (fgets(buffer,10000000,pfile) != NULL){
    fputs(buffer, pbkfile);
  }
  fclose(pfile);
  fclose(pbkfile);
  free(buffer);
  return 0;
}
int getbackup(char *bkkey,char *key,char *bkfile ,char *file){

  FILE *pkey = fopen(key,"w");
  FILE *pbkkey = fopen(bkkey,"r");
  char *buff = malloc(80*sizeof(char));
  while (fgets(buff,80,pbkkey) != NULL){
    fputs(buff, pkey);
  }
  fclose(pkey);
  fclose(pbkkey);
  free(buff);
  FILE *pfile = fopen(file,"w");
  FILE *pbkfile = fopen(bkfile,"r");
  char *buffer = malloc(100000000*sizeof(char));
  while (fgets(buffer,10000000,pbkfile) != NULL){
    fputs(buffer, pfile);
  }
  fclose(pfile);
  fclose(pbkfile);
  free(buffer);
  return 0;
}
int main (int argc, char *argv[]){
  defpaths();
  int s,a,d,m,A,B,U;
  U = 3;
  s = a = d = m = A = B = 0;
  char *test = malloc(10000000*sizeof(char));
     

  if ((argc > 1 ) ){
    if (*argv[1] == '-'){
      if ( *(argv[1]+1)== 'b'){
        makebackup(bkkey,keypath,bkfile,filepath);
      }
      else if ( *(argv[1]+1)== 'g' && *(argv[1]+2)== 'b' ){
        getbackup(bkkey,keypath,bkfile,filepath);
      }
      else {
        decrypt(filepath,keypath);
        FILE *decryptiontest = fopen(filepath,"r");
        while (fgets(test,10000000,decryptiontest) != NULL && U-- >=0){
          ++B;
        }
        fclose(decryptiontest);
        free(test);
        if (B != 1 ){
          if ( *(argv[1]+1)== 'A'){
            showallaccs(filepath);
          }
          else if ( *(argv[1]+1)== 's'){
            char *keyword;
            keywordsearch(filepath,argv[2]);
          }
          else if ( *(argv[1]+1)== 'd'){
            delaccount(atoi(argv[2]),filepath);
          }
          else if ( *(argv[1]+1)== 'a'){
            getaccount(filepath); }
          else if ( *(argv[1]+1)== 'm'){
            modifyaccount(atoi(argv[2]),(argv[3]+1),filepath);
          }
          encrypt(filepath); 
          char *command = malloc(300*sizeof(char));
          sprintf(command,"mv key.key %s",keypath);
          system(command);
          free(command);
        }
        else {
        printf("decryption eror\n");
        return -2;

        }}}

    return 0;
  }
  else {
    return -1 ;
  }

  free(test);
}
