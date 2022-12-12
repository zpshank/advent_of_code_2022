#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct node_t;
typedef struct node_t {
	char value;
	struct node_t* l;
	struct node_t* r;
} node_t;

typedef struct deque_t {
	node_t *l;
	node_t *r;
} deque_t;

// Push a node to the left side of the deque
void d_push_left(deque_t* d, node_t* n) {
	if(d->l == NULL) {
		d->l = n;
		d->r = n;
		return;
	}
	// Update the left most node in the deque
	d->l->l = n;
	// Update the incoming node
	n->r = d->l;
	n->l = NULL;
	// Update the deque
	d->l = n;
};

// Push a node to the right side of the deque
void d_push_right(deque_t* d, node_t* n) {
	if (d->r == NULL) {
		d->l = n;
		d->r = n;
		return;
	}
	// Update the right most node in the deque
	d->r->r = n;
	// Update the incoming node
	n->l = d->r;
	n->r = NULL;
	// Update the deque
	d->r = n;
}


// Pop a node from the left side of the deque_t
// This is a destructive action
node_t* d_pop_left(deque_t* d) {
	if (d->l == NULL)
		return NULL;

	node_t* n = d->l;

	// Check if last node
	if (n->r == NULL) {
		d->l = NULL;
		d->r = NULL;
	} else {
		d->l = n->r;
		d->l->l = NULL;
	}

	n->l = NULL;
	n->r = NULL;
	return n;
}

node_t* d_pop_right(deque_t* d) {
	if (d->r == NULL)
		return NULL;

	node_t* n = d->r;

	// Check if last node
	if (n->l == NULL) {
		d->l = NULL;
		d->r = NULL;
	} else {
		d->r = n->l;
		d->r->r = NULL;
	}

	n->l = NULL;
	n->r = NULL;
	return n;
}

void d_destroy(deque_t* d) {
	node_t* n = d_pop_left(d);
	while (n != NULL) {
		free(n);
	}
}

void d_print(deque_t *d) {
	node_t *n = d->l;
	while (n != NULL) {
		printf("[%c] ", n->value);
		n = n->r;
	}
	printf("\n");
}

int main(void) {
	node_t* a = calloc(1, sizeof(node_t));
	a->value = 'a';

	node_t* b = calloc(1, sizeof(node_t));
	b->value = 'b';

	node_t* c = calloc(1, sizeof(node_t));
	c->value = 'c';

	deque_t d;
	d_push_left(&d, a);
	d_push_right(&d, b);
	d_push_left(&d, c);

	d_print(&d);

	node_t* n = d_pop_left(&d);
	printf("[%c]\n", n->value);
	free(n);
	n = d_pop_right(&d);
	printf("[%c]\n", n->value);
	free(n);
	n = d_pop_left(&d);
	printf("[%c]\n", n->value);
	free(n);

	d_destroy(&d);

	return 0;
}

