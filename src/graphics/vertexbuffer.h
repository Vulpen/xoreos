/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  A vertex buffer.
 */

#ifndef GRAPHICS_VERTEXBUFFER_H
#define GRAPHICS_VERTEXBUFFER_H

#include <vector>

#include "graphics/types.h"

namespace Graphics {

/**  Vertex attribute data index enum, hardcoded for now */
enum VertexAttribIdEnum {
	VPOSITION = 0, ///< Vertex position
	VNORMAL,       ///< Vertex normal
	VCOLOR,        ///< Vertex color
	VTCOORD        ///< Vertex texture coordinates, VTCOORDi = VTCOORD + i
};

/**  Generic vertex attribute data */
struct VertexAttrib {
	GLuint index;          ///< Index of the vertex attribute (see VertexAttribIdEnum)
	GLint size;            ///< Number of components per vertex attribute, must be 1, 2, 3, 4
	GLenum type;           ///< Data type of each attribute component in the array
	GLsizei stride;        ///< Byte offset between consecutive vertex attributes
	const GLvoid *pointer; ///< Offset of the first component of the first generic vertex attribute
};

/** Vertex data layout */
typedef std::vector<VertexAttrib> VertexDecl;

/** Buffer containing vertex data */
class VertexBuffer {
public:
	VertexBuffer();

	VertexBuffer(const VertexBuffer &other);

	~VertexBuffer();

	VertexBuffer &operator=(const VertexBuffer &other);

	/** Change buffer size. Will allocate memory, free previous */
	void setSize(uint32 vertCount, uint32 vertSize);

	/** Set vertex declaration for this buffer */
	void setVertexDecl(const VertexDecl &decl);

	/** Access buffer data */
	GLvoid *getData();

	/** Access buffer data */
	const GLvoid *getData() const;

	/** Access vertex declaration */
	const VertexDecl &getVertexDecl() const;

	/** Get vertex count */
	uint32 getCount() const;

	/** Get vertex element size in bytes */
	uint32 getSize() const;

	/** Initialise internal buffer object for GL handling. */
	void initGL(GLuint hint = GL_STATIC_DRAW);

	/** Update existing GL buffer object. Try not to call while rendering. */
	void updateGL();

	/** Clear (destroy) GL resources associated with the buffer. */
	void destroyGL();

	GLuint getVBO();

private:
	VertexDecl _decl; ///< Vertex declaration
	uint32 _count;    ///< Number of elements in buffer
	uint32 _size;     ///< Size of a buffer element in bytes (vertex attributes size sum)
	byte  *_data;     ///< Buffer data

	GLuint _vbo;      ///< Vertex Buffer Object.
	GLuint _hint;     ///< GL hint for static or dynamic data.
};

}

#endif // GRAPHICS_VERTEXBUFFER_H
