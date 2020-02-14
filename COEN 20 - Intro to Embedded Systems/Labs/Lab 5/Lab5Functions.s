// Vineet Joshi
// January 16, 2020
// puzzle.s
// This is my starter code for Lab5c of COEN 20.

		.syntax		unified
		.cpu		cortex-m4
		.text
	
	// void	CopyCell(RGB_PXL *dst, RGB_PXL *src);
		.global		CopyCell
		.thumb_func
	CopyCell: //R0 = *dst, R1 = *src
		LDR		R2,=0				//R2 = row
	F1:	LDR		R3,=0				//R3 = col
	F2:	LDR		R12,[R1,R3,LSL 2] 	//R12 = src[col]
		STR		R12,[R0,R3,LSL 2] 	//dst[col] = src[col]
		ADD		R3,R3,1				//Increment Col
		CMP		R3,60				//If R3 (col) < 60
		BLO		F2					//Then repeat F2
		//End Loop 2 (inside)
		ADD		R0,R0,960			 //Increment dist
		ADD		R1,R1,960			 //Increment src
		ADD		R2,R2,1				//Increment Row
		CMP		R2,60				//If R2 (row) < 60
		BLO		F1					//Then repeat F1
		//End Loop 1 (outside)
		BX		LR
	
	
	// void FillCell(RGB_PXL *dst, uint32_t color);
		.global		FillCell
		.thumb_func
	FillCell: //R0 = *dst, R1 = pixel
		LDR		R2,=0				//R2 = row
	L1:	LDR		R3,=0				//R3 = col
	L2:	STR		R1,[R0,R3,LSL 2] 	//dst[col] <- R1 (pixel)
		//STR		R1,[R1] 			//dst[col] = pixel
		ADD		R3,R3,1				//Increment Col
		CMP		R3,60				//If R3 (col) < 60
		BLO		L2					//Then repeat F2
		//End Loop 2 (inside)
		ADD		R0,R0,960 			//Increment dist
		ADD		R2,R2,1				//Increment Row
		CMP		R2,60				//If R2 (row) < 60
		BLO		L1					//Then repeat F1
		//End Loop 1 (outside)
		BX		LR
		
	
		.end