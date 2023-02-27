#include <cstdint>  // types

#define OP_ADDR         (opcode & 0x0FFFu)
#define OP_BYTE         (opcode & 0x00FFu)
#define OP_NIBBLE       (opcode & 0x000Fu)
#define OP_X            ((opcode & 0x0F00u) >> 8u)
#define OP_Y            ((opcode & 0x00F0u) >> 4u)

#define MAX_MEMORY      0xE00
#define MAX_OPCODES     35

class Chip8Disasm
{
	private:
		uint8_t     romFile[MAX_MEMORY];
		uint64_t    romSize;
		uint16_t    opcode;
		uint8_t     offset = 0x00;

		void OP_NULL(); // Do nothing
		void OP_00E0(); // CLS
		void OP_00EE(); // RET
		void OP_0NNN(); // SYS address
		void OP_1NNN(); // JP address
		void OP_2NNN(); // CALL address
		void OP_3XKK(); // SE Vx, byte
		void OP_4XKK(); // SNE Vx, byte
		void OP_5XY0(); // SE Vx, Vy
		void OP_6XKK(); // LD Vx, byte
		void OP_7XKK(); // ADD Vx, byte
		void OP_8XY0(); // LD Vx, Vy
		void OP_8XY1(); // OR Vx, Vy
		void OP_8XY2(); // AND Vx, Vy
		void OP_8XY3(); // XOR Vx, Vy
		void OP_8XY4(); // ADD Vx, Vy
		void OP_8XY5(); // SUB Vx, Vy
		void OP_8XY6(); // SHR Vx
		void OP_8XY7(); // SUBN Vx, Vy
		void OP_8XYE(); // SHL Vx
		void OP_9XY0(); // SNE Vx, Vy
		void OP_ANNN(); // LD I, address
		void OP_BNNN(); // JP V0, address
		void OP_CXKK(); // RND Vx, byte
		void OP_DXYN(); // DRW Vx, Vy, height
		void OP_EX9E(); // SKP Vx
		void OP_EXA1(); // SKNP Vx
		void OP_FX07(); // LD Vx, DT
		void OP_FX0A(); // LD Vx, K
		void OP_FX15(); // LD DT, Vx
		void OP_FX18(); // LD ST, Vx
		void OP_FX1E(); // ADD I, Vx
		void OP_FX29(); // LD F, Vx
		void OP_FX33(); // LD B, Vx
		void OP_FX55(); // LD [I], Vx
		void OP_FX65(); // LD Vx, [I]

		uint16_t opcodeMask[MAX_OPCODES] = {
			0x0000, 0xFFFF, 0xFFFF, 0xF000, 0xF000, 0xF000, 0xF000, 0xF00F, 0xF000,
			0xF000, 0xF00F, 0xF00F, 0xF00F, 0xF00F, 0xF00F, 0xF00F, 0xF00F, 0xF00F,
			0xF00F, 0xF00F, 0xF000, 0xF000, 0xF000, 0xF000, 0xF0FF, 0xF0FF, 0xF0FF,
			0xF0FF, 0xF0FF, 0xF0FF, 0xF0FF, 0xF0FF, 0xF0FF, 0xF0FF, 0xF0FF
		};

		uint16_t opcodeId[MAX_OPCODES] = {
			0x0FFF, 0x00E0, 0x00EE, 0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000,
			0x7000, 0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005, 0x8006, 0x8007,
			0x800E, 0x9000, 0xA000, 0xB000, 0xC000, 0xD000, 0xE09E, 0xE0A1, 0xF007,
			0xF00A, 0xF015, 0xF018, 0xF01E, 0xF029, 0xF033, 0xF055, 0xF065
		};

	public:
		Chip8Disasm();
		bool loadRom(const char* fileName);
		void disasm();
};
