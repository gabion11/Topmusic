
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

/* portul folosit */
#define PORT 2024

sqlite3* db;
/* codul de eroare returnat de anumite apeluri */
extern int errno;

static int callback (void *str, int argc, char **argv, char **azColName)
{
    int i;
    char* data = (char*) str;

    for (i = 0; i < argc; i++)
    {
        strcat (data, azColName[i]);
        strcat (data, " = ");
        if (argv[i])
            strcat (data, argv[i]);
        else
            strcat (data, "NULL");
        strcat (data, "\n");
    }

    strcat (data, "\n");
    return 0;
}



void clientt(int client)
{
   /* s-a realizat conexiunea, se astepta mesajul */
      char newaccount[]="user register";
      char login[]="user login",loginn[]="admin login";
      char command[100];
      char username[20];
      char password[20];
      char raspuns[1000]="logare reusita";
      char loginFAIL[]="login fail";
      char wrongCommand[]="wrong command";
      char songName[30];
      char addTop[]="add top ";
      char viewTop[]="view top";
      char voteSong[]="vote";
      char user[]="user";
      char admin[]="admin";
      char play[]="play ";
      char Quit[]="quit";
      char viewComm[]="view comm";
      char addComm[]="add comment ";
      char restrictt[]="restrict";
      char viewSongs[]="view songs";
      char viewUsers[]="view user";
      char eliminate[]="eliminate";
      printf ("[server]Asteptam mesajul...\n");
      fflush (stdout);
      
      int login_OK=0,quit=0;
      
    char* zErrMsg;
    char str[10000];
    char sql[10000];
    int rc = sqlite3_open ("storage.db", &db);  //stabilire conexiune baza date

    if (rc)                                     //verificare conexiune
    {   printf("gf");
        fprintf(stderr, "error: %s\n", sqlite3_errmsg (db));
        return 0;
    }

while(!login_OK){
      /* citirea mesajului */
 
      if (read (client, &command, sizeof(command)) <= 0)
  {
    perror ("[server]Eroare la read() de la client.\n");
    close (client); /* inchidem conexiunea cu clientul */
    /* continuam sa ascultam */
  }
  printf ("[server]Mesajul a fost receptionat...");
  
  if(strstr(command,newaccount)!=0)
      { printf("creem acontul");
       
        if (read (client, &username, sizeof(username)) <= 0)
       {
        perror ("[server]Eroare la read() de la client la citirea username-ul.\n");
        close (client); /* inchidem conexiunea cu clientul */
      
        }
      
       if (read (client, &password, sizeof(password)) <= 0)
      {
        perror ("[server]Eroare la read() de la client la citirea parolei.\n");
        close (client); /* inchidem conexiunea cu clientul */
      }
      sql[0]=0;
      str[0]=0;
      sprintf(sql,"SELECT *FROM account;");
      rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

       if (rc != SQLITE_OK)
        {
         printf("eroare la select");
         sqlite3_free (zErrMsg);
       }
       else 
        if(strstr(str,username)!=NULL)
         {
              printf("sunt aici1");
              raspuns[0]='\0';
              strcpy(raspuns,loginFAIL);
            }
          else {
           sql[0]=0;
           str[0]=0;
           sprintf(sql,"INSERT INTO account VALUES('%s','%s','%s',10);",username,password,admin);
           rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

              if (rc != SQLITE_OK)
               {
                printf("eroare la inser 1");
                sqlite3_free (zErrMsg);
               }
               else
                  { strcpy(raspuns,"logare reusita");
                    login_OK=1;

                  }
             }     
           
        
      

      if (write (client, &raspuns, sizeof(raspuns)) <= 0)
        {
          perror ("[server]Eroare la write() catre client la raspuns.\n");
    
        }       
          } 
else
     if(strstr(command,login)!=NULL)
     {
        printf("incercam sa ne logam");


        
        if (read (client, &username, sizeof(username)) <= 0)
      {
        perror ("[server]Eroare la read() de la client la citirea username-ul.\n");
        close (client); /* inchidem conexiunea cu clientul */
      
       }
      
       if (read (client, &password, sizeof(password)) <= 0)
      {
        perror ("[server]Eroare la read() de la client la citirea parolei.\n");
        close (client); /* inchidem conexiunea cu clientul */
      }
      char u[]="user";
      sql[0]=0;
      str[0]=0;
      sprintf(sql,"SELECT *FROM account;");
      rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

       if (rc != SQLITE_OK)
        {
         printf("eroare la select");
         sqlite3_free (zErrMsg);
       }
       else 
        if(strstr(str,username)!=NULL)
         {
           sql[0]=0;
           str[0]=0;
           sprintf(sql,"SELECT * FROM account where username=%s;",username);
           rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

              if (rc != SQLITE_OK)
               {
                printf("eroare la inser 1");
                sqlite3_free (zErrMsg);
               }
               else{
                  if(strstr(str,password)!=NULL&&strstr(str,u)!=NULL)
                    {
                   raspuns[0]='\0';
                    strcpy(raspuns,"logare reusita"); 
                   login_OK=1;
                    }
                  else 
                  {
                   raspuns[0]='\0';
                    strcpy(raspuns,"wrong password"); 
                  }
             } }
          else   
           {
             raspuns[0]='\0';
              strcpy(raspuns,"wrong username");
            }    
           
        
      

      if (write (client, &raspuns, sizeof(raspuns)) <= 0)
        {
          perror ("[server]Eroare la write() catre client la raspuns.\n");
    
        }       
          } 
          else
     if(strstr(command,loginn)!=NULL)
     {
        printf("incercam sa ne logam");


        
        if (read (client, &username, sizeof(username)) <= 0)
      {
        perror ("[server]Eroare la read() de la client la citirea username-ul.\n");
        close (client); /* inchidem conexiunea cu clientul */
      
       }
      
       if (read (client, &password, sizeof(password)) <= 0)
      {
        perror ("[server]Eroare la read() de la client la citirea parolei.\n");
        close (client); /* inchidem conexiunea cu clientul */
      }
    
      sql[0]=0;
      str[0]=0;
      sprintf(sql,"SELECT *FROM account;");
      rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

       if (rc != SQLITE_OK)
        {
         printf("eroare la select");
         sqlite3_free (zErrMsg);
       }
       else 
        if(strstr(str,username)!=NULL)
         {
           sql[0]=0;
           str[0]=0;
           sprintf(sql,"SELECT * FROM account where username='%s';",username);
           rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

              if (rc != SQLITE_OK)
               {
                printf("eroare la inser 1");
                sqlite3_free (zErrMsg);
               }
               else
                  if(strstr(str,password)!=NULL&&strstr(str,"admin")!=NULL)
                    {
                   raspuns[0]='\0';
                    strcpy(raspuns,"logare reusita"); 
                   login_OK=1;
                    }
                  else 
                  {
                   raspuns[0]='\0';
                    strcpy(raspuns,"wrong password"); 
                  }
             } 
          else   
           {
             raspuns[0]='\0';
              strcpy(raspuns,"wrong username");
            }    
           
        
      

      if (write (client, &raspuns, sizeof(raspuns)) <= 0)
        {
          perror ("[server]Eroare la write() catre client la raspuns.\n");
    
        }       
          } 

           else if(strstr(command,Quit)!=NULL)
                     { login_OK=1;
                      raspuns[0]='\0';

                           strcpy(raspuns,"La revedere!");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           } 

                    }

  
       
     else     
                 if (write (client, &wrongCommand, sizeof(wrongCommand)) <= 0)
        {
          perror ("[server]Eroare la write() catre client la raspuns.\n");
    
        }  
      }


        while(!quit)
        {  printf ("[server]asteptam comenzi...\n");
           /* citirea mesajului */
              if (read (client, &command, sizeof(command)) <= 0)
                {
                  perror ("[server]Eroare la read() de la client.\n");
                  close (client); /* inchidem conexiunea cu clientul */
                  /* continuam sa ascultam */
 
                }  
            printf ("[server]Mesajul a fost receptionat...");
  
          if(strstr(command,addTop)!=NULL)
            {
              strcpy(songName,command+7);
             sql[0] = 0;
             str[0] = 0;

             sprintf (sql, "INSERT INTO usersTop (id, songName) VALUES ('%s', '%s');", username,songName);
             rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
              if (rc != SQLITE_OK)
                      {
                           printf("eroare la inserare");
                            sqlite3_free (zErrMsg);
                        }
                 else 
                        {  
                          
                   
                        
                           raspuns[0]='\0';
                           strcpy(raspuns,"Done");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }  
                      }   
            } // top
            else
             if(strstr(command,viewSongs)!=NULL)
            {
              
             sql[0] = 0;
             str[0] = 0;

             sprintf (sql, "SELECT nume,type FROM songs;");
             rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
              if (rc != SQLITE_OK)
                      {
                           printf("eroare la inserare");
                            sqlite3_free (zErrMsg);
                        }
                 else 
                        {  
                          
                   
                        
                           raspuns[0]='\0';
                           strcpy(raspuns,str);
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }  
                      }   
            } // top
             else if(strstr(command,viewTop)!=NULL)
                    {

                           raspuns[0]='\0';
                           strcpy(raspuns,"\n Type on of this option:\n\npersonal\nvoted\ngender\n");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }
                            if (read (client, &command, sizeof(command)) <= 0)
                           {
                             perror ("[server]Eroare la read() de la client.\n");
                             close (client); /* inchidem conexiunea cu clientul */
                  
                           }  
                           if(strstr(command,"personal")!=NULL)
                           {
                          sql[0]=0;
                          str[0]=0;
  
                          sprintf(sql,"SELECT songName FROM usersTop WHERE id='%s';",username);
                          rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                         if (rc != SQLITE_OK)
                           {
                           printf("eroare la select");
                            sqlite3_free (zErrMsg);
                           }
                         else 
                           {    
                          raspuns[0]='\0';

                           strcpy(raspuns,str);
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }  
                           }
                           }
                            else if(strstr(command,"voted")!=NULL)
                    
                            {
                            sql[0]=0;
                            str[0]=0;

                            sprintf(sql,"SELECT nume FROM songs WHERE voteCount>0 ORDER BY voteCount DESC;");
                            rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                            if (rc != SQLITE_OK)
                           {
                           printf("eroare la select");
                            sqlite3_free (zErrMsg);
                          }
                          else 
                          {    
                          raspuns[0]='\0';

                           strcpy(raspuns,str);
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }  
                         } 
                       }
                          else if(strstr(command,"gender")!=NULL)
                          {
                            raspuns[0]='\0';
                           strcpy(raspuns,"\n Type a musical gender");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }
                            if (read (client, &command, sizeof(command)) <= 0)
                           {
                             perror ("[server]Eroare la read() de la client.\n");
                             close (client); /* inchidem conexiunea cu clientul */
                  
                           } 
                           
                          char *gen;
                          gen=strtok(command," ");
                           
                           sql[0]=0;
                           str[0]=0;

                          sprintf(sql,"SELECT nume as " " FROM songs WHERE type='%s' AND voteCount>0 ORDER BY voteCount DESC;",gen);
                          rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                           if (rc != SQLITE_OK)
                          {
                           printf("eroare la select");
                            sqlite3_free (zErrMsg);
                          }
                            else 
                          {    
                          raspuns[0]='\0';
                          
                           strcpy(raspuns,str);
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }  
                          }
                        }
                  }
                    else if(strstr(command,voteSong)!=NULL)
                        {  raspuns[0]='\0';
                         strcpy(raspuns,"write the song name");

                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }
                           if (read (client, &command, sizeof(command)) <= 0)
                           {
                            perror ("[server]Eroare la read() de la client.\n");
                           close (client); /* inchidem conexiunea cu clientul */
                               /* continuam sa ascultam */
 
                             } 
                             char songname[30];
                             strcpy(songname,command);
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM songs;");
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                             else 
                              if(strstr(str,songname)!=NULL)
                          {
                             strcpy(songName,command);
                             sql[0] = 0;
                             str[0] = 0;

                            sprintf (sql, "SELECT * FROM songs;"); 
                            rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
                            
                             if (rc != SQLITE_OK)
                            {
                              printf("eroare la select 1");
                              sqlite3_free (zErrMsg);
                            }
                               else {
                               
                                  if(strstr(str,songName)!=NULL)
                                    {
  
                                         sql[0] = 0;
                                         str[0] = 0;

                                         sprintf (sql, "UPDATE songs SET voteCount= voteCount + 1 WHERE nume= %s;",songName); 
                                         rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
                            
                                          if (rc != SQLITE_OK)
                                        {
                                       printf("eroare la update 11");
                                       sqlite3_free (zErrMsg);
                                        }    
                                        else
                                        {
                                           raspuns[0]='\0';
                                           strcpy(raspuns,"Done");
                                         }
                                       }
                                       else {

                                        raspuns[0]='\0';
                                        strcpy(raspuns,"song not found");
                                       }


                                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                           {
                                            perror ("[server]Eroare la write() catre client la raspuns.\n");
          
                                            }  
                                           
                                        
                                       }
                                     }
                 }
                   

                      else if(strstr(command,addComm)!=NULL)
                      { 
                         raspuns[0]='\0';
                         strcpy(raspuns,"write the song name");

                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }
                           if (read (client, &command, sizeof(command)) <= 0)
                           {
                            perror ("[server]Eroare la read() de la client.\n");
                           close (client); /* inchidem conexiunea cu clientul */
                               /* continuam sa ascultam */
 
                             } 
                             char songname[30];
                             strcpy(songname,command);
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM songs;");
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                             else 
                              if(strstr(str,songname)!=NULL)
                             {    
                            raspuns[0]='\0';
                            strcpy(raspuns,"write the comment ");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           } 
                               if (read (client, &command, sizeof(command)) <= 0)
                           {
                                 perror ("[server]Eroare la read() de la client.\n");
                                 close (client); /* inchidem conexiunea cu clientul */
                               /* continuam sa ascultam */
 
                             } 
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"INSERT INTO comm VALUES('%s','%s','%s');",songname,username,command);
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else
                               {
                                 raspuns[0]='\0';
                                 strcpy(raspuns,"Done");
                                 if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                {
                                  perror ("[server]Eroare la write() catre client la raspuns.\n");
                                 } 
                               }
                           }
                           else  
                                {    
                          raspuns[0]='\0';

                           strcpy(raspuns,"wrong song name ");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                           perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           } 
                         }


                      }

                      else if(strstr(command,viewComm)!=NULL)
                      { 
                         raspuns[0]='\0';
                         strcpy(raspuns,"write the song name");

                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }
                           if (read (client, &command, sizeof(command)) <= 0)
                           {
                            perror ("[server]Eroare la read() de la client.\n");
                           close (client); /* inchidem conexiunea cu clientul */
                               /* continuam sa ascultam */
 
                             } 
                             char songname[30];
                             strcpy(songname,command);
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM songs;");
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                             else 
                              if(strstr(str,songname)!=NULL)
                                {    
                         
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM comm WHERE numeSong='%s';",command);
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else
                               {
                                 raspuns[0]='\0';
                                 strcpy(raspuns,str);
                                 if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                {
                                  perror ("[server]Eroare la write() catre client la raspuns.\n");
                                 } 
                               }
                           }
                           else  
                                {    
                          raspuns[0]='\0';

                           strcpy(raspuns,"wrong song name ");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                           perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           } 
                         }


                      }
                      else if(strstr(command,play)!=NULL)
                          {
                             strcpy(songName,command+5);
                             sql[0] = 0;
                             str[0] = 0;

                            sprintf (sql, "SELECT * FROM songs;"); 
                            rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
                            
                             if (rc != SQLITE_OK)
                            {
                              printf("eroare la select 1");
                              sqlite3_free (zErrMsg);
                            }
                               else {
                               
                                  if(strstr(str,songName)!=NULL)
                                    {
  
                                         sql[0] = 0;
                                         str[0] = 0;

                                         sprintf (sql, "SELECT link FROM songs WHERE nume= %s;",songName); 
                                         rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
                            
                                          if (rc != SQLITE_OK)
                                        {
                                       printf("eroare la update 11");
                                       sqlite3_free (zErrMsg);
                                        }    
                                        else
                                        {  char url[50]="firefox ";
                                           strcat(url,str);
                                           system(url);
                                           raspuns[0]='\0';
                                           strcpy(raspuns,"Done");
                                         }
                                       }
                                       else {

                                        raspuns[0]='\0';
                                        strcpy(raspuns,"song not found");
                                       }


                                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                           {
                                            perror ("[server]Eroare la write() catre client la raspuns.\n");
          
                                            }  
                                           
                                        
                                       }
                                     }
                 
                   



                      //admin
                      else if(strstr(command,restrictt)!=NULL||strstr(command,eliminate)!=NULL||strstr(command,viewUsers)!=NULL)
                         {
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM account where username='%s';",username);
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else if(strstr(str,"admin")!=NULL)
                                     
                               if(strstr(command,restrictt)!=NULL)
                             {
                               raspuns[0]='\0';
                                strcpy(raspuns,"type the username  ");
                                if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                              {
                                 perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                                 } 
                                if (read (client, &command, sizeof(command)) <= 0)
                               {
                                 perror ("[server]Eroare la read() de la client.\n");
                                 close (client); /* inchidem conexiunea cu clientul */
                          
                                }
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM account;");
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else if(strstr(str,command)!=NULL)
                                  {sql[0]=0;
                                  str[0]=0;

                             sprintf(sql,"UPDATE account SET voteCount=0 WHERE username='%s';",command);
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else
                               {
                                raspuns[0]='\0';

                                strcpy(raspuns,"Done\n");
                                if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                {
                                 perror ("[server]Eroare la write() catre client la raspuns.\n");
                                } 

                               }

                                  }
                                  else
                                  { raspuns[0]='\0';
                                    strcpy(raspuns,"wrong username\n");
                                    if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                    {
                                     perror ("[server]Eroare la write() catre client la raspuns.\n");
                                    } 
                               }

                      }
                      else  if(strstr(command,eliminate)!=NULL)
                             {
                               raspuns[0]='\0';
                                strcpy(raspuns,"type the songname ");
                                if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                              {
                                 perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                                 } 
                                if (read (client, &command, sizeof(command)) <= 0)
                               {
                                 perror ("[server]Eroare la read() de la client.\n");
                                 close (client); /* inchidem conexiunea cu clientul */
                          
                                }
                             sql[0]=0;
                             str[0]=0;

                             sprintf(sql,"SELECT * FROM songs;");
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else if(strstr(str,command)!=NULL)
                                  {sql[0]=0;
                                  str[0]=0;
                                  printf("%sl\n",command);
                                   strcpy(songName,command);
                                    printf("\n%sl\n",songName);
                             sprintf(sql,"UPDATE songs SET voteCount=0 WHERE nume=%s;",songName);
                             rc=sqlite3_exec(db,sql,callback,str,&zErrMsg);

                              if (rc != SQLITE_OK)
                               {
                                 printf("eroare la select");
                                 sqlite3_free (zErrMsg);
                               }
                               else
                               {
                                raspuns[0]='\0';

                                strcpy(raspuns,"Done\n");
                                if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                {
                                 perror ("[server]Eroare la write() catre client la raspuns.\n");
                                } 

                               }

                                  }
                                  else
                                  { raspuns[0]='\0';
                                    strcpy(raspuns,"this song did not exist\n");
                                    if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                                    {
                                     perror ("[server]Eroare la write() catre client la raspuns.\n");
                                    } 
                                   }

                      }
                    else
                     if(strstr(command,viewUsers)!=NULL)
                    {
              
                          sql[0] = 0;
                          str[0] = 0;
                          printf("\n got here");
                         sprintf (sql, "SELECT username FROM account ;");
                          rc = sqlite3_exec (db, sql, callback, str, &zErrMsg);
                         if (rc != SQLITE_OK)
                       {
                           printf("eroare la inserare");
                            sqlite3_free (zErrMsg);
                        }
                         else 
                        {  
                          
                        printf("and here");
                        
                           raspuns[0]='\0';
                           strcpy(raspuns,str);
                          
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           }  
                      }   
            } 
            } // top
                    else if(strstr(command,Quit)!=NULL)
                     { quit=1;
                      raspuns[0]='\0';

                           strcpy(raspuns,"La revedere!");
                           if (write (client, &raspuns, sizeof(raspuns)) <= 0)
                           {
                             perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                           } 

                    }
                    else     
                         if (write (client, &wrongCommand, sizeof(wrongCommand)) <= 0)
                      {
                        perror ("[server]Eroare la write() catre client la raspuns.\n");
    
                     }  
      }
      

        printf("Pa");
              close (client);
              exit(0);
    }//procesul copil


int nr=0;
int main ()
{
  struct sockaddr_in server;  // structura folosita de server
  struct sockaddr_in from;  
 
  int sd;     //descriptorul de socket 

  /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }

  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));
  
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;  
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 5) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }

  /* servim in mod iterativ clientii... */
  while (1)
    {
      int client;
      int length = sizeof (from);

      printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
      client = accept (sd, (struct sockaddr *) &from, &length);
      
      
      pid_t P=fork();
      
          if(P==0){
      /* eroare la acceptarea conexiunii de la un client */
      if (client < 0)
  {
    perror ("[server]Eroare la accept().\n");
    continue;
  }

      /* s-a realizat conexiunea, se astepta mesajul */
      
   clientt(client);
   exit(0);
    }//procesul copil
  
   }       /* while */
  
}       /* main */