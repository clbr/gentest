#include <genesis.h>
#include <sram.h>
#include "files.h"

static const u16 pal[16] = {
	RGB24_TO_VDPCOLOR(0x1a1a1a),
	RGB24_TO_VDPCOLOR(0xffffff),
	RGB24_TO_VDPCOLOR(0x181818),
	RGB24_TO_VDPCOLOR(0x4f4f4f),
	RGB24_TO_VDPCOLOR(0x232323),
	RGB24_TO_VDPCOLOR(0x1b1b1b),
	RGB24_TO_VDPCOLOR(0x686868),
	RGB24_TO_VDPCOLOR(0x989898),
	RGB24_TO_VDPCOLOR(0x0d0d0d),
	RGB24_TO_VDPCOLOR(0x191919),
	RGB24_TO_VDPCOLOR(0x383838),
	RGB24_TO_VDPCOLOR(0x141414),
	RGB24_TO_VDPCOLOR(0x030303),
	RGB24_TO_VDPCOLOR(0x080808),
	RGB24_TO_VDPCOLOR(0xf0f0f0),
	RGB24_TO_VDPCOLOR(0x171717),
};

static const TileSet * tiles[] = {
	&ani_000_png,
	&ani_001_png,
	&ani_002_png,
	&ani_003_png,
	&ani_004_png,
	&ani_005_png,
	&ani_006_png,
	&ani_007_png,
	&ani_008_png,
	&ani_009_png,
	&ani_010_png,
	&ani_011_png,
	&ani_012_png,
	&ani_013_png,
	&ani_014_png,
	&ani_015_png,
	&ani_016_png,
	&ani_017_png,
	&ani_018_png,
	&ani_019_png,
	&ani_020_png,
	&ani_021_png,
	&ani_022_png,
	&ani_023_png,
	&ani_024_png,
	&ani_025_png,
	&ani_026_png,
	&ani_027_png,
	&ani_028_png,
	&ani_029_png,
	&ani_030_png,
	&ani_031_png,
	&ani_032_png,
	&ani_033_png,
	&ani_034_png,
	&ani_035_png,
	&ani_036_png,
	&ani_037_png,
	&ani_038_png,
	&ani_039_png,
	&ani_040_png,
	&ani_041_png,
	&ani_042_png,
	&ani_043_png,
	&ani_044_png,
	&ani_045_png,
	&ani_046_png,
	&ani_047_png,
	&ani_048_png,
	&ani_049_png,
	&ani_050_png,
	&ani_051_png,
	&ani_052_png,
	&ani_053_png,
	&ani_054_png,
	&ani_055_png,
	&ani_056_png,
	&ani_057_png,
	&ani_058_png,
	&ani_059_png,
	&ani_060_png,
	&ani_061_png,
	&ani_062_png,
	&ani_063_png,
	&ani_064_png,
	&ani_065_png,
	&ani_066_png,
	&ani_067_png,
	&ani_068_png,
	&ani_069_png,
	&ani_070_png,
	&ani_071_png,
	&ani_072_png,
	&ani_073_png,
	&ani_074_png,
	&ani_075_png,
	&ani_076_png,
	&ani_077_png,
	&ani_078_png,
	&ani_079_png,
	&ani_080_png,
	&ani_081_png,
	&ani_082_png,
	&ani_083_png,
	&ani_084_png,
	&ani_085_png,
	&ani_086_png,
	&ani_087_png,
	&ani_088_png,
	&ani_089_png,
};

int main() {

	SRAM_disable();

	Z80_init();
	Z80_loadDriver(Z80_DRIVER_4PCM_ENV, 1);

	u8 frame = 0, tick = 0;

	SYS_disableInts();
	VDP_setEnable(0);

	VDP_setScreenWidth256();
	VDP_clearPlan(VDP_PLAN_A, 1);
	VDP_clearPlan(VDP_PLAN_B, 1);

	VDP_setPaletteColors(0, (u16 *) pal, 16);

	VDP_setPaletteColor(31, 0xfff);
	VDP_setTextPalette(1);

	VDP_drawText("Music by Plastic3, cc by-sa", 1, 1);

	u8 x, y, i;
	i = 0;
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 15; x++) {
			VDP_setTileMapXY(VDP_PLAN_A,
						TILE_ATTR_FULL(0, 0, 0, 0, TILE_USERINDEX + i++),
						x + 8, y + 10);
		}
	}

	VDP_setEnable(1);
	SYS_enableInts();

	while (1) {
		VDP_waitVSync();

		if (tick >= 5) {
			tick = 0;

			// Load the next frame
			VDP_loadTileSet(tiles[frame], TILE_USERINDEX, 1);

			frame++;
			frame %= 90;
		}

		tick++;
	}

	return 0;
}
