#include <Arduino.h>

//#define RENDER_WIDTH  96
//#define RENDER_HEIGHT 60

class Animation;

class AnimationFrameBuffer {
public:
	constexpr AnimationFrameBuffer(uint32_t *pixelbuf, unsigned int w, unsigned int h) :
		width(w), height(h), pixels(pixelbuf) {
	};
	void render();

	int width;
	int height;
	uint32_t *pixels; // always 32bit RGB (alpha unused)

	uint32_t getPixelColor(int x, int y) {
		if (x < 0 || x >= width) return 0;
		if (y < 0 || y >= height) return 0;
		return pixels[y * width + x];
	}

	void setPixelColor(int x, int y, uint32_t color) {
		if (x < 0 || x >= width) return;
		if (y < 0 || y >= height) return;
		pixels[y * width + x] = color | 0xFF000000;
	}

	void setPixelColorAlpha(int x, int y, uint32_t color) {
		if (x < 0 || x >= width) return;
		if (y < 0 || y >= height) return;
		uint32_t alpha = color >> 24;
		if (alpha == 0) return;
		uint32_t *pix = &pixels[y * width + x];
		if (alpha == 0xFF) {
			*pix = color;
			return;
		}
		uint32_t nalpha = 255 - alpha;
		uint32_t old = *pix;
		uint32_t r = (((old >> 16) & 255) * nalpha + ((color >> 16) & 255) * alpha) >> 8;
		uint32_t g = (((old >> 8) & 255) * nalpha + ((color >> 8) & 255) * alpha) >> 8;
		uint32_t b = (((old >> 0) & 255) * nalpha + ((color >> 0) & 255) * alpha) >> 8;
		*pix = (r << 16) | (g << 8) | b;
	}

	//uint32_t buffer[RENDER_WIDTH * RENDER_HEIGHT] = {0};

	Animation *list = nullptr;
};



class Animation {
public:
	constexpr Animation(AnimationFrameBuffer &fb) : framebuf(fb) {
	}

	AnimationFrameBuffer &framebuf;

	Animation *prev = nullptr;
	Animation *next = nullptr;
	//int z = 0;

	bool active = false;
	virtual void render();

	void add(int zorder) {
		//z = zorder; // TODO: implement z order

		if (framebuf.list == nullptr) {
			next = nullptr;
			prev = nullptr;
			framebuf.list = this;
		} else {
			Animation *last; // add at end of list: newest draw "on top" of older
			for (last=framebuf.list; last->next; last = last->next) ;
			last->next = this;
			prev = last;
			next = nullptr;
		}
		active = true;
	}
	void end() {
		if (!active) return;
		active = false;
		if (prev) {
			prev->next = next;
		} else {
			framebuf.list = next;
		}
		if (next) next->prev = prev;
	}
};

class AnimationSquare : public Animation {
public:
	virtual void render();


};

class AnimationExpandingCircle : public Animation {
public:
	constexpr AnimationExpandingCircle(AnimationFrameBuffer &fb) : Animation(fb) {
	}
	virtual void render();
	void begin(float x, float y, uint32_t c, float duration=0.3f);

	float xpos=0;
	float ypos=0;
	float xinc=0;
	float yinc=0;
	float radius=2.2;
	float radius_inc_per_frame=0;
	unsigned int frame_count=0;
	unsigned int frame_end=0;
	uint32_t color=0;
	int alpha_inc=0;

	unsigned int frames_remaining() {
		if (!active) return 0;
		if (frame_count >= frame_end) return 0;
		return frame_end - frame_count;
	}

};

