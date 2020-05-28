// Vineet Joshi
// November 26, 2019
// floating-point.s
// This is my starter code to Lab8b of COEN 20.

		.syntax		unified
		.cpu		cortex-m4
		.text
		
		.global		Discriminant
		.thumb_func
	// float Discriminant(float a, float b, float c);
	Discriminant: //S0=a S1=b S2=c
		VMOV		S3,4.0		//S3=4
		VMUL.f32	S3,S0,S3	//S0=4a
		VMUL.f32	S0,S1,S1	//S1 = b^2
		VMLS.f32	S0,S3,S2	//S0= b^2 - 4ac
		BX		LR

		.global		Quadratic
		.thumb_func
	// float Quadratic(float x, float a, float b, float c);
	Quadratic://S0=x S1=a S2=b S3=c
		VMUL.f32	S2,S2,S0	//S2 = bx
		VMUL.f32	S0,S0,S0	//S0 = x^2
		VMLA.f32	S2,S0,S1	//S1=ax^2 + bx
		VADD.f32	S0,S2,S3	//S0=ax^2 + bx + c
		BX		LR
		
		.global		Root1
		.thumb_func
	// float Root1(float a, float b, float c);
	Root1://S0=a S1=b S2=c
		PUSH		{LR}
		VPUSH		{S16, S17, S18}
		VMOV		S16,S0
		VMOV		S17,S1
		VMOV		S18,S2
		BL		Discriminant	//S0=Discriminant(a, b, c)
		VSQRT.f32	S0,S0		//S0=SquareRoot(Discriminant(a, b, c))
		VSUB.f32	S0,S0,S17	//R0=SquareRoot(Discriminant(a, b, c)) - b
		VMOV		S4,2.0
		VMUL.f32	S16,S16,S4	//S0 = 2*a
		VDIV.f32	S0,S0,S16	//SquareRoot(Discriminant(a, b, c)) - b / 2a
		VPOP		{S16, S17, S18}
		POP		{PC}

		.global		Root2
		.thumb_func
	// float Root2(float a, float b, float c);
	Root2://S0=a S1=b S2=c
		PUSH		{LR}
		VPUSH		{S16, S17, S18}
		VMOV		S16,S0
		VMOV		S17,S1
		VMOV		S18,S2
		BL		Discriminant	//S0=Discriminant(a, b, c)
		VSQRT.f32	S0,S0		//S0=SquareRoot(Discriminant(a, b, c))
		VNEG.f32	S17,S17		//S1=-b
		VSUB.f32	S0,S17,S0	//R0=SquareRoot(Discriminant(a, b, c)) - b
		VMOV		S4,2.0		
		VMUL.f32	S16,S16,S4	//S0 = 2*a
		VDIV.f32	S0,S0,S16	//SquareRoot(Discriminant(a, b, c)) + -b / 2a
		VPOP		{S16, S17, S18}		
		POP		{PC}
		
		.end