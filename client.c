
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main (int argc, char *argv[])
{
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  struct opera
{
   int number1;  //operand 1
   int number2;  //operand 2
   char op;      //opcode - '+','-','*' sau '/'
}operation;
struct responese
{
  char message[30];
  int result;
}res;
int msg;
  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }
  char command[100];
  char username[20],password[20];
  char raspuns[1000];
  char type[100];
  char loginFail[]="login fail";
  int login_OK=0;
  /* citirea mesajului */
  printf ("                 --------------------------                      \n");
  printf ("                | Welcome to our music app |                     \n");
  printf ("                 --------------------------                      \n");
  printf("\n\n\n\n");
  char url[]= "firefox https://google.com";
 // system(url);
  while(!login_OK){
  printf("\n                 To continue type one of this commnads \n");
  printf("\n      user login\n      admin login\n      user register\n");

  fgets(command,sizeof(command),stdin);
  /* trimiterea mesajului la server */


  if (write (sd,command,sizeof(command)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    strcpy(type,command);

   printf("introduceti username-ul: ");
   fgets(username,sizeof(username),stdin);
   printf("introduceti parola: ");
   fgets(password,sizeof(password),stdin); 
   if (write (sd,&username,sizeof(username)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }if (write (sd,&password,sizeof(password)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }

  if (read (sd, &raspuns,sizeof(raspuns)) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    } 

  /* afisam mesajul primit */

  printf ("%s\n",raspuns);
  if(strstr(raspuns,"logare reusita")!=NULL)
    login_OK=1;
  else printf("\ntry again");
  }
  if(strstr(type,"user"))
  printf("\n Type one of this commands\n\n      comands\n      view songs\n      view top\n      add top\n      vote\n      add comment\n      view comm\n      play\n      quit\n");
  else
    printf("\n Type one of this commands\n\n      comands\n      view user\n      view songs\n      view top\n      add top\n      vote\n      add comment\n      view comm\n      play\n      eliminate a song\n      restrict a user vote number\n      quit\n");
   
   char com[1000];
  sprintf(com,"\n Type one of this commands\n\n      comands\n      view user\n      view songs\n      view top\n      add top\n      vote\n      add comment\n      view comm\n      play\n      eliminate a song\n      restrict a user vote number\n      quit\n");
  
while(1)
{ 
   fgets(command,sizeof(command),stdin);
  /* trimiterea mesajului la server */
if(strstr(command,"comands"))
  printf("%s",com);
else{

  if (write (sd,command,sizeof(command)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
      if (read (sd, &raspuns,sizeof(raspuns)) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    } 



  /* afisam mesajul primit */
  printf ("%s\n",raspuns);
  
  if(strstr(raspuns,"La revedere")!=NULL)
    break;
}}
  /* inchidem conexiunea, am terminat */
  close (sd);
}