//
//  TextBox.h
//  OpenGL_Timer_CPP
//
//  Created by Ran Bao on 4/27/13.
//  Copyright (c) 2013 Ran Bao. All rights reserved.
//

#ifndef __OpenGL_Timer_CPP__TextBox__
#define __OpenGL_Timer_CPP__TextBox__

#include <iostream>
#include <GL/freeglut.h>
#include "GLColor.h"


class NewTextBox {
	void *font;
	std::string text;
	float x_axis, y_axis;
	float color[3];
public:
	NewTextBox();
	NewTextBox(float x, float y, const float *fontColor = GLColor::GL_WHITE_COLOR,
		void *f = GLUT_BITMAP_HELVETICA_18);
	~NewTextBox();
	void update(const std::string &text_to_display);
	void draw();
	void diag_info();
};

#endif /* defined(__OpenGL_Timer_CPP__TextBox__) */
