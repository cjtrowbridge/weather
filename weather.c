#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

//http://api.wunderground.com/api/1655f919bbcd29ed/conditions/q/ZIPCODE.json

const int PORT = 80;
const char HOST[] = "api.wunderground.com";
const char PATH[] = "";

int main(int argc, char **argv)
{
    struct sockaddr_in sa;
    int sockfd;
    
    //printf("Starting...\n");
    if(argc < 2)
    {
        fprintf(stderr,"Usage: %s zipcode\n",argv[0]);
        fprintf(stderr,"Example: %s 95603 /\n",argv[0]);
        exit(1);
    }
    
    //printf("\nLooking Up IP Address of %s\n",HOST);
    struct hostent *he = gethostbyname(HOST);
    
    //List all the IPs we found and count them
    int found = 0;
    struct in_addr **addr_list;
    addr_list = (struct in_addr **) he->h_addr_list;
    for(int i = 0; he->h_addr_list[i] != NULL; i++)
    {
        //printf("%2d: %s\n", i, inet_ntoa(*addr_list[i]) );
        found++;
    }
    //printf("Found %d IPs for %s. Using %s\n\n",found, HOST, inet_ntoa(*addr_list[0]));
    
    struct in_addr *ip = (struct in_addr *)he->h_addr_list[0];
    
    //printf("Creating stucture\n");
    sa.sin_family = AF_INET;
    sa.sin_port   = htons(PORT);
    sa.sin_addr   = *((struct in_addr *)ip);
    
    //printf("Creating Socket\n");
    sockfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd == -1)
    {
        fprintf(stderr,"Can't create socket\n");
        exit(3);
    }
    
    //printf("Connecting...");
    int res = connect(sockfd, (struct sockaddr *)&sa,sizeof(sa));
    if(res == -1)
    {
        fprintf(stderr, "Can't connect\n");
        exit(2);
    }
    //printf("Connected!\n");
    
    //Make the sockfd into a FILE *
    FILE *sock = fdopen(sockfd, "r+");
    
    //Now we can use fprintf, fgets, fscanf, etc to interact with the server.
    //printf("Sending GET\n");
    //fprintf(sock, "GET %s HTTP/1.0\n",PATH);
    fprintf(sock, "GET /api/1655f919bbcd29ed/conditions/q/%s.json HTTP/1.0\n", argv[1]);
    fprintf(sock, "HOST: %s\n",HOST);
    fprintf(sock,"\n");
    
    //printf("Receiving response\n");
    char buf[1000];
    int count = 0;
    
    char observation_time[100]  = "Not Found";
    char full[100]              = "Not Found";
    float temp_f                = 0;
    char relative_humidity[100] = "Not Found";
    float wind_mph              = 0;
    char wind_dir[100]          = "Not Found";
    
    
    //printf("======================================\n");
    //printf("Relevant Lines From Response:\n");
    //printf("======================================\n");
    
    while((fgets(buf,1000,sock)) != NULL)
    {
    
        if(
            (strstr(buf, "\"observation_time\"") != NULL) ||
            (strstr(buf, "full")                 != NULL) ||
            (strstr(buf, "temp_f")               != NULL) ||
            (strstr(buf, "relative_humidity")    != NULL) ||
            (strstr(buf, "wind_mph")             != NULL) ||
            (strstr(buf, "wind_dir")             != NULL)
        )
        {
            //printf("%3d: %s",count,buf);
        }
        
        sscanf(buf, " \"observation_time\": \"%[^\"]\" , ", observation_time);
        sscanf(buf, " \"full\": \"%[^\"]\" , ",             full);
        sscanf(buf, " \"temp_f\":%f , ",                    &temp_f);
        sscanf(buf, " \"relative_humidity\":\"%[^\"]\" , ", relative_humidity);
        sscanf(buf, " \"wind_mph\":%f , ",                  &wind_mph);
        sscanf(buf, " \"wind_dir\":\"%[^\"]\" , ",          wind_dir);
        
        count++;
        
    }
    
    
    printf("\n======================================\n");
    printf("Weather\n");
    printf("======================================\n");
    
    printf("Observation time:         %s\n",    observation_time);
    printf("City and State:           %s\n",    full);
    printf("Current temperature (F):  %f\n",    temp_f);
    printf("Relative humidity:        %s\n",    relative_humidity);
    printf("Wind speed and direction: %f %s\n", wind_mph, wind_dir);
    
    printf("\n");
    
    fclose(sock);
    close(sockfd);
    
}