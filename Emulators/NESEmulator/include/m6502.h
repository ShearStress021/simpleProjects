#pragma once
#include <cstdint>


namespace nes
{
	class NesBus;

	class Nes6502 {
		public:
			Nes6502();
			~Nes6502();
		public:
			void ConnectBus(NesBus *n) {bus = n;}
			enum FLAGSTATUS 
			{
				C = (1 << 0), // Carry Bit
				Z = (1 << 1), // ZERO
				I = (1 << 2), // Disable Interrupts
				D = (1 << 3), // Decimal Mode
				B = (1 << 4), // Break
				U = (1 << 5), // Unused
				V = (1 << 6), // overflow
				N = (1 << 7), // Negative
			};

			uint8_t  a{0x00};     // accumulator
			uint8_t  x{0x00};     // index register x
			uint8_t  y{0x00};     // index register y
			uint8_t  SP{0x00};    // stack pointer
			uint16_t PC{0x0000};  // program counter
			uint8_t status{0x00}; // status register
								  //
								  

			// Addressing Modes
			uint8_t IMP();
			uint8_t ZPO();
			uint8_t ZPY();
			uint8_t ABS();
			uint8_t ABY();
			uint8_t IZX();
			uint8_t IMM();
			uint8_t ZPX();
			uint8_t REL();
			uint8_t ABX();
			uint8_t IND();
			uint8_t IZY();

			// Instruction Set
			//add mem to Acc with Carry //add mem with acc //Shifr Left one Bit
			uint8_t ADC();              uint8_t AND();     uint8_t ASL();
			//Branch on carry clear    //Brch on carry set //branch on result zero
			uint8_t BCC();              uint8_t BCS();     uint8_t BEQ();
			//test bit in mem with acc //brch on res minus //branch on res not zero
			uint8_t BIT();              uint8_t BMI();     uint8_t BNE();
			//branch on res plus       //force break       //branch on overflow clear
			uint8_t BPL();              uint8_t BRK();     uint8_t BVC();
			//brnch on ovrflw set      //clear carry flag  //clear Decimal mode
			uint8_t BVS();              uint8_t CLC();     uint8_t CLD();
			//clear intrpt disble bit  //clear ovrflw flag //cmp mem and acc
			uint8_t CLI();              uint8_t CLV();     uint8_t CMP();
			//cmp mem and idx x        //cmp mem and idx y //dec mem by one
			uint8_t CPX();              uint8_t CPY();     uint8_t DEC();
			//dec idx x by one         //dec idx y by one  //eor mem with acc
			uint8_t DEX();              uint8_t DEY();     uint8_t EOR();
			//inc mem by one           //inc idx x by one  //inc idx y by one
			uint8_t INC();              uint8_t INX();     uint8_t INY();
			//jmp to new loc           //jmp to nw lox sra //load acc with mem
			uint8_t JMP();              uint8_t JSR();     uint8_t LDA();
			//load idx x with mem      //lod idx y wth mem //shft 1 bit right(mem/acc)
			uint8_t LDX();              uint8_t LDY();     uint8_t LSR();
			//no operation             //or mem wth acc    //psh acc on stack
			uint8_t NOP();              uint8_t ORA();     uint8_t PHA();
			//psh prc sts on stck      //pll acc frm stack //pll prc sts from stack
			uint8_t PHP();              uint8_t PLA();     uint8_t PLP();
			//rtt 1 bit lft(mem/acc)   //rt 1bit rgt(mem/acc) //rtrn frm intrpt
			uint8_t ROL();              uint8_t ROR();     uint8_t RTI();
			//rtrn frm subroutine      //sub mem frm acc w b  //set carry flag
			uint8_t RTS();              uint8_t SBC();     uint8_t SEC();
			//set dec mode             //set intrpt dsble sts //str acc in mem
			uint8_t SED();              uint8_t SEI();     uint8_t STA();
			//str idx x in mem         //str idx Y in mem  //trnsf acc to idx x
			uint8_t STX();              uint8_t STY();     uint8_t TAX();
			//trnsf acc to idx y       //trnsf SP to idx x //trnsf idx x to acc
			uint8_t TAY();              uint8_t TSX();     uint8_t TXA();
			//trnsf idx x to SP        //trnsf idx y to acc 
			uint8_t TXS();              uint8_t TYA();     


			uint8_t XXX();// catching illegal opcodes 

			void clock(); // perform one clock cycle's worth of update

			void reset(); // reset interrupt 
			void irq();   // Interrupt request
			void nmi();   // non-maskable Interrupt request
						 
			uint8_t  fetch();         //read data mem address
			uint8_t  fetched{0x00};   //  reps the working input val to the ALU
			uint16_t addr_abs{0x0000}; // 
			uint16_t addr_rel{0x00};
			uint8_t cycles{0};

		private:
			NesBus  *bus = nullptr;
			uint8_t read(uint16_t a);
			void    write(uint16_t a,uint8_t d);
			uint8_t GetFlag(FLAGSTATUS f);
			void 	SetFlag(FLAGSTATUS f, bool v);
	};

}
