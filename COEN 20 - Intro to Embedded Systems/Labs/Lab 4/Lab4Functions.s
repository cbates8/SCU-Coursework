.syntax       unified
.cpu          cortex-m4
.text

// Discriminant(a, b, c) { return b^2 - 4ac ;}

.global   Discriminant
    .thumb_func
    .align
Discriminant:     //R0 = a, R1 = b, R2 = c
LDR   R3,=4       //R3 = 4
MUL   R1,R1,R1    //R1 = R1 * R1 (b * b = b^2)
LSL	  R0,R0,2	  //R0 = R0 * 4 (a*4)
MLS   R0,R0,R2,R1 //R0 = R1 - R0 * R2 (b^2 - (4a*c))
BX    LR


// Root1(a, b, c) { return (-b + SquareRoot(Discriminant(a, b, c))) / (2 * a) ;}

.global   Root1
    .thumb_func
    .align
Root1:              //R0 = a, R1 = b, R2 = c
PUSH  {R4, R5, LR}
MOV   R4,R0         //R4 = R0 (Preserve value of a in R4)
MOV   R5,R1         //R5 = R1 (Preserve value of b in R5)
BL    Discriminant  //R0 = Discriminant(a, b, c)
BL    SquareRoot    //R0 = SquareRoot(Discriminant(a, b, c))
SUB   R0,R0,R5      //R0 = R0 - R5 (SquareRoot(Discriminant(a, b, c) - b = -b + SquareRoot(Discriminant(a, b, c)))
LSL	  R4,R4,1		//R4 = R4 * 2 (2 * a)
SDIV  R0,R0,R4      //R0 = R0/R3 ([-b + SquareRoot(Discriminant(a, b, c))] / [2*a])
POP   {R4, R5, PC}


// Root2(a, b, c) { return (-b - SquareRoot(Discriminant(a, b, c))) / (2 * a) ;}

.global   Root2
    .thumb_func
    .align
Root2:              //R0 = a, R1 = b, R2 = c
PUSH  {R4, R5, LR}
MOV   R4,R0         //R4 = R0 (Preserve value of a in R4)
MOV   R5,R1         //R5 = R1 (Preserve value of b in R5)
BL    Discriminant  //R0 = Discriminant(a, b, c)
BL    SquareRoot    //R0 = SquareRoot(Discriminant(a, b, c))
LDR	  R3,=0			//R3 = 0
SUB	  R5,R3,R5		//R5 = R3 - R5 (0 - b = -b)
SUB   R0,R5,R0      //R0 = R5 - R0 (-b - SquareRoot(Discriminant(a, b, c)))
LSL	  R4,R4,1		//R4 = R4 * 2 (2 * a)
SDIV  R0,R0,R4      //R0 = R0/R3 ([-b - SquareRoot(Discriminant(a, b, c))] / [2*a])
POP   {R4, R5, PC}

// Quadratic(x, a, b ,c) { return ax^2 + bx + c ;}

.global Quadratic
    .thumb_func
    .align
Quadratic: //R0 = x, R1 = a, R2 = b, R3 = c
MUL   R2,R2,R0    //R2 = R2 * R0 (b * x)
MUL   R0,R0,R0    //R0 = R0 * R0 (x * x = x^2)
MLA   R0,R1,R0,R2    //R1 = R1 * R0 (bx + a * x^2)
ADD   R0,R0,R3    //R0 = R0 + R3 (ax^2 + bx + c)
BX    LR


.end
