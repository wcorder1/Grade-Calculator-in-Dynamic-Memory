#include <stdio.h>
#include <stdlib.h>

int frees = 1;
int allocs = 1;
int totalSize = 0;
int loopCount = 0;
int count = 0;
double sum = 0;

/*The begin function just outputs instructions for the user while saving space in 
  the main function */

void begin();


/*The overload function is what the main program runs when the heap has been
  filled after 5 grades are input. It reallocates the pointer to be 40 bytes larger
  than its last size as well as copies the first 5 grade values over to the new array */

void overLoad(double ** p1);


/*Stop function instructs the program what to do when a negative value
  is entered to the scan in main. Outputs the average grade then lists all
  grades previously input and whether they are >= or < the average */

void stop(double ** p1); 


int main() {
  double x;
  
  begin();  
  double * p1 = (double *)malloc(40);
  
  while (count%5 == 0) {
    for (int i=loopCount; i<loopCount+5; i++) {     
      if (count > 0) { sum += x; }      
      scanf("%lf",&x);      
      *(p1+i) = x;

      if (x < 0) {
	stop(&p1);
	return 0;
      }

      if (count == 0) {
	printf("Allocated 40 bytes to to the heap at %p.\n", (void*)p1);
      }
      
      count++;
      printf("Stored %lf in the heap at %p.\n",x,(void*)(p1+i));
      
      if (count%5 == 0) {
	loopCount += 5;
	overLoad(&p1);
      }
    }
  } //for
} //while


void begin() {
  printf("Enter a list of grades below where each grade is separated by a newline character. \n");
  printf("After the last grade is entered, enter a negative value to end the list. \n");
}


void overLoad(double ** p1) {
  int store = (40 + loopCount*sizeof(double));
  
  printf("Stored %d grades (%d bytes) to the heap at %p.\n",count,store,(void*)*p1);
  printf("Heap at %p is full.\n",(void*)*p1);

  double * temp = (double *)malloc(store);
  
  for (int i=0; i<count; i++) {
    *(temp+i) = *(*p1+i);
  } //floatzel

  printf("Allocated %d bytes to the heap at %p\n", store, (void*)temp);
  printf("Copied %d grades from %p to %p.\n", count, (void*)*p1, (void*)temp);

  free(*p1);
  *p1 = temp;

  allocs++;
  frees++;
  totalSize += store;
}


void stop(double ** p1) {  

  int store = (40 + loopCount*sizeof(double));
  
  double avg = sum/(double)count;

  if (count == 0) {
    printf("The average of %d grades is %lf.\n",count,*(*p1+1));
    printf("total heap usage: %d allocs, %d frees, %d bytes allocated.\n",allocs-1,frees-1,totalSize);
  }
  
  else if (count != 0) {
    printf("The average of %d grades is %lf.\n",count,avg);
    for (int k=0; k<count; k++) {
      if (*(*p1+k) >= (sum/count)) {
	printf("%d. The grade of %lf is >= the average.\n",(k+1),*(*p1+k));
      }
      else if (*(*p1+k) < (sum/count)) { 
	printf("%d. The grade of %lf is < the average.\n",(k+1),*(*p1+k));
      }
    }
    totalSize += 40;
    printf("Freed %d bytes from the heap at %p.\n",store,(void*)*p1);
    printf("total heap usage: %d allocs, %d frees, %d bytes allocated.\n",allocs,frees,totalSize);
  }
  
  free(*p1);
}
