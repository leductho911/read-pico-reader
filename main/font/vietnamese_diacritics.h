/* SPDX-License-Identifier: LicenseRef-Kiikoread-Personal-Study-1.0
 * 中文：越南语带调字母分解、基础字符映射与声调/变音符光栅化合成。
 * English: Vietnamese accented letter decomposition, base character mapping, and diacritic raster synthesis.
 */
#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    VN_MOD_NONE = 0,
    VN_MOD_CIRCUMFLEX = 1,
    VN_MOD_BREVE = 2,
    VN_MOD_HORN = 3,
    VN_MOD_STROKE = 4,
} vn_mod_t;

typedef enum {
    VN_TONE_NONE = 0,
    VN_TONE_GRAVE = 1,
    VN_TONE_ACUTE = 2,
    VN_TONE_HOOK = 3,
    VN_TONE_TILDE = 4,
    VN_TONE_DOT = 5,
} vn_tone_t;

typedef struct {
    uint8_t base;
    uint8_t mod;
    uint8_t tone;
} vn_decomp_t;

static inline vn_decomp_t vietnamese_decompose(uint32_t cp) {
    switch (cp) {
        case 0x00C0: return (vn_decomp_t){'A', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00C1: return (vn_decomp_t){'A', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00C2: return (vn_decomp_t){'A', VN_MOD_CIRCUMFLEX, VN_TONE_NONE};
        case 0x00C3: return (vn_decomp_t){'A', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x00C8: return (vn_decomp_t){'E', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00C9: return (vn_decomp_t){'E', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00CA: return (vn_decomp_t){'E', VN_MOD_CIRCUMFLEX, VN_TONE_NONE};
        case 0x00CC: return (vn_decomp_t){'I', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00CD: return (vn_decomp_t){'I', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00D2: return (vn_decomp_t){'O', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00D3: return (vn_decomp_t){'O', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00D4: return (vn_decomp_t){'O', VN_MOD_CIRCUMFLEX, VN_TONE_NONE};
        case 0x00D5: return (vn_decomp_t){'O', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x00D9: return (vn_decomp_t){'U', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00DA: return (vn_decomp_t){'U', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00DD: return (vn_decomp_t){'Y', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00E0: return (vn_decomp_t){'a', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00E1: return (vn_decomp_t){'a', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00E2: return (vn_decomp_t){'a', VN_MOD_CIRCUMFLEX, VN_TONE_NONE};
        case 0x00E3: return (vn_decomp_t){'a', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x00E8: return (vn_decomp_t){'e', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00E9: return (vn_decomp_t){'e', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00EA: return (vn_decomp_t){'e', VN_MOD_CIRCUMFLEX, VN_TONE_NONE};
        case 0x00EC: return (vn_decomp_t){'i', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00ED: return (vn_decomp_t){'i', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00F2: return (vn_decomp_t){'o', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00F3: return (vn_decomp_t){'o', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00F4: return (vn_decomp_t){'o', VN_MOD_CIRCUMFLEX, VN_TONE_NONE};
        case 0x00F5: return (vn_decomp_t){'o', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x00F9: return (vn_decomp_t){'u', VN_MOD_NONE, VN_TONE_GRAVE};
        case 0x00FA: return (vn_decomp_t){'u', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x00FD: return (vn_decomp_t){'y', VN_MOD_NONE, VN_TONE_ACUTE};
        case 0x0102: return (vn_decomp_t){'A', VN_MOD_BREVE, VN_TONE_NONE};
        case 0x0103: return (vn_decomp_t){'a', VN_MOD_BREVE, VN_TONE_NONE};
        case 0x0110: return (vn_decomp_t){'D', VN_MOD_STROKE, VN_TONE_NONE};
        case 0x0111: return (vn_decomp_t){'d', VN_MOD_STROKE, VN_TONE_NONE};
        case 0x0128: return (vn_decomp_t){'I', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x0129: return (vn_decomp_t){'i', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x0168: return (vn_decomp_t){'U', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x0169: return (vn_decomp_t){'u', VN_MOD_NONE, VN_TONE_TILDE};
        case 0x01A0: return (vn_decomp_t){'O', VN_MOD_HORN, VN_TONE_NONE};
        case 0x01A1: return (vn_decomp_t){'o', VN_MOD_HORN, VN_TONE_NONE};
        case 0x01AF: return (vn_decomp_t){'U', VN_MOD_HORN, VN_TONE_NONE};
        case 0x01B0: return (vn_decomp_t){'u', VN_MOD_HORN, VN_TONE_NONE};
        default: break;
    }
    if (cp >= 0x1EA0 && cp <= 0x1EF9) {
        static const struct { uint8_t upper, lower, mod, tone; } s_ext[] = {
            {'A', 'a', VN_MOD_NONE,       VN_TONE_DOT},   /* 1EA0 Ạ/ạ */
            {'A', 'a', VN_MOD_NONE,       VN_TONE_HOOK},  /* 1EA2 Ả/ả */
            {'A', 'a', VN_MOD_CIRCUMFLEX, VN_TONE_ACUTE}, /* 1EA4 Ấ/ấ */
            {'A', 'a', VN_MOD_CIRCUMFLEX, VN_TONE_GRAVE}, /* 1EA6 Ầ/ầ */
            {'A', 'a', VN_MOD_CIRCUMFLEX, VN_TONE_HOOK},  /* 1EA8 Ẩ/ẩ */
            {'A', 'a', VN_MOD_CIRCUMFLEX, VN_TONE_TILDE}, /* 1EAA Ẫ/ẫ */
            {'A', 'a', VN_MOD_CIRCUMFLEX, VN_TONE_DOT},   /* 1EAC Ậ/ậ */
            {'A', 'a', VN_MOD_BREVE,      VN_TONE_ACUTE}, /* 1EAE Ắ/ắ */
            {'A', 'a', VN_MOD_BREVE,      VN_TONE_GRAVE}, /* 1EB0 Ằ/ằ */
            {'A', 'a', VN_MOD_BREVE,      VN_TONE_HOOK},  /* 1EB2 Ẳ/ẳ */
            {'A', 'a', VN_MOD_BREVE,      VN_TONE_TILDE}, /* 1EB4 Ẵ/ẵ */
            {'A', 'a', VN_MOD_BREVE,      VN_TONE_DOT},   /* 1EB6 Ặ/ặ */
            {'E', 'e', VN_MOD_NONE,       VN_TONE_DOT},   /* 1EB8 Ẹ/ẹ */
            {'E', 'e', VN_MOD_NONE,       VN_TONE_HOOK},  /* 1EBA Ẻ/ẻ */
            {'E', 'e', VN_MOD_NONE,       VN_TONE_TILDE}, /* 1EBC Ẽ/ẽ */
            {'E', 'e', VN_MOD_CIRCUMFLEX, VN_TONE_ACUTE}, /* 1EBE Ế/ế */
            {'E', 'e', VN_MOD_CIRCUMFLEX, VN_TONE_GRAVE}, /* 1EC0 Ề/ề */
            {'E', 'e', VN_MOD_CIRCUMFLEX, VN_TONE_HOOK},  /* 1EC2 Ể/ể */
            {'E', 'e', VN_MOD_CIRCUMFLEX, VN_TONE_TILDE}, /* 1EC4 Ễ/ễ */
            {'E', 'e', VN_MOD_CIRCUMFLEX, VN_TONE_DOT},   /* 1EC6 Ệ/ệ */
            {'I', 'i', VN_MOD_NONE,       VN_TONE_HOOK},  /* 1EC8 Ỉ/ỉ */
            {'I', 'i', VN_MOD_NONE,       VN_TONE_DOT},   /* 1ECA Ị/ị */
            {'O', 'o', VN_MOD_NONE,       VN_TONE_DOT},   /* 1ECC Ọ/ọ */
            {'O', 'o', VN_MOD_NONE,       VN_TONE_HOOK},  /* 1ECE Ỏ/ỏ */
            {'O', 'o', VN_MOD_CIRCUMFLEX, VN_TONE_ACUTE}, /* 1ED0 Ố/ố */
            {'O', 'o', VN_MOD_CIRCUMFLEX, VN_TONE_GRAVE}, /* 1ED2 Ồ/ồ */
            {'O', 'o', VN_MOD_CIRCUMFLEX, VN_TONE_HOOK},  /* 1ED4 Ổ/ổ */
            {'O', 'o', VN_MOD_CIRCUMFLEX, VN_TONE_TILDE}, /* 1ED6 Ỗ/ỗ */
            {'O', 'o', VN_MOD_CIRCUMFLEX, VN_TONE_DOT},   /* 1ED8 Ộ/ộ */
            {'O', 'o', VN_MOD_HORN,       VN_TONE_ACUTE}, /* 1EDA Ớ/ớ */
            {'O', 'o', VN_MOD_HORN,       VN_TONE_GRAVE}, /* 1EDC Ờ/ờ */
            {'O', 'o', VN_MOD_HORN,       VN_TONE_HOOK},  /* 1EDE Ở/ở */
            {'O', 'o', VN_MOD_HORN,       VN_TONE_TILDE}, /* 1EE0 Ỡ/ỡ */
            {'O', 'o', VN_MOD_HORN,       VN_TONE_DOT},   /* 1EE2 Ợ/ợ */
            {'U', 'u', VN_MOD_NONE,       VN_TONE_DOT},   /* 1EE4 Ụ/ụ */
            {'U', 'u', VN_MOD_NONE,       VN_TONE_HOOK},  /* 1EE6 Ủ/ủ */
            {'U', 'u', VN_MOD_HORN,       VN_TONE_ACUTE}, /* 1EE8 Ứ/ứ */
            {'U', 'u', VN_MOD_HORN,       VN_TONE_GRAVE}, /* 1EEA Ừ/ừ */
            {'U', 'u', VN_MOD_HORN,       VN_TONE_HOOK},  /* 1EEC Ử/ử */
            {'U', 'u', VN_MOD_HORN,       VN_TONE_TILDE}, /* 1EEE Ữ/ữ */
            {'U', 'u', VN_MOD_HORN,       VN_TONE_DOT},   /* 1EF0 Ự/ự */
            {'Y', 'y', VN_MOD_NONE,       VN_TONE_GRAVE}, /* 1EF2 Ỳ/ỳ */
            {'Y', 'y', VN_MOD_NONE,       VN_TONE_DOT},   /* 1EF4 Ỵ/ỵ */
            {'Y', 'y', VN_MOD_NONE,       VN_TONE_HOOK},  /* 1EF6 Ỷ/ỷ */
            {'Y', 'y', VN_MOD_NONE,       VN_TONE_TILDE}, /* 1EF8 Ỹ/ỹ */
        };
        uint32_t idx = (cp - 0x1EA0) >> 1;
        uint8_t base = (cp & 1u) ? s_ext[idx].lower : s_ext[idx].upper;
        return (vn_decomp_t){base, s_ext[idx].mod, s_ext[idx].tone};
    }
    return (vn_decomp_t){0, 0, 0};
}

static inline uint32_t vietnamese_base_codepoint(uint32_t cp) {
    return vietnamese_decompose(cp).base;
}

static inline void vietnamese_pad_bounds(
    uint32_t cp, int px, int *x0, int *y0, int *x1, int *y1
) {
    vn_decomp_t d = vietnamese_decompose(cp);
    if (!d.base) return;
    bool upper_tone = d.tone >= VN_TONE_GRAVE && d.tone <= VN_TONE_TILDE;
    if ((d.mod == VN_MOD_CIRCUMFLEX || d.mod == VN_MOD_BREVE) && upper_tone) {
        *y0 -= (int)(0.38f * (float)px) + 5;
    } else if (d.mod == VN_MOD_CIRCUMFLEX || d.mod == VN_MOD_BREVE || upper_tone) {
        *y0 -= (int)(0.26f * (float)px) + 4;
    } else if (d.mod == VN_MOD_HORN) {
        *y0 -= (int)(0.16f * (float)px) + 3;
    }
    if (d.tone == VN_TONE_DOT) {
        *y1 += (int)(0.20f * (float)px) + 4;
    }
    if (d.mod == VN_MOD_HORN || d.mod == VN_MOD_STROKE) {
        *x0 -= (int)(0.16f * (float)px) + 3;
        *x1 += (int)(0.20f * (float)px) + 3;
    } else {
        *x0 -= (int)(0.12f * (float)px) + 2;
        *x1 += (int)(0.12f * (float)px) + 2;
    }
}

static inline void vn_put_seg(
    uint8_t *bmp, int w, int h, int x0, int y0,
    float ax, float ay, float bx, float by, float radius
) {
    float min_x = (ax < bx ? ax : bx) - radius - 1.2f;
    float max_x = (ax > bx ? ax : bx) + radius + 1.2f;
    float min_y = (ay < by ? ay : by) - radius - 1.2f;
    float max_y = (ay > by ? ay : by) + radius + 1.2f;
    int ix0 = (int)floorf(min_x) - x0;
    int ix1 = (int)ceilf(max_x) - x0;
    int iy0 = (int)floorf(min_y) - y0;
    int iy1 = (int)ceilf(max_y) - y0;
    if (ix0 < 0) ix0 = 0;
    if (iy0 < 0) iy0 = 0;
    if (ix1 >= w) ix1 = w - 1;
    if (iy1 >= h) iy1 = h - 1;
    float vx = bx - ax, vy = by - ay;
    float len2 = vx * vx + vy * vy;
    for (int iy = iy0; iy <= iy1; ++iy) {
        float py = (float)(iy + y0) + 0.5f;
        for (int ix = ix0; ix <= ix1; ++ix) {
            float px = (float)(ix + x0) + 0.5f;
            float t = len2 > 1e-4f ? ((px - ax) * vx + (py - ay) * vy) / len2 : 0.0f;
            if (t < 0.0f) t = 0.0f;
            else if (t > 1.0f) t = 1.0f;
            float dx = px - (ax + t * vx);
            float dy = py - (ay + t * vy);
            float dist = sqrtf(dx * dx + dy * dy);
            float cov = radius + 0.55f - dist;
            if (cov <= 0.0f) continue;
            if (cov > 1.0f) cov = 1.0f;
            uint8_t alpha = (uint8_t)(cov * 255.0f + 0.5f);
            if (alpha > bmp[iy * w + ix]) bmp[iy * w + ix] = alpha;
        }
    }
}

static inline void vietnamese_draw_diacritics(
    uint32_t cp, int px, int x0, int y0, int bx0, int by0, int bx1, int by1,
    uint8_t *bmp, int w, int h
) {
    vn_decomp_t d = vietnamese_decompose(cp);
    if (!d.base || !bmp || w <= 0 || h <= 0) return;

    float bw = (float)(bx1 - bx0);
    float bh = (float)(by1 - by0);
    if (bw < 1.0f || bh < 1.0f) return;

    /* For lowercase 'i' with an upper tone (ì, í, ĩ, ỉ), clear the tittle so the tone sits cleanly. */
    int eff_by0 = by0;
    if (d.base == 'i' && d.tone >= VN_TONE_GRAVE && d.tone <= VN_TONE_TILDE) {
        int cut_y = by0 + (int)lroundf(0.27f * bh);
        for (int gy = by0; gy <= cut_y; ++gy) {
            int iy = gy - y0;
            if (iy < 0 || iy >= h) continue;
            for (int gx = bx0; gx < bx1; ++gx) {
                int ix = gx - x0;
                if (ix >= 0 && ix < w) bmp[iy * w + ix] = 0;
            }
        }
        eff_by0 = cut_y;
    }

    float cx = 0.5f * (float)(bx0 + bx1);
    float sw = (float)px * 0.075f;
    if (sw < 1.3f) sw = 1.3f;
    float r = 0.5f * sw;

    float mod_top = (float)eff_by0;
    if (d.mod == VN_MOD_STROKE) {
        if (d.base == 'D') {
            float sy = (float)by0 + 0.48f * bh;
            vn_put_seg(bmp, w, h, x0, y0, (float)bx0 - 0.10f * bw, sy, (float)bx0 + 0.54f * bw, sy, r);
        } else {
            float sy = (float)by0 + 0.24f * bh;
            vn_put_seg(bmp, w, h, x0, y0, (float)bx0 + 0.25f * bw, sy, (float)bx1 + 0.12f * bw, sy, r);
        }
    } else if (d.mod == VN_MOD_HORN) {
        float hx0 = (float)bx1 - 0.10f * bw;
        float hy0 = (float)by0 + 0.16f * bh;
        float hx1 = (float)bx1 + 0.13f * bw;
        float hy1 = (float)by0 - 0.02f * bh;
        float hx2 = (float)bx1 + 0.06f * bw;
        float hy2 = (float)by0 - 0.14f * bh - 0.8f;
        vn_put_seg(bmp, w, h, x0, y0, hx0, hy0, hx1, hy1, r * 0.92f);
        vn_put_seg(bmp, w, h, x0, y0, hx1, hy1, hx2, hy2, r * 0.92f);
    } else if (d.mod == VN_MOD_CIRCUMFLEX) {
        float hw = 0.29f * bw;
        if (hw < 2.2f) hw = 2.2f;
        float cy_bot = (float)eff_by0 - 0.06f * (float)px - 0.7f;
        float cy_top = cy_bot - 0.13f * (float)px - 1.2f;
        vn_put_seg(bmp, w, h, x0, y0, cx - hw, cy_bot, cx, cy_top, r * 0.92f);
        vn_put_seg(bmp, w, h, x0, y0, cx, cy_top, cx + hw, cy_bot, r * 0.92f);
        mod_top = cy_top;
    } else if (d.mod == VN_MOD_BREVE) {
        float hw = 0.29f * bw;
        if (hw < 2.2f) hw = 2.2f;
        float cy_bot = (float)eff_by0 - 0.06f * (float)px - 0.7f;
        float cy_top = cy_bot - 0.12f * (float)px - 1.1f;
        vn_put_seg(bmp, w, h, x0, y0, cx - hw, cy_top, cx - 0.42f * hw, cy_bot, r * 0.90f);
        vn_put_seg(bmp, w, h, x0, y0, cx - 0.42f * hw, cy_bot, cx + 0.42f * hw, cy_bot, r * 0.90f);
        vn_put_seg(bmp, w, h, x0, y0, cx + 0.42f * hw, cy_bot, cx + hw, cy_top, r * 0.90f);
        mod_top = cy_top;
    }

    if (d.tone == VN_TONE_DOT) {
        float dy = (float)by1 + 0.11f * (float)px + 1.4f;
        vn_put_seg(bmp, w, h, x0, y0, cx, dy, cx, dy, r * 1.25f);
    } else if (d.tone >= VN_TONE_GRAVE && d.tone <= VN_TONE_TILDE) {
        float ty_bot = mod_top - 0.06f * (float)px - 0.8f;
        float ty_top = ty_bot - 0.13f * (float)px - 1.1f;
        float tcx = cx;
        if (d.mod == VN_MOD_CIRCUMFLEX) {
            ty_bot = mod_top - 0.5f;
            ty_top = ty_bot - 0.11f * (float)px - 1.0f;
            if (d.tone == VN_TONE_ACUTE || d.tone == VN_TONE_HOOK) tcx += 0.12f * bw;
            else if (d.tone == VN_TONE_GRAVE) tcx -= 0.12f * bw;
        } else if (d.mod == VN_MOD_BREVE) {
            ty_bot = mod_top - 0.3f;
            ty_top = ty_bot - 0.11f * (float)px - 1.0f;
        }
        float tw = 0.22f * bw;
        if (tw < 1.8f) tw = 1.8f;
        if (d.tone == VN_TONE_GRAVE) {
            vn_put_seg(bmp, w, h, x0, y0, tcx - 0.65f * tw, ty_top, tcx + 0.45f * tw, ty_bot, r * 0.90f);
        } else if (d.tone == VN_TONE_ACUTE) {
            vn_put_seg(bmp, w, h, x0, y0, tcx + 0.65f * tw, ty_top, tcx - 0.45f * tw, ty_bot, r * 0.90f);
        } else if (d.tone == VN_TONE_HOOK) {
            float ym = 0.5f * (ty_top + ty_bot);
            vn_put_seg(bmp, w, h, x0, y0, tcx - 0.35f * tw, ty_top + 0.25f * (ty_bot - ty_top), tcx + 0.45f * tw, ty_top, r * 0.82f);
            vn_put_seg(bmp, w, h, x0, y0, tcx + 0.45f * tw, ty_top, tcx + 0.50f * tw, ym, r * 0.82f);
            vn_put_seg(bmp, w, h, x0, y0, tcx + 0.50f * tw, ym, tcx - 0.10f * tw, ty_bot, r * 0.82f);
        } else if (d.tone == VN_TONE_TILDE) {
            float hw = 1.05f * tw;
            if (hw < 2.2f) hw = 2.2f;
            vn_put_seg(bmp, w, h, x0, y0, tcx - hw, ty_bot, tcx - 0.33f * hw, ty_top, r * 0.82f);
            vn_put_seg(bmp, w, h, x0, y0, tcx - 0.33f * hw, ty_top, tcx + 0.33f * hw, ty_bot, r * 0.82f);
            vn_put_seg(bmp, w, h, x0, y0, tcx + 0.33f * hw, ty_bot, tcx + hw, ty_top, r * 0.82f);
        }
    }
}

