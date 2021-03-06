/*-
 * Copyright (c) 2017 Frederic Culot <culot@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <string>
#include <curses.h>

namespace nenet {
namespace gfx {

struct Point {
 public:
  Point(int y, int x) : y_(y), x_(x) {}
  int  x() const {return x_;}
  int  y() const {return y_;}
  bool isNull() const {return y_ == 0 && x_ == 0;}

private:
  int y_ {0};
  int x_ {0};
};

struct Size {
public:
  void setWidth(int width) {width_ = width;}
  void setHeight(int height) {height_ = height;}
  void reset() {height_ = 0; width_ = 0;}
  int  width() const {return width_;}
  int  height() const {return height_;}
  bool isNull() const {return width_ == 0 && height_ == 0;}

  bool operator==(const Size& other) const {
    return height() == other.height() && width() == other.width();
  }
  bool operator!=(const Size& other) const {return !(*this == other);}

private:
  int width_  {0};
  int height_ {0};
};


struct Style {

  enum class Alignment {
    left,
    center,
    right
  };

  enum Color {
    none,
    black,
    cyan,
    magenta,
    red,
    yellow,
    blue,
    cyanOnBlue
  };

  bool      bold      {false};
  bool      reverse   {false};
  bool      underline {false};
  bool      highlight {false};
  bool      borders   {false};
  Alignment align     {Alignment::left};
  Color     color     {Color::none};

  int    cursesAttrs() const {
    int s = A_NORMAL;
    s |= bold ? A_BOLD : 0;
    s |= reverse ? A_REVERSE : 0;
    s |= underline ? A_UNDERLINE : 0;
    s |= highlight ? A_STANDOUT : 0;
    return s;
  };
};


class Gfx {
 public:
  static Gfx&  instance() {static Gfx instance_; return instance_;}
  void         update();
  void         print(int c, const Point& pos, const Style& style = {});
  void         print(const std::string& str, const Point& pos, const Style& style = {});

 private:
  Gfx() {init();}
  ~Gfx() {terminate();}
  Gfx(const Gfx&) = delete;
  void operator=(const Gfx&) = delete;

  void         init();
  void         terminate();
};

}
}
