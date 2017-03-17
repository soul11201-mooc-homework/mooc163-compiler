#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFF_SIZE 4096

FILE * fp;


typedef enum {
	UNKNOWN,
    IF,
    LPAREN,
    INTEGER,
    ID,
}TokenKind;

typedef struct {
	TokenKind kind;
	int row;
	int vol;
	int len;
	char * str_val;
}Token;

Token token_list[1000];
int token_num = 0;

char t[1024];

// int isspace(int c)
// {
// 	return c == '\t' || c == '\r'  || c == '\n' || c == '\v';
// }

int hash(const char * s)
{
	int len = strlen(s)	;
	int val = 0;
	for(int i =  0; i < len; ++i)
	{
		val += s[i] *10 % 9002;
	}
	return val;
}

void Token_print(Token * t);

const char *  TokenKind_2_str(TokenKind k)
{
	switch(k)
	{
		case UNKNOWN:{
			return "UNKNOWN";
		}
		case IF:{
			return "IF";
		}
		case     LPAREN:{
			return "LPAREN";
		}
		case     INTEGER:{
			return "INTEGER";
		}
		case     ID:{
			return "ID";
		}
		default:
			return '\0';
	}
}

void Token_add(const char * str,int len,int row,int vol,TokenKind kind)
{

	token_list[token_num].kind = kind;
	token_list[token_num].row = row;
	token_list[token_num].vol = vol;
	token_list[token_num].len = len;

	token_list[token_num].str_val = (char * )malloc(len + 1);
	strncpy(token_list[token_num].str_val,str,len);
	token_list[token_num].str_val[len] = '\0';
	
	
	Token_print(&token_list[token_num]);
	// printf("add token ================>>:\t %s \t@len:%d pos:(%d,%d) hashcode:%d\n", 
	// 	token_list[token_num].str_val,
	// 	len,
	// 	row,
	// 	vol,
	// 	hash(token_list[token_num].str_val)
	// );

	token_num ++;
}

void Token_print(Token * t)
{

	printf("add token ================>>:\t %s \t@len:%d pos:(%d,%d) hashcode: %d TokenKind: %s\n", 
		t->str_val,
		t->len,
		t->row,
		t->vol,
		hash(t->str_val),
		TokenKind_2_str(t->kind)
	);
}


void * generate_token(const char * str,int row)
{
	int offset = 0;
	int vol = 0;
	int line_len = strlen(str);
	printf("----------------------generate_token begin---------------------------------------\n");
	while(offset < line_len)
	{
		if(isspace(str[offset]))
		{
			offset ++;
			continue;
		}

		vol = offset;

		while(offset < line_len && !isspace(str[offset]))
		{
			++ offset;
		}

		Token_add(str + vol , offset - vol , row, vol + 1,UNKNOWN);
	}

	printf("----------------------generate_token end---------------------------------------\n\n\n\n");
}




void * generate_token_type()
{
	char * t;
	for (int i = 0; i < token_num; ++i)
	{
		if (token_list[i].kind != UNKNOWN)
		{
			continue;
		}

		t = token_list[i].str_val;
		if (strncmp(t,"if",2))
		{
			token_list[i].kind = IF;
		}
		Token_print(&token_list[i]);
		// else
	}
}



int main(int argc, char const *argv[]) {
    char temp[BUFF_SIZE];
    fp = fopen("example.l", "r");
    int i  = 1;
    
    while(fgets(temp,BUFF_SIZE,fp))
    {
    	
    	// printf("read file line:%d [%s]\n", i,temp); fgets 会读入文件的换行符
    	printf("read file line:%d ========>> \t %s", i,temp);
    	generate_token(temp,i);
    	++i;
    }

    generate_token_type();

    return 0;
}
