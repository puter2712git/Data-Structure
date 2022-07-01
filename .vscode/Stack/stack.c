#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _CRT_SECURE_NO_WARNINGS

typedef unsigned char bool;
#define true 1
#define false 0

#define MAX_COMMAND_SIZE 100
#define MAX_TOKEN_SIZE 64

#define MAX_STACK_SIZE 100

typedef int element;
element stack[MAX_STACK_SIZE] = { 0 };
int top = -1;

static inline bool strmatch(char * const str, const char *expect) {
	return (strlen(str) == strlen(expect)) && (strncmp(str, expect, strlen(expect)) == 0);
}

bool is_full() {
	return (top == MAX_STACK_SIZE);
}

bool is_empty() {
	return (top == -1);
}

void push(element data) {
	if (is_full()) {
		printf("[ERROR]: Stack is full!!\n\n");
	}
	else {
		stack[++top] = data;
		printf("Successfully pushed.\n\n");
	}

	return;
}

int pop() {
	if (is_empty()) {
		printf("[ERROR]: Stack is empty!!\n\n");
	}
	else {
		printf("Successfully popped.\n\n");
		return stack[top--];
	}
}

void show() {
	for (int i = 0; i < top + 1; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n\n");

	return;
}

static void __stack_simulator(int nr_tokens, char *tokens[]) {
	if (strmatch(tokens[0], "push")) {
		if (nr_tokens != 2) {
			printf("\n");
			printf("How to use: push [integer value]\n\n");
		}
		else {
			push(strtol(tokens[1], NULL, 0));
		}
	}
	else if (strmatch(tokens[0], "pop")) {
		if (nr_tokens != 1) {
			printf("\n");
			printf("How to use: pop\n\n");
		}
		else {
			pop();
		}
	}
	else if (strmatch(tokens[0], "show")) {
		if (nr_tokens != 1) {
			printf("\n");
			printf("How to use: show\n\n");
		}
		else {
			show();
		}
	}
	else {
		printf("Valid commands:\n");
		printf("- push\n");
		printf("- pop\n");
		printf("- show\n\n");
	}

	return;
}

static void __parse_command(char *command, int *nr_tokens, char *tokens[]) {
	char *curr = command;
	bool token_started = false;
	*nr_tokens = 0;

	while (*curr != '\0') {
		if (isspace(*curr)) {
			*curr = '\0';
			token_started = false;
		}
		else {
			if (!token_started) {
				tokens[*nr_tokens] = curr;
				*nr_tokens += 1;
				token_started = true;
			}
		}
		curr++;
	}

	return;
}

int main() {
	char command[MAX_COMMAND_SIZE] = { '\0' };

	while (true) {
		if (strmatch(command, "exit")) {
			return 0;
		}

		int nr_tokens = 0;
		char *tokens[MAX_TOKEN_SIZE] = { NULL };

		printf(">> ");
		fgets(command, sizeof(command), stdin);

		__parse_command(command, &nr_tokens, tokens);
		__stack_simulator(nr_tokens, tokens);
	}
}