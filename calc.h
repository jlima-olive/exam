
typedef struct node
{
	enum{
		ADD,
		MULTI,
		VAL
	} type;
	int val;
	struct node *l;
	struct node *r;
} node;
