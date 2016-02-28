#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct pair Pair;
typedef struct elt *Stack;

struct pair{
	int row;
	int col;
};

struct node{
	int val;
	Pair parent;
};

struct elt {
    struct elt *next;
    Pair pos;
    Pair parent;
};

#define STACK_EMPTY (0)

/* frees a 2d array created by malloc2d */
void
free2d(void **a)
{
    void **row;

    /* first free rows */
    for(row = a; *row != 0; row++) {
        free(*row);
    }

    /* then free array of rows */
    free(a);
}

/* returns a two-dimensional array with numRows rows and 
 * rowSize bytes per row, or 0 on allocation failure.
 * The caller is responsible for freeing the result with free2d. */
void **
malloc2d(size_t numRows, size_t rowSize)
{
    void **a;
    size_t i;

    /* a is an array of void * pointers that point to the rows */
    /* The last element is 0, so free2d can detect the last row */
    a = malloc(sizeof(void *) * (numRows + 1));        /* one extra for sentinel */
    if(a == 0) {
        /* malloc failed */
        return 0;
    }

    /* now allocate the actual rows */
    for(i = 0; i < numRows; i++) {
        a[i] = malloc(rowSize * sizeof(struct node));
        if(a[i] == 0) {
            /* note that 0 in a[i] will stop freed2d after it frees previous rows */
            free2d(a);
            return 0;
        }
    }

    /* initialize the sentinel value */
    a[numRows] = 0;

    return a;
}

/* push a new value onto top of stack */
void
stackPush(Stack *s, Pair child, Pair parent)
{
    struct elt *e;

    e = malloc(sizeof(struct elt));
    assert(e);

    e->pos = child;
    e->parent = parent;
    e->next = *s;
    *s = e;
}

int
stackEmpty(const Stack *s)
{
    return (*s == 0);
}

Pair
stackPop(Stack *s)
{
    Pair ret;
    struct elt *e;

    assert(!stackEmpty(s));

    ret = (*s)->pos;

    /* patch out first element */
    e = *s;
    *s = e->next;

    free(e);

    return ret;
}

int
stackPushNeighbors(Stack *s, Pair p, int width, int height, struct node **maze){
	int row = p.row;
	int col = p.col;
	int i;
	int j;
	Pair neighbor;
	int pushed = 0;

	for(i = row - 1; i <= (row + 1); i++){
		for(j = col - 1; j <= (col + 1); j++){
			if(!((row == i) && (col == j))){
				if((j >= 0) && (j < width) && 
				   (i >= 0) && (i < height)) {
				   	if(maze[i][j].val == 1){
				   		if(!(maze[row][col].parent.col == j &&
				   			 maze[row][col].parent.row == i)){
					   		neighbor.row = i;
							neighbor.col = j;
							stackPush(s, neighbor, p);
							pushed = 1;
						}
				   	}
				}
			}
		}
	}
	return pushed;
}

void
findLoop(struct node **maze, int width, int height){
	int row;
	int col;
	Stack s;
	Pair parent;
	Pair child;

	s = STACK_EMPTY;

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(maze[i][j].val == 1){
				row = i;
				col = j;
				i = height;
				break;
			}
		}
	}
	child.row = row;
	child.col = col;
	parent.row = row;
	parent.col = col;

	stackPush(&s, child, parent);

	while(!stackEmpty(&s)){
		child = s[0].pos;
		parent = s[0].parent;
		stackPop(&s);
		row = child.row;
		col = child.col;
		if(maze[row][col].parent.col == -1){
			maze[row][col].parent = parent;
			stackPushNeighbors(&s, child, width, height, maze);
		} else {
			if(maze[row][col].val == 1){
				maze[row][col].val = 2;
				while(!((parent.col == child.col) &&
					    (parent.row == child.row))){
					maze[parent.row][parent.col].val = 2;
					parent = maze[parent.row][parent.col].parent;
				}
			}
		}
	}
}

int
main(int argc, char **argv){
	int width;
	int height;
	int c;
	int row = 0;
	int col = 0;
	struct node **maze;
	struct node n;
	Pair p;

	scanf("P5 %d %d 255\n", &width, &height);

	maze = (struct node **) malloc2d(width, height * sizeof(struct node));

	for(row = 0; row < height; row++){
	   for(col = 0; col < width; col++){
	       c = getchar();
	       p.col = -1;
	       p.row = -1;
	       n.parent = p;
	       n.val = c;
	       maze[row][col] = n;
	   }
	}

	findLoop(maze, width, height);

	printf("P5 %d %d 255\n", width, height);

	for(row = 0; row < height; row++){
		for(col = 0; col < width; col++){
			putchar(maze[row][col].val);
		}
	}

	// for(row = 0; row < height; row++){
	// 	printf("%d: ", row);
	// 	for(col = 0; col < width; col++){
	// 		printf("%d", maze[row][col].val);
	// 	}
	// 	printf("\n");
	// }

	free2d((void **) maze);

	return 0;
}
