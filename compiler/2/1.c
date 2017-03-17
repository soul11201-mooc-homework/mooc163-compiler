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
    NUM,
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
void * generate_token_type(Token * t);

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
		case LPAREN:{
			return "LPAREN";
		}
		case NUM:{
			return "NUM";
		}
		case ID:{
			return "ID";
		}
		default:
			return '\0';
	}
}

void Token_add(const char * str,int len,int row,int vol)
{

	
	token_list[token_num].row = row;
	token_list[token_num].vol = vol;
	token_list[token_num].len = len;

	token_list[token_num].str_val = (char * )malloc(len + 1);
	strncpy(token_list[token_num].str_val,str,len);
	token_list[token_num].str_val[len] = '\0';
	
	generate_token_type(&token_list[token_num]);
	Token_print(&token_list[token_num]);

	token_num ++;
}

void Token_print(Token * t)
{

	printf(" %s \t@len:%d pos:(%d,%d) hashcode: %d TokenKind: %s\n", 
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

		Token_add(str + vol , offset - vol , row, vol + 1);
	}

	printf("----------------------generate_token end---------------------------------------\n\n\n\n");
}




void * generate_token_type(Token * t)
{
	t->kind = ID;

	char * s = t->str_val;
	if(strcmp(s, "if") == 0)
	{
		t->kind = IF;
	}else{
		int i = 0;
		while(isdigit(s[i++]));
		if(i -1  == t->len)
		{
			t->kind = NUM;
		}
	}
}

void Token_traval()
{

	for (int i = 0; i < token_num; ++i)
	{
		Token_print(&token_list[i]);
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

    Token_traval();
    return 0;
}
