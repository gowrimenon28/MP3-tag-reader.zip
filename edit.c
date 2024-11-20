#include<stdio.h>
#include"main.h"
#include<string.h>

Status read_and_validate_edit(char *argv[], EditInfo *editInfo)
{
    if (argv[3] != NULL)
    {
	strcpy(editInfo -> new_name,argv[3]);


    }
    if (strstr(argv[4], ".") != NULL)
    {
	if (strcmp(strstr(argv[4], "."), ".mp3") == 0)
	{
	    editInfo -> edit_mp3_fname = argv[4];
	}
	else
	{
	    printf("ERROR: not a .mp3 file");
	    return failure;
	}

    }
    else
    {
	printf("ERROR: Please pass %s file with extension\n", argv[4]);
	return failure;
    }
    return success;



}



Status edit_operation(char *argv[], EditInfo *editInfo)
{
    if (open_file_edit(editInfo)==success)
    {
	if (check_ID3_edit(editInfo -> fptr_edit_file) == success)
	{
	    if (check_version_edit(editInfo -> fptr_edit_file) == success)
	    {
		if (doing_edit(argv,editInfo->fptr_edit_file) == success)
		{
		    return success;
		}
	    }
	    else
	    {
		printf("ERROR: Not correct version\n");
	    }

	}
	else
	{
	    printf("ERROR: Not ID3 version\n");

	}


    }
    else
    {
	printf("ERROR: Opening Files Failed\n");
    }

}



Status open_file_edit(EditInfo *editInfo)
{
    editInfo->fptr_edit_file = fopen(editInfo->edit_mp3_fname, "r+");
    return success;
}


Status check_ID3_edit(FILE *fptr_edit_file)
{
    char str[3];
    fseek(fptr_edit_file,0,SEEK_SET);
    fread(str,3 ,1,fptr_edit_file);
    if (strcmp(str,"ID3")==0)
    {
	return success;
    }
    else
    {
	return failure;
    }

}



Status check_version_edit(FILE *fptr_edit_file)
{
    char version[2];
    fread(version,2,1,fptr_edit_file);
    if (version[0] == 0x03 && version[1] == 0x00)
    {
	return success;
    }
    else
    {
	return failure;
    }


}


Status doing_edit(char *argv[], FILE *fptr_edit_file)
{
    int size;
    char tag[5];
    fseek(fptr_edit_file,0,SEEK_SET);
    fseek(fptr_edit_file,10,SEEK_SET);
    for (int i=0; i<6; i++)
    {
	fread(tag,4,1,fptr_edit_file);
	size = read_size(&fptr_edit_file,4) - 1;
	fseek(fptr_edit_file,3,SEEK_CUR);
	if (strcmp(tag,"TIT2")==0)
	{
	    if (strcmp(argv[2],"-t") == 0)
	    {
		printf("------------------------------------SELECTED EDIT DETAILS-------------------------------------\n\n");
		printf("---------------------------SELECTED EDIT OPTION----------------------------------\n\n");
		printf("-------------------  CHANGE THE TITLE  --------------------------\n\n");
		printf("TITLE    : %s\n\n\n",argv[3]);
		edit_file(argv,&fptr_edit_file,size);
		printf("--------------- THE ALBUM CHANGED SUCCESSFULLY ----------------\n\n");
		return success;
	    }
	    else
	    {
		fseek(fptr_edit_file, size, SEEK_CUR);
	    }
	}

	else if (strcmp(tag,"TPE1") == 0)
	{
	    if (strcmp(argv[2],"-a") == 0)
	    {
		printf("------------------------------------SELECTED EDIT DETAILS-------------------------------------\n\n");
		printf("---------------------------SELECTED EDIT OPTION----------------------------------\n\n");
		printf("-------------------  CHANGE THE ARTIST --------------------------\n\n");
		printf("ARTIST   : %s\n\n", argv[3]);
		edit_file(argv,&fptr_edit_file, size);
		printf("--------------- THE ARTIST CHANGED SUCCESSFULLY ----------------\n\n");
		return success;

	    }
	    else
	    {
		fseek(fptr_edit_file, size, SEEK_CUR);

	    }

	}

	else if (strcmp(tag,"TALB") == 0)
	{
	    if (strcmp(argv[2],"-A") == 0)
	    {
		printf("------------------------------------SELECTED EDIT DETAILS-------------------------------------\n\n");
		printf("---------------------------SELECTED EDIT OPTION----------------------------------\n\n");
		printf("-------------------  CHANGE THE ALBUM  --------------------------\n\n");
		printf("ALBUM    : %s\n\n",argv[3]);
		edit_file(argv,&fptr_edit_file, size);		
		printf("--------------- THE ALBUM CHANGED SUCCESSFULLY ----------------\n\n");
		return success;
	    }
	    else
	    {

		fseek(fptr_edit_file, size, SEEK_CUR);
	    }

	}

	else if (strcmp(tag,"TYER") == 0)
	{
	    if (strcmp(argv[2],"-y")== 0)
	    {
		printf("------------------------------------SELECTED EDIT DETAILS-------------------------------------\n\n");
		printf("---------------------------SELECTED EDIT OPTION----------------------------------\n\n");
		printf("-------------------  CHANGE THE YEAR   --------------------------\n\n");
		printf("YEAR     : %s\n\n",argv[3]);
		edit_file(argv,&fptr_edit_file ,size);
		printf("--------------- THE YEAR CHANGED SUCCESSFULLY ----------------\n\n");
		return success;

	    }
	    else
	    {

		fseek(fptr_edit_file, size, SEEK_CUR);
	    }
	}

	else if (strcmp(tag,"TCON") == 0)
	{
	    if (strcmp(argv[2],"-m") == 0)
	    {
		printf("------------------------------------SELECTED EDIT DETAILS-------------------------------------\n\n");
		printf("---------------------------SELECTED EDIT OPTION----------------------------------\n\n");
		printf("-------------------  CHANGE THE MUSIC  --------------------------\n\n");
		printf("MUSIC    : %s\n\n",argv[3]);
		edit_file(argv,&fptr_edit_file,size);
		printf("--------------- THE MUSIC CHANGED SUCCESSFULLY ----------------\n\n");
		return success;

	    }
	    else
	    {

		fseek(fptr_edit_file, size, SEEK_CUR);
	    }
	}

	else if (strcmp(tag,"COMM") == 0)
	{
	    printf("%s\n",tag);
	    if (strcmp(argv[2],"-c") == 0)
	    {
		printf("------------------------------------SELECTED EDIT DETAILS-------------------------------------\n\n");
		printf("---------------------------SELECTED EDIT OPTION----------------------------------\n\n");
		printf("-------------------  CHANGE THE COMMENT -------------------------\n\n");
		printf("COMMENT  : %s\n\n",argv[3]);
		edit_file(argv,&fptr_edit_file, size);
		printf("--------------- THE COMMENT CHANGED SUCCESSFULLY ----------------\n\n");
		return success;
	    }
	    else
	    {

		fseek(fptr_edit_file, size, SEEK_CUR);
	    }
	}
    }

}


void edit_file(char *argv[], FILE **fptr_edit_file, int size)
{
    int len = strlen(argv[2]);
    if (size > len)
    {
	fwrite(argv[3], size, 1, *fptr_edit_file);
    }
    else
    {
	fwrite(argv[3], len+1, 1, *fptr_edit_file);
    }

}

