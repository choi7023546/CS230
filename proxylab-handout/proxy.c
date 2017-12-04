#include <stdio.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

pthread_rwlock_t lock;

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
//static const char *connection_hdr = "Connection : close\r\n";
//static const char *proxy_connection_hdr = "Proxy-Connection: close";

/* accept connection
 * read request
 * parse commmand line
 * forward request to server
 * get reponse
 * forward to client
 */
int parse_uri(char *uri, char *host, char *path, int *port);


void close_wrapper(int fd) {
    if (close(fd) < 0)
        printf("Error closing file.\n");
}

/*
return -1 if there is an error. Otherwise, return 0.
*/
int parse_uri( char *uri, char *host, char *path, int *port ) {
    char *host_begin;
    char *host_end;
    char *path_begin;
    int l=0;

    if( strncasecmp(uri,"http://",7) < 0 ) {
        host[0] = '\0';
        return -1;
    }
    host_begin = uri+7;
    host_end = uri+7;
    while( *host_end != ':' || *host_end != '/' ){
        l++;
        host_end++;
    }
    strncpy(host,host_begin,l);
    host[l] = '\0';
    if( *host_end == ':' ) {
        *port = atoi(host_end+1); 
    } else {
        *port = 80;
    }
    
    path_begin = strchr(host_begin,'/');
    if(path_begin == NULL) {
        path[0] = '\0';
    } else {
        path_begin++;
        strcpy(path,path_begin);
    }   
    return 0;
}


void *handle_connection() {
    
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE], host[MAXLINE], path[MAXLINE];
    //readline and write on buffer
    //sscanf(buf,"%s %s %s",method,uri,version); // ignore method and version 
    //
        
}

int main(int argc, char *argv[])
{
    int listenfd, *connfdp;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    
    // ignore sigpipes
    signal(SIGPIPE, SIG_IGN);

    // initialize reader/writer lock for cache
    pthread_rwlock_init(&lock, NULL);

    // establish client port (default: 29094)
    if (!argv[1]){
        printf("Missing command line port number\n");
        return -1;
    }

    // establish listening file
    listenfd = open_listenfd(argv[1]);
    clientlen = sizeof(clientaddr);

    if (listenfd < 0)
        printf("open_listenfd failed.\n");
    else {
        while (1) {
            // when a client connects, spawn a new thread to handle it.
            connfdp = Malloc(sizeof(int));
            *connfdp = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            if (connfdp < 0) {
                printf("Accept failed.\n");
                Free(connfdp);
            }
            else {
                // do something
                /*
                read all requests
                parse
                validity check
                establish connection to web server, deliver requests
                read response from server
                forward it to client
                */
                Getnameinfo(client)
            }
        }
    }
    close_wrapper(listenfd);
    pthread_rwlock_destroy(&lock);
    return 0;
}
