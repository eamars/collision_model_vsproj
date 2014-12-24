//
//  GLColor.h
//  OpenGL_Timer_CPP
//
//  Created by Ran Bao on 4/27/13.
//  Copyright (c) 2013 Ran Bao. All rights reserved.
//

#ifndef OpenGL_Timer_CPP_GLColor_h
#define OpenGL_Timer_CPP_GLColor_h


namespace GLColor {
	const float GL_RED_COLOR[] = { 1, 0, 0 };
	const float GL_GREEN_COLOR[] = { 0, 1, 0 };
	const float GL_BLUE_COLOR[] = { 0, 0, 1 };
	const float GL_YELLOW_COLOR[] = { 1, 1, 0 };
	const float GL_WHITE_COLOR[] = { 1, 1, 1 };
	const float GL_PURPLE_COLOR[] = { 1, 0, 1 };
	const float GL_CYAN_COLOR[] = { 0, 1, 1 };
	const float GL_BLACK_COLOR[] = { 0, 0, 0 };

	const float GLMakeColor(float r, float b, float g);
}

#endif
