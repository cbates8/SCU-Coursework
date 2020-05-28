// Vineet Joshi
// February 20, 2020
// change.s
// This is my starter code for Lab7b of COEN 20.

		.syntax		unified
		.cpu		cortex-m4
		.text
	
	// void Bills(uint32_t dollars, BILLS *paper);
		.global		Bills
		.thumb_func
	Bills:	//R0=dollars R1=*paper
		LDR	R2,=0xCCCCCCCD
		UMULL	R3,R2,R2,R0 	//R3 = # of twenties
		LSRS.N	R3,R2,4		
		STR	R3,[R1]		//Twenties = R3
		
		//Finding Remainder
		ADD	R2,R3,R3,LSL 2	//R2 = R3 * 5
		LSL	R2,R2,2		//R2 = R3 * 20
		SUB	R0,R0,R2	//R0 = dollars - (R3 * 20) = remainder
		B	Ten

	
	// void Coins(uint32_t cents, COINS *coins);
		.global		Coins
		.thumb_func
	Coins:	//R0=cents R1=*paper
		LDR	R2,=0x51EB851F
		UMULL	R3,R2,R2,R0 	//R3 = # of quarters
		LSRS.N	R3,R2,3		
		STR	R3,[R1]		//Quarters = R3
		
		//Finding Remainder
		ADD	R3,R3,R3,LSL 2	//R2 = R3 * 5
		ADD	R2,R3,R3,LSL 2	//R2 = R3 * 25
		SUB	R0,R0,R2	//R0 = cents - (R3 * 25) = remainder
		
	

	Ten:	LDR	R2,=0xCCCCCCCD
		UMULL	R3,R2,R2,R0 	//R3 = # of tens
		LSRS.N	R3,R2,3		
		STR	R3,[R1, 4]	//Tens = R3

		ADD	R2,R3,R3,LSL 2	//R2 = R3 * 5
		LSL	R2,R2,1		//R2 = R3 * 10
		SUB	R0,R0,R2	//R0 = dollars - (R3 * 10) = remainder
	
	Five:	LDR	R2,=0xCCCCCCCD
		UMULL	R3,R2,R2,R0 	//R3 = # of tens
		LSRS.N	R3,R2,2		
		STR	R3,[R1, 8]	//Tens = R3

		ADD	R2,R3,R3,LSL 2	//R2 = R3 * 5
		SUB	R0,R0,R2	//R0 = dollars - (R3 * 5) = remainder

	One:	//LDR	R2,=1
		//UDIV	R3,R0,R2	//R3 = # of fives
		//MLS	R0,R2,R3,R0	//R0 = Remainder
		STR	R0,[R1,12]
		BX	LR
		.end