#include "DMD2.h"

DMD_TextBox::DMD_TextBox(DMDFrame &dmd, int left, int top, int width, int height) :
  dmd(dmd),
  inverted(false),
  left(left),
  top(top),
  width(width),
  height(height),
  cur_x(0),
  cur_y(0),
  pending_newline(false)
{
}

size_t DMD_TextBox::write(uint8_t character) {
  struct FontHeader header;
  memcpy_P(&header, (void *)this->dmd.font, sizeof(FontHeader));
  uint8_t rowHeight = header.height+1;

  if(width == 0)
    width = dmd.width - left;
  if(height == 0)
    height = dmd.height - top;

  uint8_t char_width = dmd.charWidth(character) + 1;
  while((cur_x > 0 && cur_x + char_width >= this->width) || pending_newline) { // Need to wrap to new line
    if (height >= rowHeight*2) { // Can scroll
      cur_y += rowHeight;
      cur_x = 0;
      if(cur_y + rowHeight > height) { // Scroll
 // int delta = cur_y + rowHeight - height; // the amount that it's over by
      }
    } else if(pending_newline) { // No room, so just clear display
      clear();
    } else { // Scroll characters horizontally
      int scroll_by = char_width - (this->width - cur_x - 1);
      scrollX(-scroll_by);
    }
    pending_newline = false;
  }

  if(character == '\n') {
    pending_newline = true;
    // clear the rest of the line after the current cursor position,
    // this allows you to then use reset() and do a flicker-free redraw
    dmd.drawFilledBox(cur_x+left,cur_y+top,left+width,cur_y+top+rowHeight, inverted ? GRAPHICS_ON : GRAPHICS_OFF);
  }

  dmd.drawChar(cur_x+left,cur_y+top,character, inverted ? GRAPHICS_OFF : GRAPHICS_ON);
  cur_x += char_width;
  return 1;
}

void DMD_TextBox::scrollY(int scrollBy) {
  if(abs(scrollBy) >= height) { // scrolling over the whole display
    // scrolling will erase everything
    dmd.drawFilledBox(left, top, left+width-1, top+height-1, inverted ? GRAPHICS_ON : GRAPHICS_OFF);
  }
  else if(scrollBy < 0) { // Scroll up
    dmd.movePixels(left, top - scrollBy, left, top, width, height + scrollBy);
  }
  else if(scrollBy > 0) { // Scroll down
    dmd.movePixels(left, top, left, top + scrollBy, width, height - scrollBy);
  }

  cur_y += scrollBy;
  while(cur_y < 0)
    cur_y += height;
  while(cur_y > height)
    cur_y -= height;
}


void DMD_TextBox::scrollX(int scrollBy) {
  if(abs(scrollBy) >= width) { // scrolling over the whole display!
    // scrolling will erase everything
    dmd.drawFilledBox(left, top, left+width-1, top+height-1, inverted ? GRAPHICS_ON : GRAPHICS_OFF);
  }
  else if(scrollBy < 0) { // Scroll left
    dmd.movePixels(left-scrollBy, top, left, top, width + scrollBy, height);
  }
  else { // Scroll right
    dmd.movePixels(left, top, left+scrollBy, top, width - scrollBy, height);
  }

  cur_x += scrollBy;
  while(cur_x < 0)
    cur_x += width;
  while(cur_x > width)
    cur_x -= width;
}

void DMD_TextBox::clear() {
  this->reset();

  dmd.drawFilledBox(left,top,left+width,top+height,inverted ? GRAPHICS_ON : GRAPHICS_OFF);
}

void DMD_TextBox::reset() {
  cur_x = 0;
  cur_y = 0;
  pending_newline = false;
}