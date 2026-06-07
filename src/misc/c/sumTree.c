#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BLOCK_SIZE 10

typedef struct node {
	int value;
	struct node *left;
	struct node *right;
} leaf;

typedef struct context {
	int *path;
	int  dSize;
	int  pSize;
	int  target;
	int  sum;
	bool found;
} Context;


void freeTree(leaf *root){
        if(root != NULL){
                freeTree(root->left);
                freeTree(root->right);
                free(root);
        }
}

leaf *insert(leaf *root, int num) {
	if (root == NULL) {
		root = malloc(sizeof(struct node));
		memset (root, sizeof(struct node), 0);
		root->value = num;
	} else {
		if (root->value > num) {
			if (root->left == NULL) {
				root->left = malloc(sizeof(struct node));
				memset (root->left, sizeof(struct node), 0);
				root->left->value = num;
			} else {
				return insert(root->left, num);
			}

		} else {
			if (root->right == NULL) {
				root->right = malloc(sizeof(struct node));
				memset (root->right, sizeof(struct node), 0);
				root->right->value = num;
			} else {
				return insert(root->right, num);
			}
		}
	}
	return root;
}

void addPath(Context *ctx, int value) {
	if (ctx->path == NULL) {
		ctx->path = (int *)malloc(BLOCK_SIZE*sizeof(int));
		ctx->pSize = BLOCK_SIZE;
		ctx->path[ctx->dSize] = value;
                ctx->dSize++;
	} else {
		if (ctx->dSize == ctx->pSize) {
			ctx->path = (int *)realloc(ctx->path, (ctx->pSize+BLOCK_SIZE)*sizeof(int));
			ctx->pSize += BLOCK_SIZE;
			ctx->path[ctx->dSize] = value;
                	ctx->dSize++;
		} else {
			ctx->path[ctx->dSize] = value;
                	ctx->dSize++;
		}
	}
}


void findPath(leaf *root, Context *ctx) {
	if (root != NULL && !ctx->found) {
		if (ctx->sum+root->value == ctx->target) {
			ctx->sum += root->value;
			addPath(ctx, root->value);
			ctx->found = true ;
		} else if (ctx->sum+root->value < ctx->target) {
			ctx->sum += root->value;
			addPath(ctx, root->value);
			findPath(root->left, ctx);
			findPath(root->right, ctx);
		}
	}
}

int main(){

	//btree tree;
	leaf *tree = NULL;

	tree->insert(5);
	tree->insert(4);
	tree->insert(8);
	tree->insert(11);
	tree->insert(13);
	tree->insert(4);
	tree->insert(7);
	tree->insert(2);
	tree->insert(5);
	tree->insert(1);


	freeTree(tree);
