#include <stdint.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    uint16_t lfsr = 0xFFFF;
    unsigned period = 0;
    char s[16+1];

    while(lfsr) {
      ++period;
      for (int i = 0; i < 16; i++)
        {
          s[15 - i] = (lfsr & (1 << i)) ? '1' : '0'; //pour afficher en binaire
        }
      s[16] = '\0';
      printf("\n%10d: %s", period, s);
      lfsr>>=1;
    } 

    return 0;
}
