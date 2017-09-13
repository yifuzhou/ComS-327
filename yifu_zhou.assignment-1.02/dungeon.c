#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"
#include "string.h"
#include "stdint.h"

char Array[21][80];
char l_Array[21][80];
unsigned char Hardness[19][78];
unsigned char l_Hardness[19][78];
unsigned char roomData[10][4];
int b[10];
int a[10];
int num_r;
int g=0;
char *dest;
uint32_t version;
uint32_t filesize;
void setdungeon();
void savedungeon();
void loaddungeon();
int setRoom();
void setCorridor(int);
void createRoom();
void showdungeon();
void setHardness();



void setdungeon()
{
    for (int i =0; i<21; i++) {
        for (int j =0; j<80; j++) {
            Array[i][j] = ' ';
            
        }
        
    }
    int num = setRoom();
    
    setCorridor(num);
    setHardness();
    
    
}
void showdungeon()
{
    setdungeon();
    for (int i =0; i<21; i++) {
        for (int j =0; j<80; j++) {
            printf("%c", Array[i][j]);
            
        }
        printf("\n");
    }
}

int setRoom()
{
    
    for (int n =0; n<num_r; n++) {
        createRoom(n);
        
    }
    return num_r;
}
void createRoom(int n)
{
    
    int room_x = rand()%7+4;
    int room_y = rand()%10+5;
    roomData[n][2] = room_y-2;
    roomData[n][3] =room_x-2;
    
    
    int set = 0;
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    
    do
    {
        set = 0;
        i = rand()%17+2;
        j = rand()%76+2;
        for (x =i; x<i+room_x; x++) {
            for (y =j; y<j+room_y; y++) {
                if (Array[x][y] =='.'||x>=18 ||y>=77) {
                    set++;
                }
            }
        }
    }
    while (set!=0);
    
    int _x;
    int _y;
    
    _x = (rand()%2==1)?i+1:i+room_x-2;
    _y = (rand()%2==1)?j+1:j+room_y-2;
    
    int x_rand = rand()%(room_x-3);
    int y_rand = rand()%(room_y-3);
    int z = (rand()%2 ==1)?1:2;
    switch (z) {
        case 1:
            if (_x == i+1) {
                _x = _x+x_rand;
            }
            else _x = _x-x_rand;
            break;
            
        case 2:
            if (_y == j+1) {
                _y = _y+y_rand;
            }
            else _y = _y-y_rand;
            break;
    }
    roomData[n][0] = j+1;
    roomData[n][1] = i+1;
    
    for (x =i+1; x<i+room_x-1; x++) {
        for (y =j+1; y<j+room_y-1; y++) {
            Array[x][y] = '.';
            
        }
    }
    
    if (Array[_x-1][_y]==' ') {
        b[g] =_x-1;
        a[g] = _y;
        g++;
        
        
    }
    else if (Array[_x+1][_y]==' ') {
        b[g] = _x+1;
        a[g] = _y;
        g++;
        
    }
    else if (Array[_x][_y-1]==' ') {
        b[g] = _x;
        a[g] = _y-1;
        g++;
        
    }
    else if (Array[_x][_y+1]==' ') {
        b[g] = _x;
        a[g] = _y+1;
        g++;
        
    }
    
    
}

void setCorridor(int num_r)
{
    int z = 0;
    
    for (int i =0; i<21; i++) {
        for (int j =0; j<80; j++) {
            if (Array[i][j]=='#') {
                b[z] = i;
                a[z] = j;
                printf("%d,%d\n", b[z],a[z]);
                z++;
            }
        }
    }
    for (int n =1; n<num_r; n++)
    {
        Array[b[n]][a[n]] ='#';
        Array[b[n-1]][a[n-1]] ='#';
        
        while (b[n]!=b[n-1]||a[n]!=a[n-1])
        {
            if (b[n]==b[n-1]&&a[n]>a[n-1])
            {
                a[n]--;
                if (Array[b[n]][a[n]]==' ')
                {
                    Array[b[n]][a[n]] = '#';
                    
                }
                else if (Array[b[n]][a[n]]=='.')
                {
                    a[n]++;
                    b[n]++;
                    Array[b[n]][a[n]]='#';
                    
                    while (Array[b[n]][a[n]-1]=='.') {
                        b[n]++;
                        Array[b[n]][a[n]]='#';
                        
                    }
                    a[n]--;
                    Array[b[n]][a[n]]='#';
                }
                else break;
            }
            
            else if (b[n]==b[n-1]&&a[n]<a[n-1])
            {
                a[n]++;
                if (Array[b[n]][a[n]]==' ')
                {
                    Array[b[n]][a[n]] = '#';
                    
                }
                else if (Array[b[n]][a[n]]=='.')
                {
                    a[n]--;
                    b[n]++;
                    Array[b[n]][a[n]]='#';
                    
                    while (Array[b[n]][a[n]+1]=='.') {
                        b[n]++;
                        Array[b[n]][a[n]]='#';
                        
                    }
                    a[n]++;
                    Array[b[n]][a[n]]='#';
                    
                    
                }
                
                else break;
            }
            
            else if (b[n]>b[n-1]&&a[n]==a[n-1])
            {
                b[n]--;
                if (Array[b[n]][a[n]]==' ')
                {
                    Array[b[n]][a[n]] = '#';
                    
                }
                else if (Array[b[n]][a[n]]=='.')
                {
                    b[n]++;
                    a[n]++;
                    Array[b[n]][a[n]]='#';
                    
                    while (Array[b[n]-1][a[n]]=='.') {
                        a[n]++;
                        Array[b[n]][a[n]]='#';
                        
                    }
                    b[n]--;
                    Array[b[n]][a[n]]='#';
                    
                    
                }
                
                
                else break;
            }
            
            else if (b[n]<b[n-1]&&a[n]==a[n-1])
            {
                b[n]++;
                if (Array[b[n]][a[n]]==' ')
                {
                    Array[b[n]][a[n]] = '#';
                    
                }
                else if (Array[b[n]][a[n]]=='.')
                {
                    b[n]--;
                    a[n]++;
                    Array[b[n]][a[n]]='#';
                    
                    while (Array[b[n]+1][a[n]]=='.') {
                        a[n]++;
                        Array[b[n]][a[n]]='#';
                        
                    }
                    b[n]++;
                    Array[b[n]][a[n]]='#';
                    
                    
                }
                
                else break;
            }
            
            else if (b[n]>b[n-1]&&a[n]>a[n-1])
            {
                if (rand()%2==1)
                {
                    b[n]--;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        b[n]++;
                        a[n]--;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]-1][a[n]]=='.') {
                            a[n]--;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                    
                }
                else
                {a[n]--;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        a[n]++;
                        b[n]--;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]][a[n]-1]=='.') {
                            b[n]--;
                            Array[b[n]][a[n]]='#';
                            
                        }
                        
                    }
                    else break;
                }
            }
            
            
            else if (b[n]>b[n-1]&&a[n]<a[n-1])
            {
                if (rand()%2==1)
                {
                    b[n]--;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        b[n]++;
                        a[n]++;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]-1][a[n]]=='.') {
                            a[n]++;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                    
                }
                else
                {a[n]++;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        a[n]--;
                        b[n]--;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]][a[n]+1]=='.') {
                            b[n]--;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                }
                
            }
            else if (b[n]<b[n-1]&&a[n]<a[n-1])
            {
                if (rand()%2==1)
                {
                    b[n]++;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        b[n]--;
                        a[n]++;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]+1][a[n]]=='.') {
                            a[n]++;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                    
                }
                else
                {a[n]++;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        a[n]--;
                        b[n]++;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]][a[n]+1]=='.') {
                            b[n]++;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                }
                
            }
            
            else if (b[n]<b[n-1]&&a[n]>a[n-1])
            {
                if (rand()%2==1)
                {
                    b[n]++;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        b[n]--;
                        a[n]--;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]+1][a[n]]=='.') {
                            a[n]--;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                    
                }
                else
                {a[n]--;
                    if (Array[b[n]][a[n]]==' ')
                    {
                        Array[b[n]][a[n]] = '#';
                        
                    }
                    else if (Array[b[n]][a[n]]=='.')
                    {
                        a[n]++;
                        b[n]++;
                        Array[b[n]][a[n]]='#';
                        
                        while (Array[b[n]][a[n]-1]=='.') {
                            b[n]++;
                            Array[b[n]][a[n]]='#';
                            
                        }
                    }
                    else break;
                }
            }
        }
    }
    
}

void setHardness()
{
    for (int i =1; i<=19; i++) {
        for (int j = 1; j<=78; j++) {
            if (Array[i][j]!=' ') {
                Hardness[i-1][j-1] =0;
            }
            else Hardness[i-1][j-1] = rand()%254+1;
        }
    }
    
    
}

void savedungeon()
{
    filesize = 1495;
    filesize = filesize +num_r*4;
    
       
    FILE * file_streamw = fopen(dest, "wb");
    if (file_streamw==NULL) {
        printf("Can not open files bu write");
        exit(1);
    }
    
    unsigned long num_wf = fwrite("RLG327", 6, 1, file_streamw);
    if (num_wf==0) {
        printf("Nothing to save");
        exit(1);
    }
    version = 0;
    version = htobe32(version);
    fwrite(&version,4,1,file_streamw);
    filesize = htobe32(filesize);
    fwrite(&filesize, 4, 1, file_streamw);
    for(int i =0;i<19;i++){
        for (int j = 0; j<78; j++) {
            fwrite(&Hardness[i][j], sizeof(unsigned char), 1, file_streamw);
         
        }
    }
    
    for (int p =0; p<num_r; p++) {
        for (int q = 0; q<4; q++) {
            fwrite((&roomData[p][q]), sizeof(unsigned char), 1, file_streamw);
            
        }
    }
    
    fclose(file_streamw);
}

void loaddungeon()
{
    char title[6];
       
    
    FILE * file_streamr = fopen(dest, "rb");
    if (file_streamr==NULL) {
        printf("Can not open files by read");
        exit(1);
    }
    unsigned long num_rf = fread(title, sizeof(char), 6, file_streamr);
    if (num_rf==0) {
        printf("Nothing to load");
        exit(1);
    }
    fread(&version, sizeof(uint32_t), 1, file_streamr);
    version = be32toh(version);
   fread(&filesize, sizeof(uint32_t), 1, file_streamr);
    filesize = be32toh(filesize);


    
    for (int p =0; p<19; p++) {
        for (int q = 0; q<78; q++) {
            fread(&Hardness[p][q], sizeof(unsigned char), 1, file_streamr);
      
  }
    }
    int l_roomNum = (filesize-1495)/4;
    // unsigned char l_roomData[l_roomNum][4];
    for (int m=0; m<l_roomNum; m++) {
        for (int n =0; n<4; n++) {
            fread(&roomData[m][n], sizeof(unsigned char), 1, file_streamr);

        }
    }
    
    memset(l_Array, ' ', sizeof(l_Array));
    
    for (int n =0; n<l_roomNum; n++) {
        for (int y =roomData[n][1]; y<roomData[n][1]+roomData[n][3]; y++) {
            for (int x= roomData[n][0]; x<roomData[n][0]+roomData[n][2]; x++) {
                l_Array[y][x] = '.';
            }
        }
    }
    for (int f=1; f<20; f++) {
        for (int g=1; g<79; g++) {
            if (l_Array[f][g]!='.'&&Hardness[f-1][g-1]==0) {
                l_Array[f][g] = '#';
                
            }
        }
    }
    for (int w=0; w<21; w++) {
        for (int e =0; e<80; e++) {
            printf("%c",l_Array[w][e]);
        }
        printf("\n");
    }
    
    
    fclose(file_streamr);
    
}

int main(int argc, const char * argv[]) {
    
    memset(roomData, 0, sizeof(roomData));
    srand(time(NULL));
    num_r = abs(rand()%4+5);
    dest = getenv("HOME");
    dest = strcat(dest,"/.rlg327/2783095331.rlg327");

    if (argc>3) {
        printf("Please Print Correctly\n");
        printf("Print --save OR --load OR both of them");
    }
    
    else if(argc==3){
        if (strcmp(argv[1],"--save")==0&&strcmp(argv[2], "--load")==0) {
            loaddungeon();
		savedungeon();

        }
        else if (strcmp(argv[1], "--load")==0&&strcmp(argv[2],"--save")==0){
            loaddungeon();
    		savedungeon();
        }
        else
        {
            printf("Please Print Correctly\n");
            printf("Print --save OR --load OR both of them");
            
        }
    }
    
    else if (argc==2) {
        if (strcmp(argv[1],"--save")==0) {
            setdungeon();
            savedungeon();
        }
        else if(strcmp(argv[1], "--load")==0) {
            loaddungeon();
        }
        else
        {   printf("Please Print Correctly\n");
            printf("Print --save OR --load OR both of them");
        }
    }
    else if(argc==1){
        showdungeon();

    }
    
    
    
    
    return 0;
}
