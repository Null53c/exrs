#include<stdio.h>
#include<string.h>

const char key[22] = {
  0x10, 0x1d, 0x0d, 0x16, 0x00, 0x14, 0x06, 0x12,
  0x37, 0x1f, 0x36, 0x0e, 0x09, 0x3a, 0x16, 0x3a,
  0x05, 0x15, 0x2b, 0x02, 0x03, 0x00
};

const char related[22] = "this_might_be_related";

int check_password(char* mia_pass)
{
    int length;
    unsigned char check_xor = 0;

    length = strlen(mia_pass);

    if(length != 21)
    {
        return 1;
    }

    int cur_pos = 0;
    int temp_pos;

    while( cur_pos < length)
    {
        unsigned char temp_xor = 0;
        temp_pos = cur_pos;
            
        // per due volte piú il contatore cur_pos attuale
        // passa la nostra stringa e la xora con temp_xor
        
        while(length + length + cur_pos >= temp_pos) {

            // 0x400607
            int modulo = temp_pos % length;
            temp_xor = mia_pass[modulo] ^ temp_xor;
            ++temp_pos;
        }
        
        // aggiorna la variabile con cui fare lo xor e
        // riporta temp_pos alla posizione corrente

        // 0x40063a
        temp_xor = key[cur_pos] ^ temp_xor;
        temp_pos = cur_pos;

        // ripete la stessa identica operazione ma con il nuovo  xor
        
        while( length + length + cur_pos >= temp_pos) {
            // 0x400657
            // la parte prima dello xor dev'essere castata a char
            temp_xor = *((temp_pos % length) + mia_pass) ^ temp_xor;
            ++temp_pos;
        }

        // infine ripete il procedimento usando la seconda chiave
        
        temp_xor = related[cur_pos] ^ temp_xor;
        temp_pos = cur_pos;
        
        while(length + length + cur_pos >=temp_pos)
        {
            // 0x4006a7
            // castato a char
            temp_xor = (mia_pass[temp_pos % length]) ^ temp_xor;
            ++ temp_pos;
        }

        // tiene traccia della variabile di xor perché alla fine deve
        // essere 0

        check_xor = check_xor + temp_xor;
        ++cur_pos;
    }

    printf("Final xor:\t%#010x\n",check_xor);

    return check_xor;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Usage: %s password\nIs strcmp really that bad? I'll roll my own.", argv[0]);
        return 1;
    }

    if ( 0 == check_password(argv[1]) )
    {
        printf("password OK");
    }
    else
    {
        printf("password KO");
    }

    return 0;
}


//  !! SPOILER!!    //

void solution() {
    
    int c;

    for(c = 0; c < 22; ++c) {
        printf("%c",key[c] ^ related[c]);
        // dude_you_killed_it_gg
    }
}
