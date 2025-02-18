#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char*argv[]){
    char hexFormat[][9]={"%02x ","%04x ","%08x ","%016lx ","%016llx ","%016llx"};
    char decimalFormat[][9]={"%d ","%d ","%d ","%ld ","%lld "};
    char (*format)[9]=hexFormat;
    char str[100000]="This is a c-string of length 31";
    int intArray[100000]={1,2,3,4,5,6,7,8}, intArraySize = 8;
    double doubleArray[100000]={1.1,2.2,3.3,4.4}, doubleArraySize = 4;
    int length = strlen(str)+1;
    void *start = str;
    switch(argc){
        case 0:
            printf("what did you even do to call this program with no arguments :skull:\n");
            return 1;
        case 1:
            printf("proper usage: %s FORMAT [TYPE] [DATA]\n",*argv);
            printf("FORMAT: d for decimal, h or x for hexadecimal\n");
            printf("TYPE: datatype to use for the original array, c for char, i for int, f for double");
            printf("DATA: everything after the TYPE gets treated as DATA. Must be valid integers if TYPE is i");
            return 1;

        default:
            if(*argv[1]=='d') format = decimalFormat;
            else {
                char number[3]="2";

                strcpy(format[0],"%0");
                sprintf(number,"%lu",sizeof(char)*2);
                strcat(format[0],number);
                strcat(format[0],"x ");
                
                strcpy(format[1],"%0");
                sprintf(number,"%lu",sizeof(short)*2);
                strcat(format[1],number);
                strcat(format[1],"x ");
                
                strcpy(format[2],"%0");
                sprintf(number,"%lu",sizeof(int)*2);
                strcat(format[2],number);
                strcat(format[2],"x ");
                
                strcpy(format[3],"%0");
                sprintf(number,"%lu",sizeof(long)*2);
                strcat(format[3],number);
                strcat(format[3],"lx ");
                
                strcpy(format[4],"%0");
                sprintf(number,"%lu",sizeof(long long)*2);
                strcat(format[4],number);
                strcat(format[4],"llx ");

                strcpy(format[5],"%0");
                sprintf(number,"%lu",sizeof(long long)*2);
                strcat(format[5],number);
                strcat(format[5],"llx");
            }

            if(argc == 2) break;

            if(*argv[2]=='i') {
                start=(char*)intArray;
                length=intArraySize*sizeof(int);
            }
            else if (*argv[2]=='f') {
                start=(char*)doubleArray;
                length=doubleArraySize*sizeof(double);
            }
            else{
                length*=sizeof(char);
            }
            
            if(argc == 3) break;

            if(*argv[2]=='i'){
                int i;
                for(i=0 ; i+3<argc ; i++){
                    intArray[i] = atoi(argv[i+3]);
                }
                length = (argc-3)*sizeof(int);
            }
            else if(*argv[2]=='f'){
                int i;
                for(i=0 ; i+3<argc ; i++){
                    doubleArray[i] = atof(argv[i+3]);
                }
                length = (argc-3)*sizeof(double);
            }
            else{
                int i;
                strcpy(str,argv[3]);
                for(i=4; i<argc ; i++){
                    int curlen = strlen(str);
                    str[curlen]=32;
                    str[curlen+1]=0;
                    strcat(str,argv[i]);
                }
                length = strlen(str);
                length *= sizeof(char);
            }
    }

    /*
    void pointer to store a generic address without a data type
    this can be compared with other pointer types without casting
    */
    const void*end = (void*)((unsigned long)start+length);

    printf("printing as a string\n%s\n",(char*)start);

    #if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L)) || defined(__cplusplus)
    
    /* bool doesn't exist in older versions, so this has to be skipped */
    printf("printing as a bool array, size %lu\n",sizeof(bool));
    bool*bp;
    for(bp=(bool*)start;bp<end;bp++)
        printf(*bp?"true ":"false ");
    printf("\n");
    #else
    printf("skipping bool, version too old\n");
    #endif

    char*cp;
    printf("printing as a char array, size %lu\n",sizeof(char));
    for(cp=(char*)start;cp<end;cp++)
        printf(format[0],*cp);
    printf("\n");

    printf("printing as a short array, size %lu\n",sizeof(short));
    short*sp;
    for(sp=(short*)start;sp<end;sp++)
        printf(format[1],*sp);
    printf("\n");

    int*ip;
    printf("printing as an int array, size %lu\n",sizeof(int));
    for(ip=(int*)start;ip<end;ip++)
        printf(format[2],*ip);
    printf("\n");
    
    long*lp;
    printf("printing as a long array, size %lu\n",sizeof(long));
    for(lp=(long*)start;lp<end;lp++)
        printf(format[3],*lp);
    printf("\n");
    
    long long *llp;
    printf("printing as a long long array, size %lu\n",sizeof(long long));
    for(llp=(long long *)start;llp<end;llp++)
        printf(format[4],*llp);
    printf("\n");
    
    #ifdef __SIZEOF_INT128__
    __int128_t * _128p;
    printf("printing as a 128-bit integer array, size %lu\n",sizeof(__int128_t));
    for(_128p=(__int128_t*)start;_128p<end;_128p++){
        int i=(sizeof(__int128_t)/sizeof(long long));
        while(i--)
            printf(format[5],*(((long long*)_128p)+i));
        printf(" ");
    }
    printf("\n");
    #endif
    
    float*fp;
    printf("printing as a float array, size %lu\n",sizeof(float));
    for(fp=(float*)start;fp<end;fp++)
        printf("%f ",*fp);
    printf("\n");

    double*dp;
    printf("printing as a double array, size %lu\n",sizeof(double));
    for(dp=(double*)start;dp<end;dp++)
        printf("%lf ",*dp);
    printf("\n");
    
    long double *ldp;
    printf("printing as a long double array, size %lu\n",sizeof(long double));
    for(ldp=(long double*)start;ldp<end;ldp++)
        printf("%Lf ",*ldp);
    printf("\n");

    return 0;
}
