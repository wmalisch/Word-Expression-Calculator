#include <stdio.h>
#include <stdlib.h>

float sub_e,a,b;
char o;
float m_exp(float sub_exp, char op);
char get_op();
float get_num();
float s_exp(void);



// Input: none, read from stdin
// Effect: get the next numeric value of the expression
// Output: return the next numeric value of the expression.
float get_num(){
	float num;
	scanf("%f",&num);
	return num;
}
// Input: none, read from stdin
// Effect: get the next operator of the expression
// 	   this operator can be +, -, *, /, or '\n'
// 	   '\n' indicates the end of the expression input
// 	   leading spaces should be skipped
// Output: return the next operator of the expression.
char get_op(){
	char operator;
	scanf("%c", &operator);
	return operator;
}
// Input: 'sub_exp': the value of the current sub m_expression
// 		     to the left of 'op' location in stdin.
//	  'op' : an operator, '*' or '/'. 'op' could also be
//	  	 '+', '-', or '\n' indictating the end of the m_expression.
//	  	 '+', '-', or '\n' should be pushed back to stdin.
//	  the rest of the m_expression will be read in from stdin
// Effect: the m_expression is evaluated using recursion:
// 	   get next_num with get_num() and then get next_op with get_op()
// 	   use 'sub_exp op next_num' and 'next_op' to do recursive call
// Output: this function returns the value of the current m_expression
float m_exp(float sub_exp, char op){
	float next_num;
	char next_operator;
	float next_sub_exp;
	if(op == '+' || op == '-'){
		ungetc(op, stdin);
		return sub_exp;
	}else if(op =='\n'){
		return sub_exp;
	}else if(op == '*' || op == '/'){
		next_num = get_num();
		next_operator = get_op();
		if(op == '*'){
			next_sub_exp = sub_exp * next_num;
			return m_exp(next_sub_exp, next_operator);
		}else if(op == '/'){
			next_sub_exp = sub_exp / next_num;
			return m_exp(next_sub_exp, next_operator);
		}
	}else if(op == ' '){
		char operator;
		operator = get_op();
		return m_exp(sub_exp, operator);

	}else{
		exit(EXIT_FAILURE);
	}
}
/// Input: none, the s_expression will be read in from stdin
// Effect: the s_expression is evaluated using
// 	   a while loop or a do while loop:
// 	   repeated get num with m_exp() and then get op with 
// 	   get_op() while op is '+' or '-'; when op '\n', exit loop.
// Output: this function returns the value of the s_expression
float s_exp(void){
	float num;
	float next;
	char operator;
	num = m_exp(1,'*');
	operator = get_op();
	while(operator == '+' || operator == '-' || operator == '*' || operator == '/' || operator == ' '){
		next = m_exp(1,'*');
		if(operator == '+'){
			num = num + next;
			operator = get_op();
		}else if(operator == '-'){
			num = num - next;
			operator = get_op();
		}else if (operator == ' '){
			operator = get_op();
		}else if(operator != '-' || operator != '+' || operator != '\n'){
			exit(EXIT_FAILURE);
			break;
		}
	}
	return num;
}

int main(){
	int repeat = 1;
	char cont;
	while(repeat == 1){
		printf("\nPlease enter an arithmatic expression: ");
		sub_e = s_exp();
		printf("%f\n", sub_e);
		printf("\nWould you like to try again: ");
		cont = get_op();
		if(cont == 'N'){
			repeat++;
		}else if(cont == 'Y'){
			continue;
		}else{	
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
