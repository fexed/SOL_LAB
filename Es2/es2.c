#include <stdio.h>
#include <stdlib.h>

struct node_t {
	long val;
	struct node_t *sx;
	struct node_t *dx;
};

struct node_t *buildTree(long elem, struct node_t *t); // costruisce l'albero e restituisce il nodo radice
long getMin(struct node_t *root);       // restituisce il valore minimo
long getMax(struct node_t *root);       // restituisce il valore massimo
void printInOrder(struct node_t *root); // stampa gli elementi in modo ordinato
void deleteTree(struct node_t *root);   // cancella tutti i nodi dell'albero

int main(int argc, char *argv[]) {
	struct node_t *root = NULL;
   	const long array_size = 10;
	long array[] = {12, 32, 18, -1, 0, 18, -5, 54, 28, 15};
	 
	for(long i = 0; i < array_size; ++i)
		root = buildTree(array[i], root);
 
	printf("\n");
    	printf("Min: %ld\n", getMin(root));
    	printf("Max: %ld\n", getMax(root));
 
    	printInOrder(root);
    	printf("\n");
 
    	deleteTree(root);
    	return 0;
}

struct node_t *buildTree(long elem, struct node_t *t) {
	struct node_t *new = malloc(sizeof(struct node_t));
	new->val = elem;
	new->sx = NULL;
	new->dx = NULL;
	printf(". ");
	
	struct node_t *cur = t;
	do {
		if (cur == NULL) {t = new; break;}
		else if (cur->val <= new->val) {
			if (cur->sx == NULL) {
				cur->sx = new; break;
			}
			else {cur = cur->sx;}
		}
		else if (cur->val > new->val) {
			if (cur->dx == NULL) {
				cur->dx = new; break;
			}
			else {cur = cur->dx;}
		}
	} while (1);
	
	return t;
}

long getMin(struct node_t *root) {
	struct node_t *cur = root;

	while (cur->sx != NULL) cur = cur->sx;
	
	return cur->val;
}


long getMax(struct node_t *root) {
	struct node_t *cur = root;

	while (cur->dx != NULL) cur = cur->dx;
	
	return cur->val;
}

void printLeftTree(struct node_t *root) {
	if (root->sx != NULL) {
		printInOrder(root->sx);
	}
}

void printRightTree(struct node_t *root) {
	if (root->dx != NULL) {
		printInOrder(root->dx);
	}
}

void printInOrder(struct node_t *root) {
	struct node_t *cur = root;
	
	printLeftTree(cur);
	printf("%ld\t", cur->val);
	printRightTree(cur);
}


void deleteTree(struct node_t *root) {
	do {
		if (root->sx != NULL) deleteTree(root->sx);
		if (root->dx != NULL) deleteTree(root->dx);
		free(root);
	} while (root != NULL);
}