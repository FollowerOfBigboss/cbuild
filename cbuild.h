#include <stdio.h>
#include <stdlib.h>



typedef struct str{ char* p; int lenght; } string;

typedef struct files{ int count; string* strarr; } files;

enum{
 EXECUTABLE,
 STATIC_LIBRARY,
 DYNAMIC_LIBRARY
};

typedef struct target {
  char* name;
  int type;
  files* flist;
  char* output;

  int keepobjs;
  char* objdir;

} target;

#define createtarget(targetname, type, flist, output) \
	target targetname={#targetname, type, flist, output, 0, NULL};

#define createtarget_wobjs(targetname, type, flist, output, objdir) \
	target targetname={#targetname, type, flist, output, 1, objdir};

#define cso(str) {str, strlen(str)}
#define createlist(strarr) (files){sizeof(strarr)/sizeof(strarr[0]), strarr}

#define DEFAULT_C_COMPILER "gcc"
#define DEFAULT_CPP_COMPILER "g++"

void compile_object(string* object, char* outputfolder);
void compile_target(target* tg);
void link_target(target* tg);

void compile_target(target* tg){
 switch(tg->type){

  case EXECUTABLE:
  {
    int i;
    for(i=0;i<tg->flist->count; i++) {
     if(tg->keepobjs==1){
	     compile_object(&tg->flist->strarr[i], tg->objdir);
     }
     else{
	     compile_object(&tg->flist->strarr[i], NULL);
     }

    }
    link_target(tg); 
    break;
  }
 
  case STATIC_LIBRARY:
  {
    break;
  }

  case DYNAMIC_LIBRARY:
  {
    break;
  }
 }
	
}

void compile_object(string* object, char* outputfolder)
{
  char dbuff[50];
  if(outputfolder==NULL){ 
   sprintf(dbuff,"%s -c %s -o %s.o", DEFAULT_C_COMPILER, object->p, object->p);
  }
  else{ 
   sprintf(dbuff,"%s -c %s -o %s/%s.o", DEFAULT_C_COMPILER, object->p, outputfolder, object->p);
  }
  printf("%s\n", dbuff);
  system(dbuff);
}

void link_target(target* tg)
{
    char mergebuf[1024] = {0};
    char obj[50];

    strcat(mergebuf, "gcc ");
    int i;
    for(i=0;i<tg->flist->count; i++) {
     if (tg->keepobjs == 1){
       sprintf(obj, "%s/%s.o ", tg->objdir, tg->flist->strarr[i].p);
     }
     else{
       sprintf(obj, "%s.o ", tg->flist->strarr[i].p);
     }

     strcat(mergebuf, obj);
    }

    if (tg->output == NULL) {
     sprintf(obj, "-o %s", tg->name);
    }
    else{
     sprintf(obj, "-o %s", tg->output);
    }
    strcat(mergebuf, obj);
    system(mergebuf);


    if (tg->keepobjs==0){
     for(i=0;i<tg->flist->count; i++) {
        sprintf(obj, "%s.o", tg->flist->strarr[i].p);
	int r = remove(obj);
	//printf("remove %s\n", obj);
       // printf("ret val %i\n", r);
     }
    }
}
