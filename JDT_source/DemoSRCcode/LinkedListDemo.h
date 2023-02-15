#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

enum BasicNodeSignatures
{
	//if using custom then there will be no automatic malloc.
	BNS_CUSTOM = -10,
	//Single Byte.
	BNS_CHAR,
	//Double Byte.
	BNS_INT,
	//Whatever float is.
	BNS_FLOAT,
	//tetrouple(?) Byte.
	BNS_INT32,
	//Octouple Byte.
	BNS_INT64
};
typedef struct NodeDataContainer
{
	//length of the data in bytes.
	int data_size;
	/*
	Pointer to the data that is
	being stored / tracked
	*/
	void* data;
	/*
		This is a marker that will be used to
		handle how the data is going to be
		processed / used. Only really useful if
		JNodeLib is being used to do something.

		The enum called BasicNodeSignatures
		for example tracks simple datatypes.
	*/
	int signature;
}
NodeDataContainer;

/*
	This function takes 'signature' as it's argument
	What this does is it decides what the allocated
	data size will be for the NDC. This means putting
	'BNS_INT' will allocate 2 bytes for the NDC to store.
*/
NodeDataContainer newNodeDataContainerBasic(int signature)
{
	NodeDataContainer ret;
	switch (signature)
	{

	case BNS_CHAR:
		ret.data_size = sizeof(char);
	break;

	case BNS_INT:
		ret.data_size = sizeof(int);
	break;

	case BNS_FLOAT:
		ret.data_size = sizeof(float);
	break;

	case BNS_INT32:
		ret.data_size = sizeof(int32_t);
	break;

	case BNS_INT64:
		ret.data_size = sizeof(int64_t);
	break;
	
	default:
		printf("\tERROR: Attempted to pass through a value of: %d\n \
		\t\tThis means that the NDC cannot be given allocated any memory.\n \
		\t\t(NDC - Node Data Container.)\n \
		Stopping Execution...", signature);
		exit(0);
	break;
	}

	ret.signature = signature;
	ret.data = malloc(ret.data_size);
	return ret;
}

typedef struct Node
{
	/*
	The node that is above this in the
	chain, top node will have "NULL".
	*/
	struct Node* parent_node;
	//This is the node that stems from this node.
	struct Node* child_node;
	//The data that the node is keeping track of.
	NodeDataContainer data_container;    
}
Node;

Node* newNode(Node* parent_node, NodeDataContainer data);
Node* getNextNode(Node* head_node);
Node* getPreviousNode(Node* head_node);
Node* addNodeToEndOfNode(Node* current_node, NodeDataContainer data);
Node* getTargetNodeInChain(Node* head_node, int target);
Node* getLastNode(Node* head_node);
Node* addNodeToEndOfChain(Node* head_node, NodeDataContainer data);
NodeDataContainer getNodeDataContainer(Node* head_node);
int getNodeCount(Node* head_node);
Node** getFastStoredNodePTRPTR();
Node* setFastStoredNode(Node* new_fast_node);
Node* getFastStoredNode();
Node* stepFastStoredNode();
Node* stepFastStoredNodeBack();
int getTotalSizeOfDataInNodeChain(Node* head_node);
void printNodeData(Node* node);
void printFullChainData(Node* head_node);
void printNodeChainStats(Node* head_node);


/*
	Adds a new node to the node pointed to
	by the 'parent_node'.
		Returns the newly generated nodes pointer.
*/
Node* newNode(Node* parent_node, NodeDataContainer data)
{
	Node* ret = (Node*)malloc(sizeof(Node));
	if(parent_node)
	{
		parent_node->child_node = ret;
		ret->parent_node = parent_node;
	}
	ret->child_node = NULL;
	ret->data_container = data;
	return ret;
}
/*
	gets the node after the 'head_node' in the chain.
*/
Node* getNextNode(Node* head_node)
{
	return head_node->child_node;
}
/*
	gets the node before the 'head_node' in the chain.
*/
Node* getPreviousNode(Node* head_node)
{
	return head_node->parent_node;
}
/*
	Adds a new node to the end of the 'current_node'
*/
Node* addNodeToEndOfNode(Node* current_node, NodeDataContainer data)
{
	if(getNextNode(current_node) == NULL)
	{
		return newNode(current_node, data);
	}
	return getNextNode(current_node);
}
/*
	Gets the last node in the chain of nodes.
*/
Node* getTargetNodeInChain(Node* head_node, int target)
{
	Node* current_node = head_node;
	for(int i = 0; i != target && getNextNode(current_node) != NULL; i++)
	{
		current_node = getNextNode(current_node);
	}
	return current_node;
}
/*
	Gets the last node in the chain of nodes.
*/
Node* getLastNode(Node* head_node)
{
	return getTargetNodeInChain(head_node, getNodeCount(head_node));
}
/*
	Adds a node to the very end of the chain.
*/
Node* addNodeToEndOfChain(Node* head_node, NodeDataContainer data)
{
	return addNodeToEndOfNode(getLastNode(head_node), data);
}
/*
	Gets the data pointed to by the current node.
*/
NodeDataContainer getNodeDataContainer(Node* head_node)
{
	return head_node->data_container;
}
/*
	Gets the amount of nodes in the chain of nodes.
*/
int getNodeCount(Node* head_node)
{
	int a = !(!head_node);
	Node* current_node = head_node;

	while(getNextNode(current_node) != NULL)
	{
		current_node = getNextNode(current_node);
		a++;
	}
	return a;
}
/*
	This exists to have a single node that
	can be accessed faster than having to be
	scrolled through the entire chain again for.
*/
Node** getFastStoredNodePTRPTR()
{
	static Node* fast_node;
	return &fast_node;
}
/*
	Sets the fast stored node.
*/
Node* setFastStoredNode(Node* new_fast_node)
{
	(*getFastStoredNodePTRPTR()) = new_fast_node;
	return *getFastStoredNodePTRPTR();
}
/*
	Gets the fast stored node.
*/
Node* getFastStoredNode()
{
	return (*getFastStoredNodePTRPTR());
}
/*
	Steps the fast stored node to it's child node.
*/
Node* stepFastStoredNode()
{
	return setFastStoredNode(getNextNode(getFastStoredNode()));
}
/*
	Steps the fast stored node to it's parent node.
*/
Node* stepFastStoredNodeBack()
{
	return setFastStoredNode(getLastNode(getFastStoredNode()));
}
/*
	Gets the total size of the data stored by each node.
*/
int getTotalSizeOfDataInNodeChain(Node* head_node)
{
	int node_count = getNodeCount(head_node), data_size = 0;
	for(int i = 0; i != node_count; i++)
	{
		data_size += getTargetNodeInChain(head_node, i)->data_container.data_size;
	}
	return data_size;
}

/*
	Prints information regarding the 'node'.
*/
void printNodeData(Node* node)
{
	printf("Node address: %p\n", node);
	printf("Node data address: %p, Node data size: %d\n", getNodeDataContainer(node).data, getNodeDataContainer(node).data_size);
	printf("Node parent address: %p\n", getPreviousNode(node));
	printf("Node child address: %p\n\n", getNextNode(node));
}
/*
	This prints the information of every single
	node out. Intended for visualising the
	entire chain.
*/
void printFullChainData(Node* head_node)
{
	printf("\n");
	int node_count = getNodeCount(head_node), data_size = 0;
	for(int i = 0; i != node_count; i++)
	{
		printf("Node:\n\t-- %d --\n", i);
		printNodeData(getTargetNodeInChain(head_node, i));
	}
}
/*
	Prints information regarding the chain of nodes.
*/
void printNodeChainStats(Node* head_node)
{
	printf("Nodes in chain: %d\n", getNodeCount(head_node));
	printf("Total data stored in chain: %d\n", getTotalSizeOfDataInNodeChain(head_node));
}

void demo()
{
	Node* a = newNode(a, newNodeDataContainerBasic(BNS_CHAR));
	
	addNodeToEndOfChain(a, (NodeDataContainer){0, NULL});
	addNodeToEndOfChain(a, (NodeDataContainer){0, NULL});

	printNodeData(a);
	
	printNodeChainStats(a);

	printFullChainData(a);
}

/*
Side Notes and asterisk elaborations:
	NDC = Node Data Container.
	BNS = Basic Node Signature
*/
#endif