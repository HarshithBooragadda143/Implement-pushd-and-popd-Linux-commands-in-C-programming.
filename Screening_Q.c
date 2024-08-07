/*
Name:Booragadda V S Harshith
Date:
Description:
Sample Execution:
Sample Output:
 */



/* Implement pushd and popd Linux commands in C Programming */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Node {
    char *directory;
    struct Node *next;
} Node;

Node *stack = NULL;

void pushd(const char *dir) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
	fprintf(stderr, "Memory allocation error\n");
	exit(1);
    }
    new_node->directory = getcwd(NULL, 0);
    if (new_node->directory == NULL) {
	perror("getcwd");
	free(new_node);
	exit(1);
    }
    new_node->next = stack;
    stack = new_node;

    if (chdir(dir) != 0) {
	perror("chdir");
	exit(1);
    }
    printf("Changed directory to %s\n", dir);
}

void popd() {
    if (stack == NULL) {
	fprintf(stderr, "Stack is empty\n");
	return;
    }

    Node *top = stack;
    stack = stack->next;

    if (chdir(top->directory) != 0) {
	perror("chdir");
	exit(1);
    }
    printf("Changed directory to %s\n", top->directory);

    free(top->directory);
    free(top);
}

void free_stack() {
    while (stack != NULL) {
	Node *temp = stack;
	stack = stack->next;
	free(temp->directory);
	free(temp);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
	fprintf(stderr, "Usage: %s <command> [<directory>]\n", argv[0]);
	return 1;
    }

    if (strcmp(argv[1], "pushd") == 0) {
	if (argc < 3) {
	    fprintf(stderr, "Usage: %s pushd <directory>\n", argv[0]);
	    return 1;
	}
	pushd(argv[2]);
    } else if (strcmp(argv[1], "popd") == 0) {
	popd();
    } else {
	fprintf(stderr, "Unknown command: %s\n", argv[1]);
	return 1;
    }

    free_stack();
    return 0;
}

