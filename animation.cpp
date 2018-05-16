/* LED Visualization & Animation Demo
 * Copyright (c) 2018, Paul Stoffregen, paul@pjrc.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "animation.h"


void AnimationExpandingCircle::begin(float x, float y, uint32_t c, float duration)
{
	end();
	xpos = x;
	ypos = y;
	//xinc = 0.8;
	//yinc = 0.25;
	xinc = 0;
	yinc = 0;
	duration *= 30.0; // seconds to frames
	radius = 7.2;
	radius_inc_per_frame = -6.0 / duration;
	frame_count = 0;
	frame_end = duration;
	color = c;
	alpha_inc = 0;
	add(0);
}


void AnimationExpandingCircle::render()
{
	//Serial.printf("AnimationExpandingCircle render, frame=%d, end=%d, color=%X\n",
		//frame_count, frame_end, color);

	float radius_sq = radius * radius;
	unsigned int pixelcount=0;
	for (int y=0; y < framebuf.height; y++) {
		for (int x=0; x < framebuf.width; x++) {
			float xr = x - xpos;
			float yr = y - ypos;
			float r_sq = xr * xr + yr * yr;
			if (r_sq <= radius_sq) {
				framebuf.setPixelColorAlpha(x, y, color);
				//Serial.printf("  pixel: x=%d, y=%d\n", x, y);
				pixelcount++;
			}
		}
	}
	//Serial.printf("  pixelcount=%u\n", pixelcount);
	radius += radius_inc_per_frame;
	xpos += xinc;
	ypos += yinc;
	if (alpha_inc < 0) {
		uint32_t alpha = (color >> 24);
		uint32_t new_alpha = alpha + alpha_inc;
		if (new_alpha > alpha) new_alpha = 0;
		if (new_alpha > 255) new_alpha = 255;
		color = (new_alpha << 24) | (color & 0xFFFFFF);
	}
	if (++frame_count >= frame_end) {
		//Serial.printf("  end animation\n");
		end();
	}
}




void AnimationFrameBuffer::render()
{
	unsigned int i, n;

	n = width * height;
	// clear the frame buffer
	for (i=0; i < n; i++) {
		pixels[i] = 0;
	}
	// render each active animation
	Animation *a = list;
	while (a) {
		Animation *next = a->next;
		a->render();
		a = next;
	}
}
