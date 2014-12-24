//
//  TextBox.cpp
//  OpenGL_Timer_CPP
//
//  Created by Ran Bao on 4/27/13.
//  Copyright (c) 2013 Ran Bao. All rights reserved.
//

#include "TextBox.h"



NewTextBox::NewTextBox(){
	x_axis = y_axis = 0;
	font = NULL;

}

NewTextBox::NewTextBox(float x, float y, const float *fontColor, void *f){
	for (int i = 0; i < 3; i++) {
		color[i] = fontColor[i];
	}
	x_axis = x;
	y_axis = y;
	font = f;

}

NewTextBox::~NewTextBox(){

}

void NewTextBox::update(const std::string &text_to_display){
	text = text_to_display;
}

void NewTextBox::draw(){

	glPushMatrix();
	glColor3fv(color);
	glRasterPos2f(x_axis, y_axis);

	for (std::string::iterator it = text.begin(); it != text.end(); it++) {
		glutBitmapCharacter(font, *it);
	}
	glFlush();
	glPopMatrix();


}


