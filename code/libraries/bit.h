
#ifndef BIT_H_
#define BIT_H_

#define BitSet(arg, bit) ((arg) |=  (1 << (bit)))
#define BitClr(arg, bit) ((arg) &= ~(1 << (bit)))
#define BitFlp(arg, bti) ((arg) ^= (1 << (bit)))
#define BitTst(arg, bit) ((arg) & (1 << (bit)))

#endif
