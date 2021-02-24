# HEAP

Algorithms and Data Structures laboratory4

### Instructions
Implement a max heap and the following operations:
<ul>
  <li>+ v (add a number v to the heap)</li>
  <li>- (remove the maximum from the max heap (minimum from the min heap respectively) and write it on the screen)</li>
  <li>p (write all elements of the heap in the order in which they are stored in an array)</li>
  <li>r n v1 ...vn (remove all elements from the heap and create a heap out of n new elements, of the values given by v1 ...vn)</li>
  <li>s (change the orientation of the heap – from max to min or from min to max; when the orientation is min, the heap yields the minimal element; s operation can be requested multiple times)</li>
  <li>q (exit the program)</li>
</ul>
Additional remarks: Operation 'r' is not the same as a sequence of '+' operations. If both children are equal the child of the lesser index is swapped.

### Input
A sequence of instructions in the format presented below. The last instruction is q.

### Output
Results of instructions '-' and 'p'.
