//
//  GLShader.hpp
//  openGLDoom
//
//  Created by Виктор Снесаревский on 08.05.17.
//  Copyright © 2017 Виктор Снесаревский. All rights reserved.
//

#ifndef GLShader_hpp
#define GLShader_hpp

#include <stdio.h>
#include "GL/glew.h"

GLuint LoadShader(const char *vertex_path, const char *fragment_path);

#endif /* GLShader_hpp */
