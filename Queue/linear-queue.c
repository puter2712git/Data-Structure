#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMAND_SIZE 100
#define MAX_TOKEN_SIZE 64
#define MAX_QUEUE_SIZE 100

typedef unsigned char bool;
#define true 1
#define false 0

typedef int element;

element queue[MAX_QUEUE_SIZE] = { 0 };
int rear = -1;
int front = -1;

static inline bool strmatch(char * const str, const char *expect) {
	return (strlen(str) == strlen(expect)) && (strncmp(str, expect, strlen(expect)) == 0);
}

bool is_full() {
	return rear == MAX_QUEUE_SIZE - 1;
}

bool is_empty() {
	return front == rear;
}

void add_queue(element item) {
	if (is_full()) {
		printf("[ERROR]: Queue is full!!\n\n");
	}
	else {
		queue[++rear] = item;
		printf("Successfully added.\n\n");
	}

	return;
}

element delete_queue() {
	if (is_empty()) {
		printf("[ERROR]: Queue is empty!!\n\n");
	}
	else {
		printf("Successfully deleted.\n\n");
		return queue[++front];
	}
}

void show() {
	for (int i = front; i < rear + 1; i++) {
		printf("%d ", queue[i]);
	}
	printf("\n\n");
	
	return;
}

static void __queue_simulator(int nr_tokens, char *tokens[]) {
	if (strmatch(tokens[0], "add")) {
		if (nr_tokens != 2) {
			printf("\n");
			printf("How to use: add [integer value]\n\n");
		}
		else {
			add_queue(strtol(tokens[1], NULL, 0));
		}
	}
	else if (strmatch(tokens[0], "delete")) {
		if (nr_tokens != 1) {
			printf("\n");
			printf("How to use: delete\n\n");
		}
		else {
			delete_queue();
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
		printf("- add\n");
		printf("- delete\n");
		printf("- show\n");
		printf("\n");
	}
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
		__queue_simulator(nr_tokens, tokens);
	}

	return 0;
}