#include "csapp.cpp"
#include "stdio.h"

int main(int argc, char **argv)
{
	int clientfd, port;
	char *host, *image;
	rio_t rio;
    FILE *fp;
	if (argc != 4) {
		fprintf(stderr, "usage: %s <host> <port> <image>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = atoi(argv[2]);
    image= argv[3];
	fp = fopen(image,"rb");
	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
    printf("Size of the File chosen is %u", size);
	Rio_writen(clientfd, &size, sizeof(size));
	fseek(fp, 0, SEEK_SET);
	
	while(1)
	{
        /* First read file in chunks of 256 bytes */
        //printf("%d\n",size );
        unsigned char buff[256];

        //fseek(fp, 0, SEEK_SET);

        int nread = fread(buff,1,256,fp);
        printf("File read :%d bytes\n", nread);

        /* If read was successful, send data. */
        if(nread > 0)
        {
            Rio_writen(clientfd, buff, nread);
            printf("Sending %d\n",nread);
        }

        /*
         * There is something tricky going on with read 
         * Either there was error, or we reached end of file.
         */
        if (nread < (256))
        {
            if (feof(fp))
                printf("End of file\n");
            if (ferror(fp))
                printf("Error reading\n");
            break;
        }

    }
    fclose(fp);



int bytesReceived = 0;
char recvBuff[256];
char processed_image[20];
sprintf(processed_image,"GrayImage.jpg");

FILE *fp1;
fp1 = fopen(processed_image,"wb");

fseek(fp, 0, SEEK_SET);
int recData = 256;

/* Receive data in chunks of 256 bytes until size data is received*/
    while(((bytesReceived = Rio_readnb(&rio,recvBuff,recData))>0) && size>0)
    {
        fwrite(recvBuff, 1,bytesReceived,fp1);
        // printf("%s \n", recvBuff);
        size -= bytesReceived;
        //printf("remaining bytes :%d\n",size);
        if (size<256)	//if remaining bytes is less than 256, read only remaining bytes of data
        	recData = size;
    }

    fclose(fp1);
    printf("File Received Successfully\n");

}
