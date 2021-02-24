#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Heap
{
	bool maxType;
	int size;
	int* elements;
};


int getParentIndex(int i) { return (i - 1) / 2; }

int getLeftIndex(int i) { return (2 * i + 1); }

int getRightIndex(int i) { return (2 * i + 2); }

bool hasLeftChild(int index, struct Heap* heap)
{
	return getLeftIndex(index) < heap->size;
}

bool hasRightChild(int index, struct Heap* heap)
{
	return getRightIndex(index) < heap->size;
}

bool hasParent(int index)
{
	return getParentIndex(index) >= 0;
}

int leftChild(int index, struct Heap* heap)
{
	return heap->elements[getLeftIndex(index)];
}

int rightChild(int index, struct Heap* heap)
{
	return heap->elements[getRightIndex(index)];
}

int parent(int index, struct Heap* heap)
{
	return heap->elements[getParentIndex(index)];
}

void swap(int indexOne, int indexTwo, struct Heap* heap)
{
	int temp = heap->elements[indexOne];
	heap->elements[indexOne] = heap->elements[indexTwo];
	heap->elements[indexTwo] = temp;
}

void removeRoot(struct Heap* heap)
{
	if (heap->size == 0) return;
	int root = heap->elements[0];
	heap->elements[0] = heap->elements[heap->size - 1];
	heap->size--;
	heap->elements = (int*)realloc((void*)heap->elements, heap->size * sizeof(int));
	printf("%d\n", root);
}

void insertKey(int key, struct Heap* heap)
{
	if (heap->size == 1)
	{
		heap->elements = (int*)malloc(sizeof(int));
	}
	if (heap->size > 1)
	{
		heap->elements = (int*)realloc((void*)heap->elements, heap->size * sizeof(int));
	}
	heap->elements[heap->size - 1] = key;
}

void heapifyUp(struct Heap* heap)
{
	int index = heap->size - 1;
	if (heap->maxType)
	{
		while (hasParent(index) && parent(index, heap) < heap->elements[index])
		{
			swap(getParentIndex(index), index, heap);
			index = getParentIndex(index);
		}
	}
	else
	{
		while (hasParent(index) && parent(index, heap) > heap->elements[index])
		{
			swap(getParentIndex(index), index, heap);
			index = getParentIndex(index);
		}
	}
}


void heapifyDown(struct Heap* heap)
{
	int index = 0;

	if (heap->maxType)
	{
		while (hasLeftChild(index, heap))
		{
			int greaterChildIndex = getLeftIndex(index);
			if (hasRightChild(index, heap) && rightChild(index, heap) > leftChild(index, heap))
				greaterChildIndex = getRightIndex(index);

			if (heap->elements[index] > heap->elements[greaterChildIndex])
				break;

			else
				swap(index, greaterChildIndex, heap);

			index = greaterChildIndex;
		}
	}
	else
	{
		while (hasLeftChild(index, heap))
		{
			int smallerChildIndex = getLeftIndex(index);
			if (hasRightChild(index, heap) && rightChild(index, heap) < leftChild(index, heap))
				smallerChildIndex = getRightIndex(index);

			if (heap->elements[index] < heap->elements[smallerChildIndex])
				break;
			else
				swap(index, smallerChildIndex, heap);

			index = smallerChildIndex;
		}
	}
}


void heapifyMax(struct Heap* heap, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < heap->size && heap->elements[left] > heap->elements[largest])
		largest = left;

	if (right < heap->size && heap->elements[right] > heap->elements[largest])
		largest = right;

	if (largest != i) {
		swap(i, largest, heap);

		heapifyMax(heap, largest);
	}
}

void heapifyMin(struct Heap* heap, int i)
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < heap->size && heap->elements[left] < heap->elements[smallest])
		smallest = left;

	if (right < heap->size && heap->elements[right] < heap->elements[smallest])
		smallest = right;

	if (smallest != i) {
		swap(i, smallest, heap);

		heapifyMin(heap, smallest);
	}
}

void buildHeap(struct Heap* heap)
{
	int startIndex = (heap->size / 2) - 1;

	for (int i = startIndex; i >= 0; i--) {
		if (heap->maxType)
			heapifyMax(heap, i);
		else
			heapifyMin(heap, i);
	}
}


int main()
{
	char option;
	int number, i;
	int numberOfElements;

	struct Heap heap;
	heap.maxType = true;
	heap.size = 0;


	scanf_s("%c", &option);

	while (option != 'q')
	{
		switch (option)
		{
		case '+':
			heap.size++;
			scanf_s("%d", &number);
			insertKey(number, &heap);
			heapifyUp(&heap);
			break;

		case '-':
			removeRoot(&heap);
			heapifyDown(&heap);
			break;

		case 'p':
			for (i = 0; i < heap.size; i++)
			{
				printf("%d ", heap.elements[i]);
			}
			printf("\n");
			break;

		case 'r':
			scanf_s("%d", &numberOfElements);
			heap.size = numberOfElements;
			heap.elements = (int*)malloc(heap.size * sizeof(int));
			for (i = 0; i < heap.size; i++)
			{
				scanf_s("%d", &heap.elements[i]);
			}
			buildHeap(&heap);
			break;

		case 's':
			heap.maxType = !heap.maxType;
			buildHeap(&heap);
			break;
		}

		scanf_s("%c", &option);
	}
	free(heap.elements);
	return 0;
}
