/*
 * Copyright 2021, s40in
 * Distributed under the terms of the MIT License.
 *
 */
#ifndef DEBUG_CMD_H
#define DEBUG_CMD_H

#include "svga_reg.h"


#ifdef DEBUG_COMMANDS
static int
debug_getset_register(int argc, char** argv)
{
	if (argc < 2 || argc > 3) {
		kprintf("usage: %s <register> [set-to-value]\n", argv[0]);
		return 0;
	}

	uint32 reg = parse_expression(argv[1]);
	uint32 value = 0;
	bool set = argc == 3;
	if (set)
		value = parse_expression(argv[2]);

	kprintf("vmsvga register %#" B_PRIx32 "\n", reg);

	uint32 oldValue = ReadReg(reg);

	kprintf("  %svalue: %#" B_PRIx32 " (%" B_PRIu32 ")\n", set ? "old " : "",
		oldValue, oldValue);

	if (set) {
		WriteReg(reg, value);

		value = ReadReg(reg);
		kprintf("  new value: %#" B_PRIx32 " (%" B_PRIu32 ")\n", value, value);
	}

	return 0;
}


static int
debug_set_videomode(int argc, char** argv)
{
	if (argc != 3) {
		kprintf("usage: %s wight height\n", argv[0]);
		return 0;
	}
	
	SharedInfo *si = gPd->si;
	
	uint32 height, width, bpp;
	
	width = parse_expression(argv[1]);
	height = parse_expression(argv[2]);
	bpp=32;
			WriteReg(SVGA_REG_WIDTH, width);
			WriteReg(SVGA_REG_HEIGHT, height);
			WriteReg(SVGA_REG_BITS_PER_PIXEL, bpp);
			WriteReg(SVGA_REG_ENABLE, 1); 
			si->fbOffset = ReadReg(SVGA_REG_FB_OFFSET);
			si->bytesPerRow = ReadReg(SVGA_REG_BYTES_PER_LINE);
			ReadReg(SVGA_REG_DEPTH);
			ReadReg(SVGA_REG_PSEUDOCOLOR);
			ReadReg(SVGA_REG_RED_MASK);
			ReadReg(SVGA_REG_GREEN_MASK);
			ReadReg(SVGA_REG_BLUE_MASK);
	return 0;
}

#endif	// DEBUG_COMMANDS

#endif	// DEBUG_CMD_H
