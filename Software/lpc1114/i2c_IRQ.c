void I2C_IRQHandler(void) 
{
  unsigned char stats;
  stats = LPC_I2C->STAT;
  switch ( stats )
  {
	case 0x08:			// A Start condition is issued.
	LPC_I2C->DAT = w_addr;
	LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;
  
	case 0x10:			// A repeated started is issued 
	LPC_I2C->DAT = r_addr
	LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;
  
	case 0x18:			// there's a ACK
	LPC_I2C->DAT = w_data;
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x28:	// Data byte has been transmitted, there's a ACK 
	LPC_I2C->CONSET = I2CONSET_STO;      // Set Stop flag 
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x30:
	LPC_I2C->CONSET = I2CONSET_STO;      // Set Stop flag
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x40:	// Master Receive, SLA_R has been sent 
	LPC_I2C->CONSET = I2CONSET_AA;	// assert ACK after data is received 
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x50:	// Data byte has been received, there's a ACK 
	r_data = LPC_I2C->DAT;
  LPC_I2C->CONCLR = I2CONCLR_AAC;	// assert NACK on last byte 
  LPC_I2C->CONSET = I2CONSET_STO;	// Set Stop flag 
	LPC_I2C->CONCLR = I2CONCLR_SIC; // Clear SI flag
	break;
	
	case 0x58:
	r_data = LPC_I2C->DAT;
  LPC_I2C->CONCLR = I2CONCLR_AAC;	// assert NACK on last byte
	LPC_I2C->CONSET = I2CONSET_STO;	// Set Stop flag  
	LPC_I2C->CONCLR = I2CONCLR_SIC;	// Clear SI flag 
	break;

	case 0x20:		// it's a NACK
  LPC_I2C->CONCLR = I2CONCLR_AAC;	// assert NACK after data is received 
	LPC_I2C->CONSET = I2CONSET_STO;      // Set Stop flag 
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
  
	case 0x48:
  LPC_I2C->CONCLR = I2CONCLR_AAC;	// assert NACK after data is received 
	LPC_I2C->CONSET = I2CONSET_STO;      // Set Stop flag 
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
  
	default:
	break;
  }
}
