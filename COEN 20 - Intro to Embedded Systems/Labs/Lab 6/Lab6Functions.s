// Vineet Joshi
// February 13, 2020
// tetris.s
// This is my starter code for Lab6e of COEN 20.

		.syntax		unified
		.cpu		cortex-m4
		.text
	
	// BOOL GetBit(uint16_t *bits, uint32_t row, uint32_t col);
		.global		GetBit
		.thumb_func
		.set		BITBANDING, 1		// Comment out if not using bit-banding
		.ifdef		BITBANDING
	GetBit: // WITH Bitbanding R0=*bits R1=row R2=col
		ADD	R12,R2,R1,LSL 2	//Address of desired bit
		LDR	R3,=0x20000000
		SUB 	R0,R0,R3	//Bit band offset
		LSL	R0,R0,5		//insert offset into alias address
		ADD	R0,R0,R12,LSL 2	//add 4 times bit number
		LDR	R3,=0x22000000
		ADD	R0,R0,R3	//add base adrs of alias region
		LDR	R0,[R0]		//Loading desired bit into R0
		BX	LR

		.else
	
	GetBit: // W/O Bitbanding R0=*bits R1=row R2=col
		LDR	R0,[R0]		//Storing value of bits in R0
		ADD	R12,R2,R1,LSL 2	//R12 = address of desired bit
		LSR	R0,R0,R12	//Shifting desired bit to least sig bit
		UBFX	R0,R0,0,1	//Storing value of desired bit into R0
		BX	LR

		.endif
	
	// void PutBit(BOOL value, uint16_t *bits, uint32_t row, uint32_t col);
		.global		PutBit
		.thumb_func
		.ifdef		BITBANDING
	PutBit: //WITH bitbanding R0=value R1=*bits R2=row R3=col
		PUSH	{R4}
		LDR	R4,=0x20000000
		SUB 	R1,R1,R4	//compute bit band offset
		LSL	R1,R1,5		//insert offset into alias address
		ADD	R12,R3,R2,LSL 2	//address of desired bit
		ADD	R1,R1,R12,LSL 2	//add 4 times the bit number
		LDR	R4,=0x22000000
		ADD	R1,R1,R4	//add base adrs of alias region
		STR	R0,[R1]		//storing value into desired bit
		POP	{R4}
		BX	LR
	
		.else
	
	PutBit: //W/O bitbanding R0=value R1=*bits R2=row R3=col
		PUSH	{R4}
		LDR	R4,[R1]		//Storing value of bits into R4
		ADD	R12,R3,R2,LSL 2	//Address of desired bit stored in R12
		ROR	R4,R4,R12	//Rotating bits so desired bit is least sig bit
		BFC	R4,0,1		//clearing desired bit
		ORR	R4,R4,R0	//Bitwise or desired bit (0) with value, effectively: bit = value
		RSB	R12,R12,32	//Calculating how much to rotate to original position
		ROR	R4,R4,R12	//Rotate back to original position
		STR	R4,[R1]		//Storing new bit string into address of original string
		POP	{R4}
		BX	LR
		.endif
		
		.end