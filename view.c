#include<stdio.h>
#include"main.h"
#include"type.h"
#include<string.h>


Status read_and_validate(char *argv[], MP3Info *mp3Info)
{
    if (strstr(argv[2], ".") != NULL)
    {
	if (strcmp(strstr(argv[2], "."), ".mp3") == 0)
	{
	    mp3Info -> src_mp3_fname = argv[2];
	}
	else
	{
	    return failure;
	}
    }
    else
    {
	printf("ERROR: Please pass %s file with extension\n", argv[2]);
	return failure;
    }
    return success;



}



Status view_operation(MP3Info *mp3Info)
{
    if (open_file(mp3Info) == success)
    {
	if (check_ID3(mp3Info -> fptr_src_file) == success)
	{
	    if (check_version(mp3Info -> fptr_src_file) == success)
	    {
		if (view_doing(mp3Info -> fptr_src_file)== success)
		{
		    return success;
		}
	    }
	    else
	    {
		printf("ERROR: Not required version\n");
		return failure;
	    }

	}
	else
	{
	    printf("ERROR: Not ID3 file\n");
	    return failure;
	}
    }
    else
    {
	printf("ERROR: Opening Files Failure\n");
	return failure;
    }
}




Status open_file(MP3Info *mp3Info)
{
    mp3Info->fptr_src_file = fopen(mp3Info->src_mp3_fname, "r");
    return success;
}



Status check_ID3(FILE *fptr_src_file)
{
    char str[3];
    fseek(fptr_src_file,0,SEEK_SET);
    fread(str,3 ,1,fptr_src_file);
    if (strcmp(str,"ID3")==0)
    {
	return success;
    }
    else
    {
	return failure;
    }	

}



Status check_version(FILE *fptr_src_file)
{
    char version[2];
    fread(version,2,1,fptr_src_file);
    if (version[0] == 0x03 && version[1] == 0x00)
    {
	return success;
    }
    else
    {
	return failure;
    }


}



Status view_doing(FILE *fptr_src_file)
{
    ViewInfo viewInfo;
    int size;
    char tag[5];
    fseek(fptr_src_file,0,SEEK_SET);
    fseek(fptr_src_file,10,SEEK_SET);     //skip header
    for (int i=0; i<6; i++)
    {
	fread(tag,4 ,1,fptr_src_file);
	if (strcmp(tag,"TIT2") == 0)
	{
	    size = read_size(&fptr_src_file,4) - 1;
	    fseek(fptr_src_file,3,SEEK_CUR);  
	    fread(viewInfo.title,size,1,fptr_src_file);
	    viewInfo.title[size]= '\0';
	}

	else if (strcmp(tag,"TPE1") == 0)
	{
	    size = read_size(&fptr_src_file,4) - 1;
	    fseek(fptr_src_file,3,SEEK_CUR);  
	    fread(viewInfo.artist_name,size,1,fptr_src_file);
	    viewInfo.artist_name[size]= '\0';
	}
	
	else if (strcmp(tag,"TALB") == 0)
	{
	    size = read_size(&fptr_src_file,4) - 1;
	    fseek(fptr_src_file,3,SEEK_CUR);  
	    fread(viewInfo.album,size,1,fptr_src_file);
	    viewInfo.album[size]= '\0';
	}

	else if (strcmp(tag,"TYER") == 0)
	{
	    size = read_size(&fptr_src_file,4) - 1;
	    fseek(fptr_src_file,3,SEEK_CUR);  
	    fread(viewInfo.year,size,1,fptr_src_file);
	    viewInfo.year[size]= '\0';
	}

	else if (strcmp(tag,"TCON") == 0)
	{
	    size = read_size(&fptr_src_file,4) - 1;
	    fseek(fptr_src_file,3,SEEK_CUR);  
	    fread(viewInfo.content_type,size,1,fptr_src_file);
	    viewInfo.content_type[size]= '\0';
	}

	else if (strcmp(tag,"COMM") == 0)
	{
	    size = read_size(&fptr_src_file,4) - 1;
	    fseek(fptr_src_file,3,SEEK_CUR);  
	    fread(viewInfo.composer,size,1,fptr_src_file);
	    viewInfo.composer[size]= '\0';
	}



    }
    printf("-------------------------------SELECTED VIEW DETAILS---------------------------\n\n\n");
    printf("-----------------------------------------------------------------------\n");
    printf("\t\t\tMP3 TAG READER AND EDITOR FOR ID3v2\t\t\t\n");
    printf("-----------------------------------------------------------------------\n");
    printf("TITLE\t\t :\t%s\n",viewInfo.title);
    printf("ARTIST\t\t :\t%s\n",viewInfo.artist_name);
    printf("ALBUM\t\t :\t%s\n",viewInfo.album);
    printf("YEAR\t\t :\t%s\n",viewInfo.year);
    printf("MUSIC\t\t :\t%s\n",viewInfo.content_type);
    printf("COMMENT\t\t :\t%s\n",viewInfo.composer);

    return success;
}



int read_size(FILE **fptr_src_image,int count)
{
    int size = 0;
    char ch;
    for(int i = count-1;i>=0;i--)
    {
	fread(&ch,1,1,*fptr_src_image);
	size = size | (ch << i*8);
    }
    return size;

}
