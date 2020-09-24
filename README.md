# Array-manipulation-using-pthread-and-semaphores
1. Implemented an infinite loop program that creates 3 children to increment elements of array arr[3] using concurrent programming. 
2. Child i adds 1 to array[i], where i = 0, 1, 2.
3. The parent waits for the children to finish adding, and then prints the values in the array.
4. The children wait for the parent to finish printing and then repeats (adds 1 to an an element of the array)
