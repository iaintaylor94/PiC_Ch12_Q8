// program to insert a bit string into another bit string

#include <stdio.h>

// Declare Functions
int int_size (void);
unsigned int mask_create (int, int);
void bitpat_where(int, int);
void bitpat_set (unsigned int *, unsigned int, int, int);

int main(void) {

  unsigned int destination = mask_create (8, 16); 
  unsigned int source = 0b00000001  // 1
                       +0b00000100  // 4
                       +0b00100000; // 32
                      //0b00100101

  bitpat_set (&destination, source, 4, 8);

  return 0;
}

// Define Functions
int int_size (void) {
  unsigned int test = ~0; // All ones

  int i = 0;
  while (test != 0) {
    test >>= 1;
    i++;
  }

  return i;
}

unsigned int mask_create (int index, int length) {  // Left = 0
  unsigned int bitMask = 0;
  for (int i = 0; i < length; i++) {
    bitMask <<= 1;
    bitMask++;
  }
  bitMask <<= int_size() - length;
  bitMask >>= index;
  return bitMask;
}

void bitpat_where(int index, int length) {
  printf (" ");
  for ( int i = 0; i < int_size(); i++) {
    if (i == index)
      printf (">");
    else if (i == index + length + 1)
      printf ("<");
    else
      printf (" ");
  }
  printf ("\n");
}

void bitpat_set (unsigned int *destination, unsigned int source, int sourceIndex, int maskLength) {
  printf ("Source:      %#.32b\n", source);
  printf ("             ");
  bitpat_where (int_size() - maskLength, maskLength);
  
  printf ("Destination: %#.32b\n", *destination);
  printf ("             ");
  bitpat_where (sourceIndex, maskLength);
   
  // Zero Destination
  unsigned int zeroMask = mask_create (sourceIndex, maskLength); // A: Create mask
  zeroMask = ~zeroMask; // B: Not mask
  *destination &= zeroMask; // C: Zero
//  printf ("zeroMask:    %#.32b\n", zeroMask);
//  printf ("sourceZero:  %#.32b\n", *destination);

  // Set Bits
  source <<= int_size() - sourceIndex - maskLength; // A: Shift mask "source"
  *destination |= source; // B: Fill
  printf ("shiftTo:     %#.32b\n", source);
  printf ("sourceSet:   %#.32b\n", *destination);
}