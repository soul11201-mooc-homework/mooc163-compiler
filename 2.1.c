#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG  1

#ifndef DEBUG
#define DEBUG   0
#endif


typedef enum {
    IF,
    LPAREN,
    INT,
    ID,
}tokn_kind_t;
//
// const token_kind_str_map = {
//     'if',
//     '(',
// };


typedef enum {
    STATE_START,
    STATE_I,
    STATE_IF, //end-s
    // STATE_IN,

    STATE_LPAREN,
    STATE_NUM, //end-s
    STATE_DEFAULT,//end-s
}fa_state_t;



typedef struct {
    tokn_kind_t k;
    char *  lexeme;
}token;


typedef  struct {
    int start;
    int end;
}str_p_t;


/**
 *
 *return 区间左闭右开 [)
 */
str_p_t get_nex_str(char * s,int b)
{
    char t;

    while(1)
    {
        t = s[b];
        if((t < '0' ||  t > '9') && (t < 'a' || t > 'z')&&(t < 'A'||t > 'Z'))
        {
            ++b;
        }else{
            break;
        }

    }

    str_p_t temp_pos = {b,0};

    while(1)
    {
        t = s[b];
        if((t < '0' ||  t > '9') && (t < 'a' || t > 'z')&&(t < 'A'||t > 'Z'))
        {
            break;
        }else{
            ++b;
        }

    }

    // t =
    temp_pos.end = b;

    return temp_pos;
    // switch (s[b]) {
    //     case ' ':
    //     case '\t':
    //     case '\r':
    //     case '\n':
    // }
}


int c_str_cmp(const char * a,int start,int end,const char * b)
{
    int strlen_b = strlen(b);

    int i = start , j = 0;

    for( ; (i < end && j < strlen_b); ++i, ++j)
    {
        if(a[i] < b[j])
        {
            return  -1;
        }
        else if ( a[i] > b[j] )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(i ==  end) return -1;
    if(j == strlen_b) return 1;

}


int dfa(char * str, int state )
{
    // if(DEBUG) printf("read input char ascii int: %d\n",str[0]);
    // if(str == "\0" || str == "")
    if(str[0] == '\0')
    {
        return state;
    }

    switch (state)
    {
        case  STATE_START:
            {
                if(str[0] == 'i')
                {
                    return dfa(str + 1, STATE_I);
                }
                else if(str[0] == '(')
                {
                    return dfa(str + 1,STATE_LPAREN);
                }
                else if(str[0 ] >= '0' && str[0] <= '9')
                {
                    return dfa(str + 1, STATE_NUM);
                }
            }
            break;
        case STATE_I:
            {
                if(str[0] == 'f')
                {
                    return dfa(str + 1, STATE_IF);
                }

                // else if(str[0)
                // {

                // }
                else
                {
                    return STATE_DEFAULT;
                }

            }
            break;
        case STATE_IF:
            {
                //not if key word
                return STATE_DEFAULT;
            }
            break;
        case STATE_LPAREN:
            {

            }
            break;

        case STATE_NUM:
            {
                if(str[0 ] >= '0' && str[0] <= '9')
                {
                    return dfa(str + 1, STATE_NUM);
                }
                else
                {
                    return STATE_DEFAULT;
                }
            }
            break;

        default:
            {
                return STATE_DEFAULT;
            }
            break;
    }
    // for (size_t i = 0; i < temp_pos.end - temp_pos.start; i++)
    // {
        // char * c = str[0];
        // if( == 'i')
        // {
        //
        //
        // }
        // else if( == )
    // }

}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("example.l", "r");
    const  int str_stream_len = 2048;

    //read a string
    char temp[2050];

    // fscanf(fp,"%s\n",temp);
    // scanf();
    // printf("%s\n",temp);

    int row  = 1;

    while(fgets(temp,2048, fp) != NULL )
    {
        /* code */

        // printf("%s!!!!!!!!!!!!,%d\n", temp,strlen(temp));

        str_p_t temp_pos = {0,0};
        int _temp_len = strlen(temp);
        // printf("%d\n",_temp_len);
        while (temp_pos.end < _temp_len)
        {

            temp_pos = get_nex_str(temp,temp_pos.end);

            // if(DEBUG) printf("%d--%d\n",temp_pos.start,temp_pos.end);

            temp[temp_pos.end] = '\0';

            char * _str = temp + temp_pos.start;
            // if(DEBUG){

            // }

            // #if DEBUG
            // for (size_t i = 0; i <= temp_pos.end-temp_pos.start; i++) {
            //     /* code */
            //     printf("%d\n",_str[i]);
            // }
            // #endif
            fa_state_t state = dfa(_str, STATE_START);

            switch (state) {
                case STATE_DEFAULT:
                    printf("ID(%s)(%d,%d)\n",_str,row,temp_pos.start);
                    break;
                case STATE_IF:
                    printf("IF    (%d,%d)\n",row,temp_pos.start);
                    break;
                case STATE_NUM:
                    printf("NUM(%s)(%d,%d)\n",_str,row,temp_pos.start);
                    break;
            }
        }

        ++ row;
    }

    // pause();
    // pause
    // while (1) {
    //
    // }

    return 0;
}
