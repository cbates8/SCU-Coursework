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
		LDR	R2,=20
		UDIV	R3,R0,R2 	//R3 = # of twenties
		MLS	R0,R2,R3,R0	//R0 = Remainder
		STR	R3,[R1]		//Twenties = R3
		B	Ten

	
	// void Coins(uint32_t cents, COINS *coins);
		.global		Coins
		.thumb_func
	Coins:	//R0=cents R1=*paper
		LDR	R2,=25
		UDIV	R3,R0,R2 	//R3 = # of quarters
		MLS	R0,R2,R3,R0	//R0 = Remainder
		STR	R3,[R1]		//Twenties = R3
		//B	Ten
	

	Ten:	LDR	R2,=10
		UDIV	R3,R0,R2	//R3 = # of tens
		MLS	R0,R2,R3,R0	//R0 = Remainder
		STR	R3,[R1,4]
	
	Five:	LDR	R2,=5
		UDIV	R3,R0,R2	//R3 = # of fives
		MLS	R0,R2,R3,R0	//R0 = Remainder
		STR	R3,[R1,8]

	One:	LDR	R2,=1
		UDIV	R3,R0,R2	//R3 = # of fives
		//MLS	R0,R2,R3,R0	//R0 = Remainder
		STR	R3,[R1,12]
		BX	LR
		.end