#include "mymalloc.h"


void startMemory(){
	head = (struct Node*)memory;
	head->size = MEMLENGTH - sizeof(struct Node);
	head->is_free = 1;
	head->next = NULL;
}

size_t sizeAlign(size_t size){
	return size + (size % 8);
}

void* mymalloc(size_t size, char* file, int line){


	if(size == 0){
		void report_error(const char* file, int line, const char* message) {
    			fprintf(stderr, "Error in %s at line %d: %s\n", file, line, message);
		}
		printf("Error: cannot allocate 0 bytes");
		return NULL;
	}
	size = sizeAlign(size);

	struct Node* prevptr = NULL;
	struct Node* ptr = head;

	while((char*) ptr < (char*) memory + MEMLENGTH){
		int chunk_size = ptr->size;
		int is_free = ptr->is_free;

		if(chunk_size == 0 && is_free == 0){
			ptr->size = size + 8;
			ptr->is_free = 0;
			prevptr = ptr + 8;
			is_free = 1;
			struct Node* nextChunk = (struct Node*)((char*)ptr + sizeof(struct Node));
			return ptr + sizeof(struct Node);
		} 
		if(is_free == 0 && chunk_size >= size + 8){
			ptr->size = size + 8;
			ptr->is_free = 0;
			prevptr = ptr + 8;
			if(ptr->next == NULL){
				ptr->next->size = chunk_size - (size + 8);
			}
			return ptr + sizeof(struct Node);

		}
		if (is_free == 1 || chunk_size < size + 8){
			ptr = ptr->next;
	}
	void report_error(const char* file, int line, const char* message) {
    		fprintf(stderr, "Error in %s at line %d: %s\n", file, line, message);
	}
	printf("Error: not enough memory");
	return NULL;
}


void myfree(void* ptr, char* file, int line){
	struct Node *start = head;
	if((void*)start < (void*)memory){
	void report_error(const char* file, int line, const char* message) {
    		fprintf(stderr, "Error in %s at line %d: %s\n", file, line, message);
	}}
	struct Node * ptra = (struct Node*) ptr;
	while((void*)start < (void*)memory + MEMLENGTH){
		if((start->next && start->next == ptra) || (ptra->next && ptra->next == start)){
			if(start->next == ptra){
				start->size += ptra->size;
				start->next = ptra->next;
			}
			else {
				ptra->size += start->size;
				ptra->next = start->next;
			}
		}
		if(ptra->next && ptra->next->is_free){
			start->size += ptra->next;
			start->next = ptra->next->next;
		}
		ptra = NULL;
		return;
		}

		if(start == ptra){
			if(ptra->next && ptra->next->is_free){
				ptra->size += ptra->next->size;
				ptra->next = ptra->next->next;
			}
			ptra->is_free = 1;
			ptra = NULL;
			return;
		}
		start = start->next;
	}
	printf("Pointer not in heap");
	return NULL;
}

int memCleared() {
	struct Node* start = head;
	int* chunksize = start->size;
	int free = start->is_free;

	if(chunksize == NULL || free == 1){
		return 1;
	}

	return 0;
}
