#ifndef _UTIL_H_
#define _UTIL_H_
#include "classes/glwindow.h"
#include <ctype.h>
#include "vertex.h"

/**
 * Desenha um cubo na origem com lado de tamanho 1
 */
void drawCube();

/**
 * Desenha os eixos x, y e z
 */
void drawAxis();

/**
 * Verifica se está em caixa alta
 * 
 * parâmetros
 *   state: estado das teclas de controle
 */
inline bool isUpper(int state)
{
	return ((state & LeftShift) > 0 || ((state & RightShift) > 0)) != ((state & CapsLock) > 0);
}

/**
 * Traduz um caractere dependendo das teclas de controle
 * 
 * parâmetros
 *   key: tecla pressionada
 */
inline int translateKey(int key, int state)
{
	if(isUpper(state))
		return toupper(key);
	return key;
}

// Verifica se um ponto está dentro do polígono
bool pt_in_poly(const Vertex& point, const float* v, int count);

#endif /* _UTIL_H_ */
