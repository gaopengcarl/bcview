/*************************************************************************
  > File Name: bcview.c
  > Author: gaopeng
  > Mail: gaopp_200217@163.com 
  > Created Time: Thu 17 Mar 2016 08:52:51 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sz(FILE *opf)
{
	unsigned long int ed;
	fseek(opf,0,SEEK_END);
	ed=ftell(opf);
	return ed;
}


int check(char *argv)
{
	unsigned int len,i=0;
	len=strlen(argv);
	while(len--)
	{
		if(argv[i] >='0' && argv[i]<='9' )
		{
			continue;
		}
		else
		{
			return -1;
			break;
		}
		i += 1;
	}
	return 1;
}


int main(int argc,char *argv[])
{

	unsigned long int fsize,bnu=0,ctell;
	FILE *fd;
	unsigned long int blksz,ofst,cbt,bcon;
	unsigned char c;
	
	printf("******************************************************************\n");
	printf("This Tool Is Uesed For Find The Data In Binary format(Hexadecimal)\n");
	printf("Usage:./bcview file blocksize offset cnt-bytes!                   \n");
	printf("file: Is Your File Will To Find Data!                             \n");
	printf("blocksize: Is N kb Block.Eg: 8 Is 8 Kb Blocksize(Oracle)!         \n");
	printf("                         Eg: 16 Is 16 Kb Blocksize(Innodb)!       \n");
	printf("offset:Is Every Block Offset Your Want Start!					  \n");
	printf("cnt-bytes:Is After Offset,How Bytes Your Want Gets!				  \n");
	printf("Edtor QQ:22389860!                                                \n");
	printf("Used gcc version 4.1.2 20080704 (Red Hat 4.1.2-46)                \n");
	printf("******************************************************************\n");



	
	if(argc<5)
	{
		printf("usage:./bcview file blocksize offset cnt-bytes!\n");
		exit(5);
	}
	
	if((fd=fopen(argv[1],"rb"))==NULL)
	{
		perror("FILEOPEN ERROR:");
		exit(1);
	}
	if(check(argv[2]) == -1 )
	{
		printf("please input  blcoksize is a int!\n");
		exit(2);
	}
	else
	{
		sscanf(argv[2],"%ld",&blksz);
		if (blksz < 1 )
		{
			printf("please input blocksize >= 1!\n");
			exit(6);
		}
	}
	if(check(argv[3]) == -1 )
	{
		printf("please input  offset is a int!\n");
		exit(3);
	}
	else
	{
		sscanf(argv[3],"%ld",&ofst);
	}
	
	if(check(argv[4]) == -1 )
	{
		printf("please input  cnt-bytes is a int!\n");
		exit(4);
	}
	else
	{
		sscanf(argv[4],"%ld",&cbt);
		if (cbt < 1 )
		{
			printf("please input  cnt-bytes >= 1!\n");
			exit(7);
		}
	}
    bcon = cbt;	

	fsize = sz(fd);
	ctell=fseek(fd,blksz*1024*bnu+ofst,SEEK_SET);
	printf("----Current file size is :%lf Mb\n",fsize/1024.0/1024.0);
	printf("----Current use set blockszie is %ld Kb\n",blksz);
	
	while(ctell<fsize)
	{
		//fseek(fd,0,1);
		bcon = cbt;
		printf("current block:%08ld--Offset:%05ld--cnt bytes:%02ld--data is:",bnu,ofst,bcon);
		while(bcon--)
		{
			c = fgetc(fd);
			printf("%02x",c);
		}
		printf("\n");
		bnu += 1;
		fseek(fd,blksz*1024*bnu+ofst,SEEK_SET);
		ctell=ftell(fd);
	}
	fclose(fd);
	return 0;

}
