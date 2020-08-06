#include "crc16.h"

/* Exemplo de uso do calculo do CRC (FCS) */
int  main(int argc, char **argv)
{
   char   cp[DATA_SIZE+2];
   struct timeval tv;
   int    i, len;
   u16    trialfcs;
   
   len = DATA_SIZE;
    
   gettimeofday(&tv, NULL);
   srand(tv.tv_usec);
   
   for (i=0; i<len; i++)
       cp[i] = (char)rand();
   
  /*  
   *  Calcula o CRC de "len" dados a partir do ponteiro cp. 
   *  Dois ultimos bytes sao para armazenamento do CRC
   */

   trialfcs  = pppfcs16( PPPINITFCS16, cp, len );
   trialfcs  = trialfcs ^ 0xffff;  	          /* complement */
   cp[len]   = (char)(trialfcs & 0x00ff);         /* LSB first  */
   cp[len+1] = (char)((trialfcs >> 8) & 0x00ff);

   i = rand();
   i = i % 5;
   if ( i == 0 ) {
      cp[1] = ~cp[1];
      printf("Gerando erro...\n");
   }
      

  /*
   *  Calcula o CRC de "len+2" dados a partir do ponteiro cp,
   *  ou seja, calcula o CRC considerando o CRC calculado
   *  anteriormente como parte dos dados
   */  
    
   trialfcs = pppfcs16( PPPINITFCS16, cp, len + 2 );
   if ( trialfcs == PPPGOODFCS16 )
      printf("Good FCS\n");
   else
      printf("Bad FCS\n");   
}