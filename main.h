#include"type.h"

#ifndef MAIN_H
#define MAIN_H


typedef struct _editInfo
{
    char *edit_mp3_fname;
    FILE *fptr_edit_file;
    char new_name[50];
} EditInfo;


typedef struct _MP3Info
{
    char *src_mp3_fname;  
    FILE *fptr_src_file;

} MP3Info;


typedef struct _viewInfo
{
    char title[50];
    char artist_name[50];
    char album[50];
    char year[20];
    char content_type[50];
    char composer[50];
} ViewInfo;


//function prototypes

OperationType check_operation_type(char *argv[]);

Status read_and_validate(char *argv[], MP3Info *mp3Info);

Status view_operation(MP3Info *mp3Info);

Status open_file(MP3Info *mp3Info);

Status check_ID3(FILE *fptr_src_file);

Status check_version(FILE *fptr_src_file);

Status view_doing(FILE *fptr_src_file);

int read_size(FILE **fptr_src_image,int count);

Status read_and_validate_edit(char *argv[], EditInfo *editInfo);

Status edit_operation(char *argv[],EditInfo *editInfo);

Status open_file_edit(EditInfo *editInfo);

Status check_ID3_edit(FILE *fptr_edit_file);

Status check_version_edit(FILE *fptr_edit_file);

Status doing_edit(char *argv[], FILE *fptr_edit_file);

void edit_file(char *argv[], FILE **fptr_edit_file, int size);









#endif
