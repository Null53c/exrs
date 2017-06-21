#include<stdio.h>
#include<string.h>
#include <stdlib.h>

char* str_master = "this_aint_that_simple_but_good_luck_haha";
char* str_garbage  = "this_is_not_even_interesting_its_garbage";

// in realta' servono solo i primi 41
const unsigned char obj_delta[41] = {
  0x03, 0xfd, 0x03, 0xf9, 0x00, 0x03, 0x06, 0x00, 0xf1, 0x00,
  0xfa, 0x07, 0x16, 0xeb, 0x08, 0xfc, 0xf6, 0x02, 0xfe, 0xf3,
  0x04, 0x13, 0x01, 0xea, 0xed, 0x0f, 0xfd, 0xf0, 0xf2, 0x0f,
  0x0c, 0xf3, 0xf1, 0x0c, 0x07, 0x00, 0x05, 0x0e, 0x0a, 0x04,
  0x00 
};

// in realta' non necessarie, nel binario usa le var originali
char* result;
unsigned char* nu;


int check_password(char* arg) 
{
    int contatore;
    char local_18;
    int ran;
    int  modulo;
    unsigned char da_sottrarre;
    unsigned char delta;


    if (strlen(arg) != strlen(str_garbage)) {
        return 1;
    }
   
    local_18 = 1;
    contatore = 0;
    char ch;
    int c = 0;

    //strcpy(str_garbage, arg);

   do { 

        local_18 = 0;
        contatore = 0;       

        while ( contatore < 40)
        {
            if (nu[contatore] == '\x00')
            {
               ++contatore;
               continue;
            }

            // calcolo il valore da sottrarre
            delta = nu[contatore];

            da_sottrarre = rand() % delta+ 1;
            
            delta = delta - da_sottrarre;
            
            local_18 = local_18 | delta;

            nu[contatore] = delta ;
            arg[contatore] = arg[contatore] - da_sottrarre;
            
            ++contatore;

        }
        
    } while(local_18 != 0);
    
    return strcmp(str_master, arg);
}


int main(int argc, char* argv[])
{
    if ( !(argc > 1) ) 
    {
        printf("Usage: %s password\nMaybe plaintext isn't good after all.\n", argv[0]);
        return 1;   
    }

    // usiamo due variabili inutili (dummy per essere chic)
    // che sostituiscono il delta e la nostra pass
    // per non incorrere in misteriosi problemi di scrittura 
    result = (unsigned char*)malloc(sizeof(char) * 40);
    nu = (unsigned char*)malloc(sizeof(char) * 40);
    // inizializziamoe
    int i;
    for( i = 0; i < 41; ++ i)   result[i] = argv[1][i];
    for( i = 0; i < 41; ++ i)   nu[i] = obj_delta[i];
    
    if( check_password(result))
    {
        printf("password KO\n");
        return 1;
    }
   
    printf("password OK\n");
    return 0;
}


//      !!! SPOILER !!!     //

void soluzione()
{
      
    int contatore;
    char local_18;
    int ran;
    int  modulo;
    unsigned char local_19h;
    unsigned char delta;

    unsigned char* dic = (unsigned char*)malloc(sizeof(char)*40);
    for(contatore = 0; contatore <= 40; ++contatore)
    {
        dic[contatore] = 0;
    }
    char ch;
    int c = 0;

    local_18 = 1;
    contatore = 0;
        
    do {
        local_18 = 0;
        contatore = 0;       

        while ( contatore < 40)
        {
            if (nu[contatore] == '\x00')
            {
               ++contatore;
               continue;
            }

            ran = rand();
            delta = nu[contatore];

            modulo = ran % delta ;
            local_19h = modulo + 1;

            dic[contatore] = dic[contatore] + local_19h;
            delta = delta  - local_19h;
            nu[contatore] = delta ;
            
            local_18 = local_18 | delta;
            
            ++contatore;
        }
        
        ++c;
        
   } while( local_18 != 0 ) ;

    int i;
    for( i = 0; i < 40; ++ i)   ;   //printf("%#2x",dic[i]);  
    printf("\n[*] Password calcolata: ");
    for( i = 0; i < 40; ++ i)   printf("%c",str_master[i] + dic[i]);
    printf("\n");

}


