#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char*argv[]){
    char hexFormat[][9]={"%02x ","%04x ","%08x ","%016lx ","%016llx "};
    char decimalFormat[][9]={"%d ","%d ","%d ","%ld ","%lld "};
    char (*format)[9];
    char str[100000]="This is a c-string of length 31";
    int intArray[100000]={1,2,3,4,5,6,7,8};
    double doubleArray[100000]={1.1,2.2,3.3,4.4};
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
            else format = hexFormat;

            if(argc == 2) break;

            if(*argv[2]=='i') start=(char*)intArray;
            else if (*argv[2]=='f') start=(char*)doubleArray;
            
            if(argc == 3) break;

            if(*argv[2]=='i'){
                int i;
                for(i=0 ; i+3<argc ; i++){
                    intArray[i] = atoi(argv[i+3]);
                }
                length = (argc-3)*4;
            }
            else if(*argv[2]=='f'){
                int i;
                for(i=0 ; i+3<argc ; i++){
                    doubleArray[i] = atof(argv[i+3]);
                }
                length = (argc-3)*8;
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
            }
    }

    /*
    void pointer to store a generic address without a data type
    this can be compared with other pointer types without casting
    */
    const void*end = start+length;

    printf("printing as a string\n%s\n",start);

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
        if(sizeof(long long)<<1 == sizeof(__int128_t))
            printf("%016llx%016llx ",
                *(((long long*)_128p)+1),
                *((long long*)_128p)
                );
        else
            printf("%016llx ",*_128p);
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
