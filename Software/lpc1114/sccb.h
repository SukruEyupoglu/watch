#ifndef SCCB_H
#define SCCB_H

#define SDA_IN 					PIN_DIR_INPUT 		|=		 (1 << 3)
#define SDA_OUT 				PIN_DIR_OUTPUT 	  |=		 (1 << 3)

#define SCL_IN 					PIN_DIR_INPUT 		|=		 (1 << 1)
#define SCL_OUT 				PIN_DIR_OUTPUT 	  |=		 (1 << 1)

#define SDA_IN_DATA 		PIN_INN & (1 << 3)

#endif /* SCCB_H */
