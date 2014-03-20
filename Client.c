#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SERVER PORT 12345 /* arbitrary, but client & server must agree */
#define BUF SIZE 4096 /* block transfer size */
int main(int argc, char**argv)
{
int c, s, bytes;
char buf[BUF SIZE]; /* buffer for incoming file */
struct hostent*h; /* info about server*/
struct sockaddr in channel; /* holds IP address */
if (argc != 3) fatal("Usage: client server-name file-name");
h = gethostbyname(argv[1]); /*look up host’s IP address */
if (!h) fatal("gethostbyname failed");
s = socket(PF INET, SOCK STREAM, IPPROTO TCP);
if (s <0) fatal("socket");
memset(&channel, 0, sizeof(channel));
channel.sin family= AF INET;
memcpy(&channel.sin addr.s addr, h->h addr, h->h length);
channel.sin port= htons(SERVER PORT);
c = connect(s, (struct sockaddr*) &channel, sizeof(channel));
if (c < 0) fatal("connect failed");

write(s, argv[2], strlen(argv[2])+1);

while (1) {
bytes = read(s, buf, BUF SIZE); /*read from socket*/
if (bytes <= 0) exit(0); /* check for end of file */
write(1, buf, bytes); /* write to standard output*/
}
}
fatal(char*string)
{
printf("%s\n", string);
exit(1);
}
