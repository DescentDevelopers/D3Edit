/*
 THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF OUTRAGE
 ENTERTAINMENT, INC. ("OUTRAGE").  OUTRAGE, IN DISTRIBUTING THE CODE TO
 END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
 ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
 IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
 SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
 FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
 CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
 AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
 COPYRIGHT 1996-2000 OUTRAGE ENTERTAINMENT, INC.  ALL RIGHTS RESERVED.
 */
 

#ifndef OPCODES_H
#define OPCODES_H

/*	This is a list of macro-opcodes */

/*	
	Memory operations
		LOAD				rx, (ABSOLUTE)
		LOAD				rx, (ADx+IMM)
		LOAD				rx, IMM
		STORE				rx, (ABSOLUTE)
		STORE				rx, (ADx+IMM)

	Math functions
		ADD				rx, rx
		ADDI				rx, rx
		SUB				rx, rx
		MUL				rx, rx
		DIV				rx, rx
		AND				rx, rx
		MOD				rx, rx
		BAND				rx, rx
		BANDI				rx, rx
		OR					rx, rx
		BOR				rx, rx
		BORI				rx, rx
		EQU				rx, rx
		NEQ				rx, rx
		LT					rx, rx
		LTE				rx, rx
		GT					rx, rx
		GTE				rx, rx
		NEG				rx
		NOT				rx
		ABS				rx

	Math vector functions (Vector element extraction)
		VEX				rx, vx
		VEY				rx, vx
		VEY				rx, vx
		XEV				vx, rx
		YEV				vx, rx
		ZEV				vx, rx
		SCALEV			vx, i/fx

	Execution Buffer
		EPUSH				rx
		EPOP				rx
		PCALL				FN
		CALL				ABSOLUTE

	Call Stack Data Operations
		CPUSH				rx
		CPOP				rx
		TOCSP				ADx					Transfer ADx reg to CSP reg
		FROMCSP			ADx					Transger CSP reg to ADx reg
		RETURN									grabs address from current CSP (return from CALL)

	BRANCHING

		JUMP				ABSOLUTE				Branch uncoditonally
		JUMPN				ABSOLUTE, rx		Jump if rx == 0
*/

/*	
	registers
		ad0, ad1									Address registers
		i0, i1									Integer registers
		f0, f1									Float registers
		v0, v1									Vector registers
*/

#define OP_BREAK				0
#define OP_LOAD_ABS			1
#define OP_LOAD_ADI			2
#define OP_LOAD_IMM			3
#define OP_LOAD_PARM			4
#define OP_STORE_ABS			5
#define OP_STORE_ADI			6
#define OP_STORE_PARM		7
#define OP_ADD					10
#define OP_SUB					11
#define OP_MUL					12
#define OP_DIV					13
#define OP_MOD					14
#define OP_AND					15
#define OP_OR					16
#define OP_NEG					17
#define OP_NOT					18
#define OP_ABS					19
#define OP_EQU					20
#define OP_NEQ					21
#define OP_LT					22
#define OP_LTE					23
#define OP_GT					24
#define OP_GTE					25
#define OP_BOR					26
#define OP_BAND				27
#define OP_VEX					28
#define OP_VEY					29
#define OP_VEZ					30
#define OP_XEV					31
#define OP_YEV					32
#define OP_ZEV					33
#define OP_ADDI				34
#define OP_BANDI				35
#define OP_BORI				36
#define OP_EPUSH				40
#define OP_EPOP				41
#define OP_PCALL				42
#define OP_CALL				43
#define OP_CPUSH				44
#define OP_CPOP				45
#define OP_TOCSP				46
#define OP_FROMCSP			47
#define OP_RET					48
#define OP_DEFER				49
#define OP_JUMP_ABS			50
#define OP_JUMP_NCOND		51

#define VFREG_START		0
#define VFREG_NUM			16
#define REG_VF0			0
#define REG_VF1			1
#define REG_VF2			2
#define REG_VF3			3
#define REG_VF4			4
#define REG_VF5			5
#define REG_VF6			6
#define REG_VF7			7


/*	Address registers allow indirect addressing.
	Ad0 typically accesses local variables from the stack.
*/
#define AREG_START		VFREG_START+VFREG_NUM
#define AREG_NUM			2
#define REG_AD0			0
#define REG_AD1			1

#define MAX_D3X_REGS		32


typedef struct tD3XInstruction
{
	unsigned char opc;						/* Opcode */
	union 
	{
		struct									/* Register and or immediate */
		{
			unsigned char d;
			union 
			{
				int i;
				float f;
			}
			imm;
		}
		ri;
		struct 									/* register <- Address-Immediate indirect addressing */
		{
			unsigned char d,a;				
			unsigned short imm;
		}
		aii;
		struct									/* jump absolute <- register  or jump/call absolute (r = 0xff) */
		{
			unsigned short abs;
			unsigned char r;
		}
		ra;
		struct 									/* register <- Address-Immediate indirect addressing */
		{
			unsigned char d,s;				
		}
		rr;
	}
	opr;											/* Operand depends on Opcode */
}
tD3XInstruction;


/*	Values used for defer opcode */
#define DEFER_END					0
#define DEFER_DEFAULT			1

/*	Values defined for type of object the 'me' or 'it' variable will be */
#define REF_OBJTYPE				0
#define REF_TRIGTYPE				1
#define REF_LEVELTYPE			2
#define REF_GAMEMODE				3

/*	parameter types for scripts */
#define PARMTYPE_NUMBER	0
#define PARMTYPE_VECTOR	1
#define PARMTYPE_REF		2
#define PARMTYPE_STRREF	3

/*	Offsets into call stack which contain the passed arguments to a script
	SCRARG_NUM = number of arguments of script (including event arguments)
*/
#define SCRARG_NUM				4
#define SCRARG_EVENT				0
#define SCRARG_ME					1
#define SCRARG_ITTYPE			2
#define SCRARG_IT					3
#define EVTARG_NUM				8
#define SCRSTACK_START			SCRARG_NUM + EVTARG_NUM

/*	Program map entry */
#define MAX_D3XID_NAME		32

typedef struct tD3XPMap
{
	char name[MAX_D3XID_NAME];
	unsigned short ip;
	unsigned short mem;
	unsigned short type;
	unsigned short parms;
}
tD3XPMap;

#define D3X_TAG "D3X5"


#endif

