#define WIDTH 80
#define HEIGHT 25

static short xx=0;
static short yy=0;

unsigned int strlen(char *str){
    unsigned int len=0;
    while(str[len]){
        len++;
    }
    return len;
}

void vga_init(){
    short *buffer=(short *)0xB8000;
    for(short i=0;i<=80*25*2;i++){
        buffer[i]=0x4020;
    }
}
void term_put(char *str){
    short *buffer=(short *)0xB8000;
    for(char i=0;i<=strlen(str);i++){
        if(str[i]=='\n'|| xx==WIDTH){
            yy++;
            xx=0;
        }else{
            if(str[i]!='\0'){
                buffer[yy*WIDTH+xx]=str[i]|0x40<<8;
            }
            xx++;
        }
    }
}