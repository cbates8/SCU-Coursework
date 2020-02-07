
		.syntax		unified
		.cpu		cortex-m4
		.text
		
		.global		UseLDRB
		.thumb_func
	// void UseLDRB(void *dst, void *src);
	UseLDRB: //Copy 1 byte at a time
		// TODO: Write your Assembly code for the 'UseLDRB' function.
		.rept 512 //512/1
		LDRB	R2, [R1], 1
		STRB	R2, [R0], 1
		.endr
		BX		LR
	
		.global		UseLDRH
		.thumb_func
	// void UseLDRH(void *dst, void *src);
	UseLDRH: //copy 2 bytes at a time
		// TODO: Write your Assembly code for the 'UseLDRH' function.
		.rept 256 //512 / 2
		LDRH	R2, [R1], 2
		STRH	R2, [R0], 2
		.endr
		BX		LR
		
		.global		UseLDR
		.thumb_func
	// void UseLDR(void *dst, void *src);
	UseLDR: //copy 4 bytes at a time
		// TODO: Write your Assembly code for the 'UseLDR' function.
		.rept 128 //512 / 4
		LDR		R2, [R1], 4
		STR		R2, [R0], 4
		.endr
		BX		LR
		
		.global		UseLDRD
		.thumb_func
	// void UseLDRD(void *dst, void *src);
	UseLDRD: //copy 8 bytes at a time
		// TODO: Write your Assembly code for the 'UseLDRD' function.
		.rept	64 //512 / 8
		LDRD	R2, R3, [R1], 8
		STRD	R2, R3, [R0], 8
		.endr
		BX		LR
		
		.global		UseLDM
		.thumb_func
	// void UseLDM(void *dst, void *src);
	UseLDM: //copy 32 bytes at a time
		// TODO: Write your Assembly code for the 'UseLDM' function.
		PUSH {R4-R9}
		.rept	16 // 512 / 16
		LDMIA	R1!, {R2-R9}
		STMIA	R0!, {R2-R9}
		.endr
		POP	{R4-R9}
		BX		LR
		.end