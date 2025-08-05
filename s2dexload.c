#include <ultra64.h>
#include "s2dex.h"

extern u8  mySpriteTexture[];
extern u16 mySpriteTLUT[];

gfxObjectMtx objMtx;
Gfx *glistp;

ObjectRectR sprite_obj = {
    .image = {
        .imagePtr  = mySpriteTexture,
        .tmem      = 0,
        .s         = 32,
        .t         = 32,
        .siz       = G_IM_SIZ_8b,
        .fmt       = G_IM_FMT_CI,
        .palette   = 0,
        .tlutMode  = G_TT_RGBA16,
        .flip      = 0
    },
    .scaleW = 1 << 10,
    .scaleH = 1 << 10,
    .ulx = 100,
    .uly = 100,
    .lrx = 132,
    .lry = 132,
};

Gfx sprite_dl[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(mySpriteTLUT),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 1, mySpriteTexture),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE,
                0, G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                   G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, (32*32)-1, CALC_DXT(32, G_IM_SIZ_8b_BYTES)),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE,
                0, G_TX_WRAP, 5, G_TX_NOLOD,
                   G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32-1)<<G_TEXTURE_IMAGE_FRAC, (32-1)<<G_TEXTURE_IMAGE_FRAC),
    gsSPObjRenderMode(G_OBJRM_ANTIALIAS | G_OBJRM_BILERP),
    gsSPObjMatrix(&objMtx),
    gsSPObjRectangleR(&sprite_obj),
    gsSPEndDisplayList(),
};

void setup_rsp_rdp(void) {
    gSPSegment(glistp++, 0x00, 0);
    gSPDisplayList(glistp++, rspinit_dl);
    gSPDisplayList(glistp++, rdpinit_dl);
    gSPDisplayList(glistp++, gspS2DEX_fifo);
}

void draw_frame(void) {
    setup_rsp_rdp();
    gSPDisplayList(glistp++, sprite_dl);
}
