; Test INB, Cout, FO ports, for the SHARP PC-1403
; reserve 2K memory at &8031 with   NEW: POKE &FF01,&30,&E8: NEW
; AS61860 assembler, port Cout, FO, or IB

   8038                       9     .ORG  	0x8038
   8038 12 5F         [ 4]   10 	LIP	REG_COUT
   803A 10 80 36      [ 8]   11 	LIDP	0x8036	;DP = 0x8036
   803D 55            [ 3]   12 	MVMD		    ;(DP) --> (P)
   803E DF            [ 2]   13 	OUTC
   803F 37            [ 4]   14 	RTN                   
	                         15
   8040 12 5E         [ 4]   16 	LIP	REG_FO
   8042 10 80 36      [ 8]   17 	LIDP	0x8036	;DP = 0x8036
   8045 55            [ 3]   18 	MVMD		    ;(DP) --> (P)
   8046 5F            [ 3]   19 	OUTF
   8047 37            [ 4]   20 	RTN

   8048 CC            [ 4]   10 	INB		        ;Port B --> A
   8049 10 80 36      [ 8]   11 	LIDP	0x8036	;DP = 0x8036
   804C 52            [ 3]   12 	STD             ;A --> (DP)
   804D 37            [ 4]   14 	RTN
   