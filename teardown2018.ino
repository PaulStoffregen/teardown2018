
#include <OctoWS2811.h>
#include "animation.h"

// The display size and color to use
#define WIDTH  60
#define HEIGHT 32

// OctoWS2811 objects
const int ledsPerPin = WIDTH * HEIGHT / 8;
DMAMEM int displayMemory[ledsPerPin*6];
int drawingMemory[ledsPerPin*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerPin, displayMemory, drawingMemory, config);

// Animation
uint32_t FrameBufferMemory[WIDTH * HEIGHT];
AnimationFrameBuffer FrameBuffer(FrameBufferMemory, WIDTH, HEIGHT);
AnimationExpandingCircle circle1 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle2 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle3 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle4 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle5 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle6 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle7 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle8 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle9 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle10 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle11 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle12 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle13 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle14 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle15 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle16 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle17 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle18 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle19 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle20 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle21 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle22 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle23 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle24 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle25 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle26 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle27 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle28 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle29 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle30 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle31 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle32 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle33 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle34 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle35 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle36 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle37 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle38 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle39 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle40 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle41 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle42 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle43 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle44 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle45 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle46 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle47 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle48 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle49 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle50 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle51 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle52 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle53 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle54 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle55 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle56 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle57 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle58 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle59 = AnimationExpandingCircle(FrameBuffer);
AnimationExpandingCircle circle60 = AnimationExpandingCircle(FrameBuffer);

AnimationExpandingCircle *circle_list[] = {
	&circle1, &circle2, &circle3, &circle4, &circle5, &circle6, &circle7, &circle8,
	&circle9, &circle10, &circle11, &circle12, &circle13, &circle14, &circle15, &circle16,
	&circle17, &circle18, &circle19, &circle20, &circle21, &circle22, &circle23, &circle24,
	&circle25, &circle26, &circle27, &circle28, &circle29, &circle30, &circle31, &circle32,
	&circle33, &circle34, &circle35, &circle36, &circle37, &circle38, &circle39, &circle40,
	&circle41, &circle42, &circle43, &circle44, &circle45, &circle46, &circle47, &circle48,
	&circle49, &circle50, &circle51, &circle52, &circle53, &circle54, &circle55, &circle56,
	&circle57, &circle58, &circle59, &circle60
};


// Run setup once
void setup()
{
	Serial1.begin(38400);
	delay(10);
	// turn on the display
	leds.begin();
	leds.show();
}


void loop()
{
	static elapsedMicros usec=0;

	if (usec > 33333) {
		usec -= 33333;
		FrameBuffer.render();
		for (unsigned int y=0; y < HEIGHT; y++) {
			for (unsigned int x=0; x < WIDTH; x++) {
				leds.setPixel(xy(x, y), FrameBuffer.getPixelColor(x, y));
			}
		}
		leds.show();
	}
	bool newdata = false;
	int c;
	if (Serial.available()) {
		c = Serial.read();
		newdata = true;
	} else if (Serial1.available()) {
		c = Serial1.read();
		newdata = true;
	}
	if (newdata) {
		if (c == '0') {
			new_circle(0x70FF0000, 14.0);
		} else if (c == '1') {
			//Serial.printf("begin\n");
			//circle1.begin(12, 10, 0xFFFFC000);
			//circle2.begin(22, 13, 0x80FF0000);
			new_circle(0x40FFFFFF, 5.8);
		} else if (c == '2') {
			new_circle(0x600000FF, 7.2);
		} else if (c == '3') {
			new_circle(0x6000FF00, 7.2);
		} else if (c == '4') {
			new_circle(0x60FF9000, 5.2);
		} else if (c == 'a') {
			for (int i=0; i < 15; i++) {
				red_falling_circle(1);
			}
		} else if (c == 'b') {
			int x = WIDTH/2 + random(10) - 5;
			int y = HEIGHT/2 + random(6) - 3;
			for (int i=0; i < 12; i++) {
				green_startburst_circle(x, y);
			}
		} else if (c == 'c') {
			for (int i=0; i < 12; i++) {
				blue_shooting_circle();
			}
		} else if (c == 'A') {
			for (int i=0; i < 7; i++) {
				fading_circle(0x40E06000, 4.5); // orange
			}
		} else if (c == 'B') {
			for (int i=0; i < 7; i++) {
				fading_circle(0x408F8090, 4.5);
			}
		} else if (c == 'C') {
			for (int i=0; i < 7; i++) {
				fading_circle(0x4020F0C0, 4.5);
			}
		} else if (c == 'D') {
			for (int i=0; i < 7; i++) {
				fading_circle(0x4070FF00, 4.5);
			}
		} else if (c == 'E') {
			for (int i=0; i < 7; i++) {
				fading_circle(0x40FF0090, 4.5); // pink
			}


		} else {
			Serial.printf("char: %c\n", c);
		}

	}


}


AnimationExpandingCircle * get_unused_circle()
{
	unsigned int min_frames = 0xFFFFFFFF;
	AnimationExpandingCircle *min_circle = nullptr;
	unsigned int num = sizeof(circle_list) / sizeof(AnimationExpandingCircle *);

	for (unsigned int i=0; i < num; i++) {
		unsigned int frames = circle_list[i]->frames_remaining();
		if (frames == 0) return circle_list[i];
		if (frames < min_frames) {
			min_frames = frames;
			min_circle = circle_list[i];
		}
	}
	return min_circle;
}

int myrand(int n) {
	int sum=0;
	for (int i=0; i < n; i++) {
		sum += random(201) - 100;
	}
	return sum;
}

AnimationExpandingCircle * fading_circle(uint32_t color, float radius)
{
	AnimationExpandingCircle *circle = get_unused_circle();

	int margin = radius;
	if (margin < 0) margin = 0;
	float x = (float)(random((WIDTH - margin*2) * 100) + margin*100) * 0.01;
	float y = (float)(random((HEIGHT - margin*2) * 100) + margin*100) * 0.01;
	float duration = 0.5;
	circle->begin(x, y, color, duration);
	circle->radius = radius;
	circle->xinc = 0;
	circle->yinc = 0;
	circle->radius_inc_per_frame = -0.04;
	circle->alpha_inc = -((color >> 24) / circle->frame_end);
	return circle;
}

AnimationExpandingCircle * new_circle(uint32_t color, float radius)
{
	AnimationExpandingCircle *circle = get_unused_circle();

	int margin = radius * 0.25;
	if (margin < 0) margin = 0;
	float x = (float)(random((WIDTH - margin*2) * 100) + margin*100) * 0.01;
	float y = (float)(random((HEIGHT - margin*2) * 100) + margin*100) * 0.01;
	float duration = 0.4;
	if (radius > 10) duration += 0.2;
	circle->begin(x, y, color, duration);
	circle->radius = radius;
	circle->radius_inc_per_frame = -(radius - radius / 3.0) / (duration * 30.0);
	if (radius > 1.0 && radius < 10.0) {
		circle->xinc = (float)(myrand(7)) / (90.0 * radius);
		circle->yinc = (float)(myrand(7)) / (140.0 * radius);
	}
	return circle;
}

AnimationExpandingCircle * red_falling_circle(int region) // 0 to 100
{
	AnimationExpandingCircle *circle = get_unused_circle();

	float radius = 5.8;
	uint32_t color = 0xC0FF0000 | random(20) | (random(20) << 8);
	int margin = radius * 0.25;
	if (margin < 0) margin = 0;
	float x = (float)(random((WIDTH - margin*2) * 100) + margin*100) * 0.01;
	float y = random(80) * 0.1;
	float duration = 0.3;
	circle->begin(x, y, color, duration);
	circle->radius = radius;
	circle->radius_inc_per_frame = -(radius - radius / 9.0) / (duration * 30.0);
	if (radius > 1.0 && radius < 10.0) {
		circle->xinc = (float)(myrand(3)) / (790.0 * radius);
		circle->yinc = (float)(myrand(17)) / (40.0 * radius);
		if (circle->yinc < 0) circle->yinc *= -1.0;
	}
	return circle;
}

AnimationExpandingCircle * green_startburst_circle(int x, int y)
{
	AnimationExpandingCircle *circle = get_unused_circle();

	float radius = 3.8;
	uint32_t color = 0xC000FF00 | (random(20) << 16) | (random(20) << 0);
	int margin = radius * 0.25;
	if (margin < 0) margin = 0;
	float duration = 0.58;
	circle->begin(x, y, color, duration);
	circle->radius = radius;
	circle->radius_inc_per_frame = -(radius - radius / 4.0) / (duration * 30.0);
	if (radius > 1.0 && radius < 10.0) {
		circle->xinc = (float)(myrand(12)) / (40.0 * radius);
		circle->yinc = (float)(myrand(12)) / (40.0 * radius);
	}
	return circle;
}

AnimationExpandingCircle * blue_shooting_circle()
{
	AnimationExpandingCircle *circle = get_unused_circle();

	float radius = 4.8;
	uint32_t color = 0xC00000FF | (random(20) << 16) | (random(26) << 8);
	int margin = radius * 0.25;
	if (margin < 0) margin = 0;
	float duration = 0.58;
	circle->begin(WIDTH, HEIGHT/2, color, duration);
	circle->radius = radius;
	circle->radius_inc_per_frame = -(radius - radius / 4.0) / (duration * 30.0);
	if (radius > 1.0 && radius < 10.0) {
		circle->xinc = (float)(myrand(12)) / (12.0 * radius);
		if (circle->xinc > 0) circle->xinc *= -1.0;
		circle->xinc = circle->xinc - 2.0;
		circle->yinc = (float)(myrand(12)) / (50.0 * radius);
	}
	return circle;
}








// A simple xy() function to turn display matrix coordinates
// into the index numbers OctoWS2811 requires.  If your LEDs
// are arranged differently, edit this code...
unsigned int xy(unsigned int x, unsigned int y) {
  if ((y & 1) == 0) {
    // even numbered rows (0, 2, 4...) are left to right
    return y * WIDTH + x;
  } else {
    // odd numbered rows (1, 3, 5...) are right to left
    return y * WIDTH + WIDTH - 1 - x;
  }
}
